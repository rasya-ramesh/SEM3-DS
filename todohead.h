#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct sub{
    char subt[100];
    struct sub* next;
};
struct node{
    struct tm date;
    int priority;
    char task[100];
    struct node *next;
    int status; // 1 if completed, 0 if not
    struct sub *s;
    int t;
    int cnt;
};


void insert(struct node**);
void task_completed(struct node**);
void display(struct node*, int,int);
void delete_task(struct node**);
int compare_date(struct node*,struct node*);
int date_equal(struct node *,struct node*);
int validate_info(int ,struct tm);
void s(struct node*);
struct node * l();
