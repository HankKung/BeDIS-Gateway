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
*      This file contains the program to transmit the data or information from
*      LBeacons through Zigbee or UDP. Main tasks includes network setup and 
*      initialization, Beacon health monitor and comminication unit. Gateway 
*      takes the role as coordinator.
*
* File Name:
*
*      Gateway.c
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
*      Han Wang, hollywang@iis.sinica.edu.tw
*      Jake Lee, jakelee@iis.sinica.edu.tw
*      Johnson Su, johnsonsu@iis.sinica.edu.tw
*      
*/



#include "Gateway.h"



long long get_system_time() {
    /* A struct that stores the time */
    struct timeb t;

    /* Return value as a long long type */
    long long system_time;

    /* Convert time from Epoch to time in milliseconds of a long long type */
    ftime(&t);
    system_time = 1000 * t.time + t.millitm;

    return system_time;
}

/* coordinator initializes the zigbee network:
- if (PAN ID == 0) scan nearby network and chooses a PAN ID;
- channel scan to find a good operating channel;
- ready to access join requests from Lbeacons;
/* Set up Zigbee connection by calling Zigbee_routine in LBeacon_Zigbee.h */
void *NSI_routine(){

    if (startThead (Zigbee_routine()) != WORK_SCUCESSFULLY) {
        initialization_failed = true;
        NSIcleanupExit( );
    }
    
    /* Socket Set Up */
    int sock, length;
    struct sockaddr_in server, from;
    struct hostent *hp;
    char * buffer[BUFFER_SIZE];
    
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        error("Wrong Socket");
    }
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if(hp == 0)
    {
        error("Unknown Host");
    }
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);
    bzero(buffer, BUFFER_SIZE);

    // make sure WiFi has been correctly configured ....
    int ping_ret, status;
    status = system("ping google.com");
    if (-1 != status)
        ping_ret = WEXITSTATUS(status);

     /* initialize beacon_address []
     - enter a 16-bit network address in each address_map struct in the array
     .....
     // start a thread to maintain beacon_address map. The thread
     // should also check system_is_shutting_down flag periodically
     // and returns when it finds the flag is true.*/
     int beacon_count = 1;
     if (startThead (address_map_manager()) != WORK_SCUCESSFULLY) {
         initialization_failed = true;
         NSIcleanupExit( );
     }
     // finish phase 2 initialization (in ways TBD)
     NSI_initialization_complete = true;
    
     // wait for other components to complete initialization
     while ( (system_is_shutting_down == false) &&
     (ready_to_work == false))
     {
         sleep(A_SHORT_TIME);
     }
     // ready to work, check for system shutdown flag periodically
     while (system_is_shutting_down == false) {
     //do a chunk of work and/or sleep for a short time
         
     /* Upon fatal failure, set ready_to_work = true and
     then call NSIcleanupExit( )*/

    
     //NSIcleanupExit();
     // wait for all threads to have exited then returns
     }
    return;
}

/*
*
*/
void *Zigbee_routine(){

}

void *address_map_manager(){
    //gateway info
    unsigned zigbee_macaddr;
    coordinates gateway_coordinates;
    char * gateway_loc_description;
    double gateway_barcode;
    
    //initialize address table
    struct address_map beacon_address [MAX_NUMBER_NODES];
    beacon_join_request(zigbee_macaddr, gateway_coordinates,
                        gateway_loc_description, gateway_barcode);
    while(system_is_shutting_down == false){
        
        //if a new join request||(beacon_count>=32)
        //then beacon_count++;
        //startthread(beacon_join_request());
        
    }
    return;
}

void *beacon_join_request(unsigned ID,coordinates Coordinates,
                         char *Loc_Description[MAX_LENGTH_LOC_DESCRIPTION]
                         ,double Barcode){

    beacon_address[beacon_count-1].network_address = beacon_count-1;//tempt
    beacon_address[beacon_count-1].beacon_id = ID;
    beacon_address[beacon_count-1].beacon_coordinates = Coordinates;
    beacon_address[beacon_count-1].loc_description = Loc_Description;
    beacon_address[beacon_count-1].beacon_barcode = Barcode;
}

void *BHM_routine(){

    for (int i = 0; i<MAX_NUMBER_NODES; i++) {
        /* Default value is true; If beacon is failed, then set to false */
        health_report[i] = true;
    }
    // when initialization completes,
    BHM_initialization_complete = true;
     while (system_is_shutting_down == false) {
    //    do a chunk of work and/or sleep for a short time
         RFHR();
         sleep(PERIOD_TO_MONITOR);
    }
    BHM_cleanup_exit();
    return;
}

void RFHR(){

    int scan_number = 0;
     /*check beacons one by one. Default value is true; If beacon is failed,
     then set to false */
    for(int i = 0; i< MAX_NUMBER_NODES ; i++){
        scan_number++;
        //startthread(send_command_to_beacon)
        //Send signal to the beacon according beaconID
        //Wait till the beacon sends back the health report
        
        if(scan_number == beacon_count)break;
    }
}

void *CommUnit_routine(){

    inti_Command_Queue();
    //when initialization completes,
    CommUnit_initialization_complete = true;
    while (system_is_shutting_down == false) {
     //   do a chunk of work and/or sleep for a short time
            }
    CommUnit_cleanup_exit();
    return;
 }

void inti_Command_Queue(){
    ront = rear = (Command*) malloc(sizeof(Command));
    front->next = rear->next = NULL;
}

Error_code startThread(pthread_t threads ,void * (*thfunct)(void*), void *arg){

    pthread_attr_t attr;

    if ( pthread_attr_init(&attr) != 0
      || pthread_create(&threads, &attr, thfunct, arg) != 0
      || pthread_attr_destroy(&attr) != 0
      || pthread_detach(threads) != 0) {

    return E_START_THREAD;
  }

  return WORK_SCUCESSFULLY;

}

void cleanup_exit(){

    ready_to_work = false;
    send_message_cancelled = true;
    free_list(scanned_list);
    free_list(waiting_list);
    free_list(tracked_object_list);
    free(g_idle_handler);
    free(g_push_file_path);
    return;

}

void error(char * msg){

    perror(msg);
    exit(0);
    
}

int main(int argc, char **argv)
{
    
    /* Define and initialize all importent golbal variables including */
    system_is_shutting_down = false;
    ready_to_work = false;
    initialization_failed = false;
    NSI_initialization_complete = false;
    BHM_initilaization_complete = false;
    CommUnit_initialization_complete = false;

    int return_value;

    pthread_t NSI_routine_thread;

    return_value = startThread(NSI_routine_thread, NSI_routine, NULL);

    if(return_value != WORK_SCUCESSFULLY){

        perror(errordesc[E_START_THREAD].message);
        cleanup_exit();
    }

    pthread_t BHM_routine_thread;

    return_value = startThread(BHM_routine_thread, BHM_routine, NULL);

    if(return_value != WORK_SCUCESSFULLY){

        perror(errordesc[E_START_THREAD].message);
        cleanup_exit();
    }

    pthread_t CommUnit_routine_thread;

    return_value = startThread(CommUnit_thread, CommUnit_routine, NULL);

    if(return_value != WORK_SCUCESSFULLY){

        perror(errordesc[E_START_THREAD].message);
        cleanup_exit();
    }




}

