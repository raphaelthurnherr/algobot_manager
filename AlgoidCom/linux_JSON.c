/*
 ============================================================================
 Name        : linux_JSON.c
 Author      : Raph
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#define KEY_TO "{'MsgTo'"
#define KEY_FROM "{'MsgFrom'"
#define KEY_MSGID "{'MsgID'"
#define KEY_MESSAGE ""
#define KEY_MESSAGE_TYPE "{'MsgData'{'MsgType'"
#define KEY_MESSAGE_PARAM "{'MsgData'{'MsgParam'"
#define KEY_MESSAGE_VALUE "{'MsgData'{'MsgValue'"

#define KEY_MESSAGE_VALUE_DIN "{'MsgData'{'MsgValue'[*{'din'"
#define KEY_MESSAGE_VALUE_SONAR "{'MsgData'{'MsgValue'[*{'sonar'"
#define KEY_MESSAGE_VALUE_CFG_STREAM_STATE "{'MsgData'{'MsgValue'[*{'stream'{'state'"
#define KEY_MESSAGE_VALUE_SYS_APP "{'MsgData'{'MsgValue'[*{'application'"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linux_json.h"
#include "libs/lib_json/jRead.h"
#include "libs/lib_json/jWrite.h"

void ackToJSON(char * buffer, int msgId, char* to, char * from, char * msgType,char * msgParam, unsigned char orgType, unsigned char count);
char GetAlgoidMsg(ALGOID destMessage, char *srcBuffer);

ALGOID myReplyMessage;

// -----------------------------------------------------------------------------
// MAIN, APPLICATION PRINCIPALE-------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// GetAlgoidMsg
// Get message from buffer and set in the message structure
// -----------------------------------------------------------------------------

char GetAlgoidMsg(ALGOID destMessage, char *srcBuffer){
	struct jReadElement element;
	int i;

	// ENTETE DE MESSAGE
		jRead_string((char *)srcBuffer, KEY_TO, AlgoidMessageRX.msgTo, 15, NULL );
		jRead_string((char *)srcBuffer, KEY_FROM, AlgoidMessageRX.msgFrom, 15, NULL );
		AlgoidMessageRX.msgID= jRead_int((char *)srcBuffer,  KEY_MSGID, NULL);

	// MESSAGE TYPE
				char myDataString[20];
				// Clear string
				for(i=0;i<20;i++) myDataString[i]=0;

				jRead_string((char *)srcBuffer,  KEY_MESSAGE_TYPE,myDataString,15, NULL);

				AlgoidMessageRX.msgType= ERR_TYPE;
				if(!strcmp(myDataString, "command")) AlgoidMessageRX.msgType = COMMAND;
				if(!strcmp(myDataString, "request")) AlgoidMessageRX.msgType = REQUEST;
				if(!strcmp(myDataString, "ack")) AlgoidMessageRX.msgType = ACK;
				if(!strcmp(myDataString, "response")) AlgoidMessageRX.msgType = RESPONSE;
				if(!strcmp(myDataString, "event")) AlgoidMessageRX.msgType = EVENT;
				if(!strcmp(myDataString, "error")) AlgoidMessageRX.msgType = ERR_TYPE;

	// MESSAGE PARAM
				// Clear string
				for(i=0;i<20;i++) myDataString[i]=0;
				jRead_string((char *)srcBuffer,  KEY_MESSAGE_PARAM,myDataString,15, NULL);

				AlgoidMessageRX.msgParam=ERR_PARAM;
                                        if(!strcmp(myDataString, "config")) AlgoidMessageRX.msgParam = CONFIG;
                                        if(!strcmp(myDataString, "system")) AlgoidMessageRX.msgParam = SYSTEM;

				  jRead((char *)srcBuffer, KEY_MESSAGE_VALUE, &element );

					// RECHERCHE DATA ARRAY
				  if(element.dataType == JREAD_ARRAY ){
					  AlgoidMessageRX.msgValueCnt=element.elements;

				      for(i=0; i<element.elements; i++ )    // loop for no. of elements in JSON
				      {                                          
                                          if(AlgoidMessageRX.msgParam == CONFIG){
				    	  }
                                          
                                          if(AlgoidMessageRX.msgParam == SYSTEM){
				    	  }
				    }
				  }
				  else
					  AlgoidMessageRX.msgValueCnt=0;

				  if((AlgoidMessageRX.msgParam == ERR_PARAM) || (AlgoidMessageRX.msgType == ERR_TYPE)){
					  return 0;
				  }else
					  return 1;
}


// -----------------------------------------------------------------------------
// replyToHost
// convert the structure in JSON format & Send to host
// -----------------------------------------------------------------------------
void ackToJSON(char * buffer, int msgId, char* to, char* from, char* msgType, char* msgParam, unsigned char orgType, unsigned char count ){
	unsigned int buflen= MAX_MQTT_BUFF;
	unsigned char i,j;
        
// Formatage de la r�ponse en JSON
	jwOpen( buffer, buflen, JW_OBJECT, JW_PRETTY );		// start root object
		jwObj_string( "MsgTo", to );				// add object key:value pairs
		jwObj_string( "MsgFrom", from );				// add object key:value pairs
		jwObj_int( "MsgID", msgId );
		jwObj_object( "MsgData" );
			jwObj_string( "MsgType", msgType );				// add object key:value pairs
			if(msgParam!=0) jwObj_string( "MsgParam", msgParam );				// add object key:value pairs

			if(count>0){                              
				for(i=0;i<count;i++){
						switch(orgType){                                                                                
							case CONFIG :           
                                                                            switch(AlgoidResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END :   jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :    
                                                                                                            jwObj_object( "stream" );                                                                                 
                                                                                                                    jwObj_string("state", AlgoidResponse[i].CONFIGresponse.stream.state);
                                                                                                                    jwObj_int("time", AlgoidResponse[i].CONFIGresponse.stream.time);
                                                                                                                    jwObj_string("onEvent", AlgoidResponse[i].CONFIGresponse.stream.onEvent);         
                                                                                                            jwEnd(); 
                                                                                                            ; break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }		// add object key:value pairs  
                                                                            break;
                                                                                
							case SYSTEM :           
                                                                            switch(AlgoidResponse[i].responseType){
                                                                                case EVENT_ACTION_ERROR : jwObj_string("action", "error"); break;
                                                                                case EVENT_ACTION_END :   jwObj_string("action", "end"); break;
                                                                                case EVENT_ACTION_BEGIN : jwObj_string("action", "begin"); break;
                                                                                case EVENT_ACTION_ABORT : jwObj_string("action", "abort"); break;
                                                                                case RESP_STD_MESSAGE   :                                                                                    
                                                                                                            jwObj_string("application", AlgoidResponse[i].SYSCMDresponse.application);
                                                                                                          ; break;
                                                                                default : jwObj_string("error", "unknown"); break;
                                                                            }		// add object key:value pairs

                                                                            break;                                                                                
                                                                                   
							default:            break;

						}
				}
				jwEnd();
			}
		jwEnd();
		jwClose();
}
