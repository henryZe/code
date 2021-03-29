#include<malloc.h>

#define ERROR 0
#define FALSE 0
#define TURE  1
#define OK    1
#define Flase 0
#define error 0
#define Ture  1

typedef struct BT{
  struct BT *lchild,*rchild;
  char data;
} BTNode,*BiTree;

typedef BiTree QElemType;

typedef struct Node{
      QElemType data;
      struct Node *next;
}  QNode,*QueuePtr;

typedef struct{
      QueuePtr front;
      QueuePtr rear;
} LinkQueue;

int InitQueue(LinkQueue *Q){
    Q->rear=(QueuePtr)malloc(sizeof(QNode));
    Q->front=Q->rear;
   if(Q->front) {Q->rear->next=NULL;return OK;}
   else return ERROR;
  }

int DestroyQueue(LinkQueue *Q){
 QueuePtr p,q;
 p=Q->front;
 while(Q->front){
    q=p->next;
    free(p);
    p=q;} 
if(!(Q->front)) return OK;
else return ERROR;
}

int ClearQueue(LinkQueue *Q){
  free(Q->front->next);
  Q->rear=Q->front;
  Q->rear->next=NULL;
  return OK;
}

int QueueEmpty(LinkQueue *Q){
 if(Q->front==Q->rear) return OK;
 else return ERROR;
}

int QueueLength(LinkQueue Q){
     return ((Q.rear)-(Q.front));
}

int GetHead(LinkQueue Q,QElemType *e){
   if(QueueLength(Q)) {*e=(Q.front)->next->data;return OK;}
   else return ERROR;
}

int EnQueue(LinkQueue *Q,QElemType e){
   QueuePtr p;
   p=(QueuePtr)malloc(sizeof(QNode));
   if(p) {Q->rear->data=e;
          p->next=NULL;
          Q->rear->next=p;
          Q->rear=p;
         return  OK; }
   else return ERROR;
}

int DeQueue(LinkQueue *Q,QElemType *e){
  QueuePtr p;
 if(Q->rear!=Q->front){
  p=Q->front;
  *e=Q->front->data;
  Q->front=Q->front->next;
  p=NULL;
  free(p);
  return OK;
  }
 else return ERROR;
}


int CreateBiTree(BiTree *T){/*建立二叉树*/
    
    int temp=1;
    char xh,ch;
    scanf("%c",&xh);
    ch=xh;
    //while(temp&&ch != '\n')
    {
        scanf("%c",&ch);
	printf("---------%c\n",ch);
        temp=0;
    }

    if(ch == '#') 
    {
//	    (*T)=NULL;
	    return ;
    }
    else 
    {
	  if(!((*T)=(BiTree)malloc(sizeof(BTNode))))  return ERROR;
           (*T)->data=ch;
	   CreateBiTree(&((*T)->lchild));
	   CreateBiTree(&((*T)->rchild));
    }
    return OK;
}

void InOrderTraverse(BiTree T)
{/*中序遍历二叉树*/
  if(T)
  { 
	  InOrderTraverse(T->lchild);
          printf("%c",T->data);
          InOrderTraverse(T->rchild);
  }
}

void PreOrderTraverse(BiTree T)
{/*先序遍历二叉树*/
   if(T)
   { 
	   printf("%c",T->data);
           PreOrderTraverse(T->lchild);
	   PreOrderTraverse(T->rchild);
   }
}


void LevelOrderTraverse(BiTree T)
{/*层序遍历二叉树*/
  LinkQueue Q;
  BiTree p;
  if(T->data)
  {
  	InitQueue(&Q);
  	EnQueue(&Q,T);
  	while(Q.rear!=Q.front)
  	{
  		DeQueue(&Q,&p);
		printf("%c",p->data);
	  	T=p;
  		if(T->lchild)EnQueue(&Q,T->lchild);
	  	if(T->rchild)EnQueue(&Q,T->rchild);
  	}
  }
}


void PostOrderTraverse(BiTree T)
{/*后序遍历二叉树*/
   if(T)
   {  
	   PostOrderTraverse(T->lchild);
           PostOrderTraverse(T->rchild);
	   printf("%c",T->data);
   }
}


int main()
{
	BiTree T;
 	CreateBiTree(&T);
	printf("the InOrderTraverse :\n");
	InOrderTraverse(T);
	printf("\n the PreOrderTraverse:\n");
	PreOrderTraverse(T);
	printf("\n the PostOrderTraverse:\n");
 	PostOrderTraverse(T);
 	printf("\n the LevelOrderTraverse:\n");
 	LevelOrderTraverse(T);
	return 0;
}


