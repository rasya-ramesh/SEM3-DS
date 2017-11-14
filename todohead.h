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
    int cnt;
};
int getdig();
void getdat(int*,int*,int*);
void edit_subtask(struct node *p);
void insert(struct node**);
void task_completed(struct node**);
void display(struct node*, int,int);
void display_current(struct node*, int);
void edit_task(struct node** first,struct node * prev,struct node * current);
void task(struct node**);
int compare_date(struct tm,struct tm);
int date_equal(struct node *,struct node*);
int validate_info(int );
int validate_date(struct tm);
void s(struct node*);
struct node * l();
void prompt(struct node*first);
void extension(struct node**first);
struct node* insert_new(struct node *first,struct node *e);
