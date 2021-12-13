#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct address{
	char telephone[20];
	char name[20];
	char email[20];
};
typedef struct address address;
int Bsearch(address A[],int start,int finish,char b[]){
	int middle = (start + finish)/2;
	if(start == finish){
		if(strcmp(A[middle].name,b)==0) return middle;
		else return -1;
	}
	if(strcmp(A[middle].name,b)==0){
		return middle;
	}
	if(strcmp(A[middle].name,b)<0){
		return Bsearch(A,middle+1,finish,b);
	}
	else Bsearch(A,start,middle-1,b);
}
void task1(){
	FILE *f;
	f = fopen("baithi/test.txt","r");
	address A[100];
	address value;
	int i;
	for(i=0;i<10;i++){
		fscanf(f,"%s\t",value.name);
		fscanf(f,"%s\t",value.telephone);
		fscanf(f,"%s\n",value.email);
		A[i] = value;
	}
	fclose(f);
	printf("nhap ten can tim: ");
	char tim[31];
	fflush(stdin);
	gets(tim);
	int a = Bsearch(A,0,9,tim);
	if(a == -1) printf("khong tim thay trong danh sach\n");
	else printf("%-20s%-20s%-20s\n",A[a].name,A[a].telephone,A[a].email);
}
struct node{
	address data;
	struct node *next;
};
typedef struct node node;
node *createNode(address x){
    node *temp = (node*)malloc(sizeof(node));
    temp->next = NULL;
    temp->data = x;
    return temp;
}
void printList(node *l){
	node *p = l;
	while (p != NULL){
		printf("%-20s%-20s%-20s\n",p->data.name,p->data.telephone,p->data.email);
		p = p->next;
	}
}
node *addElement(node*p, address x){
	node *temp = createNode(x);
	p->next = temp;
	return temp;
}
node *searchNode(node *l,address x){
	node *p = l;
	while(p != NULL){
		if(strcmp(p->data.name,x.name)==0) return p;
		p = p->next;
	}
	return NULL;
}
void task2(){
	FILE *f;
	f = fopen("baithi/test.txt","r");
	address value;
	fscanf(f,"%s\t",value.name);
	fscanf(f,"%s\t",value.telephone);
	fscanf(f,"%s\n",value.email);
	node *l = createNode(value);
	node *p = l;
	int i;
	for(i=1;i<10;i++){
		fscanf(f,"%s\t",value.name);
		fscanf(f,"%s\t",value.telephone);
		fscanf(f,"%s\n",value.email);
		p = addElement(p,value);
	}
	fclose(f);
	printf("nhap ten can tim: ");
	address x;
	fflush(stdin);
	gets(x.name);
	node *q = searchNode(l,x);
	if(q == NULL) printf("khong tim thay trong danh sach\n");
	else printf("%-20s%-20s%-20s\n",q->data.name,q->data.telephone,q->data.email);
}
struct queueNode{
	address data;
	struct queueNode *next;
};
typedef struct queueNode queueNode;
struct queue{
	queueNode *front;
	queueNode *rear;
};
typedef struct queue queue;
queueNode* createNodeQ(address x){
	queueNode* temp = (queueNode*)malloc(sizeof(queueNode));
	temp->data = x;
	temp->next = NULL;
	return temp; 
}
queue* createQueue(){
	queue* q = (queue*)malloc(sizeof(queue));
	q->front = NULL;
	q->rear = NULL;
	return q;
}
void enQueue(queue* q, address x){
	queueNode* temp = createNodeQ(x);
	if(q->rear == NULL){
		q->front = temp;
		q->rear = temp;
		return ;
	}
	q->rear->next = temp;
	q->rear = temp;
}
void deQueue(queue* q){
	if(q->front == NULL){
		q->rear = NULL;
		return ; 
	}
	queueNode* temp = q->front;
	q->front = q->front->next;
	free(temp);
}
void task3(){
	FILE *f;
	f = fopen("baithi/test.txt","r");
	queue *q = createQueue();
	address value;
	int i;
	for(i=0;i<10;i++){
		fscanf(f,"%s\t",value.name);
		fscanf(f,"%s\t",value.telephone);
		fscanf(f,"%s\n",value.email);
		enQueue(q,value);
	}
	printf("nhap ten can tim: ");
	address x;
	fflush(stdin);
	gets(x.name);
	int dem=0;
	while(q->front != NULL){
		if(strcmp(q->front->data.name,x.name) == 0){
			dem++;
			printf("%-20s%-20s%-20s\n",q->front->data.name,q->front->data.telephone,q->front->data.email);
			break;
		}
		deQueue(q);
	}
	if(dem == 0) printf("khong tim thay trong danh sach\n");
}
void task4(){
	queue *q = createQueue();
	address value;
	int i;
	for(i=0;i<11;i++){
		printf("phan tu thu %d\n",i+1);
		printf("nhap ten: "); fflush(stdin); scanf("%s",value.name);
		printf("nhap sdt: "); fflush(stdin); scanf("%s",value.telephone);
		printf("nhap email: "); fflush(stdin); scanf("%s",value.email);
		enQueue(q,value);
	}
	printf("du lieu da loai bo\n");
	printf("%-20s%-20s%-20s\n",q->front->data.name,q->front->data.telephone,q->front->data.email);
	deQueue(q);
}
void menu(){
	printf("1. task1\n");
	printf("2. task2\n");
	printf("3. task3\n");
	printf("4. task4\n");
	printf("5. thoat\n");
}
int chonmenu(){
	int n=0;
	printf("\nchon chuc nang: ");
	scanf("%d",&n);
	if(n>0 && n<6) return n;
	else return chonmenu();
}
void xulymenu(){
	int chon = chonmenu();
	switch(chon){
		case 1:
			printf("1. task1\n");
			task1();
			break;
		case 2:
			printf("2. task2\n");
			task2();
			break;
		case 3:
			printf("3. task3\n");
			task3();
			break;
		case 4:
			printf("4. task4\n");
			task4();
			break;
		case 5:
			printf("5. thoat\n");
			exit(1);
			break;
	}
}
int main(){
	menu();
	while(1){
		xulymenu();
		printf("\n");
		menu();
	}
	return 0;
}