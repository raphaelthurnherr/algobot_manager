
#define MAX_MQTT_BUFF 4096


// DEFINITION DES TYPES DE MESSAGE
typedef enum msgformat{
	EVENT_ACTION_ERROR,
	EVENT_ACTION_END,
	EVENT_ACTION_BEGIN,
	EVENT_ACTION_ABORT,
	RESP_STD_MESSAGE,
} t_msgformat;

// DEFINITION DES TYPES DE MESSAGE
typedef enum msgtype{
	ERR_TYPE,
	COMMAND,
	REQUEST,
	ACK,
	RESPONSE,
	EVENT,
        DATAFLOW,
} t_msgtype;

// DEFINITION DES PARAMETRES DE TYPE PARAMETRE
typedef enum msgparam{
        ERR_HEADER,     // Not use
	ERR_PARAM,      // Not use
        CONFIG,
        SYSTEM,
}t_msgparam;

struct mStream{
	char state[25];
        char onEvent[25];
	int time;
};

struct mConfig{
	struct mStream stream;
};

struct mSystem{
	char name[32];
        int startUpTime;
        char firmwareVersion[32];
        char mcuVersion[32];
        char HWrevision[32];
        float battVoltage;
        int wan_online;
        int tx_message;
        int rx_message;   
};

struct mSystemCmd{
        char application[32];
        char firmwareUpdate[32];
        char webAppUpdate[32];
};


// Structure d'un message algoid recu
typedef struct JsonCommand{
	char msgTo[32];
	char msgFrom[32];
	int msgID;
	t_msgtype msgType;
	t_msgparam msgParam;
	unsigned char msgValueCnt;

	// UNION ???
        struct mConfig Config;
        struct mSystemCmd System;
	// UNION ???

}ALGOID;

// Structure de r�ponse � un message algoid
typedef struct JsonResponse{
	int value;
	int responseType;

	// UNION ???
        struct mSystem SYSresponse;
        struct mConfig CONFIGresponse;
        struct mSystemCmd SYSCMDresponse;
	// UNION ???
}ALGOID_RESPONSE;

ALGOID AlgoidCommand;    // Utilis� par main.c
ALGOID AlgoidMessageRX;
ALGOID AlgoidMsgRXStack[10];

// Buffer de sortie pour les msgValue[
ALGOID_RESPONSE AlgoidResponse[20];


extern char GetAlgoidMsg(ALGOID DestReceiveMessage,char *srcDataBuffer);
void ackToJSON(char * buffer, int msgId, char* to, char * from, char * msgType,char * msgParam, unsigned char value, unsigned char count);
