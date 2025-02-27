/*******************************************************************************
################################################################################
#   Copyright (c) [2017-2019] [Radisys]                                        #
#                                                                              #
#   Licensed under the Apache License, Version 2.0 (the "License");            #
#   you may not use this file except in compliance with the License.           #
#   You may obtain a copy of the License at                                    #
#                                                                              #
#       http://www.apache.org/licenses/LICENSE-2.0                             #
#                                                                              #
#   Unless required by applicable law or agreed to in writing, software        #
#   distributed under the License is distributed on an "AS IS" BASIS,          #
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   #
#   See the License for the specific language governing permissions and        #
#   limitations under the License.                                             #
################################################################################
*******************************************************************************/

/********************************************************************20**
  
        Name:    RLC - TMR module file
    
        Type:    C source file
  
        Desc:    Source code for timer functions such as, 

                 - rlcStartTmr
                 - rlcStopTmr
                 - rlcTmrExpiry
                 - rlcBndTmrExpiry  
                  
        File:    rlc_tmr.c
  
*********************************************************************21*/

/* header (.h) include files */
#include "common_def.h"
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "rlc_env.h"        /* RLC environment options */
#include "rlc_err.h"        /* Error defines */

/* extern (.x) include files */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */

#include "rlc_utils.h"            /* RLC defines */
#include "rlc_dl_ul_inf.h"
#include "rlc_dl.h"
#include "rlc_ul.h"
/** 
 * @file gp_tmr.c
 * @brief RLC Timer Module
*/

/**
 * @def RLC_TMR_CALCUATE_WAIT
 *
 *    This macro calculates and assigns wait time based on the value of the 
 *    timer and the timer resolution. Timer value of 0 signifies that the
 *    timer is not configured
 *
 * @param[out] _wait   Time for which to arm the timer changed to proper 
 *                     value according to the resolution
 * @param[in] _tmrVal   Value of the timer
 * @param[in] _timerRes   Resolution of the timer
 *
*/
#define RLC_TMR_CALCUATE_WAIT(_wait, _tmrVal, _timerRes)       \
{                                                             \
   (_wait) = ((_tmrVal) * SS_TICKS_SEC)/((_timerRes) * 1000); \
   if((0 != (_tmrVal)) && (0 == (_wait)))                     \
   {                                                          \
      (_wait) = 1;                                            \
   }                                                          \
}

/* private function declarations */
static Void rlcBndTmrExpiry(PTR cb);
void rlcThptTmrExpiry(PTR cb);

/**
 * @brief Handler to start timer
 *       
 * @param[in] gCb       Pointer to the RLC instance control block
 * @param[in] cb        Control block depending on the type of the timer event. 
 *                      It can be uplink/downlink rbCb or rgu sap control block
 * @param[in] tmrEvnt   Timer event to be started
 *
 * @return  Void
*/
void rlcStartTmr(RlcCb *gCb, PTR cb, int16_t tmrEvnt)
{
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   RlcL2MeasEvtCb *measEvtCb = NULLP;
#endif

   CmTmrArg arg;
   arg.wait = 0;

   /* kw002.201 Adjusting the wait time as per timeRes configured by layer manager */
   switch (tmrEvnt)
   {
      case EVENT_RLC_UMUL_REASSEMBLE_TMR:
      {
         RlcUmUl* umUl = &(((RlcUlRbCb *)cb)->m.umUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait, umUl->reAsmblTmrInt, gCb->genCfg.timeRes);

         arg.timers = &umUl->reAsmblTmr;
         arg.max = RLC_MAX_UM_TMR;
         break;
      }
      case EVENT_RLC_AMUL_REASSEMBLE_TMR:
      {
         RlcAmUl* amUl = &(((RlcUlRbCb *)cb)->m.amUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait, amUl->reAsmblTmrInt, gCb->genCfg.timeRes);         

         arg.timers = &amUl->reAsmblTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      }
      case EVENT_RLC_AMUL_STA_PROH_TMR:
      {
         RlcAmUl* amUl = &(((RlcUlRbCb *)cb)->m.amUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait,
                              amUl->staProhTmrInt,
                              gCb->genCfg.timeRes);                  

         arg.timers = &amUl->staProhTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      } 
      case EVENT_RLC_AMDL_POLL_RETX_TMR:
      {
         RlcAmDl* amDl = &(((RlcDlRbCb *)cb)->m.amDl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait, 
                              amDl->pollRetxTmrInt, 
                              gCb->genCfg.timeRes);                  

         arg.timers = &amDl->pollRetxTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      } 
      case EVENT_RLC_WAIT_BNDCFM:
      {
         RlcRguSapCb* rguSap = (RlcRguSapCb *)cb;
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait, rguSap->bndTmrInt, gCb->genCfg.timeRes);                  

         arg.timers = &rguSap->bndTmr;
         arg.max = RLC_MAX_RGUSAP_TMR;
         break;
      }
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
      case EVENT_RLC_L2_TMR:
      {
         measEvtCb = (RlcL2MeasEvtCb *)cb;
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         RLC_TMR_CALCUATE_WAIT(arg.wait, 
                              measEvtCb->l2TmrCfg.val, 
                              gCb->genCfg.timeRes);                  

         arg.timers = &measEvtCb->l2Tmr;
         arg.max = RLC_L2_MAX_TIMERS;
         break;
      }
#endif
      case EVENT_RLC_THROUGHPUT_TMR:
      {
         RlcThpt *thptCb = (RlcThpt *)cb;
         RLC_TMR_CALCUATE_WAIT(arg.wait, ODU_THROUGHPUT_PRINT_TIME_INTERVAL, gCb->genCfg.timeRes);
         arg.timers = &thptCb->thptTmr;
         arg.max = RLC_MAX_THPT_TMR; 
         break;
      }
      default:
      {
         DU_LOG("\nERROR  -->  RLC : rlcStartTmr: Invalid tmr Evnt [%d]", tmrEvnt);
      }
   } 

   if(arg.wait != 0)
   {
      arg.tqCp   = &gCb->rlcTqCp;
      arg.tq     = gCb->rlcTq;
      arg.cb     = cb;
      arg.evnt   = tmrEvnt;
      arg.tNum   = 0;

      cmPlcCbTq(&arg);
   }

   return;
}

/**
 * @brief Handler to stop a timer
 *       
 * @param[in] gCb       Pointer to the RLC instance control block
 * @param[in] cb        Control block depending on the type of the timer event. 
 *                      It can be uplink/downlink rbCb or rgu sap control block
 * @param[in] tmrType   Timer event to be started
 *
 * @return  Void
*/
void rlcStopTmr(RlcCb *gCb, PTR cb, uint8_t tmrType)
{
   CmTmrArg   arg;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   RlcL2MeasEvtCb *measEvtCb = NULLP;
#endif

   arg.timers = NULLP;

   switch (tmrType)
   {
      case EVENT_RLC_UMUL_REASSEMBLE_TMR:
      {
         arg.timers  = &((RlcUlRbCb *)cb)->m.umUl.reAsmblTmr;
         arg.max = RLC_MAX_UM_TMR;
         break;
      }
      case EVENT_RLC_AMUL_REASSEMBLE_TMR:
      {
         arg.timers = &((RlcUlRbCb *)cb)->m.amUl.reAsmblTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      }
      case EVENT_RLC_AMUL_STA_PROH_TMR:
      {
         arg.timers = &((RlcUlRbCb *)cb)->m.amUl.staProhTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      } 
      case EVENT_RLC_AMDL_POLL_RETX_TMR:
      {
         arg.timers = &((RlcDlRbCb *)cb)->m.amDl.pollRetxTmr;
         arg.max = RLC_MAX_AM_TMR;
         break;
      } 
      case EVENT_RLC_WAIT_BNDCFM:
      {
         arg.timers = &((RlcRguSapCb *)cb)->bndTmr;
         arg.max = RLC_MAX_RGUSAP_TMR;
         break;
      }
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
      case EVENT_RLC_L2_TMR:
      {
         measEvtCb = (RlcL2MeasEvtCb *)cb;
         arg.timers   = &measEvtCb->l2Tmr;
         arg.max  = RLC_L2_MAX_TIMERS;
         break;
      }
#endif
      case EVENT_RLC_THROUGHPUT_TMR:
      {
         arg.timers   = &((RlcThpt *)cb)->thptTmr;
         arg.max  = RLC_MAX_THPT_TMR;
      }
      default:
      {
         DU_LOG("\nERROR  -->  RLC : rlcStopTmr: Invalid tmr Evnt[%d]", tmrType);
      }
   } 
   if (tmrType != TMR0)
   {
      arg.tqCp   = &gCb->rlcTqCp;
      arg.tq     = gCb->rlcTq;
      arg.cb     = cb;
      arg.evnt   = tmrType;
      arg.wait   = 0;
      arg.tNum   = 0;
      cmRmvCbTq(&arg);
   }
   
   return;
}

/**
 * @brief Handler to invoke events on expiry of timer.
 *
 * @details
 *    This function is used to handle expiry of timer,it invokes relevant 
 *    functions.
 *       
 * @param[in] cb        Control block depending on the type of the timer event. 
 *                      It can be uplink/downlink rbCb or rgu sap control block
 * @param[in] tmrEvnt   Timer event to be started
 *
 * @return  Void
*/
Void rlcTmrExpiry(PTR cb,S16 tmrEvnt)
{
/* kw005.201 added support for L2 Measurement */

   switch (tmrEvnt)
   {
      case EVENT_RLC_UMUL_REASSEMBLE_TMR:
      {
         RlcUlRbCb *ulRbCb = (RlcUlRbCb *)cb;
         rlcUmmReAsmblTmrExp(RLC_GET_RLCCB(ulRbCb->inst), ulRbCb);

         break;
      }
      case EVENT_RLC_AMUL_REASSEMBLE_TMR:
      {
         RlcUlRbCb *ulRbCb = (RlcUlRbCb *)cb;
         rlcAmmReAsmblTmrExp(RLC_GET_RLCCB(ulRbCb->inst), ulRbCb);
         break;
      }
      case EVENT_RLC_AMUL_STA_PROH_TMR:
      {
         RlcUlRbCb *ulRbCb = (RlcUlRbCb *)cb;
         rlcAmmStaProTmrExp(RLC_GET_RLCCB(ulRbCb->inst), ulRbCb);

         break;
      }
      case EVENT_RLC_AMDL_POLL_RETX_TMR:
      {
         RlcDlRbCb *dlRbCb = (RlcDlRbCb *)cb;
         RlcCb *gCb = RLC_GET_RLCCB(dlRbCb->inst);
         
         rlcAmmPollRetxTmrExp(gCb, dlRbCb);

         gCb->genSts.protTimeOut++;
         break;
      }
      case EVENT_RLC_WAIT_BNDCFM:
      {
         rlcBndTmrExpiry(cb);
         break;
      }
      case EVENT_RLC_THROUGHPUT_TMR:
      {
         rlcThptTmrExpiry(cb);
         break;
      }
      default:
      {
         break;
      }
   }

   return;
}

/**
 * @brief Handler to check if the timer is running
 *       
 * @param[in] gCb       Pointer to the RLC instance control block
 * @param[in] cb        Control block depending on the type of the timer event. 
 *                      It can be uplink/downlink rbCb or rgu sap control block
 * @param[in] tmrEvnt   Timer event to be started
 *
 * @return  Bool indicating whether the timer is running or not
 *      -# ROK 
 *      -# RFAILED 
*/
bool rlcChkTmr(RlcCb *gCb, PTR cb, int16_t tmrEvnt)
{
   switch (tmrEvnt)
   {
      case EVENT_RLC_UMUL_REASSEMBLE_TMR:
      {
         return (((RlcUlRbCb *)cb)->m.umUl.reAsmblTmr.tmrEvnt == 
                  EVENT_RLC_UMUL_REASSEMBLE_TMR);
      }
      case EVENT_RLC_AMUL_REASSEMBLE_TMR:
      {
         return (((RlcUlRbCb *)cb)->m.amUl.reAsmblTmr.tmrEvnt == 
                  EVENT_RLC_AMUL_REASSEMBLE_TMR);
      }
      case EVENT_RLC_AMUL_STA_PROH_TMR:
      {
         return (((RlcUlRbCb *)cb)->m.amUl.staProhTmr.tmrEvnt == 
                  EVENT_RLC_AMUL_STA_PROH_TMR);
      } 
      case EVENT_RLC_AMDL_POLL_RETX_TMR:
      {
         return (((RlcDlRbCb *)cb)->m.amDl.pollRetxTmr.tmrEvnt == 
                  EVENT_RLC_AMDL_POLL_RETX_TMR);
      } 
      case EVENT_RLC_WAIT_BNDCFM:
      {
         return (((RlcRguSapCb *)cb)->bndTmr.tmrEvnt == EVENT_RLC_WAIT_BNDCFM);
      }
      case EVENT_RLC_THROUGHPUT_TMR:
      {
         return (((RlcThpt *)cb)->thptTmr.tmrEvnt == EVENT_RLC_THROUGHPUT_TMR);
      }
      default:
      {
         DU_LOG("\nERROR  -->  RLC : rlcChkTmr: Invalid tmr Evnt [%d]", tmrEvnt);
      }
   } 

   return FALSE;
}

/**
 * @brief Handler to do processing on expiry of the bind timer
 *
 * @details
 *    This function processes the RLC bind timer expiry. If the number of 
 *    retries is less than the maximum retry counter, bind request is sent 
 *    again, else an alarm is raised to the layer manager.
 *       
 * @param[in] cb  Pointer to the Rgu sap
 *
 * @return  Void
*/
static Void rlcBndTmrExpiry(PTR cb)
{
   RlcRguSapCb *rguSapCb; 

   rguSapCb = (RlcRguSapCb *) cb;

   if (rguSapCb->state == RLC_SAP_BINDING)
   {
      if (rguSapCb->retryCnt < RLC_MAX_SAP_BND_RETRY)
      {
         /* start timer to wait for bind confirm */
         rlcStartTmr(RLC_GET_RLCCB(rguSapCb->pst.srcInst),
                    (PTR)rguSapCb, 
                    EVENT_RLC_WAIT_BNDCFM);
         
         /* Send bind request */
         rguSapCb->retryCnt++;
         RlcLiRguBndReq (&rguSapCb->pst, rguSapCb->suId, rguSapCb->spId);
      }
      else
      {
         rguSapCb->retryCnt = 0;
         rguSapCb->state = RLC_SAP_CFG;

         /* Send alarm to the layer manager */
#ifdef LTE_L2_MEAS
         rlcLmmSendAlarm(RLC_GET_RLCCB(rguSapCb->pst.srcInst),
                        LCM_CATEGORY_INTERFACE, 
                        LCM_EVENT_BND_FAIL,
                        LCM_CAUSE_TMR_EXPIRED, 
                        0, 
                        0, 
                        0);
#else
         rlcLmmSendAlarm(RLC_GET_RLCCB(rguSapCb->pst.srcInst),
                        LCM_CATEGORY_INTERFACE, 
                        LCM_EVENT_BND_FAIL,
                        LCM_CAUSE_TMR_EXPIRED, 
                        0, /* suId */
                        0 /* ueId */);
#endif
      }
   }

   return;
}

/**
 * @brief Handler to do processing on expiry of the throughput timer
 *
 * @details
 *    This function processes the RLC throughput timer expiry.
 *
 * @param[in] cb  Pointer to the RLC throughput struct
 *
 * @return  Void
 */
void rlcThptTmrExpiry(PTR cb)
{
   uint16_t  ueIdx;
   long double tpt;
   RlcThpt *rlcThptCb = (RlcThpt*)cb; 

   /* Print throughput */
   DU_LOG("\n===================== DL Throughput ==============================");
   DU_LOG("\nNumber of UEs : %d", rlcThptCb->numActvUe);
   for(ueIdx = 0; ueIdx < rlcThptCb->numActvUe; ueIdx++)
   {
      /* Spec 28.552, section 5.1.1.3 : 
       * Throughput in kilobits/sec = (dataVol in kiloBits * 1000)/time in milligseconds
       * 
       * Since our dataVol is in bytes, multiplying 0.008 to covert into kilobits i.e. 
       * Throughput[kbits/sec] = (dataVol * 0.008 * 1000)/time in ms
       */
      tpt = (double)(rlcThptCb->thptPerUe[ueIdx].dataVol * 8)/(double)ODU_THROUGHPUT_PRINT_TIME_INTERVAL;
      
      DU_LOG("\nUE Id : %d   DL Tpt : %.2Lf", rlcThptCb->thptPerUe[ueIdx].ueIdx, tpt);
      rlcThptCb->thptPerUe[ueIdx].dataVol = 0;
   }
   DU_LOG("\n==================================================================");

   /* Restart timer */
   rlcStartTmr(RLC_GET_RLCCB(rlcThptCb->inst), (PTR)rlcThptCb, EVENT_RLC_THROUGHPUT_TMR);

   return;
}

  
/********************************************************************30**
  
         End of file
**********************************************************************/
