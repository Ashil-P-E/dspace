/* Start of user code source file */
/* Define user code ID */
#define DS_BUS_CUSTOM_FEATURE_NAME UserCRCTest
/* Mandatory include file */
#include <DsBusCustomCode_PduUserCode.h>

/* Further required include files */
#include <stdio.h>
#include <stdlib.h>

#define CUSTOM_CRC_OK 0x00 /* Expected checksum value received */
#define CUSTOM_CRC_FAILED 0x01 /* Unexpected checksum value received */
#define CUSTOM_CRC_COUNTER_FAILED 0x02 /* Unexpected counter value received */
#define CUSTOM_CRC_COUNTER_INITIALIZED 0x04 /* Counter initialized */

/* Struct to store counter data */
struct UserCode_FeatureData
{
 uint32 counter_value; /* Current counter value */
 uint32 counter_is_initialized; /* Flag indicating whether the counter is initialized */
};
/***** Initialization phase *****/
Std_ReturnType DsBusCustomCode_onApplicationInit(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
 {
	 /* Declare data pointers. */
	 
	 uint8* featureDataPtr;
	 char* featureDescriptor;
	 struct UserCode_FeatureData* featureInstanceData;

	 /* Execute the DSBUSCUSTOMCODE_CHECK_NULL macro to check whether the PduFeatureHandle is NULL.
	* If it is, a message is written to the application log and the DsBusCustomCode_onApplicationInit function
	* returns E_NOT_OK. */
	
	 DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
	 DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor);

	 /* Create an instance of the UserCode_FeatureData struct to store PDU-specific feature data.
	* Assign the instantiated struct to the featureInstanceData pointer.
	* Check the pointer via the DSBUSCUSTOMCODE_CHECK_NULL macro. */

	 featureInstanceData = (struct UserCode_FeatureData*)malloc(sizeof(struct UserCode_FeatureData));
	 DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, featureInstanceData);
	 /* Initialize the counter of the PDU with 0. */
	 featureInstanceData->counter_value = 0;
	 featureInstanceData->counter_is_initialized = 0;

	 /* Assign the instantiated UserCode_FeatureData struct via its featureInstanceData pointer to
	* the featureDataPtr pointer.
	* Assign the featureDataPtr pointer to the PDUFeatureHandle.
	* Execute the DSBUSCUSTOMCODE_TRY macro to check whether the DsBusCustomCodePduFeature_setFeatureDataPtr
	* function is called successfully.
	* If it is not, a message is written to the application log and the DsBusCustomCode_onApplicationInit
	* function returns E_NOT_OK. */
	
	 featureDataPtr = (uint8*)featureInstanceData;
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_setFeatureDataPtr(PduFeatureHandle,featureDataPtr));

	 /* Return whether DsBusCustomCode_onApplicationInit function is implemented correctly. */
	 return E_OK;
 }
 
Std_ReturnType DsBusCustomCode_onPduFeatureExecution(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
 /* Part 1: Common part of the DsBusCustomCode_onPduFeatureExecution function that applies to each PDU to which
* the PDU User Code feature is added, regadless of the PDU direction. */

 /* Part 2 and 3: If-Else loop that checks whether the PDU is a TX PDU. */
 /* Declare required handles, data pointers, and variables, for example, the following: */
	 boolean isTx = FALSE;
	 struct UserCode_FeatureData* featureDataPtr;
	 char* featureDescriptor;
	 DsBusCustomCodePduHandle pduHandle;
	 uint8* IPdu_SduDataPtr;
	 uint32 IPdu_SduLength;
	 DsBusCustomCodeSignalHandle *Signals;
	 uint32 SignalCount;
	 uint32 ISignalCounterPos;
	 uint32 ISignalCrcPos;
	 uint8 tmpcrcval;
	 uint32 tmpPos;
	 uint32 tmpCounterPos;
	 uint32 tmpCrcPos;
	 /* Access the PduFeatureHandle and its data.
	* Check the PduFeatureHandle via the DSBUSCUSTOMCODE_CHECK_NULL macro. */
	 DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
	 /* Get the descriptor of the PduFeatureHandle. */
	 DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor, DsBusCustomCode_getDescriptor(PduFeatureHandle,&featureDescriptor));
	 /* Get the data structure that is addressed via the featureDataPtr pointer, i.e., the data of the
	* related UserCode_FeatureData struct that was created during the execution of the
	* DsBusCustomCode_onApplicationInit function. */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getFeatureDataPtr(PduFeatureHandle,(uint8**)&featureDataPtr));

	 /* Access the PduHandle and its data.
	* Get the PduHandle of the PDU from its PduFeatureHandle. */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &pduHandle));
	 /* Get properties of the PDU from its PduHandle */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduLength(pduHandle, &IPdu_SduLength));
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduDataPtr(pduHandle, &IPdu_SduDataPtr));
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getIsTx(pduHandle, &isTx));

	 /* Access the signals of the PDU.
	* Get the user signal array of the PDU from its PduFeatureHandle. */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserSignals(PduFeatureHandle,&Signals));
	 /* Get the number of user signals of the PDU from its PduFeatureHandle. */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(PduFeatureHandle, &SignalCount));

	 /* Get the start bit position of the first two signals in the signal array.
	* Assign the ISignalCrcPos and ISignalCounterPos variables to the start bit position. */
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[0], &ISignalCrcPos));
	 DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[1],
	&ISignalCounterPos));

	 /* Specify initial values for some variables of each PDU feature handle. */
	 tmpcrcval = 0;
	 tmpPos = IPdu_SduLength;
	 tmpCounterPos = ISignalCounterPos >> 3;
	 tmpCrcPos = ISignalCrcPos >> 3;

 /* End of part 1, i.e., end of the common part of the DsBusCustomCode_onPduFeatureExecution function. */

 /* Part 2 and 3: If-Else loop that checks whether the PDU is a TX PDU. */
	if (isTx)
	{
		/* Part 2: Executed only if the PDU is a TX PDU.
		* For details, see below. */
		/* Exclude the CRC position from the checksum calculation. */

		/* Write counter value to the allocated position of the PDU's payload. */
		if (IPdu_SduLength > tmpCounterPos)
		{
		IPdu_SduDataPtr[tmpCounterPos] = (++(featureDataPtr->counter_value) & 0xFF);
		}

		/* Iterate over the PDU's data buffer and calculate the new checksum value. */
		while (tmpPos)
		{
		 tmpPos--;
		 if (tmpPos != tmpCrcPos)
		 tmpcrcval += (0xFF ^ IPdu_SduDataPtr[tmpPos]);
		}

		/* Write the calculated checksum value to the allocated position of the PDU's payload. */
		if (IPdu_SduLength > tmpCrcPos)
		{
		IPdu_SduDataPtr[tmpCrcPos] = tmpcrcval;
		}
	 }

	else
	{
	 /* Part 3: Executed only if the PDU is an RX PDU For details, see below. */ 
		uint32 status = CUSTOM_CRC_OK;
		/* Check whether the RX counter has been initialized. */
		if (IPdu_SduLength > tmpCounterPos)
		{
			 /* If the RX counter has not been initialized yet, initialize it with the received counter value. */
			 if (!featureDataPtr->counter_is_initialized)
			 {
				 featureDataPtr->counter_value = IPdu_SduDataPtr[tmpCounterPos];
				 status |= CUSTOM_CRC_COUNTER_INITIALIZED;
				 featureDataPtr->counter_is_initialized = 1;
			 }
			 /* If the RX counter has already been initialized, increase the local counter value and compare it with the received counter value. */
			 else
			 {
				 featureDataPtr->counter_value++;
				 if ((featureDataPtr->counter_value & 0xFF) != IPdu_SduDataPtr[tmpCounterPos])
				 {
				 featureDataPtr->counter_is_initialized = 0;
				 status |= CUSTOM_CRC_COUNTER_FAILED;
				 }
			 }

			 if (IPdu_SduLength > tmpCrcPos)
			 {
				 while (tmpPos)
				 {
					 tmpPos--;
					 if (tmpPos != tmpCrcPos)
					 tmpcrcval += (0xFF ^ IPdu_SduDataPtr[tmpPos]);
				 }
				 /* Compare the expected checksum value with the received checksum value. */
				 if (tmpcrcval != IPdu_SduDataPtr[tmpCrcPos])
				 {
				 status |= CUSTOM_CRC_FAILED;
				 }
			 }
			 /* Write the result to the Result function port of the PDU User Code feature. */
			 DsBusCustomCodeUserCodePduFeature_setResult(PduFeatureHandle, status);
		}
	}

 /* Return whether DsBusCustomCode_onPduFeatureExecution function is implemented correctly. */
 return E_OK;
 }
 
 