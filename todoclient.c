#include "todohead.h"

int main()
{

    struct node *first;
    int ch,x;
    // first=NULL;//pointer to the first node of the list
    first=l();
    prompt(first);
  //  extension(first);
    while(1){
        printf("\n1.Insert Task\n");
        printf("2.View Tasks\n");
        printf("3.View Highest Priority Tasks\n");
        printf("4.View Completed Tasks\n");
        printf("5.Mark Task as Completed\n");
        printf("6.Delete Task\n");
        printf("7.Exit\n");
        scanf("%d",&ch);
        switch(ch){
        case 1:insert(&first);
                break;
        case 2:display(first,6,0);
                break;
        case 3:display(first,2,0);
                break;
        case 4:display(first,6,1);
                    break;
        case 5:task_completed(&first);
                break;
        case 6:delete_task(&first);
                break;
        case 7:s(first);
                exit(0);
                break;
        default: printf("Enter a valid choice.\n");
                break;
        }
    }
}
