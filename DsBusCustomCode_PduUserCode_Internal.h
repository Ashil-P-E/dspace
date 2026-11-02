/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_PduUserCode_Internal.h
*
*   @brief PduUserCode data type and function declarations
*
*   @description
*       This file is the internal interface of the PDU User Code feature.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_PDUUSERCODE_INTERNAL_H
#define DSBUSCUSTOMCODE_PDUUSERCODE_INTERNAL_H

#include "DsBusCustomCode_Internal.h"
#include "DsBusCustomCode_PduUserCode.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DSCUSTOM_PDU_FEATURE_USERCODE 5

typedef struct {
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeFeatureParameterStruct Feature;
    DsBusCustomCodePduFeatureParameterStruct PduFeature;
    DsBusCustomCodeSignalHandle* Signals;
    uint32 SignalsIsSet;
    uint32 SignalsCount;
    uint32 SignalsCountIsSet;
    uint32 Result;
    uint32 ResultIsSet;
    DsBusCustomCodeUserPortHandle* UserPorts;
    uint32 UserPortsIsSet;
    uint32 UserPortsCount;
    uint32 UserPortsCountIsSet;
} DsBusCustomCodeUserCodePduFeatureInfoType;

Std_ReturnType DsBusCustomCodeUserCodePduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle);
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle, DsBusCustomCodeSignalHandle* Data);
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setNumberOfUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle, uint32 Data);

/* User Ports */
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle, DsBusCustomCodeUserPortHandle* Data);																
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setNumberOfUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle, uint32 Data);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_PDUUSERCODE_INTERNAL_H */
