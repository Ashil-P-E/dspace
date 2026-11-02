/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_SecOC.h
*
*   @brief SecOC feature data type and function declarations to be used in user code
*
*   @description
*       This file is the public interface of the SecOC feature.
*       Before it is included in the user code,
*       DS_BUS_CUSTOM_FEATURE_NAME must be defined in the respective user code.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_SECOC_H
#define DSBUSCUSTOMCODE_SECOC_H

#include "DsBusCustomCode_Internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** <!------------------------------------------------------------------------->
*   Get the authentic PDU related to the secured IPDU.
*
*   @description
*   - This function gets a handle to the authentic PDU which is related to the
*     provided secured IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePduFeature_getPdu()
*
*   @code
*   // The PduFeatureHandle is typically provided as a parameter of an interface
*   // call, e.g. DsBusCustomCode_onApplicationInit
*   DsBusCustomCodePduHandle securedIPdu_PduHandle, authenticIPdu_PduHandle;
*   DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &securedIPdu_PduHandle);
*   DsBusCustomCodeSecuredIPdu_getAuthenticPdu(securedIPdu_PduHandle, &authenticIPdu_PduHandle);
*   @endcode
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthenticPduHandle The PDU handle of the authentic PDU related to
*                                 the provided secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticPdu(DsBusCustomCodePduHandle PduHandle,
                                                          DsBusCustomCodePduHandle* AuthenticPduHandle);

/** <!------------------------------------------------------------------------->
*   Get the data ID of a secured IPDU.
*
*   @description
*   - This function gets the data ID of a secured IPDU, this is a unique
*     numerical identifier.
*   - The data ID of the secured IPDU is typically included in the authenticator
*     calculation.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getKeyId()
*
*   @code
*   DsBusCustomCodePduHandle securedIPdu_PduHandle;
*   DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &securedIPdu_PduHandle);
*   DsBusCustomCodeSecuredIPdu_getDataId(securedIPdu_PduHandle, &dataId);
*   // ... prepare authentication data including data ID and generate MAC
*   @endcode
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param DataId The data ID of the secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getDataId(DsBusCustomCodePduHandle PduHandle,
                                                    uint16* DataId);

/** <!------------------------------------------------------------------------->
*   Get the key ID of a secured IPDU.
*
*   @description
*   - The key ID is used to assign keys to a specific key slot.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getDatId()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param KeyId The key ID
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getKeyId(DsBusCustomCodePduHandle PduHandle,
                                                   uint32* KeyId);

/** <!------------------------------------------------------------------------->
*   Is the secured IPDU used as cryptographic IPDU?
*
*   @description
*   - Get whether the secured IPDU is used as a cryptographic IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param UseAsCryptographicIPdu TRUE, if the secured IPDU is used as
*                                     cryptographic IPDU, otherwise FALSE
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseAsCryptographicPdu(DsBusCustomCodePduHandle PduHandle,
                                                                   boolean* UseAsCryptographicIPdu);

/** <!------------------------------------------------------------------------->
*   Get the length in bits of the authenticator that is included in the payload
*   of the secured IPDU.
*
*   @description
*   - This function gets the number of bits of the authenticator that can
*     be included in the payload of the secured IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getFreshnessValueLength()
*
*   @code
*   uint32 authInfoTxLength;
*   DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength(securedIPdu_PduHandle, &authInfoTxLength);
*   // Copy authInfoTxLength number of bits of authenticator to secured IPDU
*   @endcode
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthInfoTxLength The length in bits of the authenticator that is
*                               included in the payload of the secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength(DsBusCustomCodePduHandle PduHandle,
                                                              uint32* AuthInfoTxLength);

/** <!------------------------------------------------------------------------->
*   Get the length of the freshness value in bits.
*
*   @description
*   - The length of the freshness value in bits.
*   - This is usually larger than the number of bits of the freshness value
*     that are transmitted.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param FreshnessValueLength Length of freshness value in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueLength(DsBusCustomCodePduHandle PduHandle,
                                                                  uint32* FreshnessValueLength);

/** <!------------------------------------------------------------------------->
*   Get the length in bits of the freshness value that is included in the
*   payload of the secured IPDU.
*
*   @description
*   - The number of bits of the freshness value that are actually transmitted.
*   - This is usually smaller than the number of bits of the freshness value.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength()
*   - #DsBusCustomCodeSecuredIPdu_getFreshnessValueLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param FreshnessValueTxLength Length in bits of the freshness value that
*                                     is included in the payload of the secured
*                                     IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueTxLength(DsBusCustomCodePduHandle PduHandle,
                                                                    uint32* FreshnessValueTxLength);

/** <!------------------------------------------------------------------------->
*   Get the name of the SecOc algorithm defined in the communication matrix.
*
*   @description
*   - This attribute is available as of AUTOSAR 4.3.0: "CMAC" or "AES-128"
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength()
*   - #DsBusCustomCodeSecuredIPdu_getFreshnessValueLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthAlgorithmNameAsString The name of the authentication
*                                        algorithm to be used
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthAlgorithmName(DsBusCustomCodePduHandle PduHandle,
                                                               char** AuthAlgorithmNameAsString);

/** <!------------------------------------------------------------------------->
*   Get a Boolean value that indicates if a part of the authentic PDU must be
*   passed to the SWC that verifies and generates the freshness value.
*
*   @description
*    - This attribute describes whether a part of the authentic PDU contained in a
*      secured IPDU must be passed to the SWC that verifies and generates the
*      freshness value. The part of the authentic PDU is defined by the
*      authDataFreshnessStartPosition and authDataFreshnessLength.
*    - If it is set to TRUE, the SecOCAuthDataFreshnessStartPosition and
*      SecOCAuthDataFreshnessLen parameters must be set to specify the bit position
*      and length within the authentic PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessLength()
*   - #DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessStartPosition()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param UseAuthDataFreshness The value for this switch
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseAuthDataFreshness(DsBusCustomCodePduHandle PduHandle,
                                                                  boolean* UseAuthDataFreshness);

/** <!------------------------------------------------------------------------->
*   Get the length of the external authentic PDU data in bits defined in the
*   communication matrix.
*
*   @description
*   - This attribute defines the length in bits of the authentic PDU data
*     passed to the SWC that verifies and generates the freshness value.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getUseAuthDataFreshness()
*   - #DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessStartPosition()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthDataFreshnessLength The length of the external authentic PDU
*                                      data in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessLength(DsBusCustomCodePduHandle PduHandle,
                                                                     uint16* AuthDataFreshnessLength);

/** <!------------------------------------------------------------------------->
*   Get the start position in bits of the authentic PDU that must be
*   passed to the SWC that verifies and generates the freshness value.
*
*   @description
*   - This value determines the start position in bits of the authentic PDU that
*     must be passed on to the SWC that verifies and generates the freshness value.
*   - The bit position starts counting from the MSB of the first byte of the PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getUseAuthDataFreshness()
*   - #DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthDataFreshnessStartPosition The start position in bits of the
*                                             authentic PDU that must be passed
*                                             to the SWC that verifies and generates
*                                             the freshness value.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessStartPosition(DsBusCustomCodePduHandle PduHandle,
                                                                            uint16* AuthDataFreshnessStartPosition);

/** <!------------------------------------------------------------------------->
*   Get the number of authentication build attempts.
*
*   @description
*   - This attribute specifies the number of authentication build attempts.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthenticationBuildAttempts The number of authentication build
*                                          attempts
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticationBuildAttempts(DsBusCustomCodePduHandle PduHandle,
                                                                         uint16* AuthenticationBuildAttempts);

/** <!------------------------------------------------------------------------->
*   Get the number of additional authentication attempts.
*
*   @description
*   - This attribute defines the additional number of authentication attempts
*     that are to be carried out if the generation of the authentication
*     information failed for a given secured IPDU.
*   - If set to zero, only one authentication attempt is done.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthenticationBuildAttempts()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthenticationRetries The number of authentication attempts
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticationRetries(DsBusCustomCodePduHandle PduHandle,
                                                                   uint32* AuthenticationRetries);

/** <!------------------------------------------------------------------------->
*   Get the number of resynchronization attempts for the freshness counter.
*
*   @description
*   - This attribute defines the number of resynchronization attempts for the
*     freshness counter if a verification failed for a secured IPDU.
*   - If set to zero, there will be no additional verification attempt
*     to synchronize with a potentially better fitting freshness counter value.
*   - This attribute is only applicable if useFreshnessTimestamp is FALSE.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param FreshnessCounterSyncAttempts The number of resynchronization attempts
*                                           for the freshness counter
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessCounterSyncAttempts(DsBusCustomCodePduHandle PduHandle,
                                                                          uint32* FreshnessCounterSyncAttempts);

/** <!------------------------------------------------------------------------->
*   Get the factor that specifies the time period for the freshness time stamp.
*
*   @description
*   - This attribute defines a factor that specifies the time period for the
*     freshness time stamp.
*   - It holds a multiplication factor that specifies the concrete meaning of a
*     freshness time stamp increment by one on basis of microseconds.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param FreshnessTimestampPeriodFactor The factor that specifies the
*                                             time period for the freshness
*                                             time stamp
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessTimestampPeriodFactor(DsBusCustomCodePduHandle PduHandle,
                                                                            uint32* FreshnessTimestampPeriodFactor);

/** <!------------------------------------------------------------------------->
*   Get the ID of the freshness value.
*
*   @description
*   - This parameter defines the ID of the freshness value.
*   - The freshness value might be a normal counter or a time stamp value.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param FreshnessValueId The ID of the freshness value
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueId(DsBusCustomCodePduHandle PduHandle,
                                                              uint16* FreshnessValueId);

/** <!------------------------------------------------------------------------->
*   Get the length of the message linker of the authentic PDU in bits.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - DsBusCustomCodeSecuredIPdu_getMessageLinkPosition()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param MessageLinkLength The length of the message linker of the
*                                authentic PDU (in bits)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getMessageLinkLength(DsBusCustomCodePduHandle PduHandle,
                                                               uint16* MessageLinkLength);

/** <!------------------------------------------------------------------------->
*   Get the position of the message linker inside the authentic PDU in bits.
*
*   @note
*   - Thread-safe: yes
*   - Intended usage: during runtime
*   - Execution time: deterministic
*
*   @see
*   - DsBusCustomCodeSecuredIPdu_getMessageLinkLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param MessageLinkPos The position of the message linker inside the
*                             authentic PDU in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getMessageLinkPosition(DsBusCustomCodePduHandle PduHandle,
                                                                 uint16* MessageLinkPos);

/** <!------------------------------------------------------------------------->
*   Get the length of the secured PDU header in the secured IPDU.
*
*   @description
*   - The length (in bytes) of the secured PDU header in the secured IPDU.
*   - A length of zero means there is no secured PDU header in the secured IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthPduHeaderLength The length of the secured PDU header in
*                                  the secured IPDU (in bytes)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthPduHeaderLength(DsBusCustomCodePduHandle PduHandle,
                                                                 uint8* AuthPduHeaderLength);

/** <!------------------------------------------------------------------------->
*   Get the length of the secured area
*
*   @description
*   - The length (in bytes) of the secured area in the secured IPDU.
*   - The length of zero means there is no secured area in the secured IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param SecuredAreaLength The length of the secured area in
*                                the secured IPDU (in bytes)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getSecuredAreaLength(DsBusCustomCodePduHandle PduHandle,
                                                               uint32* SecuredAreaLength);

/** <!------------------------------------------------------------------------->
*   Get the length of the secured PDU header in the secured IPDU.
*
*   @description
*   - The length (in bytes) of the secured PDU header in the secured IPDU.
*   - The length of zero means there is no secured PDU header in the secured IPDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param AuthPduHeaderLength The length of the secured PDU header in the
*                                  secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getSecuredAreaOffset(DsBusCustomCodePduHandle PduHandle,
                                                               uint32* SecuredAreaOffset);

/** <!------------------------------------------------------------------------->
*   Get the value that indicates whether the authentication information of a
*   secured IPDU is verified on the receiver side.
*
*   @description
*   - This attribute describes whether the authentication information of a secured
*     IPDU is verified on the receiver side
*     (IPduPort with communicationDirection = in).
*   - If this attribute is set to false, the secured IPDU will be routed by the
*     PduR directly to the COM module in the receiving ECU and the SecOC module
*     will not be used.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param RxSecurityVerification The value whether the authentication
*                                     information of a secured IPDU is
*                                     verified on the receiver side
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getRxSecurityVerification(DsBusCustomCodePduHandle PduHandle,
                                                                    boolean* RxSecurityVerification);

/** <!------------------------------------------------------------------------->
*   Get the maximum allowed deviation from the expected time stamp.
*
*   @description
*   - This attribute is used to define the maximum allowed deviation from the
*     expected time stamp in the SecOC module for which a secured IPDU is still
*     deemed authentic.
*   - The value of TimeStampRxAcceptanceWindow in AUTOSAR 4.2.2 represents the
*     allowed deviation in seconds, in this case milliseconds are assumed.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param TimeStampRxAcceptanceWindow The maximum allowed deviation
*                                          from the expected time stamp
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getTimeStampRxAcceptanceWindow(DsBusCustomCodePduHandle PduHandle,
                                                                         uint64* TimeStampRxAcceptanceWindow);

/** <!------------------------------------------------------------------------->
*   Get the value for using time stamps or a counter for generating the
*   freshness value.
*
*   @description
*   - This attribute specifies whether the freshness value is generated by a
*     freshness counter or by a time stamp.
*   - The value is set to TRUE when time stamps are used.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param UseFreshnessTimestamp The value for using time stamps (TRUE) or
*                                    counter (FALSE) for generating a freshness
*                                    value
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseFreshnessTimestamp(DsBusCustomCodePduHandle PduHandle,
                                                                   boolean* UseFreshnessTimestamp);

/** <!------------------------------------------------------------------------->
*   Get a SecOC key defined in the communication matrix for a specific PDU.
*
*   @description
*   - This function allows the user to get a SecOC key related to a specific PDU
*     as string, which is defined in the communication matrix in an appropriate
*     way.
*   - The user might parse the key in a user-defined C function and set the
*     resulting byte array for the respective key by using the
*     DsBusCustomCodeSecOCPduFeature_setKeyLength and
*     DsBusCustomCodeSecOCPduFeature_setKeyPtr functions.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_setKeyLength()
*   - #DsBusCustomCodeSecOCPduFeature_setKeyPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyAsString The key defined in the communication matrix as char*
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyAsString(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                             char** KeyAsString);

/** <!------------------------------------------------------------------------->
*   Set the key length of a SecOC key for a specific PDU.
*
*   @description
*   - This function allows the user to set the length of a SecOC key byte array
*     related to a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_getKeyAsString()
*   - #DsBusCustomCodeSecOCPduFeature_setKeyPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyLength The length of the key in bytes
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g.,a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyLength(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint32 KeyLength);

/** <!------------------------------------------------------------------------->
*   Set the pointer to a SecOC key byte array for a specific PDU.
*
*   @description
*   - This function allows the user to set the pointer to a SecOC key byte array
*     related to a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_getKeyAsString()
*   - #DsBusCustomCodeSecOCPduFeature_setKeyLength()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyPtr The pointer to the key byte array
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                        uint8* KeyPtr);

/** <!------------------------------------------------------------------------->
*   Get the key length of a SecOC key for a specific PDU
*
*   @description
*   - This function gets the length of a SecOC key byte array related to a
*     specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_setKeyLength()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyLength The length of the key in bytes
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyLength(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint32* KeyLength);

/** <!------------------------------------------------------------------------->
*   Get the pointer to a SecOC key byte array for a specific PDU.
*
*   @description
*   - This function gets the pointer to a SecOC key byte array related
*     to a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_setKeyPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyPtr The pointer to the key byte array
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                        uint8** KeyPtr);

/** <!------------------------------------------------------------------------->
*   Get the AuthenticatorPositionOffset parameter in bits of a specific PDU.
*
*   @description
*   - This function gets the AuthenticatorPositionOffset parameter of a specific
*     SecOC related PDU.
*   - For inspection purpose only.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_setAuthenticatorPositionOffset()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param KeyPtr The pointer to the key byte array
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_getAuthenticatorPositionOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             sint32* AuthenticatorPositionOffset);

/** <!------------------------------------------------------------------------->
*   Set the AuthenticatorPositionOffset parameter in bits of a specific PDU.
*
*   @description
*   - This function applies AuthenticatorPositionOffset parameter to a SecOC
*     related PDU.
*   - Provides inspection of the actual transmitted Authenticator
*     and Freshness Values, even if their position is differing from the position
*     defined by AUTOSAR.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCPduFeature_getAuthenticatorPositionOffset()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param AuthenticatorPositionOffset The AuthenticatorPositionOffset
*                                          parameter, default value 0
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCPduFeature_setAuthenticatorPositionOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             sint32 AuthenticatorPositionOffset);

/** <!------------------------------------------------------------------------->
*   Get the enable authentication value for a specific TX PDU set by the user
*   via TRC and/or model.
*
*   @description
*   - This function gets the value of the enable authentication variable set by
*     the user via TRC and/or the model.
*   - The user code should use this variable to decide, whether authenticator
*     calculation shall be performed or a user-defined authenticator value
*     (refer to UserDefinedAuthenticatorPtr) shall be used.
*   - The detailed behavior depends on the user code implementation.
*   - It is proposed to use the value zero for disabling the authenticator
*     calculation and using the UserDefinedAuthenticatorPtr instead and non-zero
*     values to enable authenticator calculation in the user code.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCTxPduFeature_getUserDefinedAuthenticatorPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param EnableAuthentication The value of the enable authentication
*                                   variable set by the user via TRC and/or
*                                   the model.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getEnableAuthentication(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        uint32* EnableAuthentication);

/** <!------------------------------------------------------------------------->
*   Get the user-defined authenticator value for a specific TX PDU set by the
*   user via TRC and/or the model.
*
*   @description
*   - This function gets the value of the user-defined authenticator set by the
*     user via TRC and/or the model as pointer to a byte array.
*   - The length of the byte array in bytes must be defined at least
*     as (FreshnessValueTxLength + 7) / 8.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCTxPduFeature_getEnableAuthentication()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param UserDefinedAuthenticatorPtr The pointer to the user-defined
*                                          authenticator byte array set by the
*                                          user via TRC and/or model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getUserDefinedAuthenticatorPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                               uint8** UserDefinedAuthenticatorPtr);

/** <!------------------------------------------------------------------------->
*   Get the authentication type value for a specific TX PDU set by the user via
*   TRC and/or the model.
*
*   @description
*   - This function gets the value of the authentication type variable set by
*     the user via TRC and/or the model.
*   - The user code must use this variable to decide how the
*     authenticator calculation must be performed.
*   - The detailed behavior depends on the user code implementation.
*   - It is proposed to use the zero value for a correct authenticator
*     calculation and non-zero values to enable authenticator invalidation in the
*     user code.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param AuthenticationType The value of the authentication type variable
*                                 set by the user via TRC and/or the model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getAuthenticationType(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32* AuthenticationType);

/** <!------------------------------------------------------------------------->
*   Get the enable freshness value calculation value for a specific TX PDU set
*   by the user via TRC and/or the model.
*
*   @description
*   - This function gets the value of the enable freshness value calculation
*     variable set by the user via TRC and/or the model.
*   - The user code must use this variable to decide whether a freshness value
*     calculation must be performed (e.g., by retrieving a time value from a
*     component providing a freshness time stamp) or a user-defined freshness
*     value (refer to UserDefinedFreshnessValue) must be used.
*   - The detailed behavior depends on the user code implementation.
*   - It is proposed to use the zero value for disabling the freshness value
*     calculation and using the UserDefinedFreshnessValue instead and non-zero
*     values to enable freshness value calculation in the user code.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCTxPduFeature_getUserDefinedFreshnessValue()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param EnableFreshnessValueCalculation The value of the enable
*                                              freshness value calculation
*                                              variable set by the user
*                                              via TRC and/or the model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getEnableFreshnessValueCalculation(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                                   uint32* EnableFreshnessValueCalculation);

/** <!------------------------------------------------------------------------->
*   Get the freshness value for a specific TX PDU set by the user
*   via TRC and/or the model.
*
*   @description
*   - This function gets the value of the freshness value set by
*     the user via TRC and/or model.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCTxPduFeature_getEnableFreshnessValueCalculation()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param UserDefinedFreshnessValue The freshness value set by
*                                        the user via TRC and/or the model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getUserDefinedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             uint64* UserDefinedFreshnessValue);

/** <!------------------------------------------------------------------------->
*   Get the offset for the freshness value for a specific TX PDU set by the
*   user via TRC and/or the model.
*
*   @description
*   - This function gets the offset for the freshness value set by the user via
*     TRC and/or the model.
*   - The user code must add this offset to the freshness value derived by
*     freshness value calculation or from the UserDefinedFreshnessValue.
*   - Both positive and negative offsets are possible.
*     Setting the offset to zero leads to the original freshness value to be used.
*   - The detailed behavior depends on the user code implementation.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param FreshnessValueOffset The value of the freshness value offset
*                                   variable set by the user via TRC and/or
*                                   the model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getFreshnessValueOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        sint64* FreshnessValueOffset);

/** <!------------------------------------------------------------------------->
*   Set the freshness value calculated in the user code for a specific TX PDU
*
*   @description
*   - This function allows the user code to set the freshness value that is
*     used for the authentication.
*   - This value can be provided to the user as TRC and/or model variable.
*   - The detailed behavior depends on the user code implementation.
*
*   @note
*   - Thread-safe: yes
*   - Intended usage: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param CalculatedFreshnessValue The freshness value calculated in
*                                       the user code.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                            uint64 CalculatedFreshnessValue);

/** <!------------------------------------------------------------------------->
*   Get the freshness value calculated in the user code for a specific RX PDU.
*
*   @description
*   - This function allows the user code to get the calculated freshness value
*     set by DsBusCustomCodeSecOCTxPduFeature_setCalculatedFreshnessValue.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCTxPduFeature_setCalculatedFreshnessValue()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param CalculatedFreshnessValue The freshness value calculated in the
*                                       user code.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                            uint64* CalculatedFreshnessValue);

/** <!------------------------------------------------------------------------->
*   Get the enable verification value for a specific RX PDU set by the user via
*   TRC and/or model.
*
*   @description
*   - This function gets the value of the enable verification variable set by
*     the user via TRC and/or the model.
*   - The user code must use this variable to decide whether verification
*     must be performed.
*   - The detailed behavior depends on the user code implementation.
*   - It is proposed to use the zero value for disabling the verification
*     calculation and a non-zero value to enable verification in the user code.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param EnableVerification The value of the enable verification variable
*                                 set by the user via TRC and/or the model
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getEnableVerification(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32* EnableVerification);

/** <!------------------------------------------------------------------------->
*   Set the verification result for a specific RX PDU
*
*   @description
*   - This function allows the user code to set the verification result for a
*     specific RX PDU.
*   - This value can be provided to the user as TRC and/or model variable.
*   - The detailed behavior depends on the user code implementation.
*   - It is proposed to use the following result values:
*     SECOC_VERIFICATIONSUCCESS     0x00
*     SECOC_VERIFICATIONFAILURE     0x01
*     SECOC_FRESHNESSFAILURE        0x02
*     SECOC_VERIFICATIONNOTEXECUTED 0x3F (if verification is disabled)
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCRxPduFeature_getVerificationResult()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param VerificationResult The verification result calculated in the
*                                 user code
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setVerificationResult(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32 VerificationResult);

/** <!------------------------------------------------------------------------->
*   Get the verification result for a specific RX PDU
*
*   @description
*   - This function allows the user code to get the verification result.
*   - The user code must set the verification result by calling
*     DsBusCustomCodeSecOCRxPduFeature_setVerificationResult
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCRxPduFeature_setVerificationResult()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param VerificationResult The verification result calculated in the
*                                 user code.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getVerificationResult(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32* VerificationResult);

/** <!------------------------------------------------------------------------->
*   Set the freshness value calculated in the user code for a specific RX PDU
*
*   @description
*   - This function allows the user code to set the freshness value that is used
*     for the verification.
*   - This value can be provided to the user as TRC and/or model variable.
*   - The detailed behavior depends on the user code implementation.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCRxPduFeature_getCalculatedFreshnessValue()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param CalculatedFreshnessValues The freshness value calculated in the
*                                        user code
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                            uint64 CalculatedFreshnessValue);

/** <!------------------------------------------------------------------------->
*   Get the freshness value calculated in the user code for a specific RX PDU.
*
*   @description
*   - This function allows the user code to get the calculated freshness value
*     set by DsBusCustomCodeSecOCRxPduFeature_setCalculatedFreshnessValue.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecOCRxPduFeature_setCalculatedFreshnessValue()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param CalculatedFreshnessValue The freshness value calculated in the
*                                       user code
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                            uint64* CalculatedFreshnessValue);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_SECOC_H */
