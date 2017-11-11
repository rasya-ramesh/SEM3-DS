#include "todohead.h"

int no_of_tasks=0;

//function to save file
void s(struct node * q){
    remove("dat.txt");
    if (q==NULL)
        return;
    struct node *temp=q;
    FILE *f;
    f=fopen("dat.txt","wb");
    struct sub * temp_sub;

    int i=0,j=0;
    fwrite(&no_of_tasks,sizeof(int),1,f);
    while(i<no_of_tasks){
        j=0;
        if(q->cnt!=0)
            temp_sub=temp->s;
        printf("temp%d:%d\n",i,temp->cnt);
        fwrite(temp,sizeof(struct node),1,f);
        while(j<temp->cnt){
            printf("temp_sub:%s\n",temp_sub->subt);
            fwrite(temp_sub,sizeof(struct sub),1,f);
            temp_sub=temp_sub->next;
            j+=1;
        }
        i+=1;
        temp=temp->next;
    }
}

//function to read file
struct node * l(){

    FILE *f;
    f=fopen("dat.txt","rb");
    if (f==NULL)
        return NULL;
    struct node *head,*prev,*curr;
    // head=NULL;
    int i=0;
    int count;
    fread(&count,sizeof(int),1,f);
    no_of_tasks=count;
    while(i<count){
        curr=(struct node *)malloc(sizeof(struct node));
        fread(curr,sizeof(struct node),1,f);
        curr->next=NULL;
        if (i==0){
            head=curr;
            // printf("%s",head->task);
            prev=curr;
        }
        else{
            prev->next=curr;
            prev=prev->next;
        }
        int cnt=curr->cnt;
        int j=0;
        struct sub *prev_s,*curr_s;
        while(j<curr->cnt){
            curr_s=(struct sub *)malloc(sizeof(struct sub));
            curr_s->next=NULL;
            fread(curr_s,sizeof(struct sub),1,f);
            if(j==0){
                prev_s=curr_s;
                curr->s=prev_s;
            }
            else{
                prev_s->next=curr_s;
                prev_s=prev_s->next;
            }
        j+=1;
        }
        i+=1;
    }

    return head;
}
void display(struct node* temp, int cutoff, int stat){
    if(temp==NULL){
        printf("NO WORK TO DO! GO HAVE SOME FUN!!\n");
        return;
    }
    int i=1;
    while (temp!=NULL) {
        if(temp->priority<cutoff && stat==temp->status){
            printf("\nTask Number : %d\n",i);
            printf("Task Name : %s",temp->task);
            printf("Task Priority : %d\n",temp->priority);
            printf("Submission Date : %d/%d/%d\n",(temp->date).tm_mday,(temp->date).tm_mon,(temp->date).tm_year);
            if(temp->t==1){
                printf("Subtasks:\n");
                int j=1;
                struct sub *prev_s;
                prev_s=temp->s;
                while(prev_s!=NULL){
                    printf("%d. %s",j,prev_s->subt);
                    prev_s=prev_s->next;
                    j+=1;
                }
            }
        }
        temp=temp->next;
        i+=1;
    }
}

int compare_date(struct tm temp,struct tm curr){
    if((temp).tm_year>(curr).tm_year)
        return 1;
    else if((temp).tm_year<(curr).tm_year)
        return 0;
    if((temp).tm_mon>(curr).tm_mon)
        return 1;
    else if((temp).tm_mon<(curr).tm_mon)
        return 0;
<<<<<<< HEAD
    if((temp).tm_wday>(curr).tm_wday)
        return 1;
    else if((temp).tm_wday<(curr).tm_wday)
=======
    if((temp->date).tm_mday>(curr->date).tm_mday)
        return 1;
    else if((temp->date).tm_mday<(curr->date).tm_mday)
        return 0;
    if(curr)
>>>>>>> 967dc0b8f12815a5f1d70d7848e24e7dfe7461d5
        return 0;
    printf("yolo");
    return 2;
}
<<<<<<< HEAD
// int date_equal(struct node *temp,struct node *curr){
//     if((temp->date).tm_year==(curr->date).tm_year)
//       if((temp->date).tm_mon==(curr->date).tm_mon)
//         if((temp->date).tm_wday==(curr->date).tm_wday)
//           return 1;
//     return 0;
// }
=======
int date_equal(struct node *temp,struct node *curr){
    if((temp->date).tm_year==(curr->date).tm_year)
        return 1;
    if((temp->date).tm_mon==(curr->date).tm_mon)
        return 1;
    if((temp->date).tm_mday==(curr->date).tm_mday)
        return 1;
    return 0;
}
>>>>>>> 967dc0b8f12815a5f1d70d7848e24e7dfe7461d5
void insert(struct node** list){
    no_of_tasks+=1;
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->next=NULL;
    printf("Enter the following details! \n");
    char name[100],temp_sub;
    printf("Name of your task : ");
    scanf("\n");
    fgets(name,100,stdin);
    int priority;
    printf("Priority in 1-5 : ");
    scanf("%d",&priority);
    struct tm date;
    printf("Date in DD MM YYYY format : ");
    scanf("%d%d%d",&date.tm_mday,&date.tm_mon,&date.tm_year );

    if(validate_info(priority)==0){
        printf("INVALID PRIORITY\n");
        return;
      }
    switch (validate_date(date)) {

      case -1:
        printf("OOpss Date passed already\n" );
        break;
      case 1:
        printf("Date is Not within a month\n");
        break;
      case 2:
      printf("Good Going,Valiod Date\n");
      break;
    }
    strcpy(temp->task,name);
    temp->priority=priority;
    temp->date=date;
    temp->status=0;
    temp->cnt=0;
    printf("Does this task have subtasks?(y/n)" );
    scanf("\n");
    scanf("%c",&temp_sub);
    if (temp_sub=='y'){
        temp->cnt+=1;
        temp->t=1;
        struct sub *prev_s;
        prev_s=(struct sub*)malloc(sizeof(struct sub));
        printf("Enter subtask : ");
        scanf("\n");
        fgets(prev_s->subt,100,stdin);
        prev_s->next=NULL;
        temp->s=prev_s;
        printf("More subtasks?(y/n)\n");
        scanf("%c",&temp_sub);
        while(temp_sub=='y'){
            temp->cnt+=1;
            printf("Enter subtask : ");
            struct sub *curr_s;
            curr_s=(struct sub*)malloc(sizeof(struct sub));
            char subt0[100];
            scanf("\n");
            fgets(subt0,100,stdin);
            strcpy(curr_s->subt,subt0);
            curr_s->next=NULL;
            prev_s->next=curr_s;
            prev_s=prev_s->next;
            printf("More subtasks?(y/n)\n");
            scanf("%c",&temp_sub);
        }
    }
    else{
        temp->t=0;
    }
    if(*list==NULL){

        *list=temp;
        return;
    }
    struct node *curr;
    struct node *prev;
    prev=NULL;
    curr=*list;
    while((curr!=NULL)&&(compare_date(temp->date,curr->date))){
        prev=curr;
        curr=curr->next;
    }
    if(compare_date(temp->date,prev->date)==2 && prev!=NULL){
        curr=prev;
        while((curr!=NULL)&&compare_date(temp->date,curr->date)==2&&(curr->priority<=temp->priority)){
            prev=curr;
            curr=curr->next;
        }
    }
    if(curr==NULL){
        prev->next=temp;
        return;
    }
    else{
        if(prev==NULL){
            temp->next=curr;
            *list=temp;
        }
        else{
            prev->next=temp;
            temp->next=curr;
        }
    }
}


void delete_task(struct node ** first){
    char a,name[20];
    struct node *current,*prev;
    prev=NULL;
    current=*first;
    printf("\nEnter the name of the task you wish to delete: ");
    scanf("\n");
    fgets(name,100,stdin);
    while((current!=NULL)&&(strcmp(current->task,name)!=0)){
        prev=current;
        current=current->next;
    }
    if(current==NULL)
    printf("This task does not exist\n");

    else{
        printf("Task Name : %s",current->task);
        printf("Task Priority : %d\n",current->priority);
        printf("Submission Date : %d/%d/%d\n",(current->date).tm_mday,(current->date).tm_mon,(current->date).tm_year);
        printf("\nDo you wish to delete above task (y/n) : ");
        scanf("%c",&a);
        if (a=='y'||a=='Y'){
            if(prev==NULL)
                *first=current->next;
            else
                prev->next=current->next;
            free(current);
        }
    }
}

void task_completed(struct node**first){
    struct node *n=*first;
    char name[100];
    printf("\nEnter name of task completed : ");
    scanf("\n");
    fgets(name,100,stdin);
    while(n!=NULL&&strcmp(n->task,name)!=0){
        n=n->next;
    }
    if(n!=NULL){
        if(strcmp(n->task,name)==0){
            n->status=1;
            printf("Congrats on completing a task.\n");
        }
    }
    if (n->status!=1){
        printf("This task does not exist\n");
    }
}
int validate_info(int p){
    if(!(p>=1 && p<=5))
        return 0;
<<<<<<< HEAD
    return 1;
}
int validate_date(struct tm dt)
{
  time_t my_time;
  struct tm *tlocal;
  time(&my_time);
  tlocal=localtime(&my_time);
  struct tm tl;
  tl.tm_wday=tlocal->tm_wday;
  tl.tm_mon=tlocal->tm_mon;
  tl.tm_year=(tlocal->tm_year)+1900;
  int i=compare_date(dt,tl);
    struct tm tmax;
  if(i==1)
  {

    if((tl.tm_mon + 3)>12)
    {
      tmax.tm_mon=((tl.tm_mon)%12)+3;
      tmax.tm_year=tl.tm_year+1;
    }

  }
  else
    return -1;
  int flag=i;
  flag+=compare_date(tmax,dt);
  return flag;
=======
    if(!(dt.tm_mday>0 && dt.tm_mday<=31))
        return 0;
    if(!(dt.tm_mon>0 && dt.tm_mon<=12))
        return 0;
    // if(!((dt.tm_year%10000)==0))
    //     return 0;
    return 1;
}

void prompt(struct node*first)
{
    struct node *current=first;
    int flag1=0,flag2=0;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if(current!=NULL)
        printf("Here are the tasks you have to do today:\n");
    while(current!=NULL)
    {
        if(current->date.tm_mday==timeinfo->tm_mday&&current->date.tm_mon==(timeinfo->tm_mon)+1&&current->date.tm_year==(timeinfo->tm_year)+1900)
        {
            printf("\nTask Name : %s",current->task);
            printf("Task Priority : %d\n",current->priority);
            flag1=1;
        }
        current=current->next;
    }
    if(first!=NULL)
        if(!flag1)
            printf("None");
    current=first;
    if(current!=NULL)
        printf("\nHere are the other tasks you have to do this month:\n");
    while(current!=NULL)
    {
        if(current->date.tm_mon==(timeinfo->tm_mon)+1&&current->date.tm_year==(timeinfo->tm_year)+1900)
        {
            if(current->date.tm_mday!=timeinfo->tm_mday)
            {
                printf("\nTask Name : %s",current->task);
                printf("Task Priority : %d\n",current->priority);
                flag2=1;
            }
        }
        current=current->next;
    }
    if(first!=NULL)
        if(!flag2)
            printf("None\n");
>>>>>>> 967dc0b8f12815a5f1d70d7848e24e7dfe7461d5
}
