# Samarth-trees1.c
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;   
	int H; //Height
}node;
int height(struct node *T)
{
	int a,b;
	if(T==NULL)// checks whether tree is empty or not. 
		return(0);
	if(T->left==NULL)
		a=0;
	else
    	a=1+T->left->H;
	if(T->right==NULL)
		b=0;
	else
		b=1+T->right->H;
	if(a>b)
		return(a);
	else
	    return(b);
}

struct node *RightRotation(struct node *x)
{
	struct node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->H=height(x);
	y->H=height(y);
	return(y);
}
struct node *LeftRotation(struct node *x)
{
	struct node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->H=height(x);
	y->H=height(y);
	return(y);
}

struct node * RightRight(struct node *T)
{
	T=LeftRotation(T);
    printf("Right-Right rotation done\n");
	return(T);
}
struct node * LeftLeft(struct node *T)
{
	T=RightRotation(T);
    printf("Left-Left rotation done\n");
	return(T);
}
struct node * LeftRight(struct node *T)
{
	T->left=LeftRotation(T->left);
  	printf("Right-Left rotation done\n");
	T=RightRotation(T);
        printf("Right-Right rotation done\n");
	return(T);
}
struct node * RightLeft(struct node *T)
{
	T->right=RightRotation(T->right);
        printf("Right-Right rotation done\n");
	T=LeftRotation(T);
        printf("Right-Left rotation done\n");
	return(T);
}
 
int BalancingFactor(struct node *T)
{
	int a,b;
	if(T==NULL)
		return(0);
 	if(T->left==NULL)
		a=0;
	else
		a=1+T->left->H;
	if(T->right==NULL)
		b=0;
	else
		a=1+T->right->H; 
	return(a-b);
}

void inorder(struct node *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		printf("%d(Bf=%d)",T->data,BalacingFactor(T));
		inorder(T->right);
	}
}

struct node * create(struct node *T,int x)
{
	if(T==NULL)
	{
		T=(struct node*)malloc(sizeof(node));
		T->data=x;
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(x > T->data)		// insertion in right subtree
		{
			T->right=create(T->right,x);
			if(BalacingFactor(T)==-2)
				if(x > T->right->data)
					T=RightRight(T);     //RR means right right imbalance,,,so we are performing right right rotation
				else
					T=RightLeft(T);    //RR means right left imbalance,,,so we are performing right left rotation
		}
		else
			if(x < T->data)   //insertion in left subtree
			{
				T->left=create(T->left,x);
				if(BalancingFactor(T)==2)
					if(x < T->left->data)
						T=LeftLeft(T);    //RightRight means left left imbalance,,,so we are performing left left rotation
					else
						T=LeftRight(T);    //LeftRight means left right imbalance,,,so we are performing left right rotation
			}
		T->H=height(T);
		return(T);
}

int main()
{
	struct node *root=NULL;
	int x,n,i,op;
	do
	{
		printf("\n1)Create:");
		printf("\n2)Print:");
		printf("\n3)Quit:");
		printf("\n\nEnter Your Choice:");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1: printf("\nEnter no. of elements:");
					scanf("%d",&n);
					printf("\nEnter tree data:");
					root=NULL;
					for(i=0;i<n;i++)
					{
						scanf("%d",&x);
						root=create(root,x);
					}
					break;
			
			case 2: printf("\n\nInorder sequence:\n");
					inorder(root);
					printf("\n");
					break;			
		}
	}while(op!=3);
	
	return 0;
}
