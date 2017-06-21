//
//  data_structure.c
//  IA_PPP
//
//  Created by pablo ibarra on 12-06-17.
//  Copyright © 2017 pablo ibarra. All rights reserved.
//
#include <stdio.h>
#include "data_structure.h"
#include "string.h"
#define size 200

//Generate a random list of size_list
struct list generate_random_list(int size_list,struct list* params, int seed){
    srand(seed);
    generate_empty_list(size_list, params);
    for(int i = 0; i < params->length; i++){
        change_value(params, i, rand() % 2);
    }
    return*(params);
};

//Generate a matrix
void generate_new_matrix(struct matrix* mat, int nrow, int ncol){
    mat->length=0;
    for(int k =0; k<nrow; k++){
        struct list *new;
        new = malloc(sizeof(struct list));
        
        generate_empty_list(ncol, new);
        if(mat->length == 0){
            mat->first = new;
            mat->last = new;
            mat->length += 1;
        }
        else if(mat->length != 0){
            mat->last->next = new;
            new->prev = mat->last;
            mat->last = new;
            mat->length += 1;
        }
    }
};

//This function generate a empty list with size size_list
struct list generate_empty_list(int size_list,struct list* params){
    params->length=0;
    for(int r = 0; r < size_list; r++){
        struct variable *aux;
        aux = malloc(sizeof(struct variable));
        aux->index = r;
        aux->value = 0;
        if(params->length == 0){
            params->first = aux;
            params->last = aux;
            params->length += 1;
        }
        else if(params->length != 0){
            params->last->next = aux;
            aux->prev = params->last;
            params->last = aux;
            params->length += 1;
        }
    }
    
    return*(params);
};


//This function release memory from the list
void release_list(struct list* params){
    struct variable *aux;
    for (int k = 0; k < params->length; k++) {
        aux = params->first;
        if(params->first->next != NULL){
            params->first = params->first->next;
            free(aux);
        }
        else if(params->first == NULL){
            free(aux);
        }
    }
};

void release_matrix(struct matrix* mat){
    struct list *aux;
    for(int z = 0; z<mat->length;z++){
        aux = mat->first;
        release_list(aux);
        if(mat->first->next != NULL){
            mat->first= mat->first->next;
            free(aux);
        }
        else if(mat->first == NULL){
            free(aux);
        }
    }
};


//This function change a value from a list, the value with index index
void change_value(struct list* params,int index,int value){
    struct variable *aux;
    aux = params->first;
    for (int k = 0; k < params->length; k++) {
        if(aux->index == index){
            aux->value = value;
            break;
        }
        else if(aux->index != index){
            aux = aux->next;
        }
    }
};


//This function get a value from a list, the value with index index
int get_value(struct list* params,int index){
    int value = 0;
    struct variable *aux;
    aux = params->first;
    for (int k = 0; k < params->length; k++) {
        if(aux->index == index){
            value = aux->value;
            break;
        }
        else if(aux->index != index){
            aux = aux->next;
        }
    }
    return(value);
};



//This function read a csv file and generate a list
void generate_list_from_file(const char *filename,struct list* params,struct list* params2, int* periods){
    params->length=0;
    params2->length=0;
    int line = 0;
    FILE *file;
    file = fopen(filename,"r");
    char tempbuf[size];
    char *pt;
    {
        while(fgets(tempbuf,size,file) != NULL){
            int index_counter = 0;
            pt = strtok (tempbuf,",");
            while (pt != NULL) {
                if(line == 2){
                    struct variable *aux;
                    aux = malloc(sizeof(struct variable));
                    int a = atoi(pt);
                    aux->index = index_counter;
                    aux->value = a;
                    index_counter += 1;
                    if(params2->length == 0){
                        params2->first = aux;
                        params2->last = aux;
                        params2->length += 1;
                    }
                    else if(params2->length != 0){
                        params2->last->next = aux;
                        aux->prev = params2->last;
                        params2->last = aux;
                        params2->length += 1;
                    }
                }
                if(line == 1){
                    struct variable *aux;
                    aux = malloc(sizeof(struct variable));
                    int a = atoi(pt);
                    aux->index = index_counter;
                    aux->value = a;
                    index_counter += 1;
                    if(params->length == 0){
                        params->first = aux;
                        params->last = aux;
                        params->length += 1;
                    }
                    else if(params->length != 0){
                        params->last->next = aux;
                        aux->prev = params->last;
                        params->last = aux;
                        params->length += 1;
                    }
                }
                if(line == 0){
                    *periods = atoi(pt);
                }
                pt = strtok (NULL, ",");
            }
            line +=1;
        }
    }
};


