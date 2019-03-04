/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: raph-pnp
 *
 * Created on 22. juin 2018, 08:45
 */
#define VERSION "1.01"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include "buggy_descriptor.h"
#include "messagesManager.h"
#include "linux_json.h"
#include "udpPublish.h"
#include "timerManager.h"

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned char total_length=15;
    
    char line[total_length];

    unsigned int sequencer=0;    
    pid_t pid;
    
    system("clear");
    printf("Starting KEHOPS manager %s / build %s\n", VERSION, __DATE__);
    printf("---------------------------------------\n");
   
// Création de la tâche pour la gestion de la messagerie avec ALGOID
    if(InitMessager()) printf ("#[CORE] Creation tâche messagerie : ERREUR\n");
    else printf ("#[CORE] Demarrage tache Messager: OK\n");
    
// Création de la tâche pour la gestion des différents timers utilisés
    if(InitTimerManager()) printf ("#[CORE] Creation tâche timer : ERREUR\n");
    else printf ("#[CORE] Demarrage tache timer: OK\n");

// Initialisation UDP pour broadcast IP Adresse
    initUDP();
    
    
    while(1){  
       
        // Contrôle de la messagerie, recherche d'éventuels messages ALGOID et effectue les traitements nécéssaire
        // selon le type du message [COMMAND, REQUEST, NEGOCIATION, ACK, REPONSE, ERROR, etc...]
        if(pullMsgStack(0)){
            switch(AlgoidCommand.msgType){
                    case COMMAND : processManagerCommand(); break;						// Traitement du message de type "COMMAND"
                    case REQUEST : processManagerRequest(); break;						// Traitement du message de type "REQUEST"
                    default : ; break;
            }
        }
        
        // Contrôle du TIMER 100mS
    	if(t100msFlag){
            switch(sequencer){
                case 5:  wsTcpGataway_check(); break;
    //            case 5: mosquitto_check(); break;
                case 10: kehopsFirmware_check(); break;
                default : break;
            }		
            
            if(sequencer++>=15)
                sequencer=0;
            // Quittance le flag 100mS           
            t100msFlag=0;
    	}


        
    }
    
    sleep(1);
    printf("Terminate Algobot manager ! Bye\n\n");
    return (EXIT_SUCCESS);
}





// -------------------------------------------------------------------
// PROCESSCOMMAND
// Séléctionne et traite le paramètre de commande recue [LL2WD, BACK, FORWARD, STOP, SPIN, etc...]
// -------------------------------------------------------------------
int processManagerCommand(void){    
	switch(AlgoidCommand.msgParam){
		case 123456 : 	break;
		default : break;
	}
	return 0;
}

// -------------------------------------------------------------------
// PROCESSREQUEST
// Séléction et traite le paramètre de requete recu [DISTANCE, TENSION BATTERIE, ENTREE DIGITAL, etc...]
// -------------------------------------------------------------------
int processManagerRequest(void){
	switch(AlgoidCommand.msgParam){
		case 123456 : break;
		default : break;
	}
	return 0;
}

int wsTcpGataway_check(){
    int bashStatus=-1;
    
    printf("Process check wsTcpGataway:\n");
    bashStatus=system("pgrep node");
    
    if(WEXITSTATUS(bashStatus)){
        printf("MANAGER->WARNING, NODE GATEWAY IS DOWN, RESTARTING...\n");
        system("ws-tcp-bridge --method=ws2tcp --lport=9001 --rhost=127.0.0.1:1883&");
        usleep(500000);
        system("ws-tcp-bridge --method=tcp2ws --lport=1883 --rhost=ws://127.0.0.1:9001&");        
        usleep(100000);
    }
    
    printf("\n");
    return 0;
}
    
int mosquitto_check(){
    int bashStatus=-1;
    
    printf("Process check mosquitto:\n");
    bashStatus=system("pgrep mosquitto");

    if(WEXITSTATUS(bashStatus)){
        printf("MANAGER->WARNING, MOSQUITTO IS DOWN, RESTARTING...\n");
        system("mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf&");
    }
        printf("\n");
    return 0;
}

int kehopsFirmware_check(){
    int bashStatus=-1;
    
    printf("Process check KEHOPS binary file: \n");
    bashStatus=system("pgrep -x ./kehops");
    
    if(WEXITSTATUS(bashStatus)){
        printf("MANAGER->WARNING, KEHOPS FIRMWARE IS DOWN, RESTARTING...\n");
        system("./kehops/kehops -n kehops_simu&");      
    }        
    
    printf("\n");
    return 0;
}

