/*
 * messagesManager.h
 *
 *  Created on: 15 mars 2016
 *      Author: raph
 */

#ifndef MESSAGESMANAGER_H_
#define MESSAGESMANAGER_H_

extern char ClientID[50];

// Definition of topics for manager publish/subscrib
#define TOPIC_MANAGER "Manager"					// Topic d'�coute de l'hote
#define TOPIC_DEBUG "Debug"

// Initialisation de la messagerie system (JSON<->MQTT)
int InitMessager(void);
int pullMsgStack(unsigned char ptrStack);
int CloseMessager(void);
void sendMqttReport(int msgId, char * msg);
void sendResponse(int msgId, char * msgTo, unsigned char msgType, unsigned char msgParam, unsigned char valCnt);


#endif /* MESSAGESMANAGER_H_ */
