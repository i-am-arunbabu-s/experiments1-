
/*
 * =====================================================================================
 *
 *       Filename:  linkedlist1.c
 *
 *    Description:  Creation,insertion,reversing and deletion
 *                  of single,double and circular linked list.
 *                  Implementation of stack,heap,binary heap,
 *                  heap operations search algorithms 
 *                  Binary Tree ,Queue Programs Scheduling 
 *                  Algorithms- Priority Scheduling, Shortest 
 *                  Job First, Round Robin Scheduling, First 
 *                  Come First Serve,Vector Program ,Tire 
 *                  Program, Magic Square Puzzle 
 *
 *        Version:  1.0
 *        Created:  Monday 10 April 2023 09:53:51  IST
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
int data;
struct node *ptr;
};
typedef struct node NODE;
struct dnode
{
struct dnode *prev;
int data;
struct dnode *next;
};
typedef struct dnode DNODE;
void create(NODE **);
void display(NODE *);
void insert(NODE **,int,int);
void reversal(NODE **);
NODE *reversalfn1(NODE **);
void reversalfn2(NODE **,NODE **);
unsigned int sizeoflist(NODE *);
int main()
{
    NODE *head,*reversed,*tobereversed,*temp;
    unsigned int u_n32Size,u_n32Data,u_n32Position;
    printf("creating the linked list \n");
    create(&head);
    printf("Displaying the nodes \n");
    printf("\n");
    display(head);
    u_n32Size=sizeoflist(head);
    printf("\n");
    printf("The size of the list is %d\n",u_n32Size);
    printf("Inserting the items in the beginning\n");
    printf("Enter the data to be inserted\n");
    scanf("%d",&u_n32Data);
    insert(&head,0,u_n32Data);
    printf("\n");
    printf("Displaying the nodes \n");
    display(head);
    printf("\n");
    printf("Inserting the items in the end \n");
    printf("Enter the data to be inserted\n");
    scanf("%d",&u_n32Data);
    insert(&head,-1,u_n32Data);
    printf("\n");
    printf("Displaying the nodes \n");
    display(head);
    printf("\n");
    printf("Enter the position in which data to be inserted\n");
    scanf("%d",&u_n32Position);
    printf("Inserting the items in the position %d\n",u_n32Position);
    printf("Enter the data to be inserted\n");
    scanf("%d",&u_n32Data);
    insert(&head,u_n32Position,u_n32Data);
    printf("\n");
    printf("Displaying the nodes \n");
    display(head);
    printf("\n");
    temp=head;
    printf("Reversing the linked list \n");
    reversal(&head);
    printf("Displaying the nodes \n");
    display(head);
    printf("\n");
    head=temp;
    printf("Reversing the linked list preserving the original list\n");
    reversalfn2(&head,&reversed);
    printf("Displaying the nodes \n");
    display(reversed);
    printf("\n");
    printf("Reversing the linked list using return function \n");
    tobereversed=reversalfn1(&head);
    printf("Displaying the nodes \n");
    display(tobereversed);
    printf("\n");
    printf("------------------Single Linked List ---------------------");
    printf("\n");

    


}
unsigned int sizeoflist(NODE *head)
{
    unsigned int count=0;
    while(head!=0)
    {
        count++;
        head=head->ptr;
    }
    return count;
}
void insert(NODE **head,int position,int data)
{
    NODE *temp,*rear=0;
    if(position==0)
    {
        temp=(NODE*)malloc(sizeof(NODE));
        temp->data=data;
        temp->ptr=*head;
        *head=temp;
     }
     if(position==-1)
     {
        rear=*head;
        temp=(NODE*)malloc(sizeof(NODE));
        temp->data=data;
        temp->ptr=0;
        while(rear->ptr!=0)
        {
            rear=rear->ptr;
        }
        rear->ptr=temp;
     }
     if((position<(int)sizeoflist(*head))&&(position>0))
     {
       rear=*head;
       temp=(NODE*)malloc(sizeof(NODE));
       temp->data=data;
       while(--position)
       {    
            rear=rear->ptr;
       }
       temp->ptr=rear->ptr;
       rear->ptr=temp;

     }
    else
     {
        printf("Please enter a number between 1 and the size of the list \n");
     }
}
void create(NODE **head)
{
    NODE *temp,*first=0;
    int choice=1;
    while(choice)
    {
        first=(NODE *)malloc(sizeof(NODE));
        printf("enter the data");
        scanf("%d",&first->data);
        printf("\n");
        if(temp==0)
        {
            *head=first;
        }
        else
        {
            temp->ptr=first;
        }
        temp=first;
        fflush(stdin);
        printf("Do you want to continue or not ?");
        scanf("%d",&choice);
        printf("\n");
    }
}
void display(NODE *head)
{
    while(head!=0)
    {
        printf("%d=>>",head->data);
        head=head->ptr;
    }
}
        
void reversal(NODE **head)
{
    NODE *temp,*newnode,*nodecreated=0;
    temp=*head;
    while(temp!=0)
    {
        newnode=(NODE *)malloc(sizeof(NODE));
        newnode->data=temp->data;
        newnode->ptr=nodecreated;
        nodecreated=newnode;
        temp=temp->ptr;
    }
    *head=newnode;
   
}
NODE *reversalfn1(NODE **head)
{
    NODE *temp,*newnode,*nodecreated=0;
    temp=*head;
    while(temp!=0)
    {
        newnode=(NODE *)malloc(sizeof(NODE));
        newnode->data=temp->data;
        newnode->ptr=nodecreated;
        nodecreated=newnode;
        temp=temp->ptr;
    }
    return newnode;
}
void reversalfn2(NODE **head,NODE **returnhead)
{
    NODE *temp,*newnode,*nodecreated=0;
    temp=*head;
    while(temp!=0)
    {
        newnode=(NODE *)malloc(sizeof(NODE));
        newnode->data=temp->data;
        newnode->ptr=nodecreated;
        nodecreated=newnode;
        temp=temp->ptr;
    }
    *returnhead=newnode;
    
}   

