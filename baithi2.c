#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
//tao stack kieu char
struct StackNode{
	char item;
	struct StackNode *next;
};
typedef struct StackNode StackNode;
struct Stack{
	StackNode *top;
};
typedef struct Stack Stack;
Stack *StackConstruct(){
	Stack *s;
	s = (Stack *)malloc(sizeof(Stack));
	if(s == NULL) return NULL;
	s->top = NULL;
	return s;
}

void StackPush(Stack *s,char item){
	StackNode *node;
	node = (StackNode *)malloc(sizeof(StackNode));
	node->item = item;
	node->next = s->top;
	s->top = node;
}
void StackPop(Stack *s){
	StackNode *node;
	if(s->top == NULL){
		return;
	}
	node = s->top;
	s->top = node->next;
	free(node);
}
void StackDestroy(Stack *s){
	while(s->top != NULL){
		StackPop(s);
	}
	free(s);
}
struct stackNode{
	int data;
	struct stackNode *next;
};
typedef struct stackNode stackNode;
struct stack{
	stackNode *top;
};
typedef struct stack stack;
stack *stackConstruct(){
	stack *s;
	s = (stack *)malloc(sizeof(stack));
	if(s == NULL) return NULL;
	s->top = NULL;
	return s;
}
int stackEmpty(stack *s){
	return s->top == NULL;
}
void stackPush(stack *s,char x){
	stackNode *node;
	node = (stackNode *)malloc(sizeof(stackNode));
	node->data = x;
	node->next = s->top;
	s->top = node;
}
void stackPop(stack *s){
	stackNode *node;
	if(stackEmpty(s)){
		return;
	}
	node = s->top;
	s->top = node->next;
	free(node);
}
void stackDestroy(stack *s){
	while(!stackEmpty(s)){
		stackPop(s);
	}
	free(s);
}
//tao stack kieu int
struct stack1 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
struct stack1* createstack1( unsigned capacity ) 
{ 
    struct stack1* stack1 = (struct stack1*) malloc(sizeof(struct stack1)); 
  
    if (!stack1) return NULL; 
  
    stack1->top = -1; 
    stack1->capacity = capacity; 
    stack1->array = (int*) malloc(stack1->capacity * sizeof(int)); 
  
    if (!stack1->array) return NULL; 
  
    return stack1; 
} 
  
int isEmpty(struct stack1* stack1) 
{ 
    return stack1->top == -1 ; 
} 
  
char peek(struct stack1* stack1) 
{ 
    return stack1->array[stack1->top]; 
} 
  
char pop(struct stack1* stack1) 
{ 
    if (!isEmpty(stack1)) 
        return stack1->array[stack1->top--] ; 
    return '$'; 
} 
  
void push(struct stack1* stack1, char op) 
{ 
    stack1->array[++stack1->top] = op; 
} 
  
//tinh gia tri hau to  
int giatrihauto(char* exp) 
{ 
    struct stack1* stack1 = createstack1(strlen(exp)); 
    int i; 
    if (!stack1) return -1; 
  
    for (i = 0; exp[i]; ++i) 
    { 
        if (isdigit(exp[i])) 
            push(stack1, exp[i] - '0');  
        else
        { 
            int val1 = pop(stack1); 
            int val2 = pop(stack1); 
            switch (exp[i]) 
            { 
            case '+': push(stack1, val2 + val1); break; 
            case '-': push(stack1, val2 - val1); break; 
            case '*': push(stack1, val2 * val1); break; 
            case '/': push(stack1, val2/val1); break; 
            } 
        } 
    } 
    return pop(stack1); 
}
//do uu tien toan tu
int thutu(char x){
	if(x == '(') return 0;
	if(x == '+' || x == '-') return 1;
	if(x == '*' || x == '/') return 2;
	if(x == '^') return 3;
}
int main(){
	Stack *s;
	s = StackConstruct();
	char infix[10];
	fflush(stdin);
	gets(infix);
	char postfix[] ="";
	char c;
	char x;
	char y;
	int i=0;
	int j=0;
	int dem = 0;
	while(i < strlen(infix)){
		c = infix[i];
		if(c != ' '){
			if(c - '0' >= 0 && c -'0' <= 9 || isalpha(c)) {
				postfix[j++] = c;
			}
			else{
				if(c == '(') {
					StackPush(s,c);
					dem++;
				}
				else{
					if(c == ')'){
						while(s->top->item != '('){
							postfix[j++] = s->top->item;
							StackPop(s);
						}
						StackPop(s);
						
					}
					else{
						while(s->top != NULL && thutu(c) <= thutu(s->top->item)){
							postfix[j++] = s->top->item;
							StackPop(s);
						}
						StackPush(s,c);
						
					}
				}	
			}
		}
		i++;
	}
	while(s->top != NULL){
		if(s->top->item == '(' || s->top->item == ')' || isdigit(s->top->item)){
			continue;
		}
		postfix[j++] = s->top->item;
		for(i=0;i<dem;i++){
			postfix[strlen(postfix)-1] = '\0';
		}
		StackPop(s);
	}
	postfix[strlen(postfix)-1] = '\0';
	printf("bieu thuc hau to: %s\n",postfix);
	printf("gia tri bieu thuc hau to: %d", giatrihauto(postfix));
}