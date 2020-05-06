#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STK_LENGTH 3
typedef struct Stack Stack;
typedef int typen;
struct Stack
{
    int _top;
    typen _s[MAX_STK_LENGTH];
};
void init(Stack *stk){stk->_top = -1;}
int size(const Stack *stk){return stk->_top + 1;}
int empty(const Stack *stk){return stk->_top == -1;}
int full(const Stack *stk){return stk->_top == MAX_STK_LENGTH - 1;}
typen top(const Stack *stk){return stk->_s[stk->_top];}
typen pop(Stack *stk)
{
    if(!empty(stk))
    {
        typen tmp = stk->_s[stk->_top];
        stk->_top--;
        return tmp;
    }
    fprintf(stderr,"stack is empty!\n");
    return -1;
}
void push(Stack *stk,int x)
{
    if(!full(stk))
    {   
        stk->_top++;
        stk->_s[stk->_top] = x;
        return;
    }
    fprintf(stderr,"stack is full!\n");
}

int main(int argc,char** argv)
{
    Stack s;
    init(&s);
    push(&s,1);
    printf("top:%d\n",top(&s));
    printf("pop:%d\n",pop(&s));
    printf("%d\n",pop(&s));
    push(&s,2);
    push(&s,3);
    printf("size:%d\n",size(&s));
    push(&s,4);
    printf("size:%d\n",size(&s));
    push(&s,5);
    printf("size:%d\n",size(&s));
    printf("top:%d\n",top(&s));
    return 0;
}