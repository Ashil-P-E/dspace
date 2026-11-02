/* Start of feature parameter definition, must be at the beginning of the file, before all includes, etc. */
#define DS_BUS_CUSTOM_FEATURE_NAME MyUserCode_SameByte
/* End of feature parameter definition */

#include <stdio.h>
#include <stdlib.h>
#include <DsBusCustomCode_PduUserCode.h>

#define CUSTOM_CRC_OK                       0x00
#define CUSTOM_CRC_FAILED                   0x01
#define CUSTOM_CRC_COUNTER_FAILED           0x02
#define CUSTOM_CRC_COUNTER_INITIALIZED      0x04

/* struct to store custom counter counter */
struct UserCode_FeatureData
{
	uint32 counter_value;               /* current counter value */
	uint32 counter_is_initialized;      /* flag to indicate counter is initialized */
};



Std_ReturnType DsBusCustomCode_onApplicationInit(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
	/* declare data pointers. */
	uint8* featureDataPtr;
	char* featureDescriptor;
    struct UserCode_FeatureData* featureInstanceData;
	
	/* execute the DSBUSCUSTOMCODE_CHECK_NULL macro to check whether the PduFeatureHandle is NULL.
	* If it is, a message is written to the application log and the DsBusCustomCode_onApplicationInit function
	* returns E_NOT_OK. */
	DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
	
	/* assign the instantiated UserCode_FeatureData struct via its featureInstanceData pointer to the featureDataPtr pointer. */
	DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor);

	/* create feature user data pointer */
	featureInstanceData = (struct UserCode_FeatureData*)malloc(sizeof(struct UserCode_FeatureData));
	DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, featureInstanceData);

	/* specific code, init counter to zero */
	featureInstanceData->counter_value = 0;
	featureInstanceData->counter_is_initialized = 0;

	featureDataPtr = (uint8*)featureInstanceData;
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_setFeatureDataPtr(PduFeatureHandle, featureDataPtr));

	return E_OK;
}




Std_ReturnType DsBusCustomCode_onPduFeatureExecution(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
	/*************** declare required handles, data pointers, and variables, for example, the following: ***************/	
	/* declare data pointers. */
	struct UserCode_FeatureData* featureDataPtr;
	char* featureDescriptor;
	/* this handle represents a PDU */
	DsBusCustomCodePduHandle pduHandle;		
	/* the pointer SduDataPtr points to the SDU bytes, i.e., the data bytes of the PDU */
	uint8* IPdu_SduDataPtr;	
	/* this handle represents the signals of a PDU specified in the PDU User Code feature*/
	DsBusCustomCodeSignalHandle *Signals;
	/* this handle represents the user ports that are available for the PDU User Code feature of a PDU */
	DsBusCustomCodeUserPortHandle* UserPorts;
	
	/* variable for checking the PDU direction */
	boolean isTx = FALSE;
	/* variable for the SDU length of a PDU in bytes */	
	uint32 IPdu_SduLength;
	
	/* variables for the Signals: Count, Bit-Position, Length */	
	uint32 SignalCount;
	uint32 ISignalCounterPos;
	uint32 ISignalCrcPos;
	uint32 ISignalCounterLength;
	uint32 ISignalCrcLength;
	
	/* variables for the bit-shifted signal byte number (bit to byte transformation)*/	
    uint8 tmpcrcval;
    uint32 tmpPos;
    uint32 tmpCounterPos;
    uint32 tmpCrcPos;
	
	/* variable for count and direction of user ports */
	uint32 UserPortCount;
	/* get the number of user ports of the PDU from the PDU's PduFeatureHandle */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getNumberOfUserPorts(PduFeatureHandle, &UserPortCount));
	boolean portIsOut[UserPortCount];
	
	/* variables for CAN frame triggering (frame identifier, identifier format, frame type) */
	DsBusCustomCodeCanFrameTriggeringType My_CanFrameTriggering;
	uint32 My_ID;
	uint8 My_AddressingMode;
	uint8 My_FrameBehavior;
	

	/*************** feature handle & data ***************/
	/* execute the DSBUSCUSTOMCODE_CHECK_NULL macro to check whether the PduFeatureHandle is NULL. */
	DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
	DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor, DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor));
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getFeatureDataPtr(PduFeatureHandle, (uint8**)&featureDataPtr));

	/*************** PDU handle & data ***************/
	/* get the PDU via its PDU handle */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &pduHandle));
	/* get the SDU length, i.e., the payload length of a PDU in bytes */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduLength(pduHandle, &IPdu_SduLength));
	/* get the SduDataPtr pointer of a PDU. The pointer points to the SDU bytes, i.e., the data bytes of the PDU */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduDataPtr(pduHandle, &IPdu_SduDataPtr));
	/* get the direction of a PDU, i.e, whether a PDU is transmitted (TX PDU) or received (RX PDU) */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getIsTx(pduHandle, &isTx));

	/*************** signals handle & data ***************/
	/* get the array of the user signals that are specified for a PDU */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserSignals(PduFeatureHandle, &Signals));
	/* get the number of user signals that are specified for a PDU via the PDU User Code feature */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(PduFeatureHandle, &SignalCount));

	/*************** signal array ***************/
	/* get the start bit position of a signal in bits. 
	* The start bit position determines the first bit in the payload of a PDU that is used by the signal */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[0], &ISignalCounterPos));
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[1], &ISignalCrcPos));
	/* get the length of a signal in bits */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getLength(Signals[0], &ISignalCounterLength));
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getLength(Signals[1], &ISignalCrcLength));
	
	/*************** user ports ***************/
	/* get the array of the user ports that are specified for a PDU via the PDU User Code feature */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserPorts(PduFeatureHandle, &UserPorts));
	
	/* get the direction of the user ports of the UserPorts array and provide the direction to the portIsOut array */
	for (uint32 i = 0; i < UserPortCount; i++){
		DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserPort_getDirection(UserPorts[i], &portIsOut[i]));
	}	
	
	
	/*************** forward can frame information to user ports ***************/
	/* Let the pointer point to the CAN frame triggering structure and extract frame triggering variables */
	DsBusCustomCodePdu_getCanFrameTriggering(pduHandle, &My_CanFrameTriggering);
	My_ID = (uint32)My_CanFrameTriggering.Identifier;
	My_AddressingMode = (uint8)My_CanFrameTriggering.AddresingMode;
	My_FrameBehavior = (uint8)My_CanFrameTriggering.FrameBehavior;
	
	/* Write the data of the CAN frame triggering variables to the user ports of the UserPorts array */
	if (portIsOut[0])
		DsBusCustomCodeUserPort_setPortData(UserPorts[0], My_ID);
	if (portIsOut[1])
		DsBusCustomCodeUserPort_setPortData(UserPorts[1], My_AddressingMode);
	if (portIsOut[2])
		DsBusCustomCodeUserPort_setPortData(UserPorts[2], My_FrameBehavior);
	
	
	/*************** declare variables for Counter and CRC calculation ***************/
	/* bit shift to get the signal byte number (bit to byte transformation: division by 8)*/
	tmpcrcval = 0;	
	tmpPos = IPdu_SduLength;
	tmpCounterPos = ISignalCounterPos >> 3;
	tmpCrcPos = ISignalCrcPos >> 3;
	
	/* set bit-values for bits of the same byte */
	uint8 BitsCounter;
	uint8 BitsCrC;
	BitsCounter = (1 << ISignalCounterLength) - 1;
	BitsCrC = (1 << (8-ISignalCrcLength)) - 1;	
	
	/* specify variables for Count- & CRC calculation */
	uint8 CalcCounterValue;
	uint8 CalcCrCValue;
	CalcCounterValue = 0;
	CalcCrCValue = 0;

	/*************** This code is being executed when transmitting the PDU ***************/
	if (isTx)
	{
		/***** calculate counter value *****/
		if (IPdu_SduLength > tmpCounterPos)
			CalcCounterValue = ++(featureDataPtr->counter_value) & BitsCounter;			

		/***** iterate over pdu buffer and calculate new CRC-value *****/
		while (tmpPos)
		{
			tmpPos--;
           /* exclude CRC position from calculation */
		   /* and include Counter to calculation*/
			if (tmpPos != tmpCrcPos)
				tmpcrcval += 0xFF ^ (IPdu_SduDataPtr[tmpPos] | CalcCounterValue);				
		}		

		/* calculate CRC-value according to bit position */
		CalcCrCValue = (tmpcrcval & BitsCrC) << ISignalCrcLength;
		
		/* Combine Counter & CRC on same Byte*/
		/* and write calculated Count- and CRC-value to its position */
		if (IPdu_SduLength > tmpCrcPos)			
			IPdu_SduDataPtr[tmpCounterPos] = CalcCounterValue | CalcCrCValue;
	}
	
	/*************** This code is being executed when receiving the PDU ***************/
	else
	{	/* initialize the CRC value as valid */
		uint32 status = CUSTOM_CRC_OK;
		
		/***** check if rx counter had been initialized *****/
		if (IPdu_SduLength > tmpCounterPos) {
			if (!featureDataPtr->counter_is_initialized)
			{	
				featureDataPtr->counter_value = IPdu_SduDataPtr[tmpCounterPos] & BitsCounter;
				status |= CUSTOM_CRC_COUNTER_INITIALIZED;
				featureDataPtr->counter_is_initialized = 1;
			}
			else
			{
				/* increase local counter and compare */
				featureDataPtr->counter_value++;				
				if ((featureDataPtr->counter_value & BitsCounter) != (IPdu_SduDataPtr[tmpCounterPos] & BitsCounter))
				{
					featureDataPtr->counter_is_initialized = 0;
					status |= CUSTOM_CRC_COUNTER_FAILED;
					msg_info_printf(0,0,"RX Counter failed");
				}
			}
		}
		
		/***** iterate over pdu buffer and calculate expected CRC-value *****/
		if (IPdu_SduLength > tmpCrcPos) {
			while (tmpPos)
		{
			tmpPos--;
           /* exclude CRC position from calculation */
		   /* and include expected Counter to calculation*/
			if (tmpPos != tmpCrcPos)				
				tmpcrcval += 0xFF ^ (IPdu_SduDataPtr[tmpPos] | featureDataPtr->counter_value);
		}	
			/* consider bit length */
			tmpcrcval = (tmpcrcval & BitsCrC);
			
			/***** compare calculated CRC-value with the received one *****/			
			if (tmpcrcval != (((IPdu_SduDataPtr[tmpCrcPos]) >> ISignalCrcLength) & BitsCrC)) {
				status |= CUSTOM_CRC_FAILED;
			}
		}	
		/* return the status of Counter and CRC comparsion to RESULT port*/		
		DsBusCustomCodeUserCodePduFeature_setResult(PduFeatureHandle, status);
	}
	return E_OK;
}
