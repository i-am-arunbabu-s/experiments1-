/*
 * =====================================================================================
 *
 *       Filename:  practise2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 13 April 2023 11:21:49  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Arun Babu S (), arun.tata@agappe.in arunbabu.s@tataautocomp.com
 *        Company:  Agappe Diagnostics LTD
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>
struct node
{
    struct node *prev;
    int data;
    struct node *next;
};
typedef struct node DNODE;
void insert(DNODE **,int,int);
void reverse(DNODE **);
void createDoubleLinkedList(DNODE **);
void display(DNODE *);
void reversal(DNODE **);
unsigned int sizeoflist(DNODE *);
int main()
{
        DNODE *head,*temp;
        int n32Value,n32Position;
        printf("Creating the double linked list\n");
        createDoubleLinkedList(&head);
        printf("\n");
        printf("---------------------------------------------------------------------\n");
        printf("Displaying Double Linked List Nodes");
        printf("\n");
        display(head);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("\nthe size of list %d\n",sizeoflist(head));
        printf("---------------------------------------------------------------------\n");
        printf("Enter the value to insert : ");
        scanf("%d",&n32Value);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        insert(&head,0,n32Value);
        printf("Displaying Double Linked List Nodes afer inserting in the begining");
        printf("\n");
        display(head);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("\nthe size of list %d\n",sizeoflist(head));
        printf("--------------------------------------------------------------------\n");
        printf("Enter the value to insert : ");
        scanf("%d",&n32Value);
        printf("\n");
        insert(&head,-1,n32Value);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("Displaying Double Linked List Nodes afer inserting in the end ");
        printf("\n");
        display(head);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("\nthe size of list %d\n",sizeoflist(head));
        printf("--------------------------------------------------------------------\n");
        printf("enter the position in which value is to insert : ");
        scanf("%d",&n32Position);
        printf("\n");
        printf("Enter the value to insert : ");
        scanf("%d",&n32Value);
        printf("\n");
        insert(&head,n32Position,n32Value);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("Displaying Double Linked List Nodes afer inserting in the position : %d ",n32Position);
        printf("\n");
        display(head);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("\nthe size of list %d\n",sizeoflist(head));
        printf("--------------------------------------------------------------------\n");
        printf("Displaying Double Linked List Nodes afer reversing ");
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        temp=head;
        reversal(&temp);
        display(temp);
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        



}
void createDoubleLinkedList(DNODE **head)
{
        DNODE *temp,*first=0;
        int choice=1;
        while(choice)
        {
                first=(DNODE*)malloc(sizeof(DNODE));
                printf("Enter the data : \n");
                scanf("%d",&first->data);
                first->prev=-0;
                first->next=0;
                if(temp==0)
                {
                    *head=first;
                }
                else
                {
                    first->prev=temp;
                    temp->next=first;
                }
                temp=first;
                fflush(stdin);
                printf("Do you want to continue or not ? ");
                scanf("%d",&choice);
                printf("\n");
        }
}
void display(DNODE *head)
{
        while(head!=0)
        {
            printf("%d==>",head->data);
            head=head->next;
        }
}
unsigned int sizeoflist(DNODE *head)
{
    unsigned int count=0;
    while(head!=0)
    {
        count++;
        head=head->next;
    }
    return count;
}
void insert(DNODE **head,int position,int value)
{       
        DNODE *temp,*rear=0;
        if(position==0)
        {
            rear=*head;
            temp=(DNODE*)malloc(sizeof(DNODE));
            temp->data=value;
            temp->prev=0;
            temp->next=rear;
            rear->prev=temp;
            *head=temp;
        }
        if(position==-1)
        {
            rear=*head;
            while(rear->next!=0)
            {
                rear=rear->next;
            }
            temp=(DNODE*)malloc(sizeof(DNODE));
            temp->data=value;
            temp->next=0;
            rear->next=temp;
            temp->prev=rear;
            
        }

       if((position>0) && (position<(sizeoflist(*head))))
       {
            rear=*head;
            temp=(DNODE*)malloc(sizeof(DNODE));
            temp->data=value;
            //temp->prev=0;
            //temp->next=0;
            while(--position)
            {
                rear=rear->next;
            }
            temp->prev=rear;
            temp->next=rear->next;
            rear->next=temp;
            rear=temp->next;
            rear->prev=temp;
       }
       else
       {
            printf("\nEnter position number less than the current size of the list\n");
       } 
}
void reversal(DNODE **head)
{
      DNODE *temp,*created=0;
      temp=*head;
      while(temp!=0)
      {
           created=temp->prev;
           temp->prev=temp->next;
           temp->next=created;
           temp=temp->prev;
      }
      if(created!=0)
      {    
            *head=created->prev;
      }
      
}
