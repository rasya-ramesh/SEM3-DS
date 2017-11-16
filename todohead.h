#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct sub{
    char subt[100];//The name of the subtask
    struct sub* next;//The next pointer to the next subtask
};
struct node{
    struct tm date;//submission date
    int priority;//Priority of task in 1-5
    char task[100];//The name of the task
    struct node *next;//The pointer to next most immediate task
    int status; // 1 if completed, 0 if not
    struct sub *s;//The pointer to list of subtasks assosciated with this array
    int cnt;//The no of subtasks
};
int getdig();//gets character and converts it to be used as a number
void getdat(int*,int*,int*);//function to read date in required format
void edit_subtask(struct node *p);//function to edit subtasks
void insert(struct node**);//function to insert tasks
void task_completed(struct node**);//to mark if the task is completed
void display(struct node*, int,int);//function to display tasks
void display_current(struct node*, int);//function to display required task
void edit_task(struct node** first,struct node * prev,struct node * current);//function to edit tasks as required
void task(struct node**);//function to look for the task to be edited
int compare_date(struct tm,struct tm);//function to compare two dates
int date_equal(struct node *,struct node*);

int validate_info(int );//Validation of priority.
int validate_date(struct tm);//Validation of date ,if its greater than today's date
//returns 1 if greater than or equal to system date ,0 otherwise
void s(struct node*);//function to save file
struct node * l();//function to read file
void prompt(struct node*first);//function to prompt user about the tasks which are due in existing day and month
void extension(struct node**first);//function to give user option to extend date if the submission date of task
// has passed and it hasnt been completed
int isunique(char *);//checks if entered name is unique

void next(struct node *);
