//
//  simulating_annealing.h
//  IA_PPP
//
//  Created by pablo ibarra on 13-06-17.
//  Copyright © 2017 pablo ibarra. All rights reserved.
//

#ifndef simulating_annealing_h
#define simulating_annealing_h
#include <stdio.h>

/* Funcion evaluadora */
int evaluation_function(struct list host_list,struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int period, int periods);
/* Maxima capacidad de botes */
int max_boat_capacity(struct list host_list, struct list capacity,struct list crew);
/* Only party on host constraint, this contraint is for a puntual period*/
int only_party_on_host(struct list host_list, struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int period);
/* This constraint is for all period*/
int all_period_constraint(struct list host_list, struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int periods);
/* Movement */
int move_host_list(struct list host_list,struct matrix visit, struct list capacity, struct list crew, struct matrix meet, int period, int periods,int iteration,int temperatura);

int max_crew_capacity(struct list crew);


#endif /* simulating_annealing_h */
