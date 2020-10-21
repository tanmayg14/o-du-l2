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
  
     Name:     general layer
  
     Type:     C file
  
     Desc:     Packing/Unpacking for structures, defined in cm_tkns.x
   
     File:     cm_tkns.c
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_mblk.h"
#include "cm_tkns.h"       /* common tokens */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_mblk.x"
#include "cm_tkns.x"       /* common tokens */

  

/*
 *      PACKING FUNCTIONS
 */


/*
 *
 *      Fun:   cmPkTknS16
 *
 *      Desc:  This function unpacks a token S16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
#ifdef ANSI
S16 cmPkTknS16
(
TknS16 *tknS16,             /* token S16 */
Buffer *mBuf                /* message buffer */
)
#else
S16 cmPkTknS16(tknS16, mBuf)
TknS16 *tknS16;             /* token S16 */
Buffer *mBuf;               /* message buffer */
#endif
{

   if (tknS16->pres)
   {
      /* Value */
      CMCHKPK(SPkS16, tknS16->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknS16->pres, mBuf);

   return ROK;
} /* end of cmPkTknS16 */
  

/*
 *
 *      Fun:   cmPkTknBStr32
 *
 *      Desc:  This function packs a token bit string of size 32
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknBStr32
(
TknBStr32 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
S16 cmPkTknBStr32(tknStr, mBuf)
TknBStr32 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{

   CMPKTKNBSTR(tknStr, mBuf);

   return ROK;

} /* end of cmPkTknBStr32 */

/*
 *
 *      Fun:   cmPkTknStr8
 *
 *      Desc:  This function packs a token string of size 8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStr8
(
TknStr8 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
S16 cmPkTknStr8(tknStr, mBuf)
TknStr8 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{

   CMPKTKNSTR(tknStr, mBuf);

   return ROK;

} /* end of cmPkTknStr8 */


/*
 *
 *      Fun:   cmPkTknStr16
 *
 *      Desc:  This function packs a token string of size 16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStr16
(
TknStr16 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
S16 cmPkTknStr16(tknStr, mBuf)
TknStr16 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{

   CMPKTKNSTR(tknStr, mBuf);

   return ROK;

} /* end of cmPkTknStr16 */


/*
 *
 *      Fun:   cmPkTknStrOSXL
 *
 *      Desc:  This function packs a Long Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrOSXL
(
TknStrOSXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmPkTknStrOSXL(tknStr, mBuf)
TknStrOSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;


   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(oduUnpackUInt8, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(oduUnpackUInt16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;

} /* end of cmPkTknStrOSXL */



/*
 *
 *      Fun:   cmPkTknStrBSXL
 *
 *      Desc:  This function packs a Long bit string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrBSXL
(
TknStrBSXL *tknStr,             /* token string */
Buffer     *mBuf              /* message buffer */
)
#else
S16 cmPkTknStrBSXL(tknStr, mBuf)
TknStrBSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;
   U16 len;


   if(tknStr->pres)
   {
      if (tknStr->len % 8)
         len = (tknStr->len/8) + 1;
      else
         len = (tknStr->len/8);
   
      /* Value */
      for (ndx = 0; ndx < len; ndx++)
      {
         CMCHKPK(oduUnpackUInt8, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(oduUnpackUInt16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;

} /* end of cmPkTknStrBSXL */

  
/*
 *
 *      Fun:   cmPkTknStrBMP4
 *
 *      Desc:  This function packs a BMP token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrBMP4
(
TknStrBMP4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmPkTknStrBMP4(tknStr, mBuf)
TknStrBMP4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;


   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(oduUnpackUInt16, tknStr->val[ndx], mBuf);
      }

      /* Length */
      CMCHKPK(oduUnpackUInt8, tknStr->len, mBuf);
   }

   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;
} /* end of cmPkTknStrBMP4 */


/*
 *
 *      Fun:   cmPkTknStrBMPXL
 *
 *      Desc:  This function packs a Long BMP Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrBMPXL
(
TknStrBMPXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmPkTknStrBMPXL(tknStr, mBuf)
TknStrBMPXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
#endif
{
   U16 ndx;


   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(oduUnpackUInt16, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(oduUnpackUInt16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;
} /* end of cmPkTknStrBMPXL */

  
/*
 *
 *      Fun:   cmPkTknStrUNI4
 *
 *      Desc:  This function packs a UNI token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrUNI4
(
TknStrUNI4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmPkTknStrUNI4(tknStr, mBuf)
TknStrUNI4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;


   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(oduUnpackUInt32, tknStr->val[ndx], mBuf);
      }

      /* Length */
      CMCHKPK(oduUnpackUInt8, tknStr->len, mBuf);
   }

   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;
} /* end of cmPkTknStrUNI4 */


/*
 *
 *      Fun:   cmPkTknStrUNIXL
 *
 *      Desc:  This function packs a Long UNI Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmPkTknStrUNIXL
(
TknStrUNIXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmPkTknStrUNIXL(tknStr, mBuf)
TknStrUNIXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
#endif
{
   U16 ndx;


   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(oduUnpackUInt32, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(oduUnpackUInt16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(oduUnpackUInt8, tknStr->pres, mBuf);

   return ROK;
} /* end of cmPkTknStrUNIXL */

/*
 *      UNPACKING FUNCTIONS
 */


/*
 *
 *      Fun:   cmUnpkTknS16
 *
 *      Desc:  This function unpacks a token S16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
#ifdef ANSI
S16 cmUnpkTknS16
(
TknS16 *tknS16,             /* token S16 */
Buffer *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknS16(tknS16, mBuf)
TknS16 *tknS16;             /* token S16 */
Buffer *mBuf;               /* message buffer */
#endif
{

   /* Token Header */
   CMCHKUNPK(oduPackUInt8, &tknS16->pres, mBuf);

   if (tknS16->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkS16, &tknS16->val, mBuf);
   }

   return ROK;
} /* end of cmUnpkTknS16 */
  

/*
 *
 *      Fun:   cmUnpkTknBStr32
 *
 *      Desc:  This function packs a token bit string of size 32
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknBStr32
(
TknBStr32 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknBStr32(tknStr, mBuf)
TknBStr32 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{

   CMUNPKTKNBSTR(tknStr, mBuf);

   return ROK;

} /* end of cmUnpkTknBStr32 */


/*
 *
 *      Fun:   cmUnpkTknStr8
 *
 *      Desc:  This function packs a token string of size 8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStr8
(
TknStr8 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknStr8(tknStr, mBuf)
TknStr8 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{

   CMUNPKTKNSTR(tknStr, mBuf);

   return ROK;

} /* end of cmUnpkTknStr8 */


/*
 *
 *      Fun:   cmUnpkTknStr16
 *
 *      Desc:  This function packs a token string of size 16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStr16
(
TknStr16 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknStr16(tknStr, mBuf)
TknStr16 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{

   CMUNPKTKNSTR(tknStr, mBuf);

   return ROK;

} /* end of cmUnpkTknStr16 */


/*
 *
 *      Fun:   cmUnpkTknStrOSXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrOSXL
(
TknStrOSXL *tknStr,             /* token string */
Buffer     *mBuf,               /* message buffer */
Ptr         ptr                 /* pointer to memory control block */
)
#else
S16 cmUnpkTknStrOSXL(tknStr, mBuf, ptr)
TknStrOSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
Ptr         ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;

   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt16, &tknStr->len, mBuf);

      if( cmGetMem(ptr, tknStr->len, (Ptr *)&tknStr->val) != ROK)
      {
         return RFAILED;
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(oduPackUInt8, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   return ROK;

} /* end of cmUnpkTknStrOSXL */



/*
 *
 *      Fun:   cmUnpkTknStrBSXL
 *
 *      Desc:  This function packs a long bit token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrBSXL
(
TknStrBSXL *tknStr,             /* token string */
Ptr         ptr,                /* pointer to memory control block */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknStrBSXL(tknStr, ptr, mBuf)
TknStrBSXL *tknStr;             /* token string */
Ptr         ptr;                /* pointer to control memory block */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;
   U16 len;


   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt16, &tknStr->len, mBuf);

      if (tknStr->len % 8)
         len = (tknStr->len/8) + 1;
      else
         len = (tknStr->len/8);
         
      if( cmGetMem(ptr, len, (Ptr *)&tknStr->val) != ROK)
      {
         return RFAILED;
      }
      /* Value */
      for (ndx = 1; ndx <= len; ndx++)
      {
         CMCHKUNPK(oduPackUInt8, &tknStr->val[len - ndx], mBuf);
      }
   }

   return ROK;

} /* end of cmUnpkTknStrBSXL */

  
/*
 *
 *      Fun:   cmUnpkTknStrBMP4
 *
 *      Desc:  This function unpacks a BMP token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrBMP4
(
TknStrBMP4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknStrBMP4(tknStr, mBuf)
TknStrBMP4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;


   /* Token Header */
   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt8, &tknStr->len, mBuf);

      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(oduPackUInt16, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   return ROK;
} /* end of cmUnpkTknStrBMP4 */


/*
 *
 *      Fun:   cmUnpkTknStrBMPXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrBMPXL
(
TknStrBMPXL *tknStr,             /* token string */
Buffer      *mBuf,               /* message buffer */
Ptr          ptr                 /* pointer to memory control block */
)
#else
S16 cmUnpkTknStrBMPXL(tknStr, mBuf, ptr)
TknStrBMPXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
Ptr          ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;


   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt16, &tknStr->len, mBuf);

      /* Each BMP Character is 2 octet long */
      if( cmGetMem(ptr, 2*(tknStr->len), (Ptr *)&tknStr->val) != ROK)
      {
         return RFAILED;
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(oduPackUInt16, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   return ROK;

} /* end of cmUnpkTknStrBMPXL */

  
/*
 *
 *      Fun:   cmUnpkTknStrUNI4
 *
 *      Desc:  This function unpacks a UNI token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrUNI4
(
TknStrUNI4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
S16 cmUnpkTknStrUNI4(tknStr, mBuf)
TknStrUNI4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;


   /* Token Header */
   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt8, &tknStr->len, mBuf);

      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(oduPackUInt32, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   return ROK;
} /* end of cmUnpkTknStrUNI4 */


/*
 *
 *      Fun:   cmUnpkTknStrUNIXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
S16 cmUnpkTknStrUNIXL
(
TknStrUNIXL *tknStr,             /* token string */
Buffer      *mBuf,               /* message buffer */
Ptr          ptr                 /* pointer to memory control block */
)
#else
S16 cmUnpkTknStrUNIXL(tknStr, mBuf, ptr)
TknStrUNIXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
Ptr          ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;


   CMCHKUNPK(oduPackUInt8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(oduPackUInt16, &tknStr->len, mBuf);

      /* Each UNI Character is 4 octets long */
      if( cmGetMem(ptr, 4*tknStr->len, (Ptr *)&tknStr->val) != ROK)
      {
         return RFAILED;
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(oduPackUInt32, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   return ROK;

} /* end of cmUnpkTknStrUNIXL */

/**********************************************************************
         End of file
**********************************************************************/
