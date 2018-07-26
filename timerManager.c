/*
 * timerManager.c
 *
 *  Created on: 8 avr. 2016
 *      Author: raph
 */

// Defninition des emplacement dans les variables timer avec callback				// Slot Data pour No de LED

#include "pthread.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timerManager.h"

// Thread Messager
pthread_t th_timers;

unsigned char t100msFlag;
unsigned char t5secFlag;
unsigned char t10secFlag;
unsigned char t60secFlag;

// ------------------------------------------
// Programme principale TIMER
// ------------------------------------------
void *TimerTask (void * arg){
	unsigned int cyclicTimer50ms;	// Compteur du timer cyclique 50mS
	unsigned int cyclicTimer100ms;	// Compteur du timer cyclique 100mS
	unsigned int cyclicTimer10sec;	// Compteur du timer cyclique 10Secondes
        unsigned int cyclicTimer5sec;	// Compteur du timer cyclique 10Secondes
        
        unsigned int cyclicTimer60sec;	// Compteur du timer cyclique 10Secondes
        
	while(1){

		// Controle le time out de 50ms
		if(cyclicTimer50ms>=50){
			cyclicTimer50ms=0;				// Reset le compteur 50ms
		}

		// Controle le time out de 100ms
		if(cyclicTimer100ms>=100){
			t100msFlag=1;
			cyclicTimer100ms=0;				// Reset le compteur 100ms
		}
                
                // Controle le time out de 10 secondes
		if(cyclicTimer5sec>=5000){
			t5secFlag=1;
			cyclicTimer5sec=0;				// Reset le compteur 10secondes
		}
                

		// Controle le time out de 10 secondes
		if(cyclicTimer10sec>=10000){
			t10secFlag=1;
			cyclicTimer10sec=0;				// Reset le compteur 10secondes
		}

                // Controle le time out de 60 secondes
		if(cyclicTimer60sec>=60000){
			t60secFlag=1;
			cyclicTimer60sec=0;				// Reset le compteur 10secondes
		}
		cyclicTimer50ms++;				// Reset le compteur 10secondes
		cyclicTimer100ms++;				// Reset le compteur 100ms
		cyclicTimer10sec++;				// Reset le compteur 10secondes
                cyclicTimer60sec++;
                cyclicTimer5sec++;
                
		usleep(1000);
	}
	pthread_exit (0);
}

// ------------------------------------------------------------------------------------
// TIMERMANAGER: Initialisation du gestionnaire de timer
// - D�marre le thread
// ------------------------------------------------------------------------------------
int InitTimerManager(void){
	// CREATION DU THREAD DE TIMER
	  if (pthread_create (&th_timers, NULL, TimerTask, NULL)!=0) {
		return (1);
	  }else return (0);
}

// ------------------------------------------------------------------------------------
// CLOSETIMER: Fermeture du gestionnaire de timers
// - Stop le thread timers
// ------------------------------------------------------------------------------------

int CloseTimerManager(void){
	int result;
	// TERMINE LE THREAD DE MESSAGERIE
	pthread_cancel(th_timers);
	// Attends la terminaison du thread de messagerie
	result=pthread_join(th_timers, NULL);
	return (result);
}