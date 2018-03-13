/*
* Copyright (c) 2016 Academia Sinica, Institute of Information Science
*
* License:
*
*      GPL 3.0 : The content of this file is subject to the terms and
*      cnditions defined in file 'COPYING.txt', which is part of this source
*      code package.
*
* Project Name:
*
*      BeDIPS
*
* File Description:
*
*      
*
* File Name:
*
*     CommUnit.c
*
* Abstract:
*
*      BeDIPS uses LBeacons to deliver 3D coordinates and textual
*      descriptions of their locations to users' devices. Basically, a
*      LBeacon is an inexpensive, Bluetooth Smart Ready device. The 3D
*      coordinates and location description of every LBeacon are retrieved
*      from BeDIS (Building/environment Data and Information System) and
*      stored locally during deployment and maintenance times. Once
*      initialized, each LBeacon broadcasts its coordinates and location
*      description to Bluetooth enabled user devices within its coverage
*      area.
*
* Authors:
*
*      Hank Kung, hank910140@gmail.com
*      
*/

#include "CommUnit.h"

void *CommUnit_routine(){

    inti_Command_Queue();
    //when initialization completes,
    CommUnit_initialization_complete = true;
    while (system_is_shutting_down == false) {
        //   do a chunk of work and/or sleep for a short time

        //DeQueue()
        //If command queue is empty then sleep for a while. Else:
        //get the command out and run the corresponding function(not by thread)
        //
        }
    CommUnit_cleanup_exit();
    return;
 }

void inti_Command_Queue(){
//    ront = rear = (Command*) malloc(sizeof(Command));
//    front->next = rear->next = NULL;
}

void RFHR(){

}