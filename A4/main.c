#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define left previous
#define right next

struct data
{
	char firstName[100];
	char lastName[100];
	int age;
	char birthday[100];
};

struct node
{
	struct data nodeData;
	struct node *next;
	struct node *previous;
};

struct queue
{
	struct node *front;
	struct node *rear;
	int num;
};

struct stack
{
	struct node *top;
	int num;
};

struct treeNode
{
	struct data treeNodeData;
	struct treeNode *left;
	struct treeNode *right;
	struct treeNode *nextParent;
};

struct binaryTree
{
	struct treeNode *headRoot;
	int height;
};

struct list
{
	struct node* first;
	struct node* last;
	int length;
};

typedef struct data DATA;
typedef struct node NODE;
typedef struct queue QUEUE;
typedef struct stack STACK;
typedef struct treeNode TREENODE;
typedef struct binaryTree BINARYTREE;
typedef struct list LIST;

QUEUE q;
STACK s;
BINARYTREE bt;
LIST l;


void enqueue(DATA dataToEnqueue);
DATA dequeue();
void push(DATA dataToPush);
DATA pop();
void preOrderTraverse(TREENODE* StartingNode);
void postOrderTraverse(TREENODE* StartingNode);
NODE* inOrderTraverseToLinkedList(TREENODE* StartingNode);
void quickSort(LIST l,NODE* left, NODE* right, int length);

int main()
{
	//while(1)
	{
		q.front = NULL;
		q.rear = NULL;
		q.num = 0;
		
		s.top = NULL;
		s.num = 0;
		
		bt.headRoot = NULL;
		bt.height = 0;
		
		l.first = NULL;
		l.last = NULL;
		l.length = 0;
		
		FILE *fp;
		char buff [100];
		char *splitStr;
		int strType = 1;
		fp = fopen("InputFileTest.dat","r");
		if (fp==NULL)
		{
			printf ("error");
			fclose (fp);
		}
		while(fgets(buff,sizeof(buff),fp)!=NULL)
		{
			splitStr = strtok(buff, " ,\t\n");
			//if((strcmp(splitStr,"")!=0))
			{
				DATA newdata;
				//newdata = malloc(sizeof(DATA));
				while((splitStr != NULL))
				{
					if((strcmp(splitStr,"Captain")==0))
					{
					}
					else
					{
						switch (strType)
						{
							case 1:
							strcpy(newdata.firstName, splitStr);
							strType = 2;
							break;
							case 2:
							strcpy(newdata.lastName, splitStr);
							strType = 3;
							break;
							case 3:
							newdata.age = atoi(splitStr);
							strType = 4;
							break;
							case 4:
							strcpy(newdata.birthday, splitStr);
							strType = 1;
							break;
						}
					}
					splitStr = strtok(NULL," ,\t\n");
				}
				enqueue(newdata);
			}
		}
		
		int i;
		for(i=1;i<=q.num;i++)
		{
			DATA data2; 
			data2 = dequeue();
			enqueue(data2);
		}
		
		printf("Press ENTER to continue\n");
		while (getchar()!='\n') ;
		
		while(q.num>0)
		{
			DATA data3;
			data3 = dequeue();
			push(data3);
		}
		
		while(s.num>0)
		{
			DATA data4;
			data4 = pop();
			enqueue(data4);
		}
		
		int m;
		for(m=1;m<=q.num;m++)
		{
			DATA data5;
			data5 = dequeue();
			printf("%s %s, %d, %s\n",data5.firstName,data5.lastName,data5.age,data5.birthday);
			enqueue(data5);
		}
		
		printf("Press ENTER to continue\n");
		while (getchar()!='\n') ;

		TREENODE* root;
		root = (TREENODE*) malloc(sizeof(TREENODE));
		TREENODE* current;
		current = (TREENODE*) malloc(sizeof(TREENODE));
		TREENODE* nextCurrent;
		nextCurrent = (TREENODE*) malloc(sizeof(TREENODE));
		NODE* nextChild;
		nextChild = (NODE*) malloc(sizeof(NODE));
		root->treeNodeData = q.front->nodeData;
		root->left = NULL;
		root->right = NULL;
		root->next = NULL;
		bt.headRoot = root;
		dequeue();
		nextChild = q.front;
		current = root;
		nextCurrent = root;
		while(q.num>0)
		{
			TREENODE* newChild;
			newChild = (TREENODE*) malloc(sizeof(TREENODE));
			newChild->treeNodeData = nextChild->nodeData;
			newChild->left = NULL;
			newChild->right = NULL;
			newChild->nextParent = NULL;
			if(!current->left)
			{
				current->left = newChild;
				nextCurrent->nextParent = newChild;
				nextCurrent = newChild;
				dequeue();
				nextChild = q.front;
			}
			else if(!current->right)
			{
				current->right = newChild;
				nextCurrent->nextParent = newChild;
				nextCurrent = newChild;
				dequeue();
				nextChild = q.front;
			}
			else if(current->left && current->right)
			{
				current = current->nextParent;
			}
		}
		
		preOrderTraverse(root);
		
		printf("Press ENTER to continue\n");
		while (getchar()!='\n') ;
		
		postOrderTraverse(root);
		
		printf("Press ENTER to continue\n");
		while (getchar()!='\n') ;
		
		NODE* LLNodeLast;
		LLNodeLast = inOrderTraverseToLinkedList(root);
		printf("%s %s, %d, %s\n",l.first->nodeData.firstName,l.first->nodeData.lastName,l.first->nodeData.age,l.first->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->nodeData.firstName,l.first->next->nodeData.lastName,l.first->next->nodeData.age,l.first->next->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->next->nodeData.firstName,l.first->next->next->nodeData.lastName,l.first->next->next->nodeData.age,l.first->next->next->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->next->next->nodeData.firstName,l.first->next->next->next->nodeData.lastName,l.first->next->next->next->nodeData.age,l.first->next->next->next->nodeData.birthday);
		
		printf("Press ENTER to continue to sort\n");
		while (getchar()!='\n') ;
		
		quickSort(l,l.first,l.last,l.length);
		printf("%s %s, %d, %s\n",l.first->nodeData.firstName,l.first->nodeData.lastName,l.first->nodeData.age,l.first->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->nodeData.firstName,l.first->next->nodeData.lastName,l.first->next->nodeData.age,l.first->next->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->next->nodeData.firstName,l.first->next->next->nodeData.lastName,l.first->next->next->nodeData.age,l.first->next->next->nodeData.birthday);
		printf("%s %s, %d, %s\n",l.first->next->next->next->nodeData.firstName,l.first->next->next->next->nodeData.lastName,l.first->next->next->next->nodeData.age,l.first->next->next->next->nodeData.birthday);

		
//		printf("%s\n",root->treeNodeData.firstName);
//		printf("%s\n",root->nextParent->treeNodeData.firstName);
//		printf("%s\n",root->nextParent->nextParent->treeNodeData.firstName);
//		printf("%s\n",root->nextParent->nextParent->nextParent->treeNodeData.firstName);
//	return 0;
	}
}

void enqueue(DATA dataToEnqueue)		//enqueue for a queue
{
	NODE *newnode;
	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->nodeData = dataToEnqueue;
	newnode->previous = q.rear;
	newnode->next = NULL;
	if(q.num==0)
	{
		q.front = newnode;
		q.rear = q.front;
		q.num++;
	}
	else
	{
		q.rear->next = newnode;
		q.rear = newnode;
		q.num++;
	}
	printf("Enqueued %s %s, %d, %s\n", q.rear->nodeData.firstName, q.rear->nodeData.lastName, q.rear->nodeData.age, q.rear->nodeData.birthday);
}

DATA dequeue()
{
	if(q.num<=0)
	{
		printf("ERROR: Queue underflow\n");
	}
	else
	{
		NODE *temp;
		DATA tempData;
		temp = (NODE*)malloc(sizeof(NODE));
		temp = q.front;
		tempData = q.front->nodeData;
		q.front = q.front->next;
		if(q.num!=1) 
		{
			q.front->previous = NULL;
		}
		q.num--;	
		free(temp);
		printf("Dequeued %s %s, %d, %s\n",tempData.firstName,tempData.lastName,tempData.age,tempData.birthday);
		return tempData;
	}
}

void push(DATA dataToPush)
{
	NODE *newnode;
	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->nodeData = dataToPush;
	newnode->previous = NULL;
	newnode->next = s.top;
	if(s.num==0)
	{
		s.top = newnode;
		s.num++;
	}
	else
	{
		s.top->previous = newnode;
		s.top = newnode;
		s.num++;
	}
	printf("Pushed %s %s, %d, %s\n",s.top->nodeData.firstName,s.top->nodeData.lastName,s.top->nodeData.age,s.top->nodeData.birthday);
}

DATA pop()
{
	if(s.num<=0)
	{
		printf("ERROR: Stack underflow\n");
	}
	else
	{
		NODE *temp;
		DATA tempData;
		temp = (NODE*)malloc(sizeof(NODE));
		temp = s.top;
		tempData = s.top->nodeData;
		s.top = s.top->next;
		if(s.num!=1)
		{
			s.top->previous = NULL;
		}
		s.num--;
		free(temp);
		printf("Popped %s %s, %d, %s\n",tempData.firstName,tempData.lastName,tempData.age,tempData.birthday);
		return tempData;
	}
}

void preOrderTraverse(TREENODE* startingNode) 
{
	printf("%s %s, %d, %s\n",startingNode->treeNodeData.firstName,startingNode->treeNodeData.lastName,startingNode->treeNodeData.age,startingNode->treeNodeData.birthday);
	if (startingNode->left != NULL) 
	{
		preOrderTraverse(startingNode->left);
	}
	if (startingNode->right != NULL) 
	{
		preOrderTraverse(startingNode->right);
	}
}

void postOrderTraverse(TREENODE* startingNode) 
{
	if (startingNode->left != NULL) 
	{
		postOrderTraverse(startingNode->left);
	}
	if (startingNode->right != NULL) 
	{
		postOrderTraverse(startingNode->right);
	}
	printf("%s %s, %d, %s\n",startingNode->treeNodeData.firstName,startingNode->treeNodeData.lastName,startingNode->treeNodeData.age,startingNode->treeNodeData.birthday);
}

NODE* inOrderTraverseToLinkedList(TREENODE* startingNode)
{
	NODE* LLNodePrevious;
	NODE* LLNodeNext;
	if (startingNode->left != NULL) 
	{
		LLNodePrevious = inOrderTraverseToLinkedList(startingNode->left);
	}
	if(l.first==NULL)
	{
		NODE* LLNode;
		LLNode = (NODE*) malloc(sizeof(NODE));
		LLNode->nodeData = startingNode->treeNodeData;
		LLNode->next = NULL;
		LLNode->previous = LLNode->next;
		l.first = LLNode;
		l.length++;
		return LLNode;
	}
	else
	{
		NODE* LLNode;
		LLNode = (NODE*) malloc(sizeof(NODE));
		LLNode->nodeData = startingNode->treeNodeData;
		LLNode->next = LLNodeNext;
		LLNode->previous = LLNodePrevious;
		LLNodePrevious->next = LLNode;
		LLNodeNext->previous = LLNode;
		l.length++;
		l.last = LLNode;
		return LLNode;
	}
	if (startingNode->right != NULL) 
	{
		LLNodeNext = inOrderTraverseToLinkedList(startingNode->right);
	}
}

void quickSort( LIST l, NODE* left, NODE* right, int length )
{
	NODE* pivot;
	NODE* temp;
	NODE* initLeft;
	NODE* initRight;
	pivot = (NODE*) malloc(sizeof(NODE));
	temp = (NODE*) malloc(sizeof(NODE));
	initLeft = (NODE*) malloc(sizeof(NODE));
	initRight = (NODE*) malloc(sizeof(NODE));
	int inOrder;
	int leftCount;
	int rightCount;
	inOrder = 1;
	leftCount = 1;
	rightCount = length;
	initLeft = left;
	initRight = right;
	if ( left->nodeData.age == right->nodeData.age )
	{
		return;
	}
//	if ( left->nodeData.age >= left->next->nodeData.age )
//	{
//		pivot = left;
//	}
//	else
//	{
//		pivot = left->next;
//	}
	pivot = left;
	while ( leftCount < rightCount )
	{
		while (( left->nodeData.age < pivot->nodeData.age ) && ( leftCount < rightCount))
		{
			left = left->next;
			leftCount++;
		}
		while (( right->nodeData.age >= pivot->nodeData.age ) && ( leftCount < rightCount))
		{
			right = right->previous;
			rightCount--;
		}
		if ( leftCount != rightCount )
		{
			temp->nodeData = left->nodeData;
			left->nodeData = right->nodeData;
			right->nodeData = temp->nodeData;
			inOrder = 0;
		} 
	} 
	if (inOrder==0)
	{
		quickSort( l, initLeft, left->previous, leftCount+1 );
		quickSort( l, left, initRight, length-leftCount );
	} 
} 