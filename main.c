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
#define VERSION "beta"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned char total_length=15;
    
    char line[total_length];
    
    pid_t pid;
    
    system("clear");
    printf("Starting Algobot manager %s / build %s\n", VERSION, __DATE__);
    printf("---------------------------------------\n");
    
    FILE * command = popen("pidof algobot_onionomega","r");
    fgets(line,total_length,command);
    pid=strtoul(line,NULL,10);
    pclose(command);
    
    if(pid>0){
        printf("Kill ALL Process algobot_onionomega... ");
        //char sys_command [20] ="";
        //sprintf(sys_command,"kill %d",pid);
        //system(sys_command);
        system("killall algobot_onionomega");
        sleep(1);
        printf("OK\n");
    }
    else {
         printf("No process algobot_onionomega found !\n");
         }
      
    sleep(1);
    printf("Terminate Algobot manager ! Bye\n\n");
    return (EXIT_SUCCESS);
}

