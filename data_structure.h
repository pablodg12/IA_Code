//
//  data_structure.h
//  IA_PPP
//
//  Created by pablo ibarra on 12-06-17.
//  Copyright © 2017 pablo ibarra. All rights reserved.
//

#ifndef data_structure_h
#define data_structure_h
#include <stdlib.h>

struct matrix{
    size_t length;
    struct list *first;
    struct list *last;
};

struct list {
    size_t length;
    struct variable *first;
    struct variable *last;
    struct list *next;
    struct list *prev;
};

struct variable {
    int index;
    int value;
    struct variable *prev;
    struct variable *next;
};

/* Generate a matrix of nrowxncol */
void generate_new_matrix(struct matrix* mat, int nrow, int ncol);
/* This function generate a list with parameters from a csv */
void generate_list_from_file(const char *filename,struct list* params,struct list* params2, int* periods);
/* Generate empty list with size n */
struct list generate_empty_list(int size_list,struct list* params);
/* Generate empty list with random numbers size n and seed k*/
struct list generate_random_list(int size_list, struct list* params, int seed);
/* Get the value[index] from a list*/
int get_value(struct list* params,int index);
/* Change the value[index] from va list*/
void change_value(struct list* params,int index,int value);
/* Free list*/
void release_list(struct list* params);
/* Free Matrix*/
void release_matrix(struct matrix* mat);






#endif /* data_structure_h */
