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

/* This file stores defines used at RLC interface */
uint8_t fillRlcUeCfgRsp(RlcUeCfgRsp *rlcCfgRsp, RlcCfgCfmInfo *rlcCRsp);
uint8_t SendRlcUeCfgRspToDu(Pst *pst, RlcCfgCfmInfo *cfgRsp);
uint8_t sendRlcUeDeleteRspToDu(uint8_t ueIdx, uint16_t cellId, UeDeleteResult result);

/**********************************************************************
         End of file
**********************************************************************/
