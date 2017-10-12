#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct node{
    struct tm date;
    int priority;
    char task[100];
    struct node *next;
    int status; // 1 if completed, 0 if not
};


void insert(struct node**);
void task_completed(struct node**);
void display(struct node*, int,int);
void delete_task(struct node**);
int compare_date(struct tm,struct tm);
int date_equal(struct node *,struct node*);
int validate_info(int ,struct tm);
int validate_priority(int p);
int validate_date(struct tm);
