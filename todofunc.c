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
    while(temp!=NULL){
        j=0;
        if(q->cnt!=0)
            temp_sub=temp->s;
        fwrite(temp,sizeof(struct node),1,f);
        while(temp_sub!=NULL){
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

void display_current(struct node*current,int i){
    printf("\n%d. Task Name : %s",i,current->task);
    printf("Task Priority : %d\n",current->priority);
    printf("Submission Date : %d/%d/%d\n",(current->date).tm_mday,(current->date).tm_mon,(current->date).tm_year);
    struct sub *subtask=current->s;
    if(subtask!=NULL)
        printf("Here are the subtasks for this task: ");
    int j=1;
    while(subtask!=NULL){
        printf("\n\t%d. Subtask Name: %s",j,subtask->subt);
        j++;
        subtask=subtask->next;
    }
}


void display(struct node* temp, int cutoff, int stat){
    if(temp==NULL){
        printf("NO WORK TO DO! GO HAVE SOME FUN!!\n");
        return;
    }
    int i=1;
    while (temp!=NULL) {
        if(temp->priority<cutoff && stat==temp->status){
            display_current(temp,i);
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
    if((temp).tm_mday>(curr).tm_mday)
        return 1;
    else if((temp).tm_mday<(curr).tm_mday)
        return 0;
    return 2;
}
// int date_equal(struct node *temp,struct node *curr){
//     if((temp->date).tm_year==(curr->date).tm_year)
//       if((temp->date).tm_mon==(curr->date).tm_mon)
//         if((temp->date).tm_wday==(curr->date).tm_wday)
//           return 1;
//     return 0;
// }

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
    printf("Priority in 1-5 : ");
    int priority;
    reset_priority:
    scanf("%d",&priority);
    if(validate_info(priority)==0){
        printf("INVALID PRIORITY\n");
        printf("Enter the priority again: ");
        goto reset_priority;
     }
    printf("Submission Date in DD MM YYYY format : ");
    struct tm date;
    reset_date:
    scanf("%d%d%d",&date.tm_mday,&date.tm_mon,&date.tm_year );
    //See whether you have to deallocate the memory before returning
    if(validate_date(date)==0){
        printf("INVALID INPUT\n");
        printf("Enter valid date in DD MM YYYY format: ");
        goto reset_date;
    }
    if(validate_date(date)==2){
        printf("That task is far into the future, chill.\n");
        printf("Enter valid date in DD MM YYYY format: ");
        goto reset_date;
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

void edit_task(struct node** first,struct node * prev,struct node * current){
    printf("\n1.Delete Current Task\n2.Edit Current Task Submission Date\n3.Edit Current Task Priority\n");
    int ch,nos=0;
    scanf("%d",&ch);
    char subtname[100];
    switch (ch){
        case 1:
            if(prev==NULL)
                *first=current->next;
            else
                prev->next=current->next;
            free(current);

            no_of_tasks-=1;
            break;
        case 2:
            printf("\nSubmission Date in DD MM YYYY format : ");
            struct tm date;
            reset_date:
            scanf("%d%d%d",&date.tm_mday,&date.tm_mon,&date.tm_year );
            //See whether you have to deallocate the memory before returning
            if(validate_date(date)==0){
                printf("INVALID INPUT\n");
                printf("Enter valid date in DD MM YYYY format: ");
                goto reset_date;
            }
            if(validate_date(date)==2){
                printf("That task is far into the future, chill.\n");
                printf("Enter valid date in DD MM YYYY format: ");
                goto reset_date;
            }
            current->date=date;

            break;
        case 3:
            printf("Priority in 1-5 : ");
            int priority;
            reset_priority:
            scanf("%d",&priority);
            if(validate_info(priority)==0){
                printf("INVALID PRIORITY\n");
                printf("Enter the priority again: ");
                goto reset_priority;
             }
             current->priority=priority;
            break;
    }
}

void task(struct node ** first){
    char name[20];
    int ch;
    struct node *current,*prev;
    prev=NULL;
    current=*first;
    printf("\nEnter the name of the task you wish to edit/delete: ");
    scanf("\n");
    fgets(name,100,stdin);
    while((current!=NULL)&&(strcmp(current->task,name)!=0)){
        prev=current;
        current=current->next;
    }
    if(current==NULL)
        printf("This task does not exist\n");

    else{
        display_current(current,1);
        printf("\nDo you wish to edit/delete above \n1. Task\n2. Subtasks: ");
        scanf("%d",&ch);
        switch (ch) {
          case 1:

            edit_task(first,prev,current);
            break;
          case 2:

            edit_subtask(current);
            break;
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
    return 1;
}

int validate_date(struct tm dt){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if((timeinfo->tm_year)+1900>dt.tm_year)
        return 0;
    if(dt.tm_year>(timeinfo->tm_year)+1902)
        return 2;
    if((timeinfo->tm_mon)+1>dt.tm_mon||(dt.tm_mon>12))
        return 0;
    if(timeinfo->tm_mday>dt.tm_mday)
        return 0;
    switch(dt.tm_mon){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
                if(dt.tm_mday>31)
                    return 0;
                break;
        case 4:
        case 6:
        case 9:
        case 11:
                if(dt.tm_mday>30)
                    return 0;
                break;
        case 2:
                if((1900+dt.tm_year)%4 == 0){
                    if((1900+dt.tm_year) %100 == 0){
                        if ((1900+dt.tm_year)%400 == 0){
                            if(dt.tm_mday>29)
                                return 0;
                        }
                        else{
                            if(dt.tm_mday>28)
                                return 0;
                        }
                    }
                    else{
                        if(dt.tm_mday>29)
                            return 0;
                    }
                }
                else{
                    if(dt.tm_mday>28)
                        return 0;
                }
                break;
    }
    return 1;
}

void prompt(struct node*first){
    struct node *current=first;
    int flag1=0,flag2=0;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if(current!=NULL)
        printf("Here are the tasks you have to do today:\n");
    int i=1;
    while(current!=NULL){
        if(current->date.tm_mday==timeinfo->tm_mday&&current->date.tm_mon==(timeinfo->tm_mon)+1&&current->date.tm_year==(timeinfo->tm_year)+1900){
            display_current(current,i);
            flag1=1;
            i++;
        }
        current=current->next;
    }
    if(first!=NULL)
        if(!flag1)
            printf("None");
    current=first;
    i=1;
    if(current!=NULL)
        printf("\nHere are the other tasks you have to do this month:\n");
    while(current!=NULL){
        if(current->date.tm_mon==(timeinfo->tm_mon)+1&&current->date.tm_year==(timeinfo->tm_year)+1900){
            if(current->date.tm_mday!=timeinfo->tm_mday){
                display_current(current,i);
                flag2=1;
                i++;
            }
        }
        current=current->next;
    }
    if(first!=NULL)
        if(!flag2)
            printf("None\n");
}



void extension(struct node **first){}
/*
void extension(struct node **first)

{
  time_t my_time;
  struct tm *tlocal;
  time(&my_time);
  tlocal=localtime(&my_time);
  struct tm tl;
  tl.tm_mday=tlocal->tm_mday;
  tl.tm_mon=tlocal->tm_mon+1;
  tl.tm_year=(tlocal->tm_year)+1900;
  //now tl has the present sytem date.
  struct node*curr;
  curr=*first;
  struct node*prev=NULL;
  reset_loop:
  while(curr!=NULL)
  {
    //printf("System Date : %d/%d/%d\n",tl.tm_mday,tl.tm_mon,tl.tm_year);
    int v=compare_date(tl,curr->date);
    if(v==1)//local date is greater than task submission date
    {
        printf("Deadline is Over for the task");
        printf("Task Name : %s",curr->task);
        printf("Task Priority : %d\n",curr->priority);
        printf("Submission Date : %d/%d/%d\n",(curr->date).tm_mday,(curr->date).tm_mon,(curr->date).tm_year);
        if(curr->s!=NULL)
        {
            printf("Subtasks:\n");
            int j=1;
            struct sub *prev_s;
            prev_s=curr->s;
            while(prev_s!=NULL)
            {
                printf("%d. %s",j,prev_s->subt);
                prev_s=prev_s->next;
                j+=1;
            }
        }
        printf("Make a choice\n1. Enter new Submission Date\n2. Delete the task\n");
        int choice;
        struct node *p;
        p=curr;
        scanf("%d",&choice );
        switch (choice)
        {
            case 1:
            if(prev==NULL)
                *first=curr->next;
            else
                prev->next=curr->next;
            *first=insert_new(*first,p);
            curr=*first;
            free(p);
            goto reset_loop;
            break;
        }
    }//END OF IF
     prev=curr;
     curr=curr->next;
 }//END OF WHILE
}
struct node* insert_new(struct node *first,struct node *e)
{
  struct node *temp;
  temp=(struct node*)malloc(sizeof(struct node));
  temp->next=NULL;
  printf("Date in DD MM YYYY format : ");
  struct tm date;
  reset_date:
  scanf("%d%d%d",&date.tm_mday,&date.tm_mon,&date.tm_year );
  //See whether you have to deallocate the memory before returning
  if(validate_date(date)==0){
      printf("INVALID INPUT\n");
      printf("Enter valid date in DD MM YYYY format: ");
      goto reset_date;
  }
  if(validate_date(date)==2)
  {
      printf("That task is far into the future, chill.\n");
      printf("Enter valid date in DD MM YYYY format: ");
      goto reset_date;
  }
  strcpy(temp->task,e->task);
  temp->priority=e->priority;
  temp->date=e->date;
  temp->status=0;
  temp->cnt=e->cnt;
  temp->s=e->s;
  if(first==NULL){
        first=temp;
        return first;
  }
  struct node *curr;
  struct node *prev;
  prev=NULL;
  curr=first;
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
        return first;
    }
  else{
        if(prev==NULL){
            temp->next=curr;
            first=temp;
        }
        else{
            prev->next=temp;
            temp->next=curr;
        }
    }
  return first;
}*/
void edit_subtask(struct node *p){
    //@RADHIKA WHAT IS THIS p WHAT's THIS NAMING SCHEME LEMME SEE IF YOU FIND THIS COMMENT -_-

    if(p->cnt!=1){
        printf("\n1.Delete All Subtasks\n2.Delete a particular Subtask\n3.Edit a particular Subtask\n");
        struct sub *curr_s;
        curr_s=p->s;
        struct sub *prev_s;
        prev_s=NULL;
        int ch,nos=0;
        scanf("%d",&ch);
        char subtname[100];
        switch (ch){
            case 1:
                while(curr_s!=NULL){
                    prev_s=curr_s;
                    curr_s=curr_s->next;
                    free(prev_s);
                    prev_s=NULL;
                }
                p->s=NULL;
                p->cnt=0;
                break;
            case 2:
            case 3:
                printf("Enter subtask no.: ");
                int index=1,input;
                scanf("%d",&input);
                if(input>p->cnt||input<1){
                    printf("\n Number out of range. Try Again." );
                    return;
                }
                struct sub *curr_s=p->s;
                struct sub *prev_s=NULL;
                while((curr_s!=NULL)&&(index<input)){
                    prev_s=curr_s;
                    curr_s=curr_s->next;
                    index+=1;
                    //nos+=1;
                }
                if(curr_s==NULL)
                    printf("NOT FOUND!\n" );
                else{
                    if(ch==2){
                        if(prev_s== NULL)
                            p->s=curr_s->next;
                        else
                            prev_s->next=curr_s->next;
                        p->cnt--;
                        free(curr_s);
                        if(p->cnt==0){
                            p->s=NULL;
                        }
                    }
                    if(ch==3){
                        printf("\nEnter changed subtask : ");
                        char subt0[100];
                        scanf("\n");
                        fgets(subt0,100,stdin);
                        strcpy(curr_s->subt,subt0);
                    }
                }
        }
    }
  else
    printf("No subtasks\n");
}
