#include "todohead.h"

void display(struct node* temp, int cutoff){
    if(temp==NULL){
        printf("NO WORK TO DO! GO HAVE SOME FUN!!\n");
        return;
    }
    int i=1;
    while (temp!=NULL) {
        if(temp->priority<cutoff){
            printf("Task Number : %d\n",i);
            printf("Task Name : %s",temp->task);
            printf("Task Priority : %d\n",temp->priority);
            printf("Submission Date : %d/%d/%d",(temp->date).tm_wday,(temp->date).tm_mon,(temp->date).tm_year);
        }
        temp=temp->next;
        i+=1;
    }
}

int compare_date(struct node*temp,struct node*curr)
{
  if((temp->date).tm_year>(curr->date).tm_year)
    return 1;
  if((temp->date).tm_mon>(curr->date).tm_mon)
    return 1;
  if((temp->date).tm_wday>(curr->date).tm_wday)
    return 1;
  return 0;
}
int date_equal(struct node *temp,struct node *curr)
{
  if((temp->date).tm_year==(curr->date).tm_year)
    return 1;
  if((temp->date).tm_mon==(curr->date).tm_mon)
    return 1;
  if((temp->date).tm_wday==(curr->date).tm_wday)
    return 1;
  return 0;
}
void insert(struct node** list)
{
  struct node *temp;
  temp=(struct node*)malloc(sizeof(struct node));
  temp->next=NULL;
  printf("Enter the following details! \n");
  char name[100];
  printf("Name of your task : ");
  scanf("%[^\n]s",name);
  int priority;
  printf("\nPriority in 1-5 : ");
  scanf("%d",&priority);
  struct tm date;
  printf("\nDate in DD MM YYYY format : ");
  scanf("%d%d%d",&date.tm_wday,&date.tm_mon,&date.tm_year );
  strcpy(temp->task,name);
  temp->priority=priority;
  temp->date=date;
  temp->status=0;


  if(*list==NULL)
  {
    *list=temp;
    return;
  }
  struct node *curr;
  struct node *prev;
  prev=NULL;
  curr=*list;
  while((curr!=NULL)&&(compare_date(temp,curr)))
  {
    prev=curr;
    curr=curr->next;
  }
  while((curr!=NULL)&&date_equal(temp,curr)&&(curr->priority<=temp->priority))
  {
    prev=curr;
    curr=curr->next;
  }
  if(curr==NULL)
  {
    prev->next=temp;
    return;
  }
  else
  {
    prev->next=temp;
    temp->next=curr;
  }

}


void delete_task(struct node ** first)
{
  char name[20];
  struct node *current,*prev;
  prev=NULL;
  current=*first;
  printf("\nEnter the name of the task you wish to delete: ");
  scanf("%s",name);
  while((current!=NULL)&&(strcmp(current->task,name)==0))
  {
    prev=current;
    current=current->next;
  }
  if(current==NULL)
    printf("This task does not exist\n");
  else if(prev==NULL)
    *first=current->next;
  else
    prev->next=current->next;
  free(current);
}
