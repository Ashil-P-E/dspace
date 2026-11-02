/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_SecOC_Internal.h
*
*   @brief SecOC feature data type and internal function declarations
*
*   @description
*       This file is the internal interface of the SecOC feature.
*       For further documentation refer to the public interface.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_SECOC_INTERNAL_H
#define DSBUSCUSTOMCODE_SECOC_INTERNAL_H

#include "DsBusCustomCode_Internal.h"
#include "DsBusCustomCode_SecOC.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DSCUSTOM_PDU_FEATURE_CUSTOM_CODE_PRE_CRC 0
#define DSCUSTOM_PDU_FEATURE_CUSTOM_CODE_POST_CRC 1
/* Definition of a SecOC feature type identifier */
#define DSCUSTOM_PDU_FEATURE_SECOC 2
/* Definition of a SecOC TX feature type identifier */
#define DSCUSTOM_PDU_FEATURE_SECOCTX 3
/* Definition of a SecOC RX feature type identifier */
#define DSCUSTOM_PDU_FEATURE_SECOCRX 4

/**
*   Base structure for all SecOC features.
*   For a description of the elements refer to
*   the corresponding set/get functions
*/
typedef struct
{
    uint32 KeyLength;
    uint32 KeyLengthIsSet;
    uint8* KeyPtr;
    uint32 KeyPtrIsSet;
    char* KeyAsString;
    uint32 KeyAsStringIsSet;
    sint32 AuthenticatorPositionOffset;
    uint32 AuthenticatorPositionOffsetIsSet;
} DsBusCustomCodeSecOCPduFeatureParameterStruct;

/**
*   Structure for SecOC TX features.
*   For a description of the elements refer to
*   the corresponding set/get functions
*/
typedef struct
{
    uint32 AuthenticationType;
    uint32 AuthenticationTypeIsSet;
    uint64 CalculatedFreshnessValue;
    uint32 CalculatedFreshnessValueIsSet;
    uint32 EnableAuthentication;
    uint32 EnableAuthenticationIsSet;
    uint32 EnableFreshnessValueCalculation;
    uint32 EnableFreshnessValueCalculationIsSet;
    sint64 FreshnessValueOffset;
    uint32 FreshnessValueOffsetIsSet;
    uint8* UserDefinedAuthenticatorPtr;
    uint32 UserDefinedAuthenticatorPtrIsSet;
    uint64 UserDefinedFreshnessValue;
    uint32 UserDefinedFreshnessValueIsSet;
} DsBusCustomCodeSecOCTxPduFeatureParameterStruct;

/**
*   Structure for SecOC RX features.
*   For a description of the elements refer to
*   the corresponding set/get functions
*/
typedef struct
{
    uint32 EnableVerification;
    uint32 EnableVerificationIsSet;
    uint32 VerificationResult;
    uint32 VerificationResultIsSet;
    uint64 CalculatedFreshnessValue;
    uint32 CalculatedFreshnessValueIsSet;
    sint64 FreshnessValueOffset;
    uint32 FreshnessValueOffsetIsSet;
} DsBusCustomCodeSecOCRxPduFeatureParameterStruct;

/**
*   Structure for IPDU parameters.
*   For a description of the elements refer to
*   the corresponding set/get functions
*/
typedef struct
{
    uint32 KeyId;
    uint32 KeyIdIsSet;
    DsBusCustomCodePduHandle AuthenticPdu;
    uint32 AuthenticPduIsSet;
    uint32 AuthInfoTxLength;
    uint32 AuthInfoTxLengthIsSet;
    uint32 FreshnessValueLength;
    uint32 FreshnessValueLengthIsSet;
    uint32 FreshnessValueTxLength;
    uint32 FreshnessValueTxLengthIsSet;
    boolean UseAsCryptographicIPdu;
    uint32 UseAsCryptographicIPduIsSet;
    uint16 DataId;
    uint32 DataIdIsSet;
    char* AuthAlgorithmNamePtr;
    uint32 AuthAlgorithmNamePtrIsSet;
    uint16 AuthDataFreshnessLength;
    uint32 AuthDataFreshnessLengthIsSet;
    uint16 AuthDataFreshnessStartPosition;
    uint32 AuthDataFreshnessStartPositionIsSet;
    uint16 AuthenticationBuildAttempts;
    uint32 AuthenticationBuildAttemptsIsSet;
    uint32 AuthenticationRetries;
    uint32 AuthenticationRetriesIsSet;
    uint32 FreshnessCounterSyncAttempts;
    uint32 FreshnessCounterSyncAttemptsIsSet;
    uint32 FreshnessTimestampPeriodFactor;
    uint32 FreshnessTimestampPeriodFactorIsSet;
    uint16 FreshnessValueId;
    uint32 FreshnessValueIdIsSet;
    uint16 MessageLinkLength;
    uint32 MessageLinkLengthIsSet;
    uint16 MessageLinkPosition;
    uint32 MessageLinkPositionIsSet;
    boolean RxSecurityVerification;
    uint32 RxSecurityVerificationIsSet;
    uint64 TimeStampRxAcceptanceWindow;
    uint32 TimeStampRxAcceptanceWindowIsSet;
    boolean UseAuthDataFreshness;
    uint32 UseAuthDataFreshnessIsSet;
    boolean UseFreshnessTimestamp;
    uint32 UseFreshnessTimestampIsSet;
    uint8  AuthPduHeaderLength;
    uint32 AuthPduHeaderLengthIsSet;
    uint32 SecuredAreaLength;
    uint32 SecuredAreaLengthIsSet;
    uint32 SecuredAreaOffset;
    uint32 SecuredAreaOffsetIsSet;
} DsBusCustomCodeSecuredIPduParameterStruct;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodePduParameterStruct Pdu;
    DsBusCustomCodeSecuredIPduParameterStruct SecuredIPdu;
} DsBusCustomCodeSecuredIPduInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeFeatureParameterStruct Feature;
    DsBusCustomCodePduFeatureParameterStruct PduFeature;
    DsBusCustomCodeSecOCPduFeatureParameterStruct SecOCPduFeature;
} DsBusCustomCodeSecOCPduFeatureInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeFeatureParameterStruct Feature;
    DsBusCustomCodePduFeatureParameterStruct PduFeature;
    DsBusCustomCodeSecOCPduFeatureParameterStruct SecOCPduFeature;
    DsBusCustomCodeSecOCTxPduFeatureParameterStruct SecOCTxPduFeature;
} DsBusCustomCodeSecOCTxPduFeatureInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeFeatureParameterStruct Feature;
    DsBusCustomCodePduFeatureParameterStruct PduFeature;
    DsBusCustomCodeSecOCPduFeatureParameterStruct SecOCPduFeature;
    DsBusCustomCodeSecOCRxPduFeatureParameterStruct SecOCRxPduFeature;
} DsBusCustomCodeSecOCRxPduFeatureInfoType;

/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_generateHandle(DsBusCustomCodePduHandle* PduHandle);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticPdu(DsBusCustomCodePduHandle PduHandle,
                                                          DsBusCustomCodePduHandle AuthenticPduHandle);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setDataId(DsBusCustomCodePduHandle PduHandle,
                                                    uint16 DataId);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setKeyId(DsBusCustomCodePduHandle PduHandle,
                                                   uint32 KeyId);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseAsCryptographicPdu(DsBusCustomCodePduHandle PduHandle,
                                                                   boolean UseAsCryptographicPdu);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthInfoTxLength(DsBusCustomCodePduHandle PduHandle,
                                                              uint32 AuthInfoTxLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueLength(DsBusCustomCodePduHandle PduHandle,
                                                                  uint32 FreshnessValueLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueTxLength(DsBusCustomCodePduHandle PduHandle,
                                                                    uint32 FreshnessValueTxLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthAlgorithmName(DsBusCustomCodePduHandle PduHandle,
                                                               char* AuthAlgorithmName);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthDataFreshnessLength(DsBusCustomCodePduHandle PduHandle,
                                                                     uint16 AuthDataFreshnessLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthDataFreshnessStartPosition(DsBusCustomCodePduHandle PduHandle,
                                                                            uint16 AuthDataFreshnessStartPosition);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticationBuildAttempts(DsBusCustomCodePduHandle PduHandle,
                                                                         uint16 AuthenticationBuildAttempts);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticationRetries(DsBusCustomCodePduHandle PduHandle,
                                                                   uint32 AuthenticationRetries);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessCounterSyncAttempts(DsBusCustomCodePduHandle PduHandle,
                                                                          uint32 FreshnessCounterSyncAttempts);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessTimestampPeriodFactor(DsBusCustomCodePduHandle PduHandle,
                                                                            uint32 FreshnessTimestampPeriodFactor);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueId(DsBusCustomCodePduHandle PduHandle,
                                                              uint16 FreshnessValueId);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setMessageLinkLength(DsBusCustomCodePduHandle PduHandle,
                                                               uint16 MessageLinkLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setMessageLinkPosition(DsBusCustomCodePduHandle PduHandle,
                                                                 uint16 MessageLinkPosition);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setRxSecurityVerification(DsBusCustomCodePduHandle PduHandle,
                                                                    boolean RxSecurityVerification);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setTimeStampRxAcceptanceWindow(DsBusCustomCodePduHandle PduHandle,
                                                                         uint64 TimeStampRxAcceptanceWindow);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseAuthDataFreshness(DsBusCustomCodePduHandle PduHandle,
                                                                  boolean UseAuthDataFreshness);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseFreshnessTimestamp(DsBusCustomCodePduHandle PduHandle,
                                                                   boolean UseFreshnessTimestamp);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthPduHeaderLength(DsBusCustomCodePduHandle PduHandle,
                                                                 uint8 AuthPduHeaderLength);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setSecuredAreaOffset(DsBusCustomCodePduHandle PduHandle,
                                                               uint32 SecuredAreaOffset);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecuredIPdu_setSecuredAreaLength(DsBusCustomCodePduHandle PduHandle,
                                                               uint32 SecuredAreaLength);

#if defined(HOST_DEBUG)
Std_ReturnType DsBusCustomCodeSecOCPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle);
#endif

/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyAsString(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                             const char* KeyAsString);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCPduFeature_setAuthenticatorPositionOffset(DsBusCustomCodePduFeatureHandle Handle,
                                                                             sint32 AuthenticatorPositionOffset);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setAuthenticationType(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32 AuthenticationType);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setEnableAuthentication(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        uint32 EnableAuthentication);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setEnableFreshnessValueCalculation(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                                   uint32 EnableFreshnessValueCalculation);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setFreshnessValueOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        sint64 FreshnessValueOffset);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setUserDefinedAuthenticatorPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                               uint8* UserDefinedAuthenticatorPtr);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setUserDefinedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             uint64 UserDefinedFreshnessValue);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle);
/* Refer to the corresponding get function in the public interface for further documentation. */
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setEnableVerification(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32 EnableVerification);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_SECOC_INTERNAL_H */
