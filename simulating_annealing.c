//
//  simulating_annealing.c
//  IA_PPP
//
//  Created by pablo ibarra on 16-06-17.
//  Copyright © 2017 pablo ibarra. All rights reserved.
//

#include <stdio.h>
#include "data_structure.h"
#include <math.h>



int max_boat_capacity(struct list host_list,struct list capacity,struct list crew){
    int cap = 0;
    for(int t = 0; t <host_list.length; t++){
        cap = cap + get_value(&host_list, t)*(get_value(&capacity, t));
    }
    return(cap);
};

int max_crew_capacity(struct list crew){
    int cap = 0;
    for(int t = 0; t <crew.length; t++){
        cap = cap + get_value(&crew, t);
    }
    return cap;
};

/* Constrain */

int only_party_on_host(struct list host_list, struct matrix visit, struct list capacity, struct list crew, struct matrix meet,int period){
    int exit_signal = 0;
    struct list *new;
    new = visit.first;
    
    struct list *new2;
    new2 = visit.first;
    
    struct list * new_m;
    new_m = meet.first;
    
    for(int c = 0; c<host_list.length*(period-1);c++){
        new = new->next;
        new2 = new2->next;
        new_m = new_m->next;
    }
    
    for(int zz = 0; zz<host_list.length;zz++){
        int auxiliar = 0;
        for(int xx = 0;xx<host_list.length;xx++){
            auxiliar = auxiliar + get_value(new2, zz);
            new2 = new2->next;
        }
        if(get_value(&host_list, zz) + auxiliar != 1){
            exit_signal = exit_signal + 100;
        }
        new2=visit.first;
        auxiliar = 0;
        for(int c = 0; c<host_list.length*(period-1);c++){
            new2 = new2->next;
        }
    }
    
    
    for(int r = 0; r<host_list.length;r++){
        int size = 0;
        for(int t = 0; t<host_list.length; t++){
            if(r != t){
                for(int u = 0; u<host_list.length;u++){
                    if(r != u){
                        if(get_value(new, t)> get_value(&host_list, r)){
                            exit_signal = exit_signal + 100;
                        }
                        if(t<u){
                            if(get_value(new_m, u) < get_value(new, t) + get_value(new, u) -1){
                                exit_signal = exit_signal + 10;
                            }
                        }
                    }
                }
                size = size + get_value(new, t)*get_value(&crew, t)-get_value(&host_list, r)*get_value(&crew, r);;
            }
        }
        if(get_value(&host_list, r)*get_value(&capacity, r) <size){
            exit_signal = exit_signal + 10;
        }
        new = new->next;
    }

    return(exit_signal);
};

int all_period_constraint(struct list host_list, struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int periods){
    int exit_signal = 0;
    int acum = 0;
    struct list *new;
    struct list *new_m;
    
    for (int c = 0; c<host_list.length; c++) {
        
        struct list temporal;
        generate_empty_list((int)host_list.length, &temporal);
        new = visit.first;
        
        struct list meet_list;
        generate_empty_list((int)host_list.length, &meet_list);
        new_m = meet.first;
        
        for(int t = 0;t < periods*host_list.length;t++){
            if(c != (t % host_list.length)){
                change_value(&temporal, t % host_list.length, get_value(&temporal, t % host_list.length)+get_value(new, c));
            }
            if(c < (t % host_list.length)){
                change_value(&meet_list,t % host_list.length, get_value(&meet_list, t % host_list.length)+get_value(new_m, c));
            }
            new = new->next;
            //ojo
            new_m = new_m->next;
        }
        
        for(int k = 0; k<host_list.length;k++){
            acum = acum + get_value(&meet_list, k);
            if(get_value(&temporal, k)>get_value(&host_list, k)){
                exit_signal = exit_signal + 500;
                release_list(&temporal);
                break;
            };
        }
        if(acum>host_list.length){
            exit_signal = exit_signal + 100;
            release_list(&meet_list);
            break;
        }
        
        
    }
    
    
    return(exit_signal);
};

int evaluation_function(struct list host_list,struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int period, int periods){
    int valor = 0;
    int total_crew = 0;
    

    if(max_boat_capacity(host_list, capacity, crew) - max_crew_capacity(crew) <0){
        total_crew = -1*((max_boat_capacity(host_list, capacity, crew) - max_crew_capacity(crew)))*500;
    }
    
    for(int t = 0; t<host_list.length;t++){
        valor = valor + get_value(&host_list, t) + only_party_on_host(host_list, visit, capacity, crew, meet, period) + all_period_constraint(host_list, visit, capacity, crew, meet, periods) + total_crew;
    }
    
    return(valor);
};

void move_host_list(struct list host_list,struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int period, int periods,int iteration, int temperatura){
    if (temperatura == 0){
        temperatura = 1;
    }
    
    struct list *new;
    struct list *new2;
    new = visit.first;
    new2 = meet.first;
    
    for(int c = 0; c<host_list.length*(period-1);c++){
        new = new->next;
        new2 = new2->next;
    }
    
    int temporal = round(((double)rand()/RAND_MAX)*(host_list.length-1));
    
    int actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
    if( get_value( &host_list,temporal) == 0){
        change_value(&host_list, temporal, 1);
        if(evaluation_function(host_list, visit, capacity, crew, meet, period, periods) < actual){
            temperatura = temperatura*(pow(0.99, iteration));
            actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
        }
        else if (evaluation_function(host_list, visit, capacity, crew, meet, period, periods)>actual){
            if(-1*exp((evaluation_function(host_list, visit, capacity, crew, meet, period, periods)-actual)/temperatura)>((double)rand())/RAND_MAX){
                temperatura = temperatura*(pow(0.99, iteration));
                actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
            }
            else{
                change_value(&host_list, temporal, 0);
                
            }
        }
    }
    
    else if( get_value( &host_list,temporal) == 1){
        change_value(&host_list, temporal, 0);
        if(evaluation_function(host_list, visit, capacity, crew, meet, period, periods) < actual){
            temperatura = temperatura*(pow(0.99, iteration));
            actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
        }
        else if (evaluation_function(host_list, visit, capacity, crew, meet, period, periods)>actual){
            if(-1*exp((evaluation_function(host_list, visit, capacity, crew, meet, period, periods)-actual)/temperatura)>((double)rand())/RAND_MAX){
                temperatura = temperatura*(pow(0.99, iteration));
                actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
            }
            else{
                change_value(&host_list, temporal, 1);
                
            }
        }
    }
    
    for(int r = 0; r<host_list.length;r++){
        if (temperatura == 0){
            temperatura = 1;
        }
        
        int temporal2 = round(((double)rand()/RAND_MAX)*(host_list.length-1));
    
        if( get_value(new,temporal2) == 0){
            change_value(new, temporal2, 1*get_value(&host_list, r));
            if(evaluation_function(host_list, visit, capacity, crew, meet, period, periods) < actual){
                temperatura = temperatura*(pow(0.99, iteration));
                change_value(new2, temporal2, 1*get_value(&host_list, r));
                actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
            }
            else if (evaluation_function(host_list, visit, capacity, crew, meet, period, periods)>=actual){
                if(-1*exp((evaluation_function(host_list, visit, capacity, crew, meet, period, periods)-actual)/temperatura)>((double)rand())/RAND_MAX){
                    temperatura = temperatura*(pow(0.99, iteration));
                    change_value(new2, temporal2, 1*get_value(&host_list, r));
                }
                else{
                    change_value(new, temporal2, 0*get_value(&host_list, r));
                    change_value(new2, temporal2, 0*get_value(&host_list, r));
                
                }
            }
        }
    
        else if( get_value(new,temporal2) == 1){
            change_value(new, temporal2, 0*get_value(&host_list, r));
            if(evaluation_function(host_list, visit, capacity, crew, meet, period, periods) < actual){
                temperatura = temperatura*(pow(0.99, iteration));
                change_value(new2, temporal2, 0*get_value(&host_list, r));
                actual = evaluation_function(host_list, visit, capacity, crew, meet, period, periods);
            }
            else if (evaluation_function(host_list, visit, capacity, crew, meet, period, periods)>=actual){
                if(-1*exp((evaluation_function(host_list, visit, capacity, crew, meet, period, periods)-actual)/temperatura)>((double)rand())/RAND_MAX){
                    temperatura = temperatura*(pow(0.99, iteration));
                    change_value(new2, temporal2, 0*get_value(&host_list, r));
                }
                else{
                    change_value(new, temporal2, 1*get_value(&host_list, r));
                    change_value(new2, temporal2, 1*get_value(&host_list, r));
                    
                }
            }
        }

        new=new->next;
        new2=new2->next;
                }
};

