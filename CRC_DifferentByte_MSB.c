/* Start of feature parameter definition, must be at the beginning of the file, before all includes, etc. */
#define DS_BUS_CUSTOM_FEATURE_NAME CRC_DifferentByte_MSB
/* End of feature parameter definition */

#include <stdio.h>
#include <stdlib.h>
#include <DsBusCustomCode_PduUserCode.h>

#define CUSTOM_CRC_OK                       0x00
#define CUSTOM_CRC_FAILED                   0x01
#define CUSTOM_CRC_COUNTER_FAILED           0x02
#define CUSTOM_CRC_COUNTER_INITIALIZED      0x04

int crc8_table_b[256] = {
0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D, 0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4
};

 uint8 data_TX_b[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
 int IsFirstCall_b=1;
 int crc_sim_b = 0xFF;
 int final_XOR_b = 0xFF;
 int b_b = 0;
 int i_b = 0;
 int index_b = 0x00;
 
 int B0_CRC_Protect_b(int IsFirstCall,int crc_sim,uint8 data_TX[])
 {
	 for(b_b=0;b_b<7;b_b++)
	 {
		 if(IsFirstCall==1)
		 {
			 IsFirstCall = 0;
			 crc_sim = 0xFF;
		 }
		 index_b = crc_sim ^ data_TX[b_b];
		 crc_sim = crc8_table_b[index_b];
	 }
	 crc_sim = crc_sim ^ final_XOR_b;
	 return crc_sim;
 }
 
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
	


	/*************** This code is being executed when transmitting the PDU ***************/
	if (isTx)
	{	
		IsFirstCall_b =1;
		/***** calculate counter value and write to its position*****/	
		if (IPdu_SduLength > tmpCounterPos)
			IPdu_SduDataPtr[tmpCounterPos] = (++(featureDataPtr->counter_value) & 0x0F);
		
		for(i_b=0;i_b<7;i_b++)
		{
			data_TX_b[i_b] = IPdu_SduDataPtr[i_b];
		}
		/***** iterate over pdu buffer and calculate new CRC-value *****/
		tmpcrcval = B0_CRC_Protect_b(IsFirstCall_b,crc_sim_b,data_TX_b);

		/* write calculated CRC-value to its position */
		if (IPdu_SduLength > tmpCrcPos)
			IPdu_SduDataPtr[tmpCrcPos] = tmpcrcval;
	}
	
	/*************** This code is being executed when receiving the PDU ***************/
	else
	{	/* initialize the CRC value as valid */
		uint32 status = CUSTOM_CRC_OK;
		IsFirstCall_b =1;
		
		/***** check if rx counter had been initialized *****/
		if (IPdu_SduLength > tmpCounterPos) {
			if (!featureDataPtr->counter_is_initialized)
			{
				featureDataPtr->counter_value = IPdu_SduDataPtr[tmpCounterPos];
				status |= CUSTOM_CRC_COUNTER_INITIALIZED;
				featureDataPtr->counter_is_initialized = 1;
			}
			else
			{
				/* increase local counter and compare */
				featureDataPtr->counter_value++;				
				if ((featureDataPtr->counter_value & 0x0F) != IPdu_SduDataPtr[tmpCounterPos])
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
				if (tmpPos != tmpCrcPos)
					tmpcrcval += (0xFF ^ IPdu_SduDataPtr[tmpPos]);
			}			
			
			/***** compare calculated CRC-value with the received one *****/			
			if (tmpcrcval != IPdu_SduDataPtr[tmpCrcPos]) {
				status |= CUSTOM_CRC_FAILED;
			}
		}	
		/* return the status of Counter and CRC comparsion to RESULT port*/		
		DsBusCustomCodeUserCodePduFeature_setResult(PduFeatureHandle, status);
	}
	return E_OK;
}
