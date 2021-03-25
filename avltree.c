#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
char data;
struct node *left,*right;
int ht;
}node;
node *insert(node *,char);
node *Delete(node *,char);
void preorder(node *);
void inorder(node *);
void postorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
int main()
{
node *root=NULL;
int n,i,op;
char x,st[1000];
int count[26] = {0}, f;
do
{
printf("\n|---MAIN MENU---|\n");
printf("1)Create:");
printf("\n2)Insert:");
printf("\n3)Display:");
printf("\n4)Delete:");
printf("\n5)Frequency:");
printf("\n6)Exit:");
printf("\n\nEnter Your Choice:");
scanf("%d",&op);
switch(op)
{
case 1: printf("\nEnter the data to create:");
scanf(" %s",st);
n=strlen(st);
root=NULL;
for(i=0;i<n;i++)
{
root=insert(root,st[i]);
}
printf("***Data was created succesfully***\n");
break;
case 2: printf("\nEnter a Character to insert:");
scanf(" %c",&x);
root=insert(root,x);
printf("***Data was inserted succesfully***\n");
break;
case 3:
do
{
printf("\n\n|---Which order to diplay---|");
printf("\n1.Inorder\n2.Postorder\n3.Preorder\n4.Exit from display\n");
printf("\nEnter the choice to display order:");
scanf("%d",&n);
switch(n)
{
case 1:
printf("\n---> Inorder:\n");
inorder(root);
break;
case 2:
printf("\n---> Postorder:\n");
postorder(root);
break;
case 3:
printf("\n---> Preorder:\n");
preorder(root);
break;
}
}while(n<=3);
break;
case 4: printf("\nEnter a data to delete:");
scanf(" %c",&x);
root=Delete(root,x);
printf("***Data was deleted succesfully***\n\n");
break;
case 5: printf("\nFrequency of given data:\n");
n=strlen(st);
for(i=0;i<n;i++){
if (st[i] >= 'a' && st[i] <= 'z')
{
f= st[i] - 'a';
count[f]++;
}
}
for (i = 0; i< 26; i++)
printf("%c occurs %d times in the string.\n", i+ 'a', count[i]);
break;
case 6: printf("\n----Thank you have a nice day----\n");
printf("*****Developed By Venkata Sai Sabbineni*****\n");
printf("*****Come with back new updates*****\n");
return 0;
}
}while(op!=7);
return 0;
}
node * insert(node *T,char x)
{
if(T==NULL)
{
T=(node*)malloc(sizeof(node));
T->data=x;
T->left=NULL;
T->right=NULL;
}
else
if(x > T->data)
{
T->right=insert(T->right,x);
if(BF(T)==-2)
if(x>T->right->data)
T=RR(T);
else
T=RL(T);
}
else
if(x<T->data)
{
T->left=insert(T->left,x);
if(BF(T)==2)
if(x < T->left->data)
T=LL(T);
else
T=LR(T);
}
T->ht=height(T);
return(T);
}
node * Delete(node *T,char x)
{
node *p;
if(T==NULL)
{
return NULL;
}
//Done By Venkata Sai Sabbineni
else
if(x > T->data)
{
T->right=Delete(T->right,x);
if(BF(T)==2)
if(BF(T->left)>=0)
T=LL(T);
else
T=LR(T);
}
else
if(x<T->data)
{
T->left=Delete(T->left,x);
if(BF(T)==-2)
if(BF(T->right)<=0)
T=RR(T);
else
T=RL(T);
}
else
{
if(T->right!=NULL)
{
p=T->right;
while(p->left!= NULL)
p=p->left;
T->data=p->data;
T->right=Delete(T->right,p->data);
if(BF(T)==2)
if(BF(T->left)>=0)
T=LL(T);
else
T=LR(T);\
}
else
return(T->left);
}
T->ht=height(T);
return(T);
}
int height(node *T)
{
int lh,rh;
if(T==NULL)
return(0);
if(T->left==NULL)
lh=0;
else
lh=1+T->left->ht;
if(T->right==NULL)
rh=0;
else
rh=1+T->right->ht;
if(lh>rh)
return(lh);
return(rh);
}
node * rotateright(node *x)
{
node *y;
y=x->left;
x->left=y->right;
y->right=x;
x->ht=height(x);
y->ht=height(y);
return(y);
}
node * rotateleft(node *x)
{
node *y;
y=x->right;
x->right=y->left;
y->left=x;
x->ht=height(x);
y->ht=height(y);
return(y);
}
node * RR(node *T)
{
T=rotateleft(T);
return(T);
}
node * LL(node *T)
{
T=rotateright(T);
return(T);
}
node * LR(node *T)
{
T->left=rotateleft(T->left);
T=rotateright(T);
return(T);
}
node * RL(node *T)
{
T->right=rotateright(T->right);
T=rotateleft(T);
return(T);
}
int BF(node *T)
{
int lh,rh;
if(T==NULL)
return(0);
if(T->left==NULL)
lh=0;
else
lh=1+T->left->ht;
if(T->right==NULL)
rh=0;
else
rh=1+T->right->ht;
return(lh-rh);
}
void preorder(node *T)
{
if(T!=NULL)
{
printf("%c->(Bf=%d) ",T->data,BF(T));
preorder(T->left);
preorder(T->right);
}
}
void inorder(node *T)
{
if(T!=NULL)
{
inorder(T->left);
printf("%c->(Bf=%d) ",T->data,BF(T));
inorder(T->right);
}
}
void postorder(node *T)
{
if(T!=NULL)
{
postorder(T->left);
postorder(T->right);
printf("%c->(Bf=%d) ",T->data,BF(T));
}
}
