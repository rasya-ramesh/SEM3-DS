int compare_date(struct node*temp,struct node*curr)
{
  if((temp->date).da_year>(curr->date).da_year)
    return 1;
  if((temp->date).da_mon>(curr->date).da_mon)
    return 1;
  if((temp->date).da_day>(curr->date).da_day)
    return 1;
  return 0;
}
int date_equal(struct node *temp,struct node *curr)
{
  if((temp->date).da_year==(curr->date).da_year)
    return 1;
  if((temp->date).da_mon==(curr->date).da_mon)
    return 1;
  if((temp->date).da_day==(curr->date).da_day)
    return 1;
  return 0;
}
void insert(struct node** list)
{
  struct node *temp;
  temp=(struct node*)malloc(sizeof(struct node));
  temp->next=NULL;
  printf("Enter the following details abput your task in this way! \n Name of your task \n Priority in 1-5 \n Date in date month year format");
  char name[100];
  scanf("%s\n",&name );
  int priority;
  scanf("%d\n",&d);
  struct tm date;
  scanf("%d%d%d\n",&date.da_day,&date.da_mon,&date.da_year );
  temp->task=name;
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
  while((curr!=NULL)&&(date_equal(temp,curr)&&(curr->priority<=temp->priority))
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
