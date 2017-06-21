//
//  main.c
//  IA_PPP
//
//  Created by pablo ibarra on 12-06-17.
//  Copyright © 2017 pablo ibarra. All rights reserved.
//

#include <stdio.h>
#include "data_structure.h"
#include "simulating_annealing.h"

int main(int argc, const char * argv[]) {
    int temperatura_1 = 5005;
    int temperatura = 0;
    int signal = 0;
    
    /*Variable*/
    struct matrix meet;
    struct matrix visit;
    struct list host_list;
    /*Parameters*/
    struct list capacity;
    struct list crew;
    int n_periods;
    
    /*Initialization*/
    generate_list_from_file("data_files/param1.txt",&capacity,&crew,&n_periods);
    generate_empty_list((int)capacity.length, &host_list);
    generate_new_matrix(&meet, n_periods*(int)crew.length, (int)crew.length);
    generate_new_matrix(&visit, n_periods*(int)crew.length,(int)crew.length);


    /*Evaluation function*/
    srand(1);
    int repeticion,periodo,z,ww,we,rr;

    for(repeticion =0;repeticion<10;repeticion++){
        int temperatura_1 = 5005;
        for(periodo = 1;periodo<n_periods+1;periodo++){
            for(z = 0; z <100;z++){
                if(only_party_on_host(host_list, visit, capacity, crew, meet, 4) == 0 && only_party_on_host(host_list, visit, capacity, crew, meet, 3) == 0 && only_party_on_host(host_list, visit, capacity, crew, meet, 2) == 0 && only_party_on_host(host_list, visit, capacity, crew, meet, 1) == 0 && all_period_constraint(host_list, visit, capacity, crew, meet, n_periods) == 0){
                    printf("stop\n");
                    signal = 1;
                    break;
                }
                temperatura = move_host_list(host_list, visit, capacity, crew, meet, periodo, n_periods, z, temperatura_1);
            }
            if (signal==1){
                break;
            }
        }
        if (signal==1){
            break;
        }
    };


    
    printf("----analysis-----\n");
    printf("----FO-----\n");
    printf("%d ",evaluation_function(host_list, visit, capacity, crew, meet, 1, n_periods));
    printf("%d ",evaluation_function(host_list, visit, capacity, crew, meet, 2, n_periods));
    printf("%d ",evaluation_function(host_list, visit, capacity, crew, meet, 3, n_periods));
    printf("%d\n",evaluation_function(host_list, visit, capacity, crew, meet, 4, n_periods));
    printf("----Capacidad de los botes-----\n");
    printf("%d\n",max_boat_capacity(host_list, capacity,crew));
    printf("----Cantidad de tripulantes-----\n");
    printf("%d\n",max_crew_capacity(crew));
    printf("----Penalizacion_A-----\n");
    printf("%d ",only_party_on_host(host_list, visit, capacity,crew, meet, 1));
    printf("%d ",only_party_on_host(host_list, visit, capacity,crew, meet, 2));
    printf("%d ",only_party_on_host(host_list, visit, capacity,crew, meet, 3));
    printf("%d\n",only_party_on_host(host_list, visit, capacity,crew, meet, 4));
    printf("----Penalizacion B-----\n");
    printf("%d\n",all_period_constraint(host_list, visit, capacity, crew, meet, n_periods));
    
    printf("host_list\n");
    
    for(ww = 0; ww<host_list.length; ww++){
        printf("%d\n",get_value(&host_list, ww));
    }
    
    struct list *new;
    new = visit.first;
    
    printf("meet\n");
    for(we = 0; we<n_periods;we++){
        printf("periodo\n");
        for(rr =0;rr<host_list.length;rr++){
            for(ww = 0; ww<host_list.length; ww++){
                printf("%d ",get_value(new, ww));
            }
            printf("\n");
            new = new->next;
        }
    }
    
    
    
    
    //release_list(&capacity);
    //release_list(&crew);
    //release_list(&host_list);
    //release_matrix(&meet);
    //release_matrix(&visit);
    

    return 0;
}
