#include "todohead.h"

int main()
{
    struct node *first;
    int ch,x;
    first=NULL;//pointer to the first node of the list

    while(1){
        printf("\n1.Insert Task\n");
        printf("2.View Tasks\n");
        printf("3.View Highest priority tasks\n");
        printf("4.Mark Task as Completed\n");
        printf("5.Delete Task\n");
        printf("6.Exit\n");
        scanf("%d",&ch);
        switch(ch){
        case 1:insert(&first);
                break;
        case 2:display(first,6);
                break;
        case 3:display(first,2);
                break;
        case 4:
        task_completed(&first);
                break;
        case 5:delete_task(&first);
                break;
        case 6:exit(0);
                break;
        default: printf("Enter a valid choice.\n");
                break;
        }
    }
}
