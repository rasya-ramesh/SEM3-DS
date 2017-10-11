#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node{
    struct tm date;
    int priority;
    char task[100];
    struct node *next;
    int status; // 1 if completed, 0 if not
};


void insert(struct node**);
void task_completed(struct node**);
void display(struct node*);
void delete_task(struct node**);
