#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/visitor.h"
#include "../include/database.h"

#define MAX_NAME_LENGTH 100


typedef struct Visitor
{
    /* data */
    int id;
    char name[MAX_NAME_LENGTH];
    time_t check_in_time;
    time_t check_out_time; 
} Visitor;


Visitor *create_visitor(int id, const char *name){
    Visitor *visitor = (Visitor *)malloc(sizeof(Visitor));

    if (visitor == NULL) return NULL;

    visitor->id = id;
    strncpy(visitor->name, name, MAX_NAME_LENGTH, -1);
    visitor->name[MAX_NAME_LENGTH - 1] = '\0';
    visitor->check_in_time = 0;
    visitor->check_out_time = 0;

    return visitor;

}

int visitor_check_in(const char *name){
    time_t now = time(NULL);
    if (!add_visitor_log(name, now)) {
        printf("Failed to add visitor log to database.\n");
        return 0;
    }

    printf("Visitor %s checked in at %s", name, ctime(&now));
    return 1;
}


void free_visitor(Visitor *visitor){
    free(visitor);
}