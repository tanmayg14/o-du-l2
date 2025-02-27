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
/* This file contains UE management handling functionality for DU APP */
#include "common_def.h"
#include "lrg.h"
#include "lrg.x"
#include "ckw.h"
#include "ckw.x"
#include "kwu.h"
#include "kwu.x"
#include "lkw.h"
#include "lkw.x"
#include "legtp.h"
#include "du_app_mac_inf.h"
#include "du_app_rlc_inf.h"
#include "du_cfg.h"
#include "du_utils.h"
#include "du_mgr.h"
#include "du_f1ap_msg_hdl.h"
#include "du_ue_mgr.h"

DuMacDlCcchInd packMacDlCcchIndOpts[] =
{
   packMacDlCcchInd,           /* Loose coupling */
   MacProcDlCcchInd,           /* TIght coupling */
   packMacDlCcchInd            /* Light weight-loose coupling */
};

DuMacUeCreateReq packMacUeCreateReqOpts[] =
{
   packDuMacUeCreateReq,       /* Loose coupling */
   MacProcUeCreateReq,         /* TIght coupling */
   packDuMacUeCreateReq        /* Light weight-loose coupling */
};

DuRlcUeCreateReq packRlcUeCreateReqOpts[] =
{
   packDuRlcUeCreateReq,       /* Loose coupling */
   RlcProcUeCreateReq,         /* TIght coupling */
   packDuRlcUeCreateReq        /* Light weight-loose coupling */
};

DuDlRrcMsgToRlcFunc duSendDlRrcMsgToRlcOpts[] =
{
   packDlRrcMsgToRlc,          /* Loose coupling */ 
   RlcProcDlRrcMsgTransfer,    /* Tight coupling */
   packDlRrcMsgToRlc           /* Light weight-loose coupling */
};

DuRlcUeReconfigReq packRlcUeReconfigReqOpts[] =
{
   packDuRlcUeReconfigReq,     /* Loose coupling */
   RlcProcUeReconfigReq,       /* TIght coupling */
   packDuRlcUeReconfigReq      /* Light weight-loose coupling */
};

DuMacUeReconfigReq packMacUeReconfigReqOpts[] =
{
   packDuMacUeReconfigReq,     /* Loose coupling */
   MacProcUeReconfigReq,       /* TIght coupling */
   packDuMacUeReconfigReq      /* Light weight-loose coupling */
};

DuRlcDlUserDataToRlcFunc duSendRlcDlUserDataToRlcOpts[] =
{
   packRlcDlUserDataToRlc,        /* Loose coupling */ 
   RlcProcDlUserDataTransfer,  /* Tight coupling */
   packRlcDlUserDataToRlc         /* Light weight-loose coupling */
};

DuMacUeDeleteReq packMacUeDeleteReqOpts[] =
{
   packDuMacUeDeleteReq,       /* Loose coupling */
   MacProcUeDeleteReq,         /* TIght coupling */
   packDuMacUeDeleteReq        /* Light weight-loose coupling */
};

DuRlcUeDeleteReq packRlcUeDeleteReqOpts[] =
{
   packDuRlcUeDeleteReq,       /* Loose coupling */
   RlcProcUeDeleteReq,         /* TIght coupling */
   packDuRlcUeDeleteReq        /* Light weight-loose coupling */
};

DuMacCellDeleteReq packMacCellDeleteReqOpts[] =
{
   packDuMacCellDeleteReq,       /* Loose coupling */
   MacProcCellDeleteReq,         /* TIght coupling */
   packDuMacCellDeleteReq        /* Light weight-loose coupling */
};

/*******************************************************************
 *
 * @brief Function to fillDlUserDataInfo
 *
 * @details
 *
 *    Function : fillDlUserDataInfo
 *
 *    Functionality:
 *      Function to fillDlUserDataInfo
 *
 * @params[in] teId,
 *             dlDataMsgInfo
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t fillDlUserDataInfo(uint32_t teId, RlcDlUserDataInfo *dlDataMsgInfo)
{
   uint8_t drbIdx;

   for(drbIdx = 0; drbIdx < duCb.numDrb; drbIdx++)
   {
      if(duCb.upTnlCfg[drbIdx] && (duCb.upTnlCfg[drbIdx]->tnlCfg1 != NULLP))
      {
        if(duCb.upTnlCfg[drbIdx]->tnlCfg1->teId == teId)
	{
	   dlDataMsgInfo->cellId = duCb.upTnlCfg[drbIdx]->cellId;
	   dlDataMsgInfo->ueIdx = duCb.upTnlCfg[drbIdx]->ueIdx;
           dlDataMsgInfo->rbId = duCb.upTnlCfg[drbIdx]->drbId;
	   return ROK;
	}
      }
   }
   return RFAILED;
}

 /*******************************************************************
 *
 * @brief Build and Send DL Data Message transfer to RLC
 *
 * @details
 *
 *    Function : duBuildAndSendDlUserDataToRlc
 *
 *    Functionality:
 *      Build and Send DL Data Message transfer to RLC
 *
 * @params[in] Cell ID
 *             UE Index
 *             Logical Channgel ID
 *             RRC Message
 *             RRC Message Length
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duBuildAndSendDlUserDataToRlc(uint16_t msgLen, EgtpMsg *egtpMsg)
{
   uint8_t ret = RFAILED;
   Pst     pst;
   RlcDlUserDataInfo *dlDataMsgInfo = NULLP;

   DU_ALLOC_SHRABL_BUF(dlDataMsgInfo, sizeof(RlcDlUserDataInfo));
   if(!dlDataMsgInfo)
   {
      DU_LOG("\nERROR  -->  DU_APP : Memory allocation failed for dlDataMsgInfo in duHdlEgtpDlData()");
      return RFAILED;
   }
   memset(dlDataMsgInfo, 0, sizeof(RlcDlUserDataInfo));
   if(ODU_GET_MSG_BUF(DU_APP_MEM_REGION, DU_POOL, &dlDataMsgInfo->dlMsg) != ROK)
   {
      DU_LOG("\nERROR  -->  DU_APP : Memory allocation failed for dlMsg in duHdlEgtpDlData()");
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlDataMsgInfo, sizeof(RlcDlUserDataInfo));
      return RFAILED;
   }
   dlDataMsgInfo->dlMsg = egtpMsg->msg;
   dlDataMsgInfo->msgLen = msgLen;

   /* Filling DL DATA Msg Info */
   if(fillDlUserDataInfo(egtpMsg->msgHdr.teId, dlDataMsgInfo) == ROK)
   {
      /* Filling post structure and sending msg */ 
      FILL_PST_DUAPP_TO_RLC(pst, RLC_DL_INST, EVENT_DL_USER_DATA_TRANS_TO_RLC);
      DU_LOG("\nDEBUG  -->  DU_APP : Sending User Data Msg to RLC \n");
      ret = (*duSendRlcDlUserDataToRlcOpts[pst.selector])(&pst, dlDataMsgInfo);
   }
   if(ret != ROK)
   {
      DU_LOG("\nERROR  -->  DU_APP : Failed to send User Data to RLC in duHdlEgtpDlData()");
      ODU_PUT_MSG_BUF(dlDataMsgInfo->dlMsg);
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlDataMsgInfo, sizeof(RlcDlUserDataInfo));
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Handles EGTP data from CU 
 *
 * @details
 *
 *    Function : duHdlEgtpData
 *
 *    Functionality: 
 *      Processes EGTP header and sends data to RLC
 *
 * @params[in]  Pointer to EGTP Message 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t duHdlEgtpDlData(EgtpMsg  *egtpMsg)
{
   uint16_t msgLen = 0;
   DU_LOG("\nDEBUG  --> DU_APP : Processing DL data in duHdlEgtpDlData()");
   
   if(!egtpMsg->msg)
   {
      DU_LOG("\nERROR  -->  DU_APP : Recevied Dl Data is NULLP in duHdlEgtpDlData()");
      return RFAILED;
   }
   ODU_GET_MSG_LEN(egtpMsg->msg, (MsgLen *)&msgLen);
   if(duBuildAndSendDlUserDataToRlc(msgLen, egtpMsg) != ROK)
   {
      DU_LOG("\nERROR  -->  DU_APP : Failed to build DL USer Data in duHdlEgtpDlData()");
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, egtpMsg->msg, msgLen);
      return RFAILED;
   }
   return ROK;
}

/******************************************************************
 *
 * @brief Builds and Sends DL CCCH Ind to MAC
 *
 * @details
 *
 *    Function : duBuildAndSendDlCcchInd 
 *
 *    Functionality: Builds and sends DL CCCH Ind Msg to MAC
 *
 * @params[in] dlCcchMsg - uint8_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t duBuildAndSendDlCcchInd(uint16_t *cellId, uint16_t *crnti, \
      DlCcchMsgType msgType, uint16_t dlCcchMsgSize, uint8_t *dlCcchMsg)
{
   uint8_t  ret                  = ROK;
   uint16_t idx2;
   DlCcchIndInfo *dlCcchIndInfo = NULLP;
   Pst pst;

   DU_LOG("\nDEBUG   -->  DU APP : Building and Sending DL CCCH Ind to MAC");

   DU_ALLOC_SHRABL_BUF(dlCcchIndInfo, sizeof(DlCcchIndInfo));

   if(!dlCcchIndInfo)
   {
      DU_LOG("\nERROR  -->  DU APP : Memory alloc failed while building DL CCCH Ind");
      return RFAILED;
   }

   dlCcchIndInfo->cellId = *cellId;
   dlCcchIndInfo->crnti = *crnti;
   dlCcchIndInfo->msgType = msgType;
   dlCcchIndInfo->dlCcchMsgLen = dlCcchMsgSize;

   DU_ALLOC_SHRABL_BUF(dlCcchIndInfo->dlCcchMsg, dlCcchIndInfo->dlCcchMsgLen);
   if(!dlCcchIndInfo->dlCcchMsg)
   {
      DU_LOG("\nERROR  -->  DU APP : Memory alloc failed while building DL CCCH Ind");
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlCcchIndInfo, sizeof(DlCcchIndInfo));
      return RFAILED;
   }
   for(idx2 = 0; idx2 < dlCcchIndInfo->dlCcchMsgLen; idx2++)
   {
      dlCcchIndInfo->dlCcchMsg[idx2] = dlCcchMsg[idx2];
   }
   DU_FREE(dlCcchMsg, dlCcchMsgSize);

   /* Fill Pst */
   FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_DL_CCCH_IND);
   ret = (*packMacDlCcchIndOpts[pst.selector])(&pst, dlCcchIndInfo);
   if(ret != ROK)
   {
      DU_LOG("\nERROR  -->  DU_APP : Failure in sending DL CCCH to MAC");
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlCcchIndInfo->dlCcchMsg,\
	    dlCcchIndInfo->dlCcchMsgLen);
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlCcchIndInfo, \
	    sizeof(DlCcchIndInfo));
      ret = RFAILED; 
   }

   return ret;

}

/*******************************************************************
 *
 * @brief Build and Send DL RRC Message transfer to RLC
 *
 * @details
 *
 *    Function : duBuildAndSendDlRrcMsgToRlc
 *
 *    Functionality:
 *      Build and Send DL RRC Message transfer to RLC
 *
 * @params[in] Cell ID
 *             UE Index
 *             Logical Channgel ID
 *             RRC Message
 *             RRC Message Length
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t duBuildAndSendDlRrcMsgToRlc(uint16_t cellId, RlcUeCfg ueCfg, F1DlRrcMsg *f1DlRrcMsg)
{
   Pst     pst;
   uint8_t ret;
   uint8_t lcIdx;
   RlcDlRrcMsgInfo  *dlRrcMsgInfo = NULLP;

   if(!f1DlRrcMsg)
   {
      DU_LOG("\nERROR  -->  DU APP : Received Dl RRC Msg is NULL at duBuildAndSendDlRrcMsgToRlc()");
      return RFAILED;
   }

   DU_ALLOC_SHRABL_BUF(dlRrcMsgInfo, sizeof(RlcDlRrcMsgInfo));
   if(!dlRrcMsgInfo)
   {
      DU_LOG("\nERROR  -->  DU APP : Memory allocation failed for dlRrcMsgInfo in \
         duBuildAndSendDlRrcMsgToRlc");
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, f1DlRrcMsg->rrcMsgPdu, f1DlRrcMsg->rrcMsgSize);
      return RFAILED;
   }
   
   /* Filling up the RRC msg info */
   dlRrcMsgInfo->cellId = cellId;
   dlRrcMsgInfo->ueIdx = ueCfg.ueIdx;
   for(lcIdx = 0; lcIdx <= MAX_NUM_LC; lcIdx++)
   {
      if(ueCfg.rlcLcCfg[lcIdx].lcId == f1DlRrcMsg->srbId)
      {
         dlRrcMsgInfo->rbType = ueCfg.rlcLcCfg[lcIdx].rbType;
         dlRrcMsgInfo->rbId   = ueCfg.rlcLcCfg[lcIdx].rbId;
	 dlRrcMsgInfo->lcType = ueCfg.rlcLcCfg[lcIdx].lcType;
         dlRrcMsgInfo->lcId   = ueCfg.rlcLcCfg[lcIdx].lcId;
	 break;
      }
   }
   dlRrcMsgInfo->execDup = f1DlRrcMsg->execDup;
   dlRrcMsgInfo->deliveryStaRpt = f1DlRrcMsg->deliveryStatRpt;
   dlRrcMsgInfo->msgLen = f1DlRrcMsg->rrcMsgSize;
   dlRrcMsgInfo->rrcMsg = f1DlRrcMsg->rrcMsgPdu;

   /* Filling post structure and sending msg */ 
   FILL_PST_DUAPP_TO_RLC(pst, RLC_DL_INST, EVENT_DL_RRC_MSG_TRANS_TO_RLC);
   DU_LOG("\nDEBUG   -->  DU_APP: Sending Dl RRC Msg to RLC \n");
   ret = (*duSendDlRrcMsgToRlcOpts[pst.selector])(&pst, dlRrcMsgInfo);
   if(ret != ROK)
   {
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, f1DlRrcMsg->rrcMsgPdu, f1DlRrcMsg->rrcMsgSize);
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlRrcMsgInfo, sizeof(RlcDlRrcMsgInfo));
      return RFAILED;
   }

   return ROK;
} 



/******************************************************************
 *
 * @brief Process DL RRC Msg recevied from F1AP
 *
 * @details
 *
 *    Function : duProcDlRrcMsg
 *
 *    Functionality: Process DL RRC Msg recevied from F1AP
 *
 * @params[in] dlCcchMsg - uint8_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duProcDlRrcMsg(F1DlRrcMsg *dlRrcMsg)
{
   uint8_t ueIdx, ret;
   uint16_t crnti, cellId, cellIdx;
   bool ueCcchCtxtFound = false;
   bool ueFound = false;

   ret = ROK;

   if(dlRrcMsg->srbId == SRB0_LCID) //RRC connection setup
   {
      for(ueIdx=0; ueIdx<duCb.numUe; ueIdx++)
      {
         if(dlRrcMsg->gnbDuUeF1apId == duCb.ueCcchCtxt[ueIdx].gnbDuUeF1apId)
         {
	    ueCcchCtxtFound = true;
            crnti  = duCb.ueCcchCtxt[ueIdx].crnti;
            cellId = duCb.ueCcchCtxt[ueIdx].cellId;
            break;
         }
      }
   }
   if(ueCcchCtxtFound)
   {
      ret = duBuildAndSendDlCcchInd(&cellId, &crnti, RRC_SETUP, dlRrcMsg->rrcMsgSize, dlRrcMsg->rrcMsgPdu);
      if(ret == RFAILED)
      {
	 DU_LOG("\nERROR  -->  DU APP : Failed to build DlCcch Ind at procDlRrcMsgTrans()");
      }
      else
      {
	 if(duCb.actvCellLst[cellId-1]->numActvUes < MAX_NUM_UE)
	 {
	    ret = duCreateUeCb(&duCb.ueCcchCtxt[ueIdx], dlRrcMsg->gnbCuUeF1apId);
	    if(ret == RFAILED)
	    {
	       DU_LOG("\nERROR  -->  DU APP : Failed to createUeCb for cellId [%d] at procDlRrcMsgTrans()", \
		     duCb.ueCcchCtxt[ueIdx].cellId);
	    }
	 }
	 else
	 {
	    DU_LOG("\nERROR   -->  DU_APP: Max Active UEs has reached at procDlRrcMsgTrans()");
	    ret = RFAILED;
	 }
      }
   }
   else
   {
      for(cellIdx = 0; cellIdx < MAX_NUM_CELL; cellIdx++)
      {
	 for(ueIdx = 0 ; ueIdx < MAX_NUM_UE; ueIdx++)
	 {
	    if((dlRrcMsg->gnbCuUeF1apId == duCb.actvCellLst[cellIdx]->ueCb[ueIdx].gnbCuUeF1apId)
		  && (dlRrcMsg->gnbDuUeF1apId == duCb.actvCellLst[cellIdx]->ueCb[ueIdx].gnbDuUeF1apId))
	    {
	       ueFound = true;
	       ret = duBuildAndSendDlRrcMsgToRlc(duCb.actvCellLst[cellIdx]->cellId, \
		     duCb.actvCellLst[cellIdx]->ueCb[ueIdx].rlcUeCfg, dlRrcMsg);
	       break; 
	    }
	 }
	 if(ueFound)
	    break;
      }
      if(!ueFound)
	 ret = RFAILED;
   }
   return ret;
}

/******************************************************************
 *
 * @brief Generates GNB DU Ue F1AP ID
 *
 * @details
 *
 *    Function : genGnbDuUeF1apId
 *
 *    Functionality: Generates GNB DU Ue F1AP ID
 *
 * @params[in] void
 * @return gnbDuF1apId
 *
 * ****************************************************************/
uint32_t genGnbDuUeF1apId()
{
   static uint32_t gnbDuUeF1apId = 0;

   return ++gnbDuUeF1apId;
}

/******************************************************************
 *
 * @brief Processes UL CCCH Ind recvd from MAC
 *
 * @details
 *
 *    Function : duProcUlCcchInd
 *
 *    Functionality: Processes UL CCCH Ind recvd from MAC
 *
 * @params[in] UlCcchIndInfo *ulCcchIndInfo
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t duProcUlCcchInd(UlCcchIndInfo *ulCcchIndInfo)
{

   uint8_t ret = ROK;
   uint32_t gnbDuUeF1apId = 0;

   gnbDuUeF1apId = genGnbDuUeF1apId();

   /* Store Ue mapping */
   duCb.ueCcchCtxt[duCb.numUe].gnbDuUeF1apId = gnbDuUeF1apId;
   duCb.ueCcchCtxt[duCb.numUe].crnti         = ulCcchIndInfo->crnti;
   duCb.ueCcchCtxt[duCb.numUe].cellId        = ulCcchIndInfo->cellId;

   duCb.numUe++;

   ret = (BuildAndSendInitialRrcMsgTransfer(gnbDuUeF1apId, ulCcchIndInfo->crnti, ulCcchIndInfo->ulCcchMsgLen,
	    ulCcchIndInfo->ulCcchMsg));
   if(ret != ROK)
   {
      DU_LOG("\nERROR  -->  DU_APP : BuildAndSendInitialRrcMsgTransfer failed");
   }

   DU_FREE_SHRABL_BUF(MAC_MEM_REGION, MAC_POOL, ulCcchIndInfo->ulCcchMsg, ulCcchIndInfo->ulCcchMsgLen);
   DU_FREE_SHRABL_BUF(MAC_MEM_REGION, MAC_POOL, ulCcchIndInfo, sizeof(UlCcchIndInfo));

   return ret;

}

/******************************************************************
 *
 * @brief Fills Default UL LC Cfg
 *
 * @details
 *
 *    Function : fillDefaultUlLcCfg
 *
 *    Functionality: Fills Default UL LC Cfg
 *
 * @params[in]  UlLcCfg *ulLcCfg 
 * @return void
 *****************************************************************/
void fillDefaultUlLcCfg(UlLcCfg *ulLcCfg)
{
   ulLcCfg->priority = LC_PRIORITY_1;
   ulLcCfg->lcGroup =  0;
   ulLcCfg->schReqId = 0;
   ulLcCfg->pbr = PBR_KBPS_INFINITY;
   ulLcCfg->bsd = BSD_MS_1000;
}

/******************************************************************
 *
 * @brief Fills Initial DL Bandwidth Part
 *
 * @details
 *
 *    Function : fillDefaultInitDlBwp
 *
 *    Functionality: Fills Initial DL Bandwidth Part
 *
 * @params[in]  InitialDlBwp *initDlBwp
 * @return void
 *
 *****************************************************************/
void fillDefaultInitDlBwp(InitialDlBwp *initDlBwp)
{
   uint8_t idx = 0;
   uint8_t freqDomainResource[FREQ_DOM_RSRC_SIZE] = {0};
   uint8_t coreset0EndPrb, coreset1StartPrb, coreset1NumPrb;


   if(initDlBwp)
   {
      /* Filling PDCCH Config */
      initDlBwp->pdcchPresent = TRUE;
      if(initDlBwp->pdcchPresent)
      {
	 initDlBwp->pdcchCfg.numCRsetToAddMod = PDCCH_CTRL_RSRC_SET_ONE_ID;
	 memset(initDlBwp->pdcchCfg.cRSetToAddModList, 0, MAX_NUM_CRSET);
	 if(initDlBwp->pdcchCfg.numCRsetToAddMod <= MAX_NUM_CRSET)
	 {
	    initDlBwp->pdcchCfg.cRSetToAddModList[idx].cRSetId = \
	       PDCCH_CTRL_RSRC_SET_ONE_ID;
	    memset(initDlBwp->pdcchCfg.cRSetToAddModList[idx].freqDomainRsrc, 0,\
	       FREQ_DOM_RSRC_SIZE); 
	    coreset0EndPrb = CORESET0_END_PRB;
	    coreset1StartPrb = coreset0EndPrb +6;
	    coreset1NumPrb = CORESET1_NUM_PRB;
	    /* calculate the PRBs */
	    freqDomRscAllocType0(((coreset1StartPrb)/6), (coreset1NumPrb/6), freqDomainResource);
	    memcpy(initDlBwp->pdcchCfg.cRSetToAddModList[idx].freqDomainRsrc, freqDomainResource,
	       FREQ_DOM_RSRC_SIZE);

	    initDlBwp->pdcchCfg.cRSetToAddModList[idx].duration = \
	       PDCCH_CTRL_RSRC_SET_ONE_DURATION;
	    initDlBwp->pdcchCfg.cRSetToAddModList[idx].cceRegMappingType = \
	       CCE_REG_MAPPINGTYPE_PR_NONINTERLEAVED;
	    initDlBwp->pdcchCfg.cRSetToAddModList[idx].precoderGranularity = \
	       ALL_CONTIGUOUS_RBS;
	    initDlBwp->pdcchCfg.cRSetToAddModList[idx].dmrsScramblingId = \
	       SCRAMBLING_ID;
	 }
	 initDlBwp->pdcchCfg.numCRsetToRel = 0;
	 /* Filling Serach Space */
	 initDlBwp->pdcchCfg.numSearchSpcToAddMod = PDCCH_CTRL_RSRC_SET_ONE_ID;
	 memset(initDlBwp->pdcchCfg.searchSpcToAddModList, 0, MAX_NUM_CRSET);
	 if(initDlBwp->pdcchCfg.numSearchSpcToAddMod <= MAX_NUM_CRSET)
	 {
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].searchSpaceId =\
	       PDCCH_SRCH_SPC_TWO_ID;
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].cRSetId = \
	       PDCCH_CTRL_RSRC_SET_ONE_ID;
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].\
	       mSlotPeriodicityAndOffset = SLOTPERIODICITYANDOFFSET_PR_SL1;
	    memset(initDlBwp->pdcchCfg.searchSpcToAddModList[idx].mSymbolsWithinSlot, 0,\
	       MONITORING_SYMB_WITHIN_SLOT_SIZE);
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].mSymbolsWithinSlot[idx] =\
	       PDCCH_SYMBOL_WITHIN_SLOT;
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].numCandidatesAggLevel1 =\
	       AGGREGATIONLEVEL_N8; 
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].numCandidatesAggLevel2 =\
	       AGGREGATIONLEVEL_N8; 
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].numCandidatesAggLevel4 =\
	       AGGREGATIONLEVEL_N4; 
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].numCandidatesAggLevel8 =\
	       AGGREGATIONLEVEL_N2; 
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].numCandidatesAggLevel16 =\
	       AGGREGATIONLEVEL_N1;
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].searchSpaceType = \
	       SEARCHSPACETYPE_PR_UE_SPECIFIC;
	    initDlBwp->pdcchCfg.searchSpcToAddModList[idx].ueSpecificDciFormat =\
	       PDCCH_SRCH_SPC_TWO_UE_SPEC_DCI_FORMAT;

	    initDlBwp->pdcchCfg.numSearchSpcToRel = 0;

	 }
      }
      /* Filling PDSCH Config */
      initDlBwp->pdschPresent = TRUE;
      if(initDlBwp->pdschPresent)
      {
	 initDlBwp->pdschCfg.dmrsDlCfgForPdschMapTypeA.addPos = ADDITIONALPOSITION_POS0;
	 initDlBwp->pdschCfg.resourceAllocType = RESOURCEALLOCATION_TYPE1;
	 initDlBwp->pdschCfg.numTimeDomRsrcAlloc = 1;
	 initDlBwp->pdschCfg.timeDomRsrcAllociList[idx].mappingType = \
	    MAPPING_TYPEA;
	 initDlBwp->pdschCfg.timeDomRsrcAllociList[idx].startSymbol = PDSCH_START_SYMBOL; 
	 initDlBwp->pdschCfg.timeDomRsrcAllociList[idx].symbolLength = PDSCH_LENGTH_SYMBOL;
	 initDlBwp->pdschCfg.timeDomRsrcAllociList[idx].startSymbolAndLength = \
	    calcSliv(PDSCH_START_SYMBOL, PDSCH_LENGTH_SYMBOL);
	 initDlBwp->pdschCfg.rbgSize = RBG_SIZE_CONFIG1;
	 initDlBwp->pdschCfg.numCodeWordsSchByDci = CODEWORDS_SCHED_BY_DCI_N1;
	 initDlBwp->pdschCfg.bundlingType = TYPE_STATIC_BUNDLING;
	 initDlBwp->pdschCfg.bundlingInfo.StaticBundling.size = 0;
      }
   }

}

/******************************************************************
 *
 * @brief Fills Initial UL Bandwidth Part
 *
 * @details
 *
 *    Function : fillDefaultInitUlBwp
 *
 *    Functionality: Fills Initial UL Bandwidth Part
 *
 * @params[in]  InitialUlBwp *initUlBwp
 * @return void
 *
 *****************************************************************/
void fillDefaultInitUlBwp(InitialUlBwp *initUlBwp)
{
   uint8_t idx;
   if(initUlBwp)
   {
      initUlBwp->pucchPresent = FALSE;

      /*Filling PUSCH Config */
      initUlBwp->puschPresent = TRUE;
      if(initUlBwp->puschPresent)
      {
         initUlBwp->puschCfg.dataScramblingId = SCRAMBLING_ID;
	 initUlBwp->puschCfg.dmrsUlCfgForPuschMapTypeA.addPos = ADDITIONALPOSITION_POS0; 
	 initUlBwp->puschCfg.dmrsUlCfgForPuschMapTypeA.transPrecodDisabled. \
	    scramblingId0 = SCRAMBLING_ID; 
	 initUlBwp->puschCfg.resourceAllocType = RESOURCEALLOCATION_TYPE1;
	 initUlBwp->puschCfg.numTimeDomRsrcAlloc = 1;
	 idx = 0;
	 if(initUlBwp->puschCfg.numTimeDomRsrcAlloc <= MAX_NUM_UL_ALLOC)
	 {
	    initUlBwp->puschCfg.timeDomRsrcAllocList[idx].k2 = PUSCH_K2;
	    initUlBwp->puschCfg.timeDomRsrcAllocList[idx].mappingType =\
	       MAPPING_TYPEA;
	    initUlBwp->puschCfg.timeDomRsrcAllocList[idx].startSymbol = PUSCH_START_SYMBOL;
	    initUlBwp->puschCfg.timeDomRsrcAllocList[idx].symbolLength = PUSCH_LENGTH_SYMBOL;
	    initUlBwp->puschCfg.timeDomRsrcAllocList[idx].startSymbolAndLength =\
	       calcSliv(PUSCH_START_SYMBOL, PUSCH_LENGTH_SYMBOL);
	 }
	 initUlBwp->puschCfg.transformPrecoder = TRANSFORM_PRECODER_DISABLED;
      }
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory is NULL of InitalUlBwp");
   }

}
/******************************************************************
 *
 * @brief Fills SpCell Group Info
 *
 * @details
 *
 *    Function : fillDefaultSpCellGrpInfo
 *
 *    Functionality: Fills Sp Cell Group Info
 *
 * @params[in]  SpCellCfg *spCell
 * @return void
 *
 *****************************************************************/
void fillDefaultSpCellGrpInfo(SpCellCfg *spCell)
{
   if(spCell)
   {
      spCell->servCellIdx = SERV_CELL_IDX;
      /* Filling Initial Dl Bwp */
      fillDefaultInitDlBwp(&spCell->servCellCfg.initDlBwp);

      spCell->servCellCfg.numDlBwpToAdd    = 0; 
      spCell->servCellCfg.firstActvDlBwpId = ACTIVE_DL_BWP_ID;
      spCell->servCellCfg.defaultDlBwpId   = ACTIVE_DL_BWP_ID;
      spCell->servCellCfg.bwpInactivityTmr = NULLP;
      spCell->servCellCfg.pdschServCellCfg.maxMimoLayers = NULLP;
      spCell->servCellCfg.pdschServCellCfg.maxCodeBlkGrpPerTb = NULLP;
      spCell->servCellCfg.pdschServCellCfg.codeBlkGrpFlushInd = NULLP;
      spCell->servCellCfg.pdschServCellCfg.xOverhead = NULLP;
      spCell->servCellCfg.pdschServCellCfg.numHarqProcForPdsch =\
         NUM_HARQ_PROC_FOR_PDSCH_N_16;
      /* Filling Initial UL Bwp*/
      fillDefaultInitUlBwp(&spCell->servCellCfg.initUlBwp);
      spCell->servCellCfg.numUlBwpToAdd     = 0; 
      spCell->servCellCfg.firstActvUlBwpId  = ACTIVE_DL_BWP_ID; 
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory is NULL for SpCellGrp");
   }
}

/******************************************************************
 *
 * @brief Fills Physical Cell Group Info
 *
 * @details
 *
 *    Function : fillDefaultPhyCellGrpInfo
 *
 *    Functionality: Fills Physical Cell Group Info
 *
 * @params[in]  PhyCellGrpCfg *cellGrp
 * @return void
 *
 *****************************************************************/
void fillDefaultPhyCellGrpInfo(PhyCellGrpCfg *cellGrp)
{
   if(cellGrp)
   {
      cellGrp->pdschHarqAckCodebook = PDSCH_HARQ_ACK_CODEBOOK_DYNAMIC;
      cellGrp->pNrFr1 = P_NR_FR1;
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory is NULL for Physical Cell Group");
   }
}

/******************************************************************
 *
 * @brief Fills Mac Cell Group Info
 *
 * @details
 *
 *    Function : fillDefaultMacCellGrpInfo
 *
 *    Functionality: Fills Mac Cell Group Info
 *
 * @params[in]  MacCellGrpCfg *cellGrp
 * @return void
 *
 *****************************************************************/
void fillDefaultMacCellGrpInfo(MacCellGrpCfg *cellGrp)
{
   uint8_t idx;

   if(cellGrp)
   {
      /* Filling Scheduling Request Config */
      cellGrp->schReqCfg.addModListCount = 1;
      if(cellGrp->schReqCfg.addModListCount <= MAX_NUM_SR_CFG_PER_CELL_GRP)
      {
	 for(idx = 0; idx < cellGrp->schReqCfg.addModListCount; idx++)
	 {
	    cellGrp->schReqCfg.addModList[idx].schedReqId    = SCH_REQ_ID;
	    cellGrp->schReqCfg.addModList[idx].srProhibitTmr = SR_PROHIBIT_MS_32;
	    cellGrp->schReqCfg.addModList[idx].srTransMax    = SR_TRANS_MAX_N_16;
	 }
      }
      cellGrp->schReqCfg.relListCount = 0;

      /* Filling Tag config */
      cellGrp->tagCfg.addModListCount = 1;
      if(cellGrp->tagCfg.addModListCount <= MAC_NUM_TAGS)
      {
	 for(idx = 0; idx < cellGrp->tagCfg.addModListCount; idx++)
	 {
	    cellGrp->tagCfg.addModList[idx].tagId = TAG_ID;
	    cellGrp->tagCfg.addModList[idx].timeAlignTimer = TIME_ALIGNMENT_TIMER_INFINITY;
	 }
      }
      cellGrp->tagCfg.relListCount = 0;

      /* Filling BSR config */
      cellGrp->bsrTmrCfg.periodicTimer = BSR_PERIODIC_TIMER_SF_10;
      cellGrp->bsrTmrCfg.retxTimer = BSR_RETX_TIMER_SF_320;
      cellGrp->bsrTmrCfg.srDelayTimer = BSR_SR_DELAY_TMR_2560;

      /* Filling PHR config */
      cellGrp->phrCfgSetupPres = true;
      cellGrp->phrCfg.periodicTimer = PHR_PERIODIC_TIMER_INFINITY;
      cellGrp->phrCfg.prohibitTimer = PHR_PROHIBIT_TIMER_SF_0;
      cellGrp->phrCfg.txPowerFactor = PHR_TX_PWR_FACTOR_CHANGE_INFINITY;
      cellGrp->phrCfg.multiplePHR   = false;
      cellGrp->phrCfg.dummy         = false;
      cellGrp->phrCfg.phrType2OtherCell = false;
      cellGrp->phrCfg.phrOtherCG = PHR_MODE_OTHER_CG_REAL;  

   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory is NULL for Master Cell Group");
   }
}

/*******************************************************************
 *
 * @brief Fills default modulation info for a UE
 *
 * @details
 *
 *    Function : fillDefaultModulation
 *
 *    Functionality: Fills default modulation info for a UE
 *
 * @params[in] Pointer to MAC UE configuration
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
void fillDefaultModulation(MacUeCfg *ueCfg)
{
   ueCfg->dlModInfo.modOrder = MOD_ORDER_QPSK;
   ueCfg->dlModInfo.mcsIndex = SIB1_MCS;
   ueCfg->dlModInfo.mcsTable = MCS_TABLE_QAM64; /* Spec 38.214-Table 5.1.3.1-1 */

   ueCfg->ulModInfo.modOrder = MOD_ORDER_QPSK;
   ueCfg->ulModInfo.mcsIndex = SIB1_MCS;
   ueCfg->ulModInfo.mcsTable = MCS_TABLE_QAM64; /* Spec 38.214-Table 5.1.3.1-1 */
}

/******************************************************************
 *
 * @brief Function to fill Mac Lc Cfg for SRB1
 *
 * @details
 *
 *    Function : fillMacSrb1LcCfg
 *
 *    Functionality: Function to fill Mac Lc cfg for SRB1
 *
 * @params[in]  LcCfg *lcCfg, LcCfg *ueSetReqDb
 * @return void
 *****************************************************************/

void fillMacSrb1LcCfg(LcCfg *macLcCfg)
{
   macLcCfg->lcId   = SRB1_LCID;
   macLcCfg->configType = CONFIG_ADD;
   macLcCfg->drbQos = NULLP;
   macLcCfg->snssai = NULLP;
   macLcCfg->ulLcCfgPres = true;
   fillDefaultUlLcCfg(&macLcCfg->ulLcCfg);
}

/******************************************************************
 *
 * @brief Function to fill the Lc cfg from ueSetupReqDb
 *
 * @details
 *
 *    Function : fillMacLcCfgToAddMod
 *
 *    Functionality: Function to fill the Lc cfg from ueSetupReqDb
 *
 * @params[in]  LcCfg *lcCfg, LcCfg *ueSetReqDb
 * @return ROK/RFAILED
 *
 *****************************************************************/

uint8_t fillMacLcCfgToAddMod(LcCfg *lcCfg, LcCfg *ueSetReqDb)
{
   uint8_t ret = ROK; 
   lcCfg->lcId = ueSetReqDb->lcId;
   lcCfg->configType = ueSetReqDb->configType;
   /* Filling DRBQOS */
   if(ueSetReqDb->drbQos)
   {
      if(!lcCfg->drbQos)
      {
         DU_ALLOC_SHRABL_BUF(lcCfg->drbQos, sizeof(DrbQosInfo));
         if(!lcCfg->drbQos)
         {
            DU_LOG("\nERROR  -->  DU APP : Memory Alloc failed at drQos at fillMacLcCfgToAddMod()");
            return RFAILED;
         }
      }
      if(ret == ROK)
      {
         memcpy(lcCfg->drbQos, ueSetReqDb->drbQos, sizeof(DrbQosInfo));
      }
   }
   else
   {
      lcCfg->drbQos = NULLP;
   }

   if(ret == ROK)
   {
      if(ueSetReqDb->snssai)
      {
         if(!lcCfg->snssai)
         {
            DU_ALLOC_SHRABL_BUF(lcCfg->snssai, sizeof(Snssai));
            if(!lcCfg->snssai)
            {
               DU_LOG("\nERROR  -->  DU APP : Memory Alloc failed at snnsai at fillMacLcCfgToAddMod()");
               ret = RFAILED;
            }
         }
         if(ret == ROK)
         {
            /* Filling SNSSAI */
            memcpy(lcCfg->snssai, ueSetReqDb->snssai, sizeof(Snssai));
         }
	 else
	 {
            lcCfg->snssai = NULLP;
            if(lcCfg->drbQos)
            {
               DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, lcCfg->drbQos, sizeof(DrbQosInfo));
               lcCfg->drbQos = NULLP;
            }
	    return ret;
	 }
      }
      else
         lcCfg->snssai = NULLP;
   }
   lcCfg->ulLcCfgPres = ueSetReqDb->ulLcCfgPres;
   memcpy(&lcCfg->ulLcCfg, &ueSetReqDb->ulLcCfg, sizeof(UlLcCfg));
   memcpy(&lcCfg->dlLcCfg, &ueSetReqDb->dlLcCfg, sizeof(DlLcCfg));
   return ret;
}

/******************************************************************
 *
 * @brief Function to copy the Bit rate from ueSetupReqDb
 *
 * @details
 *
 *    Function : fillAmbr
 *
 *    Functionality: Function to copy bit Rate from ueSetupReqDb
 *
 * @params[in]  AmbrCfg **macAmbr, AmbrCfg  *ueDbAmbr
 * @return ROK/RFAILED
 *
 *****************************************************************/

uint8_t fillAmbr(AmbrCfg **macAmbr, AmbrCfg *ueDbAmbr)
{
   if(ueDbAmbr)
   {
      if(*macAmbr == NULLP)
      {
         DU_ALLOC_SHRABL_BUF(*macAmbr, sizeof(AmbrCfg));
         if(*macAmbr == NULLP)
         {
            DU_LOG("\nERROR  -->  DU APP : Memory Alloc Failed at fillAmbr()");
            return RFAILED;
         }
      }
      memset(*macAmbr, 0, sizeof(AmbrCfg));
      (*macAmbr)->ulBr = ueDbAmbr->ulBr;
   }
   else
   {
      *macAmbr = NULLP;
   }
   return ROK;
}

/******************************************************************
 *
 * @brief Builds and Send UE ReConfig Request to MAC
 *
 * @details
 *
 *    Function : sendUeReCfgReqToMac
 *
 *    Functionality: Builds and Send UE ReConfig Request to MAC
 *
 * @Params[in]  MacUeCfg pointer
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t sendUeReCfgReqToMac(MacUeCfg *macUeCfg)
{
   uint8_t ret = ROK;
   Pst pst;
   
   /* Fill Pst */
   FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_UE_RECONFIG_REQ);
   
   if(macUeCfg)
   {
      /* Processing one Ue at a time to MAC */
      DU_LOG("\nDEBUG   -->  DU_APP: Sending Ue Reconfig Request to MAC");
      ret = (*packMacUeReconfigReqOpts[pst.selector])(&pst, macUeCfg);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU APP : Failed to send Reconfig Request to MAC at sendUeReCfgReqToMac()");
	 DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, macUeCfg, sizeof(MacUeCfg));
      }
   }
   else
   {
      DU_LOG("\nERROR  -->  DU_APP: Received macUeCfg is NULLP at sendUeReCfgReqToMac()");
      ret = RFAILED;
   }
   return ret;
}

/******************************************************************
 *
 * @brief Function to return Drb LcId
 *
 * @details
 *
 *    Function : getDrbLcId
 *
 *    Functionality: Function to return Drb LcId
 *
 * Returns: lcId - SUCCESS
 *         RFAILED - FAILURE
 *****************************************************************/

uint8_t getDrbLcId(uint32_t *drbBitMap)
{
   uint8_t bitMask = 1, bitPos = 0;
   bitPos = MIN_DRB_LCID;

   while(bitPos <= MAX_DRB_LCID)
   {
      if((*drbBitMap & (bitMask << bitPos)) == 0)
      {
	 *drbBitMap = ((bitMask << bitPos)| *drbBitMap);
	 return bitPos;
      }
      else
      {
	 bitPos++;
      }
   }
   DU_LOG("\nERROR   -->  DU_APP: Max LC Reached in getDrbLcId()");
   return RFAILED;
}

/******************************************************************
 *
 * @brief Fills MacUeCfg structure
 *
 * @details
 *
 *    Function : fillMacUeCfg
 *
 *    Functionality: Fills MacUeCfg
 *
 * @params[in]  cellId, ueIdx, crnti, 
 *              DuUeCfg  pointer,
 *              MacUeCfg pointer
 * @return ROK/RFAILED
 *
 *****************************************************************/
uint8_t fillMacUeCfg(uint16_t cellId, uint8_t ueIdx, uint16_t crnti, \
   DuUeCfg *ueCfgDb, MacUeCfg *macUeCfg)
{
   uint8_t ret, dbIdx, lcIdx, cellIdx;
   bool lcIdFound = false;
   MacUeCfg *duMacDb = NULLP;

   ret =ROK;

   if(!ueCfgDb)
   {
      macUeCfg->cellId       = cellId;
      macUeCfg->ueIdx        = ueIdx;
      macUeCfg->crnti        = crnti;
      fillDefaultMacCellGrpInfo(&macUeCfg->macCellGrpCfg);
      fillDefaultPhyCellGrpInfo(&macUeCfg->phyCellGrpCfg);
      fillDefaultSpCellGrpInfo(&macUeCfg->spCellCfg);
      macUeCfg->ambrCfg = NULLP;
      fillMacSrb1LcCfg(&macUeCfg->lcCfgList[0]);
      fillDefaultModulation(macUeCfg);
      macUeCfg->numLcs++;
   }
   else
   {
      /* Fetching MacDb from DuUeCb */
      GET_CELL_IDX(cellId, cellIdx);
      duMacDb = &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].macUeCfg;
      duMacDb->macUeCfgState = UE_CFG_INPROGRESS;
      /* Fetching MaUeCfg List for ADD/MOD/DEL */
      macUeCfg->cellId       = cellId;
      macUeCfg->ueIdx        = ueIdx;
      macUeCfg->crnti        = crnti;
      ret = procUeReCfgCellInfo(macUeCfg, ueCfgDb->cellGrpCfg);
      if(ret == ROK)
      {
         if(macUeCfg->spCellCfgPres == true)
         {
            if(macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschPresent)
            {
               fillStartSymbolAndLen(macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschCfg.numTimeDomRsrcAlloc,\
                     &macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschCfg, NULL);
            }
            if(macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschPresent)
            {
               fillStartSymbolAndLen(macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschCfg.numTimeDomRsrcAlloc,\
                     NULL, &macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschCfg);
            }
         }
         ret = fillAmbr(&macUeCfg->ambrCfg, ueCfgDb->ambrCfg);
         duFillModulationDetails(macUeCfg, duMacDb, ueCfgDb->ueNrCapability);
      }

      /* Filling LC Context */
      for(dbIdx = 0; (dbIdx < ueCfgDb->numMacLcs && ret == ROK); dbIdx++)
      {
         if(!ueCfgDb->macLcCfg[dbIdx].ulLcCfgPres)
         {
            /* Filling default UL LC config in MAC if not present */
            ueCfgDb->macLcCfg[dbIdx].ulLcCfgPres = true;
            fillDefaultUlLcCfg(&ueCfgDb->macLcCfg[dbIdx].ulLcCfg);
         }
         for(lcIdx = 0; lcIdx < duMacDb->numLcs; lcIdx++)
         {
            if(ueCfgDb->macLcCfg[dbIdx].lcId == duMacDb->lcCfgList[lcIdx].lcId)
            {
               lcIdFound = true;
               if((ueCfgDb->macLcCfg[dbIdx].configType == CONFIG_UNKNOWN) ||
                     (ueCfgDb->macLcCfg[dbIdx].configType == CONFIG_MOD))
               {
                  ueCfgDb->macLcCfg[dbIdx].configType = CONFIG_MOD;
                  ret = fillMacLcCfgToAddMod(&macUeCfg->lcCfgList[dbIdx], &ueCfgDb->macLcCfg[dbIdx]);
               }
            }
            else
               lcIdFound = false;
         }
         if(!lcIdFound)
         {
            /* ADD/DEL CONFIG */
            ret = fillMacLcCfgToAddMod(&macUeCfg->lcCfgList[dbIdx], &ueCfgDb->macLcCfg[dbIdx]);
         }
         if(ret == ROK)
         {
            macUeCfg->numLcs++;
         }
         else
         {
            DU_LOG("\nERROR  -->  DU APP : Failed to add Lc at Idx %d in fillMacUeCfg()", dbIdx); 
            break;
         }
      }/*End of Outer FOR loop */
   }
   return ret;
}

/******************************************************************
 *
 * @brief Fills Rlc AM Information
 *
 * @details
 *
 *    Function : fillDefaultAmInfo
 *
 *    Functionality: Fills Rlc AM Information
 *
 * @params[in]  AmBearerCfg *amCfg
 * @return void
 *
 *****************************************************************/
void fillDefaultAmInfo(AmBearerCfg *amCfg)
{
   /* DL AM */
   amCfg->dlAmCfg.snLenDl     = AM_SIZE_12;
   amCfg->dlAmCfg.pollRetxTmr = T_POLL_RETRANSMIT_VAL;
   amCfg->dlAmCfg.pollPdu     = POLL_PDU_VAL;
   amCfg->dlAmCfg.pollByte    = POLL_BYTE_VAL;
   amCfg->dlAmCfg.maxRetxTh   = MAX_RETX_THRESHOLD_VAL;   
 
   /* UL AM */
   amCfg->ulAmCfg.snLenUl     = AM_SIZE_12;
   amCfg->ulAmCfg.reAssemTmr  = T_REASSEMBLY_VAL; 
   amCfg->ulAmCfg.statProhTmr = T_STATUS_PROHIBHIT_VAL;
}

/******************************************************************
 *
 * @brief Fills RLC UM Bi Directional Information
 *
 * @details
 *
 *    Function : fillDefaultUmBiInfo
 *
 *    Functionality: Fills RLC UM Bi Directional Information
 *
 * @params[in]  UmBiDirBearerCfg *umBiDirCfg
 * @return void
 *
 *****************************************************************/
void fillDefaultUmBiInfo(UmBiDirBearerCfg *umBiDirCfg)
{
   /* UL UM BI DIR INFO */
   umBiDirCfg->ulUmCfg.snLenUlUm = UM_SIZE_12;
   umBiDirCfg->ulUmCfg.reAssemTmr = T_REASSEMBLY_VAL;

   /* DL UM BI DIR INFO */
   umBiDirCfg->dlUmCfg.snLenDlUm  = UM_SIZE_12;
}

/******************************************************************
 *
 * @brief Fills RLC UM Uni Directional UL Information
 *
 * @details
 *
 *    Function : fillDefaultUmUlInfo
 *
 *    Functionality: Fills RLC UM Uni Directional Info
 *
 * @params[in]  UmUniDirUlBearerCfg *UmUlCfg
 * @return void
 *
 *****************************************************************/
void fillDefaultUmUlInfo(UmUniDirUlBearerCfg *UmUlCfg)
{
   UmUlCfg->ulUmCfg.snLenUlUm = UM_SIZE_12;
   UmUlCfg->ulUmCfg.reAssemTmr = T_REASSEMBLY_VAL;
}

/******************************************************************
 *
 * @brief Fills RLC UM Uni Directional DL Information
 *
 * @details
 *
 *    Function : fillDefaultUmDlInfo
 *
 *    Functionality: Fills RLC UM Uni Directional DL Info
 *
 * @params[in]  UmUniDirDlBearerCfg *UmDlCfg
 * @return void
 *
 *****************************************************************/
void fillDefaultUmDlInfo(UmUniDirDlBearerCfg *UmDlCfg)
{
   UmDlCfg->dlUmCfg.snLenDlUm  = UM_SIZE_12;
}

/******************************************************************
 *
 * @brief Builds Rlc Mode Default Configuration
 *
 * @details
 *
 *    Function : fillDefaultRlcModeCfg
 *
 *    Functionality: Builds Rlc Mode Default Configuration
 *
 * @params[in]  rlcMode, RlcBearerCfg *lcCfg
 * @return ROK/RFAILED
 *
 *****************************************************************/

uint8_t fillDefaultRlcModeCfg(uint8_t rlcMode, RlcBearerCfg *lcCfg)
{

   if(lcCfg)
   {
      switch(rlcMode)
      {
         case RLC_AM :
            {
	       if(!lcCfg->u.amCfg)
	       {
                 DU_ALLOC_SHRABL_BUF(lcCfg->u.amCfg, sizeof(AmBearerCfg));
		 if(lcCfg->u.amCfg)
		    fillDefaultAmInfo(lcCfg->u.amCfg);
		 else
		 {
                    DU_LOG("\n ERROR  -->  DU APP : Memory Alloc failed at AmCfg at fillDefaultRlcModeCfg()");
		    return RFAILED;
		 }
	       }
               break;
            }
         case RLC_UM_BI_DIRECTIONAL :
            {
	       if(!lcCfg->u.umBiDirCfg)
	       {
                 DU_ALLOC_SHRABL_BUF(lcCfg->u.umBiDirCfg, sizeof(UmBiDirBearerCfg));
	         if(lcCfg->u.umBiDirCfg)
                    fillDefaultUmBiInfo(lcCfg->u.umBiDirCfg);
                 else
		 {
                    DU_LOG("\n ERROR  -->  DU APP : Memory Alloc failed at UmBiDirCfg at fillDefaultRlcModeCfg()");
		    return RFAILED;
		 }
	       }
               break;
            }
         case RLC_UM_UNI_DIRECTIONAL_UL :
            {
	       if(!lcCfg->u.umUniDirUlCfg)
	       {
                  DU_ALLOC_SHRABL_BUF(lcCfg->u.umUniDirUlCfg, sizeof(UmUniDirUlBearerCfg));
		  if(lcCfg->u.umUniDirUlCfg)
                    fillDefaultUmUlInfo(lcCfg->u.umUniDirUlCfg);
                  else
		  {
                     DU_LOG("\n ERROR  -->  DU APP : Memory Alloc failed at UmUniDirUlCfg at fillDefaultRlcModeCfg()");
		     return RFAILED;
		  }
	       }
               break;
            }
         case RLC_UM_UNI_DIRECTIONAL_DL :
            {
	       if(!lcCfg->u.umUniDirDlCfg)
	       {
                  DU_ALLOC_SHRABL_BUF(lcCfg->u.umUniDirDlCfg, sizeof(UmUniDirDlBearerCfg));
                  if(lcCfg->u.umUniDirDlCfg)
		   fillDefaultUmDlInfo(lcCfg->u.umUniDirDlCfg);
                  else
		  {
                     DU_LOG("\n ERROR  -->  DU APP : Memory Alloc failed at UmUniDirDlCfg at fillDefaultRlcModeCfg()");
		     return RFAILED;
		  }
	       }
               break;
            }
         default:
            DU_LOG("\nERROR  -->  DUAPP: Invalid rlcMode %d at extractRlcCfgToAddMod()", rlcMode);
            return RFAILED;
      }

   }
   else
   {
      DU_LOG("\nERROR  -->  DUAPP: Received LC Config is NULL");
      return RFAILED;
   }
   return ROK;
}

/*******************************************************************
 *
 * @brief Function to fill Rlc Lc Cfg for SRB1
 *
 * @details
 *
 *    Function : fillRlcSrb1LcCfg
 *
 *    Functionality: 
 *     Function to fill Rlc Lc Cfg for SRB1
 * 
 *  @params[in]     Pointer to RlcBearerCfg
 *  @return ROK/RFAILED
 * 
 *****************************************************************/

uint8_t fillRlcSrb1LcCfg(RlcBearerCfg *rlcLcCfg)
{
   uint8_t ret = ROK;

   rlcLcCfg->rbId   = SRB1_LCID;
   rlcLcCfg->rbType = RB_TYPE_SRB;
   rlcLcCfg->lcId   = SRB1_LCID;
   rlcLcCfg->lcType = LCH_DCCH;
   rlcLcCfg->rlcMode = RLC_AM;
   rlcLcCfg->configType = CONFIG_ADD;
   ret = fillDefaultRlcModeCfg(rlcLcCfg->rlcMode, rlcLcCfg);
   return ret;
}

/*******************************************************************
 *
 * @brief Processes UE ReConfig Req to RLC UL
 *
 * @details
 *
 *    Function : sendUeReCfgReqToRlc
 *
 *    Functionality: 
 *     Processes UE Reconfig Req to RLC UL
 * 
 *  @params[in]     Pointer to RlcUeCfg
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/

uint8_t sendUeReCfgReqToRlc(RlcUeCfg *rlcUeCfg)
{
   uint8_t ret;
   Pst pst;
   
   FILL_PST_DUAPP_TO_RLC(pst, RLC_UL_INST, EVENT_RLC_UE_RECONFIG_REQ);
   if(rlcUeCfg)
   {
      /* Processing one Ue at a time to RLC */
      DU_LOG("\nDEBUG   -->  DU_APP: Sending Ue Reconfig Request to RLC UL");
      ret = (*packRlcUeReconfigReqOpts[pst.selector])(&pst, rlcUeCfg);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU_APP : Failed to send Ue Reconfig Req to RLC at sendUeReCfgReqToRlc()");
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, rlcUeCfg, sizeof(RlcUeCfg));
      }
   }
   else
   {
      DU_LOG("\nERROR  -->   DU_APP: Received RlcUeCfg is NULL at sendUeReCfgReqToRlc()");
      ret = RFAILED;
   }
   return ret;
}

/******************************************************************
 *
 * @brief Fills RlcBearerCfg structure
 *
 * @details
 *
 *    Function : fillRlcUeCfg
 *
 *    Functionality: Fills Rlc Bearer Cfg
 *
 *
 *****************************************************************/
uint8_t fillRlcUeCfg(uint16_t cellId, uint8_t ueIdx,\
   DuUeCfg *ueCfgDb, RlcUeCfg *rlcUeCfg)
{
   uint8_t ret, dbIdx, lcIdx, cellIdx;
   bool lcIdFound = false;
   RlcUeCfg *duRlcDb = NULLP;

   ret = ROK;
   if(!ueCfgDb)
   {
      /* Initial RB being Added */ 
      rlcUeCfg->cellId       = cellId;
      rlcUeCfg->ueIdx        = ueIdx;
      ret = fillRlcSrb1LcCfg(&rlcUeCfg->rlcLcCfg[0]);
      if(ret == ROK)
         rlcUeCfg->numLcs++;
      else
	 memset(rlcUeCfg, 0, sizeof(RlcUeCfg));
   }
   else
   {
      /* Fetch RlcDb from DuUeCb */ 
      GET_CELL_IDX(cellId, cellIdx);
      duRlcDb = &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg;
      duRlcDb->rlcUeCfgState = UE_CFG_INPROGRESS;
      /*Filling RlcUeCfg */
      rlcUeCfg->cellId       = cellId;
      rlcUeCfg->ueIdx        = ueIdx;
      for(dbIdx = 0; (dbIdx < ueCfgDb->numRlcLcs && ret == ROK); dbIdx++)
      {
         ret = fillDefaultRlcModeCfg(ueCfgDb->rlcLcCfg[dbIdx].rlcMode, &ueCfgDb->rlcLcCfg[dbIdx]);
         if(ret == RFAILED)
         {
            DU_LOG("\n ERROR  -->  DU APP : Failed to fill Rlc Mode at fillRlcUeCfg()");
            memset(rlcUeCfg, 0, sizeof(RlcUeCfg));
            return ret;
         }
         /* Fill Rlc Ue Cfg List for ADD/MOD/DEL */
         for(lcIdx = 0; lcIdx < duRlcDb->numLcs; lcIdx++)
         { 
            if(ueCfgDb->rlcLcCfg[dbIdx].lcId == duRlcDb->rlcLcCfg[lcIdx].lcId)
            {
               lcIdFound = true;
               if((ueCfgDb->rlcLcCfg[dbIdx].configType == CONFIG_UNKNOWN)||
                     (ueCfgDb->rlcLcCfg[dbIdx].configType == CONFIG_MOD))
               {
                  /* MOD */ 
                  ueCfgDb->rlcLcCfg[dbIdx].configType = CONFIG_MOD; /* update Db for MOD type */
                  memcpy(&rlcUeCfg->rlcLcCfg[dbIdx], &ueCfgDb->rlcLcCfg[dbIdx], sizeof(RlcBearerCfg));
               }
            }
            else
               lcIdFound = false;
         }
         if(!lcIdFound)
         {
            /* ADD/ DEL Config Type */
            memcpy(&rlcUeCfg->rlcLcCfg[dbIdx], &ueCfgDb->rlcLcCfg[dbIdx], sizeof(RlcBearerCfg));
         }
         rlcUeCfg->numLcs++;
      }
   }
   return ret;
}

/******************************************************************
 *
 * @brief creates UE context
 *
 * @details
 *
 *    Function : duCreateUeCb
 *
 *    Functionality: Creates UE Conetxt
 *
 * @params[in] UeCcchCtxt Pointer
 *             UeIdx Pointer
 *
 * @return ROK     - success
 *         RFAILED - failure
 * ****************************************************************/
uint8_t duCreateUeCb(UeCcchCtxt *ueCcchCtxt, uint32_t gnbCuUeF1apId)
{
   uint8_t cellIdx = 0;
   uint8_t ret     = ROK;
   uint8_t ueIdx;

   for(cellIdx = 0; cellIdx < MAX_NUM_CELL; cellIdx++)
   {
      if(ueCcchCtxt->cellId == duCb.actvCellLst[cellIdx]->cellId)
      {
	 GET_UE_IDX(ueCcchCtxt->crnti, ueIdx);
	 DU_LOG("\nDEBUG   -->  DU_APP: Filling UeCb for ueIdx [%d]", ueIdx);

	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].f1UeDb        = NULLP;
	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].crnti         = ueCcchCtxt->crnti;
	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbDuUeF1apId = ueCcchCtxt->gnbDuUeF1apId;
	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbCuUeF1apId = gnbCuUeF1apId;
	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].drbBitMap     = NULLP;
	 duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].ueState       = UE_ACTIVE;

	 /* Filling Mac Ue Config */ 
	 memset(&duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].macUeCfg, 0, sizeof(MacUeCfg));
         ret = duBuildAndSendUeCreateReqToMac(ueCcchCtxt->cellId, ueIdx, ueCcchCtxt->crnti,\
                &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].macUeCfg);
         if(ret == RFAILED)
            DU_LOG("\nERROR  -->  DU APP : Failed to send UE create request to MAC");
         
	 /* Filling Rlc Ue Config */
         memset(&duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg, 0, sizeof(RlcUeCfg));
         ret = duBuildAndSendUeCreateReqToRlc(ueCcchCtxt->cellId, ueIdx, \
                &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg);
         if(ret == RFAILED)
            DU_LOG("\nERROR  -->  DU APP : Failed to send UE create request to RLC");

	 duCb.actvCellLst[cellIdx]->numActvUes++;
	 memset(ueCcchCtxt, 0, sizeof(UeCcchCtxt));
      }
   }
   return ret;
}

/******************************************************************
 *
 * @brief Builds and Send UE Create Request to MAC
 *
 * @details
 *
 *    Function : duBuildAndSendUeCreateReqToMac
 *
 *    Functionality: Builds and Send UE Create Request to MAC
 *
 * @Params[in]  cellId,
 *              ueIdx
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duBuildAndSendUeCreateReqToMac(uint16_t cellId, uint8_t ueIdx,\
   uint16_t crnti, MacUeCfg *duMacUeCfg)
{
   uint8_t  ret = ROK;
   MacUeCfg *macUeCfg = NULLP;
   Pst       pst;
   memset(&pst, 0, sizeof(Pst));


   ret = fillMacUeCfg(cellId, ueIdx, crnti, NULL, duMacUeCfg);
   if(ret == RFAILED)
   {
      DU_LOG("\nERROR  -->  DU APP : Failed to fill MacUeCfg at duBuildAndSendUeCreateReqToMac()");
      return RFAILED;
   }
   /* Fill Pst */
   FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_UE_CREATE_REQ);

   /* Copying ueCb to a sharable buffer */
   DU_ALLOC_SHRABL_BUF(macUeCfg, sizeof(MacUeCfg));
   if(macUeCfg)
   {
      memset(macUeCfg, 0, sizeof(MacUeCfg));
      memcpy(macUeCfg, duMacUeCfg, sizeof(MacUeCfg));
      DU_LOG("\nDEBUG   -->  DU_APP: Sending UE create request to MAC");

      /* Processing one Ue at a time to MAC */
      ret = (*packMacUeCreateReqOpts[pst.selector])(&pst, macUeCfg);
      if(ret == RFAILED)
      {
	 DU_LOG("\nERROR  -->  DU_APP : Failure in sending Ue Create Req to MAC at duBuildAndSendUeCreateReqToMac()");
	 DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, macUeCfg, sizeof(MacUeCfg));
      }
   }
   else
   {
      DU_LOG("\n ERROR  -->  DU APP : Memory alloc failed at duBuildAndSendUeCreateReqToMac()");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief To update DuUeCb Mac Cfg
 *
 * @details
 *
 *    Function : duUpdateMacCfg
 *    Functionality:  update DuUeCb MAC Cfg
 *
 * @params[in] DuUeCb Pointer
 *             F1UeContextSetupDb pointer 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t duUpdateMacCfg(MacUeCfg *macUeCfg, F1UeContextSetupDb *f1UeDb) 
{
   uint8_t ret, lcIdx, dbIdx, numLcs, lcDelIdx, cellIdx;
   MacUeCfg *oldMacUeCfg;
   ret = ROK;

   /*Filling Cell Group Cfg*/
   ret =  procUeReCfgCellInfo(macUeCfg, f1UeDb->duUeCfg.cellGrpCfg);
   if(ret == ROK)
   {
      if(macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschPresent)
      {
         fillStartSymbolAndLen(macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschCfg.numTimeDomRsrcAlloc,\
	       &macUeCfg->spCellCfg.servCellCfg.initDlBwp.pdschCfg, NULL);
      }
      if(macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschPresent)
      {
         fillStartSymbolAndLen(macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschCfg.numTimeDomRsrcAlloc,\
	       NULL, &macUeCfg->spCellCfg.servCellCfg.initUlBwp.puschCfg);
      }
      ret = fillAmbr(&macUeCfg->ambrCfg, f1UeDb->duUeCfg.ambrCfg);

      GET_CELL_IDX(macUeCfg->cellId, cellIdx);
      oldMacUeCfg = &duCb.actvCellLst[cellIdx]->ueCb[macUeCfg->ueIdx-1].macUeCfg;
      duFillModulationDetails(macUeCfg, oldMacUeCfg, f1UeDb->duUeCfg.ueNrCapability);
   }

   /* Filling LC Context */
   for(dbIdx = 0; (dbIdx < f1UeDb->duUeCfg.numMacLcs && ret == ROK); dbIdx++)
   {
      numLcs = macUeCfg->numLcs;
      for(lcIdx = 0; lcIdx < numLcs; lcIdx++)
      {
	 if(f1UeDb->duUeCfg.macLcCfg[dbIdx].lcId ==  macUeCfg->lcCfgList[lcIdx].lcId)
	 {
	    if(f1UeDb->duUeCfg.macLcCfg[dbIdx].configType == CONFIG_MOD)
	    {
	       ret = fillMacLcCfgToAddMod(&macUeCfg->lcCfgList[lcIdx],&f1UeDb->duUeCfg.macLcCfg[dbIdx]);
	    }
	    else if(f1UeDb->duUeCfg.macLcCfg[dbIdx].configType == CONFIG_DEL)
	    {
	       /* Free memory at matched  lcIdx index */
	       freeMacLcCfg(&macUeCfg->lcCfgList[lcIdx]);
	       macUeCfg->numLcs--;
	       for(lcDelIdx = lcIdx; lcDelIdx < macUeCfg->numLcs; lcDelIdx++)
	       {
	          /* moving all elements one index ahead */
		  ret = fillMacLcCfgToAddMod(&macUeCfg->lcCfgList[lcDelIdx], &macUeCfg->lcCfgList[lcDelIdx+1]);
	          freeMacLcCfg(&macUeCfg->lcCfgList[lcDelIdx+1]);
		  if(ret == RFAILED)
		  {
                     DU_LOG("\nERROR  -->  DU APP : Failed to delete LC at Idx %d in duUpdateMacCfg()", lcDelIdx);
		     break;
		  }
	       }
	    }
	 }
      } 
      if(f1UeDb->duUeCfg.macLcCfg[dbIdx].configType == CONFIG_ADD)
      {
	 ret = fillMacLcCfgToAddMod(&macUeCfg->lcCfgList[numLcs], &f1UeDb->duUeCfg.macLcCfg[dbIdx]);
	 if(ret == RFAILED)
	 {
	    DU_LOG("\nERROR  -->  DU APP : Failed to add LC at Idx %d in duUpdateMacCfg()", numLcs);
	    break;
	 }
	 macUeCfg->numLcs++;
      }
		
   }
   return ret;
}

/******************************************************************
 *
 * @brief Function to fill the RLC Lc cfg from ueSetupReqDb
 *
 * @details
 *
 *    Function : fillRlcCfgToAddMod
 *
 *    Functionality: Function to fill the RLC Lc cfg from ueSetupReqDb
 *
 *
 *****************************************************************/

uint8_t fillRlcCfgToAddMod(RlcBearerCfg *lcCfg, RlcBearerCfg *f1UeDbLcCfg)
{
   lcCfg->configType = f1UeDbLcCfg->configType;
   lcCfg->rbId       = f1UeDbLcCfg->rbId;
   lcCfg->rbType     = f1UeDbLcCfg->rbType;
   lcCfg->lcId       = f1UeDbLcCfg->lcId;
   lcCfg->lcType     = f1UeDbLcCfg->lcType;
   lcCfg->rlcMode    = f1UeDbLcCfg->rlcMode;
   switch(lcCfg->rlcMode)
   {
      case RLC_AM :
      {
         if(!lcCfg->u.amCfg)
	 {
            DU_ALLOC_SHRABL_BUF(lcCfg->u.amCfg, sizeof(AmBearerCfg));
            if(!lcCfg->u.amCfg)
	       return RFAILED;
	 }
         /* DL AM */
         lcCfg->u.amCfg->dlAmCfg.snLenDl     = f1UeDbLcCfg->u.amCfg->dlAmCfg.snLenDl;    
         lcCfg->u.amCfg->dlAmCfg.pollRetxTmr = f1UeDbLcCfg->u.amCfg->dlAmCfg.pollRetxTmr;
         lcCfg->u.amCfg->dlAmCfg.pollPdu     = f1UeDbLcCfg->u.amCfg->dlAmCfg.pollPdu;
         lcCfg->u.amCfg->dlAmCfg.pollByte    = f1UeDbLcCfg->u.amCfg->dlAmCfg.pollByte;   
         lcCfg->u.amCfg->dlAmCfg.maxRetxTh   = f1UeDbLcCfg->u.amCfg->dlAmCfg.maxRetxTh;   
 
         /* UL AM */
         lcCfg->u.amCfg->ulAmCfg.snLenUl     = f1UeDbLcCfg->u.amCfg->ulAmCfg.snLenUl;
         lcCfg->u.amCfg->ulAmCfg.reAssemTmr  = f1UeDbLcCfg->u.amCfg->ulAmCfg.reAssemTmr; 
         lcCfg->u.amCfg->ulAmCfg.statProhTmr = f1UeDbLcCfg->u.amCfg->ulAmCfg.statProhTmr;
	 break;
      }
      case RLC_UM_BI_DIRECTIONAL :
      {
         if(!lcCfg->u.umBiDirCfg)
	 {
            DU_ALLOC_SHRABL_BUF(lcCfg->u.umBiDirCfg, sizeof(UmBiDirBearerCfg));
	    if(!lcCfg->u.umBiDirCfg)
	        return RFAILED;
         }
         /* UL UM BI DIR INFO */
         lcCfg->u.umBiDirCfg->ulUmCfg.snLenUlUm  = f1UeDbLcCfg->u.umBiDirCfg->ulUmCfg.snLenUlUm;  
         lcCfg->u.umBiDirCfg->ulUmCfg.reAssemTmr = f1UeDbLcCfg->u.umBiDirCfg->ulUmCfg.reAssemTmr;
         /* DL UM BI DIR INFO */
         lcCfg->u.umBiDirCfg->dlUmCfg.snLenDlUm  = f1UeDbLcCfg->u.umBiDirCfg->dlUmCfg.snLenDlUm;
         break;
      }
      case RLC_UM_UNI_DIRECTIONAL_UL :
      {
         if(!lcCfg->u.umUniDirUlCfg)
	 {
            DU_ALLOC_SHRABL_BUF(lcCfg->u.umUniDirUlCfg, sizeof(UmUniDirUlBearerCfg));
	    if(!lcCfg->u.umUniDirUlCfg)
	       return RFAILED;
	 }
         lcCfg->u.umUniDirUlCfg->ulUmCfg.snLenUlUm  = f1UeDbLcCfg->u.umUniDirUlCfg->ulUmCfg.snLenUlUm;  
         lcCfg->u.umUniDirUlCfg->ulUmCfg.reAssemTmr = f1UeDbLcCfg->u.umUniDirUlCfg->ulUmCfg.reAssemTmr;
         break;

      }
      case RLC_UM_UNI_DIRECTIONAL_DL :
      {
         if(!lcCfg->u.umUniDirDlCfg)
	 {
            DU_ALLOC_SHRABL_BUF(lcCfg->u.umUniDirDlCfg, sizeof(UmUniDirDlBearerCfg));
	    if(!lcCfg->u.umUniDirDlCfg)
	       return RFAILED;
         }
         lcCfg->u.umUniDirDlCfg->dlUmCfg.snLenDlUm  = f1UeDbLcCfg->u.umUniDirDlCfg->dlUmCfg.snLenDlUm;
         break;
      }
      default:
         DU_LOG("\nERROR  -->  DU_APP: Invalid Rlc Mode %d at fillRlcCfgToAddMod()", lcCfg->rlcMode);
	 return RFAILED;
   }
   return ROK;
}

/*******************************************************************
 *
 * @brief To update DuUeCb Rlc Lc Cfg
 *
 * @details
 *
 *    Function : duUpdateRlcLcCfg
 *    Functionality:  update DuUeCb Rlc Lc Cfg
 *
 * @params[in] DuUeCb Pointer
 *             F1UeContextSetupDb pointer 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duUpdateRlcLcCfg(RlcUeCfg *rlcUeCfg, F1UeContextSetupDb *f1UeDb)
{
   uint8_t ret, lcIdx, dbIdx, numLcs, lcDelIdx;

   ret = ROK;
   for(dbIdx = 0; (dbIdx < f1UeDb->duUeCfg.numRlcLcs && ret ==ROK); dbIdx++)
   {
      numLcs = rlcUeCfg->numLcs;
      for(lcIdx = 0; lcIdx < numLcs; lcIdx++)
      {
	 if(f1UeDb->duUeCfg.rlcLcCfg[dbIdx].lcId == rlcUeCfg->rlcLcCfg[lcIdx].lcId)
	 {
	    if(f1UeDb->duUeCfg.rlcLcCfg[dbIdx].configType == CONFIG_MOD)
	    {
	       ret = fillRlcCfgToAddMod(&rlcUeCfg->rlcLcCfg[lcIdx], &f1UeDb->duUeCfg.rlcLcCfg[dbIdx]);
	    }
	    else if(f1UeDb->duUeCfg.rlcLcCfg[dbIdx].configType == CONFIG_DEL)
	    {
	       /* Free memory at matched lcIdx index */
	       freeRlcLcCfg(&rlcUeCfg->rlcLcCfg[lcIdx]);
	       rlcUeCfg->numLcs--;
	       for(lcDelIdx = lcIdx; lcDelIdx < rlcUeCfg->numLcs; lcDelIdx++)
	       {
	          ret = fillRlcCfgToAddMod(&rlcUeCfg->rlcLcCfg[lcDelIdx], &rlcUeCfg->rlcLcCfg[lcDelIdx+1]);
		  freeRlcLcCfg(&rlcUeCfg->rlcLcCfg[lcDelIdx+1]);
		  if(ret == RFAILED)
		  {
                     DU_LOG("\nERROR  -->  DU APP : Failed to delete LC at Idx %d in duUpdateRlcCfg()", lcDelIdx);
		     break;
		  }
	       }
	    }
	 }
      }
      if(f1UeDb->duUeCfg.rlcLcCfg[dbIdx].configType == CONFIG_ADD)
      {
	 ret = fillRlcCfgToAddMod(&rlcUeCfg->rlcLcCfg[lcIdx], &f1UeDb->duUeCfg.rlcLcCfg[dbIdx]);
	 if(ret == ROK)
	    rlcUeCfg->numLcs++;
      }
   }
   return ret;
}


/*******************************************************************
 *
 * @brief Function to fill Tunnel Config to Add/Mod
 * 
 *
 * @details
 *
 *    Function : fillTnlCfgToAddMod
 *
 *    Functionality: Function to fill tunnel Config to Add/Mod
 *
 * @params[in] Pointer to tnlCfgDb,
 *             pointer to f1TnlCfg
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t fillTnlCfgToAddMod(UpTnlCfg **ueCbTnlCfg, UpTnlCfg *f1TnlCfg)
{
   if(*ueCbTnlCfg == NULLP)
   {
      /* copying to DuCb Tnl Cfg */
      DU_ALLOC(*ueCbTnlCfg, sizeof(UpTnlCfg));
      if(*ueCbTnlCfg == NULLP)
      {
         DU_LOG("\nERROR  -->  DU_APP : fillTnlCfgToAddMod: Memory Alloc failed for drbId[%d]", f1TnlCfg->drbId);
         return RFAILED;
      }
   }
   memset(*ueCbTnlCfg, 0, sizeof(UpTnlCfg));
   (*ueCbTnlCfg)->configType = f1TnlCfg->configType;
   (*ueCbTnlCfg)->cellId    = f1TnlCfg->cellId;
   (*ueCbTnlCfg)->ueIdx     = f1TnlCfg->ueIdx;
   (*ueCbTnlCfg)->drbId     = f1TnlCfg->drbId;
   if(f1TnlCfg->tnlCfg1)
   {
      if((*ueCbTnlCfg)->tnlCfg1 == NULLP)
      {
         DU_ALLOC((*ueCbTnlCfg)->tnlCfg1, sizeof(GtpTnlCfg));
         if((*ueCbTnlCfg)->tnlCfg1 == NULLP)
         {
            DU_LOG("\nERROR  -->  DU_APP : fillTnlCfgToAddMod: Memory Alloc failed for tnlCfg1 for drbId[%d]", f1TnlCfg->drbId);
            return RFAILED;
         }
      }
      memset((*ueCbTnlCfg)->tnlCfg1, 0, sizeof(GtpTnlCfg));
      (*ueCbTnlCfg)->tnlCfg1->teId = f1TnlCfg->tnlCfg1->teId;
      (*ueCbTnlCfg)->tnlCfg1->ulTnlAddress = f1TnlCfg->tnlCfg1->ulTnlAddress;
      (*ueCbTnlCfg)->tnlCfg1->dlTnlAddress = f1TnlCfg->tnlCfg1->dlTnlAddress;
   }
   return ROK;
}

/*******************************************************************
 *
 * @brief Processing the tunnel Request to EGTP
 *        
 * @details
 *
 *    Function : duProcEgtpTunnelCfg
 *
 *    Functionality: Processing the tunnel Request to EGTP
 *
 * @params[in] UptnlCfg *duTnlCfg, UpTnlCfg *f1TnlCfg 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duProcEgtpTunnelCfg(uint8_t ueCbIdx, UpTnlCfg *duTnlCfg, UpTnlCfg *f1TnlCfg)
{
   uint8_t ret = RFAILED, delIdx;

   if(f1TnlCfg->tnlCfg1 == NULLP)
   {
      DU_LOG("\nERROR  -->  DU_APP : Tunnel config not found");
      return ret;
   }

   if(f1TnlCfg->configType == CONFIG_ADD)
   {
      if(duSendEgtpTnlMgmtReq(EGTP_TNL_MGMT_ADD, NULLP, f1TnlCfg->tnlCfg1) == ROK)
      {
	 if(fillTnlCfgToAddMod(&duCb.upTnlCfg[duCb.numDrb], f1TnlCfg) == ROK)
	 {
	    duCb.numDrb++;
	    ret = ROK;
	 }
      }      
   }
   else if(f1TnlCfg->configType == CONFIG_MOD)
   {
      if(duSendEgtpTnlMgmtReq(EGTP_TNL_MGMT_MOD, duTnlCfg->tnlCfg1->teId, f1TnlCfg->tnlCfg1) == ROK)
      {
	 if(fillTnlCfgToAddMod(&duTnlCfg, f1TnlCfg) == ROK)
	 {
	    ret = ROK;
	 }
      }   
   }
   else if(f1TnlCfg->configType == CONFIG_DEL)
   {
      if(duSendEgtpTnlMgmtReq(EGTP_TNL_MGMT_DEL, duTnlCfg->tnlCfg1->teId, f1TnlCfg->tnlCfg1) == ROK)
      {	   
	 /* Free memory at drbIdx */
	 DU_FREE(duTnlCfg->tnlCfg1, sizeof(GtpTnlCfg));
	 DU_FREE(duTnlCfg, sizeof(UpTnlCfg));
	 duCb.numDrb--;
	 for(delIdx = ueCbIdx; delIdx < duCb.numDrb; delIdx++)
	 {
	    /* moving all elements one index ahead */
	    ret = fillTnlCfgToAddMod(&duCb.upTnlCfg[delIdx], duCb.upTnlCfg[delIdx+1]);
	    if(ret != ROK)
	    {
	       return ret;
	    }
	 }
      }   
   }
   return ret;
}

/***********************************************************************
 *
 * @brief Function to fill Tunnel Config
 *        and sends tunnel Req to EGTP
 * 
 *
 * @details
 *
 *    Function : duUpdateTunnelCfgDb
 *
 *    Functionality: Function to fill tunnel Config
 *                   and sends tunnel Cfg Req to EGTP
 *
 * @params[in] ueIdx, cellId, DuUeCfg 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duUpdateTunnelCfgDb(uint8_t ueIdx, uint8_t cellId, DuUeCfg *duUeCfg)
{
   uint8_t ret = ROK, drbIdx, duCbDrbIdx;
   bool drbFound = false;

   /*If Add/Mod tunnels request for that DRB is successful in EGTP */
   /*then update drbId and tunnel Info in duCb */
   for(drbIdx=0; drbIdx < duUeCfg->numDrb; drbIdx++)
   {
      duUeCfg->upTnlInfo[drbIdx].cellId = cellId;
      duUeCfg->upTnlInfo[drbIdx].ueIdx = ueIdx;
      for(duCbDrbIdx = 0; duCbDrbIdx < duCb.numDrb; duCbDrbIdx++)
      {
	 if(duCb.upTnlCfg[duCbDrbIdx]->drbId == duUeCfg->upTnlInfo[drbIdx].drbId)
	 {
	    drbFound = true; /* existing DRB */
	    if(duProcEgtpTunnelCfg(duCbDrbIdx, duCb.upTnlCfg[duCbDrbIdx], &duUeCfg->upTnlInfo[drbIdx]) != ROK)
	    {
	       DU_LOG("\nERROR  -> DU_APP : duUpdateTunnelCfgDb: Failed to modify tunnel req for Drb id[%d]",
	       duUeCfg->upTnlInfo[drbIdx].drbId);
	       ret = RFAILED;
	    }
	    break;
	 }
	 else
	    drbFound = false;
      }
      if(!drbFound && ret == ROK)/* new DRB to Add */
      {
	 if(duProcEgtpTunnelCfg(NULLP, NULLP, &duUeCfg->upTnlInfo[drbIdx]) != ROK)
	 {
            DU_LOG("\nERROR  -> DU_APP : duUpdateTunnelCfgDb: Failed to add tunnel req for Drb id[%d]",
	    duUeCfg->upTnlInfo[drbIdx].drbId);
	    ret = RFAILED;
	    break;
	 }
      }
      else
         break;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief @brief To update DuUeCb Mac and Rlc Ue Cfg
 * 
 *
 * @details
 *
 *    Function : duUpdateDuUeCbCfg
 *
 *    Functionality: update DuUeCb Mac and Rlc Ue Cfg
 *
 * @params[in] ueIdx, cellIdx 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duUpdateDuUeCbCfg(uint8_t ueIdx, uint8_t cellId)
{
   uint8_t ret = ROK, cellIdx = 0, crnti=0;
   DuUeCb *ueCb = NULLP;

   GET_CELL_IDX(cellId, cellIdx);
   
   if((duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].macUeCfg. \
         macUeCfgState == UE_RECFG_COMPLETE) &&
      (duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg. \
         rlcUeCfgState == UE_RECFG_COMPLETE))
   {
      ueCb = &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1];

      /*Filling RLC Ue Cfg */
      ueCb->rlcUeCfg.cellId = cellId;
      ueCb->rlcUeCfg.ueIdx  = ueIdx;
      ret = duUpdateRlcLcCfg(&ueCb->rlcUeCfg, ueCb->f1UeDb);
      if(ret == ROK)
      {
         /*Filling MAC Ue Cfg */
         GET_CRNTI(crnti, ueIdx);
         ueCb->macUeCfg.cellId = cellId;
         ueCb->macUeCfg.ueIdx  = ueIdx;
         ueCb->macUeCfg.crnti  = crnti;
         ret = duUpdateMacCfg(&ueCb->macUeCfg, ueCb->f1UeDb);
         if(ret == RFAILED)
            DU_LOG("\nERROR  -->  DU APP : Failed while updating MAC LC Config at duUpdateDuUeCbCfg()");
         else
	 {
	    if(duUpdateTunnelCfgDb(ueIdx, cellId, &ueCb->f1UeDb->duUeCfg) != ROK)
	    {
               DU_LOG("\nERROR  -->  DU_APP : Failed to establish tunnel in duUpdateDuUeCbCfg()");
	       return RFAILED;
	    }
	 }
      }
      else
         DU_LOG("\nERROR  -->  DU APP : Failed while updating RLC LC Config at duUpdateDuUeCbCfg()");
   }
   else
      ret = RFAILED;
   return ret;
}

/*******************************************************************
 *
 * @brief Handle UE config response from MAC
 *
 * @details
 *
 *    Function : DuProcMacUeCfgRsp
 *
 *    Functionality: Handle UE Config response from MAC
 *
 * @params[in] Pointer to MacUeCfgRsp and Pst 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t DuProcMacUeCfgRsp(Pst *pst, MacUeCfgRsp *cfgRsp)
{
   uint8_t ret = ROK;

   if(cfgRsp)
   {
      if(cfgRsp->result == MAC_DU_APP_RSP_OK)
      {
         if(pst->event == EVENT_MAC_UE_CREATE_RSP)
         {
            DU_LOG("\nINFO   -->  DU APP : MAC UE Create Response : SUCCESS [UE IDX : %d]", cfgRsp->ueIdx);
            duCb.actvCellLst[cfgRsp->cellId -1]->ueCb[cfgRsp->ueIdx -1].\
               macUeCfg.macUeCfgState = UE_CREATE_COMPLETE;
         }
         else if(pst->event == EVENT_MAC_UE_RECONFIG_RSP)
         {
            DU_LOG("\nINFO   -->  DU APP : MAC UE Reconfig Response : SUCCESS [UE IDX : %d]", cfgRsp->ueIdx);
            duCb.actvCellLst[cfgRsp->cellId -1]->ueCb[cfgRsp->ueIdx -1].\
               macUeCfg.macUeCfgState = UE_RECFG_COMPLETE;
            if((ret = duUpdateDuUeCbCfg(cfgRsp->ueIdx, cfgRsp->cellId)) == ROK)
            {
               BuildAndSendUeCtxtRsp(cfgRsp->ueIdx, cfgRsp->cellId);
            }
         }
      }
      else
      {
         DU_LOG("\nERROR  -->  DU APP : MAC UE CFG Response for EVENT[%d]: FAILURE [UE IDX : %d]", pst->event, cfgRsp->ueIdx);
         if(pst->event == EVENT_MAC_UE_RECONFIG_RSP)
         {
            //TODO: Send the failure case in Ue Context Setup Response
         }
         ret = RFAILED;
      }
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, cfgRsp, sizeof(MacUeCfgRsp));
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Received MAC Ue Config Response is NULL at DuProcMacUeCfgRsp()");
      ret = RFAILED;
   }
   return ret;
}


/*******************************************************************
 *
 * @brief Processes UE create Req to RLC UL
 *
 * @details
 *
 *    Function : duBuildAndSendUeCreateReqToRlc
 *
 *    Functionality: 
 *     Processes UE create Req to RLC UL
 * 
 *  @params[in]  cellId,
 *               ueIdx,
 *               Pointer to RlcUeCfg
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/

uint8_t duBuildAndSendUeCreateReqToRlc(uint16_t cellId, uint8_t ueIdx,\
   RlcUeCfg *duRlcUeCfg)
{
   uint8_t  ret = ROK;
   RlcUeCfg *rlcUeCfg = NULLP;
   Pst       pst;
  
   ret = fillRlcUeCfg(cellId, ueIdx, NULL, duRlcUeCfg);
   if(ret == RFAILED)
   {
      DU_LOG("\nERROR  -->  DU APP : Failed to fill Rlc Ue Cfg at duBuildAndSendUeCreateReqToRlc()");
      return ret;
   }

   FILL_PST_DUAPP_TO_RLC(pst, RLC_UL_INST, EVENT_RLC_UE_CREATE_REQ);
   /* Copying ueCfg to a sharable buffer */
   DU_ALLOC_SHRABL_BUF(rlcUeCfg, sizeof(RlcUeCfg));
   if(rlcUeCfg)
   {
      memset(rlcUeCfg, 0, sizeof(RlcUeCfg));
      memcpy(rlcUeCfg, duRlcUeCfg, sizeof(RlcUeCfg));
      /* Processing one Ue at a time to RLC */
      DU_LOG("\nDEBUG   -->  DU_APP: Sending UE create request to RLC UL");
      ret = (*packRlcUeCreateReqOpts[pst.selector])(&pst, rlcUeCfg);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU_APP : Failure in sending Ue Create Req to RLC");
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, rlcUeCfg, sizeof(RlcUeCfg));
         ret = RFAILED;
      }
   }
   else
   {
      DU_LOG("\n ERROR  -->  DU APP : Memory alloc failed at duBuildAndSendUeCreateReqToRlc()");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Processes UE create Rsp received from RLC UL
 *
 * @details
 *
 
 *    Function : DuProcRlcUeCfgRsp
 *
 *    Functionality: 
 *     Processes UE create Rsp received from RLC UL
 * 
 *  @params[in]  Post structure
 *               Pointer to RlcCfgCfm
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/
uint8_t DuProcRlcUeCfgRsp(Pst *pst, RlcUeCfgRsp *cfgRsp)
{
   uint8_t ret = ROK;

   if(cfgRsp)
   {
      if(cfgRsp->result == RLC_DU_APP_RSP_OK)
      {
         if(pst->event == EVENT_RLC_UE_CREATE_RSP)
         {
            DU_LOG("\nINFO   -->  DU_APP: RLC UE Create Response : SUCCESS [UE IDX:%d]", cfgRsp->ueIdx);
            duCb.actvCellLst[cfgRsp->cellId -1]->ueCb[cfgRsp->ueIdx -1].\
               rlcUeCfg.rlcUeCfgState = UE_CREATE_COMPLETE;
         }
         else if(pst->event == EVENT_RLC_UE_RECONFIG_RSP)
         {
            DU_LOG("\nINFO   -->  DU_APP: RLC UE Reconfig Response : SUCCESS [UE IDX:%d]", cfgRsp->ueIdx);
            duCb.actvCellLst[cfgRsp->cellId -1]->ueCb[cfgRsp->ueIdx -1].\
               rlcUeCfg.rlcUeCfgState = UE_RECFG_COMPLETE;
            if((ret = duUpdateDuUeCbCfg(cfgRsp->ueIdx, cfgRsp->cellId)) == ROK)
            {
               BuildAndSendUeCtxtRsp(cfgRsp->ueIdx, cfgRsp->cellId);
            }   
         }
      }
      else
      {
         DU_LOG("\nERROR  -->  DU_APP: RLC UE CFG Response for EVENT[%d] : FAILED [UE IDX : %d, REASON :%d]",\
               pst->event, cfgRsp->ueIdx, cfgRsp->reason);
         if((pst->event == EVENT_RLC_UE_RECONFIG_RSP))
         {
            //TODO: update failure case in ue Context setup Response
         }
         ret = RFAILED;
      }
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, cfgRsp, sizeof(RlcUeCfgRsp));
   }
   else
   {
      DU_LOG("\nERROR  -->  DU_APP: Received RLC Ue Config Response is NULL at DuProcRlcUeCfgRsp()");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Builds and Send Ue Reconfig Req to RLC
 *
 * @details
 *
 *    Function : duBuildAndSendUeReCfgReqToRLC
 *
 *    Functionality: Builds and Send Ue Reconfig Req to RLC
 *
 * @params[in] cellId, crnti
 *             DuUeCfg *ueCfgDb
 *             RlcUeCfg *rlcUeCfg
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duBuildAndSendUeReCfgReqToRlc(uint8_t cellId, uint8_t crnti, DuUeCfg *ueCfgDb)
{
   uint8_t ret = ROK, ueIdx = 0;
   RlcUeCfg *rlcUeCfg = NULLP;

   GET_UE_IDX(crnti, ueIdx);
   DU_ALLOC_SHRABL_BUF(rlcUeCfg, sizeof(RlcUeCfg));
   if(rlcUeCfg)
   {
      memset(rlcUeCfg, 0, sizeof(RlcUeCfg));
      ret = fillRlcUeCfg(cellId, ueIdx, ueCfgDb, rlcUeCfg);
      if(ret == RFAILED)
         DU_LOG("\nERROR  -->  DU APP : Failed at duBuildAndSendUeReCfgReqToRlc()");
      else
         ret = sendUeReCfgReqToRlc(rlcUeCfg);
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory Alloc failed at duBuildAndSendUeReCfgReqToRlc()");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Builds and Send Ue Reconfig Req to MAC
 *
 * @details
 *
 *    Function : duBuildAndSendUeReCfgReqToMac
 *
 *    Functionality: Builds and Send Ue Reconfig Req to MAC
 *
 * @params[in] CellGroupConfigRrc_t *macCellGrpCfg
 *             DuUeCfg *ueCfgDb
 *             MacUeCfg    *macUeCfg
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duBuildAndSendUeReCfgReqToMac(uint8_t cellId, uint8_t crnti, DuUeCfg *ueCfgDb)
{
   uint8_t ret, ueIdx = 0;
   MacUeCfg *macUeCfg = NULLP;

   ret = ROK;
   GET_UE_IDX(crnti, ueIdx);

   DU_ALLOC_SHRABL_BUF(macUeCfg, sizeof(MacUeCfg));
   if(macUeCfg)
   {
      memset(macUeCfg, 0, sizeof(MacUeCfg));
      ret = fillMacUeCfg(cellId, ueIdx, crnti, ueCfgDb, macUeCfg);
      if(ret == RFAILED)
         DU_LOG("\nERROR  -->  DU APP : Failed to fill Mac Ue Cfg at duBuildAndSendUeReCfgReqToMac()");
      else
         ret = sendUeReCfgReqToMac(macUeCfg);
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : Memory alloc failed for macUeCfg at duBuildAndSendUeReCfgReqToMac()");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Build and Send Ue context setup request
 *
 * @details
 *
 
 *    Function : duBuildAndSendUeContextSetupReq
 *
 *    Functionality: 
 *     Build and Send Ue context setup request
 * 
 *  @params[in]  cellId, crnti, DuUeCfg pointer
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/

uint8_t duBuildAndSendUeContextSetupReq(uint16_t cellId, uint16_t crnti, DuUeCfg *duUeCfg)
{
   uint8_t ret = ROK;

   DU_LOG("\nDEBUG   -->  DU_APP: Processing Ue Context Setup Request for cellId [%d]", cellId);
   /* Filling RLC Ue Reconfig */ 
   ret = duBuildAndSendUeReCfgReqToRlc(cellId, crnti, duUeCfg);
   if(ret == RFAILED)
      DU_LOG("\nERROR  -->  DU APP : Failed to build ctxt setup req for RLC at duBuildAndSendUeContextSetupReq()");
   
   /* Filling MAC Ue Reconfig */
   ret = duBuildAndSendUeReCfgReqToMac(cellId, crnti, duUeCfg);
   if(ret == RFAILED)
      DU_LOG("\nERROR  -->  DU APP : Failed at build ctxt setup req for MAC at duBuildAndSendUeContextSetupReq()");

   return ret;
}

/*******************************************************************
 *
 * @brief Processes DL Rsp received from RLC DL
 *
 * @details
 *
 
 *    Function : DuProcRlcDlRrcMsgRsp
 *
 *    Functionality: 
 *     Processes UE Rsp received from RLC DL
 * 
 *  @params[in]  Post structure
 *               Pointer to RlcCfgCfm
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/
uint8_t DuProcRlcDlRrcMsgRsp(Pst *pst, RlcDlRrcMsgRsp *dlRrcMsg)
{
   uint8_t ret = ROK, ueIdx = 0;
   DuUeCb *ueCb = NULLP;

   if(dlRrcMsg->state == TRANSMISSION_COMPLETE)
   {
      GET_UE_IDX(dlRrcMsg->crnti, ueIdx);
      ueCb = &duCb.actvCellLst[dlRrcMsg->cellId -1]->ueCb[ueIdx -1];
      if(ueCb->f1UeDb && ueCb->f1UeDb->dlRrcMsgPres)
      {
         if(ueCb->f1UeDb->actionType == UE_CTXT_SETUP)
         {
            ret = duBuildAndSendUeContextSetupReq(dlRrcMsg->cellId, dlRrcMsg->crnti, &ueCb->f1UeDb->duUeCfg);
            if(ret == RFAILED)
               DU_LOG("\nERROR  -->  DU APP : Failed to process UE Context Setup Request in DuProcRlcDlRrcMsgRsp()");
         }
         if(ueCb->f1UeDb->actionType == UE_CTXT_MOD)
         {
            ret = duBuildAndSendUeContextModReq(dlRrcMsg->cellId, dlRrcMsg->crnti, &ueCb->f1UeDb->duUeCfg);
            if(ret == RFAILED)
               DU_LOG("\nERROR  -->  DU APP : Failed to process UE Context Mod Request in DuProcRlcDlRrcMsgRsp()");
         }
      }
   }
   else
      DU_LOG("\nERROR  -->  DU APP : Failed to transmit DL RRC Msg");

   DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, dlRrcMsg, sizeof(RlcDlRrcMsgRsp));
   return ret;
}
/*******************************************************************
 *
 * @brief Process UE context setup request from CU
 *
 * @details
 *
 *    Function : duProcUeContextSetupRequest 
 *
 *    Functionality: Process UE context setup request from CU
 *
 * @params[in] F1AP message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duProcUeContextSetupRequest(DuUeCb *ueCb)
{
   uint8_t ret, cellId;

   ret = ROK;
   if(ueCb)
   {
      cellId = duCb.actvCellLst[ueCb->f1UeDb->cellIdx]->cellId;
      /* Send DL RRC msg for security Mode */
      if(ueCb->f1UeDb->dlRrcMsg)
      {
         if(ueCb->f1UeDb->dlRrcMsg->rrcMsgPdu)
         {
            /* Sending DL RRC Message to RLC */
            ret = duBuildAndSendDlRrcMsgToRlc(cellId, ueCb->rlcUeCfg, ueCb->f1UeDb->dlRrcMsg);
            if(ret == RFAILED)
            {
               DU_LOG("\nERROR  -->  DU APP : Failed to send DL RRC msg in duProcUeContextSetupRequest()");
               DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueCb->f1UeDb->dlRrcMsg->rrcMsgPdu,\
                     ueCb->f1UeDb->dlRrcMsg->rrcMsgSize);
               DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueCb->f1UeDb->dlRrcMsg, sizeof(F1DlRrcMsg));
            }
         }
      }
      else if(ueCb->f1UeDb->actionType == UE_CTXT_SETUP)
      {
         ret = duBuildAndSendUeContextSetupReq(cellId, ueCb->crnti, &ueCb->f1UeDb->duUeCfg);
         if(ret == RFAILED)
         {
            DU_LOG("\nERROR  -->  DU APP : Failed to build ue context setup Req in duProcUeContextSetupRequest()");
         }
      }
   }
   else
   {
      //TODO: To send the failure cause in UeContextSetupRsp
      DU_LOG("ERROR  -->  DU APP : Failed to process UE CNTXT SETUP REQ at duProcUeContextSetupRequest()");
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Build and Send Ue context mod request
 *
 * @details
 *
 *
 *    Function : duBuildAndSendUeContextModReq
 *
 *    Functionality: 
 *     Build and Send Ue context mod request
 * 
 *  @params[in]  cellId, crnti, DuUeCfg pointer
 *  @return ROK     - success
 *          RFAILED - failure
 * 
 *****************************************************************/

uint8_t duBuildAndSendUeContextModReq(uint16_t cellId, uint16_t crnti, DuUeCfg *duUeCfg)
{
   uint8_t ret = ROK;

   DU_LOG("\nDEBUG   -->  DU_APP: Processing Ue Context Mod Request for cellId [%d]", cellId);
   /* Filling RLC Ue Reconfig */ 
   ret = duBuildAndSendUeReCfgReqToRlc(cellId, crnti, duUeCfg);
   if(ret == RFAILED)
      DU_LOG("\nERROR  -->  DU APP : Failed to build ctxt setup req for RLC at duBuildAndSendUeContextModReq()");
   
   /* Filling MAC Ue Reconfig */
   ret = duBuildAndSendUeReCfgReqToMac(cellId, crnti, duUeCfg);
   if(ret == RFAILED)
      DU_LOG("\nERROR  -->  DU APP : Failed at build ctxt setup req for MAC at duBuildAndSendUeContextModReq()");

   return ret;
}
/*******************************************************************
 *
 * @brief Processing Ue context mod request
 *
 * @details
 *
 *
 *    Function : duProcUeContextModReq 
 *
 *    Functionality:
 *        Processing  Ue context mod request
 *
 *  @params[in] DuUeCb *ueCb 
 *  @return ROK     - success
 *          RFAILED - failure
 *
 *****************************************************************/

uint8_t duProcUeContextModReq(DuUeCb *ueCb)
{
   uint8_t ret, cellId;

   ret = ROK;
   if(ueCb)
   {
      cellId = duCb.actvCellLst[ueCb->f1UeDb->cellIdx]->cellId;
      /* Send DL RRC msg for security Mode */
      if(ueCb->f1UeDb->dlRrcMsg)
      {
         if(ueCb->f1UeDb->dlRrcMsg->rrcMsgPdu)
         {
            /* Sending DL RRC Message to RLC */
            ret = duBuildAndSendDlRrcMsgToRlc(cellId, ueCb->rlcUeCfg, ueCb->f1UeDb->dlRrcMsg);
            if(ret == RFAILED)
            {
               DU_LOG("\nERROR  -->  DU APP : Failed to send DL RRC msg in duProcUeContextModReq()");
               DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueCb->f1UeDb->dlRrcMsg->rrcMsgPdu,\
                     ueCb->f1UeDb->dlRrcMsg->rrcMsgSize);
               DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueCb->f1UeDb->dlRrcMsg, sizeof(F1DlRrcMsg));
            }
         }
      }
      else
      {
         ret = duBuildAndSendUeContextModReq(cellId, ueCb->crnti, &ueCb->f1UeDb->duUeCfg);
         if(ret == RFAILED)
         {
            DU_LOG("\nERROR  -->  DU APP : Failed to build ue context setup Req in duProcUeContextModReq()");
         }
      }
   }
   else
   {
      //TODO: To send the failure cause in UeContextModRsp
      DU_LOG("ERROR  -->  DU APP : Failed to process UE CNTXT MOD REQ at duProcUeContextModReq()");
   }
   return ROK;
}

/*******************************************************************
*
* @brief Function to delete Pdsch ServCellCfg
*
* @details
*
*    Function : deletePdschServCellCfg
*
*    Functionality: Function to delete Pdsch ServCellCfg
*
* @params[in] PdschServCellCfg *pdschServCellCfg
* @return void
*
* ****************************************************************/

void deletePdschServCellCfg(PdschServCellCfg *pdschServCellCfg)
{
   DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,pdschServCellCfg->maxMimoLayers, sizeof(uint8_t));
   DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,pdschServCellCfg->maxCodeBlkGrpPerTb, sizeof(MaxCodeBlkGrpPerTB));
   DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,pdschServCellCfg->codeBlkGrpFlushInd, sizeof(bool));
   DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,pdschServCellCfg->xOverhead, sizeof(PdschXOverhead));
}

/*******************************************************************
 *
* @brief delete MacUeCfg from duCb
*
* @details
*
*    Function : deleteMacUeCfg 
*
*    Functionality: delete MacUeCfg from duCb
*
* @params[in] Pointer to MacUeCfg 
* @return ROK     - success
*         RFAILED - failure
*
*******************************************************************/

void deleteMacUeCfg(MacUeCfg *ueCfg)
{
   uint8_t lcCfgIdx;
   uint8_t resrcIdx;
   ServCellCfgInfo *servCellCfg;
   PucchResrcInfo *resrcToAddModList;

   if(ueCfg)
   {
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,ueCfg->ambrCfg, sizeof(AmbrCfg));
      if(ueCfg->spCellCfgPres)
      {
         servCellCfg = &ueCfg->spCellCfg.servCellCfg;
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->bwpInactivityTmr, sizeof(uint8_t));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.resrcSet,\
         sizeof(PucchResrcSetCfg));
         if(servCellCfg->initUlBwp.pucchCfg.resrc)
         {
            /*freeing the PucchResrcCfg*/
            for(resrcIdx= 0; resrcIdx< servCellCfg->initUlBwp.pucchCfg.resrc->resrcToAddModListCount; resrcIdx++)
            {
               resrcToAddModList=&servCellCfg->initUlBwp.pucchCfg.resrc->resrcToAddModList[resrcIdx];
               switch(resrcToAddModList->pucchFormat)
               {
                  case PUCCH_FORMAT_0:
                     {
                        DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,resrcToAddModList->PucchFormat.format0 ,\
                        sizeof(PucchFormat0));
                        break;
                     }
                  case PUCCH_FORMAT_1:
                     {
                        DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,resrcToAddModList->PucchFormat.format1 ,\
                        sizeof(PucchFormat1));
                        break;
                     }
                  case PUCCH_FORMAT_2:
                     {
                        DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,resrcToAddModList->PucchFormat.format2 ,\
                        sizeof(PucchFormat2_3));
                        break;
                     }
                  case PUCCH_FORMAT_3:
                     {
                        DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,resrcToAddModList->PucchFormat.format3 ,\
                        sizeof(PucchFormat2_3));
                        break;
                     }
                  case PUCCH_FORMAT_4:
                     {
                        DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,resrcToAddModList->PucchFormat.format4 ,\
                        sizeof(PucchFormat4));
                        break;
                     }
               }
            }
            DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.resrc,\
            sizeof(PucchResrcCfg));
         }
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.format1,\
         sizeof(PucchFormatCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.format2,\
         sizeof(PucchFormatCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.format3,\
         sizeof(PucchFormatCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.format4,\
         sizeof(PucchFormatCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.schedReq,\
         sizeof(PucchSchedReqCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.multiCsiCfg,\
         sizeof(PucchMultiCsiCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.spatialInfo,\
         sizeof(PucchSpatialCfg));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.dlDataToUlAck ,\
         sizeof(PucchDlDataToUlAck));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,servCellCfg->initUlBwp.pucchCfg.powerControl,\
         sizeof(PucchPowerControl));
         deletePdschServCellCfg(&servCellCfg->pdschServCellCfg);
      }
      for(lcCfgIdx=0; lcCfgIdx< ueCfg->numLcs; lcCfgIdx++)
      {
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,ueCfg->lcCfgList[lcCfgIdx].drbQos, sizeof(DrbQosInfo));
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,ueCfg->lcCfgList[lcCfgIdx].snssai, sizeof(Snssai));
      }
   }
   memset(ueCfg, 0, sizeof(MacUeCfg));
}

/*******************************************************************
*
* @brief delete UE Configuration of a particular UE
*
* @details
*
*    Function : deleteUeCfg 
*
*    Functionality: delete UE Configuration of a particular UE 
*
* @params[in] uint16_t cellIdx, uint8_t ueIdx
* @return ROK     - success
*         RFAILED - failure
*
* ****************************************************************/
uint8_t  deleteUeCfg(uint16_t cellIdx, uint8_t ueIdx)
{
   DuUeCb *ueCb = NULLP;
   if(duCb.actvCellLst[cellIdx] != NULLP)
   {
      if((duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].macUeCfg.macUeCfgState == UE_DELETE_COMPLETE)\
            &&(duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg.rlcUeCfgState == UE_DELETE_COMPLETE))
      {
         ueCb = &duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1];
         deleteMacUeCfg(&ueCb->macUeCfg);
         deleteRlcUeCfg(&ueCb->rlcUeCfg);
         if(ueCb->f1UeDb !=NULLP)
         {
            freeF1UeDb(ueCb->f1UeDb);
         }
         duCb.actvCellLst[cellIdx]->numActvUes--;
         memset(ueCb, 0, sizeof(DuUeCb));
      }
      else
      {
         DU_LOG("INFO  --> DU APP : deleteUeCfg(): MAC or RLC UE configuration state not UE_DELETE_COMPLETE");
         return RFAILED;
      }
   }
   else
   {
      DU_LOG("ERROR  --> DU APP : deleteUeCfg(): CellIdx[%d] is not found", cellIdx);
      return RFAILED;
   }
   return ROK;
}


/*******************************************************************
*
* @brief Handle UE delete response from MAC
*
* @details
*
*    Function : DuProcMacUeDeleteRsp
*
*    Functionality: Handle UE delete response from MAC
*
* @params[in] Pointer to MacUeDeleteRsp and Pst
* @return ROK     - success
*         RFAILED - failure
*
* ****************************************************************/

uint8_t DuProcMacUeDeleteRsp(Pst *pst, MacUeDeleteRsp *deleteRsp)
{
   uint8_t  ueIdx = 0,ret =ROK;
   uint16_t cellIdx=0;
   uint32_t gnbCuUeF1apId=0, gnbDuUeF1apId =0;

   if(deleteRsp)
   {
      if(deleteRsp->result == SUCCESS)
      {
         DU_LOG("\nINFO   -->  DU APP : MAC UE Delete Response : SUCCESS [UE IDX : %d]", deleteRsp->ueIdx);
         GET_CELL_IDX(deleteRsp->cellId, cellIdx);
         ueIdx = deleteRsp->ueIdx;
         if(duCb.actvCellLst[cellIdx])
         {
            duCb.actvCellLst[cellIdx]->ueCb[deleteRsp->ueIdx -1].macUeCfg.macUeCfgState = UE_DELETE_COMPLETE;
            gnbCuUeF1apId = duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbDuUeF1apId;
            gnbDuUeF1apId = duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbCuUeF1apId;
            if(deleteUeCfg(cellIdx, ueIdx) == ROK)
            {
                 ret = BuildAndSendUeContextReleaseComplete(gnbCuUeF1apId, gnbDuUeF1apId);
                 if(ret !=ROK)
                 {   
                    DU_LOG("\nERROR  -->  DU APP : DuProcMacUeDeleteRsp(): failed to send UE context release complete");
                 }
            }
         }
      }
      else
      {
         DU_LOG("\nERROR  -->  DU APP : DuProcMacUeDeleteRsp(): MAC UE Delete Response : FAILURE [UE IDX : %d]",\
         deleteRsp->ueIdx);
         ret =  RFAILED;
      }
      DU_FREE_SHRABL_BUF(pst->region, pst->pool, deleteRsp, sizeof(MacUeDeleteRsp));
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : DuProcMacUeDeleteRsp(): MAC UE Delete Response is null");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Processes UE Delete Rsp received from RLC 
 *
 * @details
 *
 *    Function : DuProcRlcUeDeleteRsp
 *
 *    Functionality:
 *     Processes UE Delete Rsp received from RLC 
 *
 *  @params[in]  Post structure
 *               Pointer to RlcUeDeleteRsp
 *  @return ROK     - success
 *          RFAILED - failure
 *
 * *****************************************************************/

uint8_t DuProcRlcUeDeleteRsp(Pst *pst, RlcUeDeleteRsp *delRsp)
{
   uint8_t  ueIdx = 0, ret = ROK;
   uint16_t cellIdx = 0;
   uint32_t gnbCuUeF1apId=0, gnbDuUeF1apId =0;   

   if(delRsp)
   {
      ueIdx = delRsp->ueIdx;
      GET_CELL_IDX(delRsp->cellId, cellIdx);

      if(delRsp->result == SUCCESSFUL)
      {
         DU_LOG("\nINFO   -->  DU_APP: RLC UE Delete Response : SUCCESS [UE IDX:%d]", ueIdx);
         if(duCb.actvCellLst[cellIdx]!=NULLP)
         {
            duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].rlcUeCfg.rlcUeCfgState = UE_DELETE_COMPLETE;
            gnbCuUeF1apId = duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbDuUeF1apId;
            gnbDuUeF1apId = duCb.actvCellLst[cellIdx]->ueCb[ueIdx-1].gnbCuUeF1apId;
            if(deleteUeCfg(cellIdx, ueIdx) == ROK)
            {
                ret = BuildAndSendUeContextReleaseComplete(gnbCuUeF1apId, gnbDuUeF1apId);
                if(ret != ROK)
                {
                   DU_LOG("\nERROR  -->  DU APP : DuProcMacUeDeleteRsp(): failed to send UE context release complete");
                }
            }
         }
      }
      else
      {
         DU_LOG("\nERROR   -->  DU_APP: RLC UE Delete Response : FAILED [UE IDX:%d]", ueIdx);
         ret = RFAILED;
      }
      DU_FREE_SHRABL_BUF(pst->region, pst->pool, delRsp, sizeof(RlcUeDeleteRsp));

   }
   return ret;
}

/*******************************************************************
 *
 * @brief Sending UE Delete Req To Mac
*
* @details
*
*    Function : sendUeDeleteReqToMac
*
*    Functionality:
*     sending UE Delete Req To Mac
*
*  @params[in]    cellId, ueIdx, crnti 
*  @return ROK     - success
*          RFAILED - failure
*
*****************************************************************/

uint8_t sendUeDeleteReqToMac(uint16_t cellId, uint8_t ueIdx, uint16_t crnti)
{
   Pst pst;
   uint8_t ret=ROK;
   MacUeDelete *ueDelete = NULLP;

   DU_ALLOC_SHRABL_BUF(ueDelete, sizeof(MacUeDelete));
   if(ueDelete)
   {
      ueDelete->cellId = cellId;
      ueDelete->ueIdx  = ueIdx;
      ueDelete->crnti  = crnti;
      FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_UE_DELETE_REQ);

      /* Processing one Ue at a time to MAC */
      DU_LOG("\nDEBUG  -->  DU_APP: Sending UE delete Request to MAC ");
      ret = (*packMacUeDeleteReqOpts[pst.selector])(&pst, ueDelete);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU_APP: sendUeDeleteReqToMac(): Failed to send UE delete Req to MAC");
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueDelete, sizeof(MacUeDelete));
      }
   }
   else
   {
      DU_LOG("\nERROR  -->   DU_APP: sendUeDeleteReqToMac(): Failed to allocate memory"); 
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Sending UE Delete Req To Rlc
 *
 * @details
 *
 *    Function : sendUeDeleteReqToRlc
 *
 *    Functionality:
 *     Sending UE Delete Req To Rlc
 *
 *  @params[in]  cellId, ueIdx 
 *  @return ROK     - success
 *          RFAILED - failure
 *
 *****************************************************************/

uint8_t sendUeDeleteReqToRlc(uint16_t cellId, uint8_t ueIdx)
{
   uint8_t ret;
   Pst pst;
   RlcUeDelete *ueDelete;

   DU_ALLOC_SHRABL_BUF(ueDelete, sizeof(RlcUeDelete));
   if(ueDelete !=NULLP)
   {
      ueDelete->cellId = cellId;
      ueDelete->ueIdx = ueIdx;
      FILL_PST_DUAPP_TO_RLC(pst, RLC_UL_INST, EVENT_RLC_UE_DELETE_REQ);

      ret = (*packRlcUeDeleteReqOpts[pst.selector])(&pst, ueDelete);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU_APP : sendUeDeleteReqToRlc():Failed to send UE Delete  Req to RLC"); 
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, ueDelete, sizeof(RlcUeDelete));
      }
   }
   else
   {
      DU_LOG("\nERROR  -->   DU_APP: sendUeDeleteReqToRlc():Memory allocation failed");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief DU processes UE delete req from CU and sends to MAC and RLC 
 *
 * @details
 *
 *    Function : duProcUeDeleteReq
 *
 *    Functionality: DU processes UE delete req from CU and sends to MAC 
 *                   and RLC 
 *
 * @params[in] cellId, crnti 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duProcUeDeleteReq(uint16_t cellId)
{
   uint8_t  ueIdx = 0, ueId =0;
   uint16_t cellIdx = 0, crnti   = 0;

   DU_LOG("\nDEBUG   -->  DU_APP: Processing UE Delete Request ");
   GET_CELL_IDX(cellId, cellIdx);
   GET_CRNTI(crnti,ueIdx);

   if(duCb.actvCellLst[cellIdx] != NULLP)
   {
      for(ueIdx =0;ueIdx< duCb.actvCellLst[cellIdx]->numActvUes; ueIdx++)
      {
         ueId = ueIdx+1;
         if(sendUeDeleteReqToRlc(cellId, ueId) == RFAILED)
         {
            DU_LOG("\nERROR  -->  DU APP : duProcUeDeleteReq():Failed to build UE  delete req for RLC ");
            return RFAILED;
         }

         GET_CRNTI(crnti,ueId);
         if(sendUeDeleteReqToMac(cellId, ueId, crnti) == RFAILED)
         {
            DU_LOG("\nERROR  -->  DU APP : duProcUeDeleteReq(): Failed to build UE  delete req for MAC ");
            return RFAILED;
         }
      }
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : duProcUeDeleteReq(): Cell Id is not found");
      return RFAILED;
   }

   return ROK;
}

/*******************************************************************
 *
 * @brief delete RlcUeCfg from duCb
 *
 * @details
 *
 *    Function : deleteRlcUeCfg
 *
 *    Functionality:
 *       delete  RlcUeCfg from duCb
 *
 *  @params[in] RlcUeCfg *ueCfg 
 *               
 *  @return ROK     - success
 *          RFAILED - failure
 *
 *****************************************************************/

void deleteRlcUeCfg(RlcUeCfg *ueCfg)
{
   uint8_t lcIdx = 0;
   RlcBearerCfg *lcCfg= NULLP;
   if(ueCfg)
   {
      for(lcIdx =0 ; lcIdx < ueCfg->numLcs ; lcIdx++)
      {
         lcCfg = &ueCfg->rlcLcCfg[lcIdx];
         switch(lcCfg->rlcMode)
         {
            case RLC_AM :
               {
                  DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, lcCfg->u.amCfg, sizeof(AmBearerCfg));
                  break;
               }
            case RLC_UM_BI_DIRECTIONAL :
               {
                  DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, lcCfg->u.umBiDirCfg, sizeof(UmBiDirBearerCfg));
                  break;
               }
            case RLC_UM_UNI_DIRECTIONAL_UL :
               {
                  DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, lcCfg->u.umUniDirUlCfg, sizeof(UmUniDirUlBearerCfg));
                  break;
               }
            case RLC_UM_UNI_DIRECTIONAL_DL :
               {
                  DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, lcCfg->u.umUniDirDlCfg, sizeof(UmUniDirDlBearerCfg));
                  break;
               }
         }
      }
      memset(ueCfg, 0, sizeof(RlcUeCfg));
   }
}

/*******************************************************************
 *
 * @brief Delete DU CellCb information 
 *
 * @details
 *
 *    Function : deleteDuCellCb
 *
 *    Functionality: Delete DU CellCb information
 *
 * @params[in] DuCellCb *cellCb
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

void deleteDuCellCb(DuCellCb *cellCb)
{

   if(cellCb->duMacCellCfg)
   {
      if(cellCb->duMacCellCfg->prachCfg.fdm[0].unsuedRootSeq)
      {
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, cellCb->duMacCellCfg->prachCfg.fdm[0].unsuedRootSeq,\
               cellCb->duMacCellCfg->prachCfg.fdm[0].numUnusedRootSeq);
      }
      if(cellCb->duMacCellCfg->sib1Cfg.sib1Pdu)
      {
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL,cellCb->duMacCellCfg->sib1Cfg.sib1Pdu,\
               cellCb->duMacCellCfg->sib1Cfg.sib1PduLen);
      }
      DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, cellCb->duMacCellCfg, sizeof(MacCellCfg));
   }
   memset(cellCb, 0, sizeof(DuCellCb));

}

/*******************************************************************
 *
 * @brief Handle Cell delete response from MAC
 *
 * @details
 *
 *    Function : DuProcMacCellDeleteRsp
 *
 *    Functionality: Handle Cell delete response from MAC
 *
 * @params[in] Pointer to MacCellDeleteRsp and Pst
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t DuProcMacCellDeleteRsp(Pst *pst, MacCellDeleteRsp *deleteRsp)
{
   uint8_t ret = ROK;
   uint16_t cellIdx=0;
   if(deleteRsp)
   {
      if(deleteRsp->result == SUCCESSFUL_RSP)
      {
         GET_CELL_IDX(deleteRsp->cellId, cellIdx);
         DU_LOG("\nINFO   -->  DU APP : MAC CELL Delete Response : SUCCESS [CELL IDX : %d]", deleteRsp->cellId);
         if(duCb.actvCellLst[cellIdx]->cellId == deleteRsp->cellId)
         {
            deleteDuCellCb(duCb.actvCellLst[cellIdx]);
            duCb.numActvCells--;
            DU_FREE(duCb.actvCellLst[cellIdx], sizeof(DuCellCb));
         }
         else
         {
            DU_LOG("\nERROR  -->  DU APP : DuProcMacCellDeleteRsp(): CellId [%d] doesnot exist", deleteRsp->cellId);
            ret = RFAILED;
         }
      }
      else
      {
         DU_LOG("\nERROR  -->  DU APP : DuProcMacCellDeleteRsp(): MAC CELL Delete Response : FAILED\
         [CELL IDX : %d]", deleteRsp->cellId);
         ret = RFAILED;
      }
      DU_FREE_SHRABL_BUF(pst->region, pst->pool, deleteRsp, sizeof(MacUeDeleteRsp));
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : DuProcMacCellDeleteRsp(): Received MAC cell delete response is NULL");
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Sending Cell Delete Req To Mac
 *
 * @details
 *
 *    Function : sendCellDeleteReqToMac
 *
 *    Functionality:
 *     sending Cell Delete Req To Mac
 *
 *  @params[in]    uint16_t cellId
 *  @return ROK     - success
 *          RFAILED - failure
 *
 *
 *****************************************************************/

uint8_t sendCellDeleteReqToMac(uint16_t cellId)
{
   Pst pst;
   uint8_t ret=ROK;
   MacCellDelete *cellDelete = NULLP;
   
   DU_ALLOC(cellDelete, sizeof(MacCellDelete));
   if(cellDelete)
   {
      cellDelete->cellId = cellId;
      FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_CELL_DELETE_REQ);

      DU_LOG("\nINFO   -->  DU APP : Sending Cell Delete Request to MAC");  
      /* Processing one Cell at a time to MAC */
      ret = (*packMacCellDeleteReqOpts[pst.selector])(&pst, cellDelete);
      if(ret == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU APP : sendCellDeleteReqToMac(): Failed to send Cell delete Req to MAC");
         DU_FREE_SHRABL_BUF(DU_APP_MEM_REGION, DU_POOL, cellDelete, sizeof(MacCellDelete));
      }
   }
   else
   {
      DU_LOG("\nERROR  -->   DU APP : sendCellDeleteReqToMac(): Failed to allocate memory"); 
      ret = RFAILED;
   }
   return ret;
}

/*******************************************************************
 *
 * @brief DU preocess Cell Delete Req to MAC 
 *
 * @details
 *
 *    Function : duProcCellDeleteReq 
 *
 *    Functionality: DU process Cell Delete Req to MAC 
 *
 * @params[in] uint16_t cellId
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t duProcCellDeleteReq(uint16_t cellId)
{
   uint16_t cellIdx = 0;
   
   DU_LOG("\nINFO   -->  DU APP : Processing Cell Delete Request ");
   GET_CELL_IDX(cellId, cellIdx);

   if(duCb.actvCellLst[cellIdx] != NULLP)
   {
      if(duBuildAndSendMacCellStop() == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU APP : duProcCellDeleteReq(): Failed to process Cell delete req for cellId[%d]",cellId);
         return RFAILED;
      }
      
      if(duCb.actvCellLst[cellIdx]->numActvUes)
      {
         DU_LOG("\nERROR  -->  DU APP : duProcCellDeleteReq(): Active UEs present Failed to process cell Delete\
         Req for cellID[%d]", cellId);
         return RFAILED;
      }
      if(sendCellDeleteReqToMac(cellId) == RFAILED)
      {
         DU_LOG("\nERROR  -->  DU APP : duProcCellDeleteReq(): Failed to build and send Cell delete req for MAC for\
         cellId[%d]",cellId);
         return RFAILED;
      }
   }
   else
   {
      DU_LOG("\nERROR  -->  DU APP : duProcCellDeleteReq(): CellId[%d] is not found", cellId);
      return RFAILED;
   }

   return ROK;
}

/**********************************************************************
  End of file
***********************************************************************/
