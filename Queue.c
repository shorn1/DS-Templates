#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define MAX_QUEUE_LENGTH 111111
typedef struct Queue Queue;
typedef int typen;
struct Queue
{
    int _front,_back,_size;
    typen _q[MAX_QUEUE_LENGTH];
};
void init(Queue *que)
{
    que->_front = 0;
    que->_back = MAX_QUEUE_LENGTH - 1;
    que->_size = 0;
}
int size(const Queue *que){return que->_size;}
int empty(const Queue *que){return que->_size == 0;}
int full(const Queue *que){return que->_size == MAX_QUEUE_LENGTH;}
typen front(const Queue *que){return que->_q[que->_front];}
typen back(const Queue *que){return que->_q[que->_back];}
void push_back(Queue *que,typen x)
{
    if(!full(que))
    {
        que->_back = (que->_back + 1) % MAX_QUEUE_LENGTH;
        que->_q[que->_back] = x;
        que->_size++;
        return;
    }
    fprintf(stderr,"queue is full!\n");
}
typen pop_front(Queue *que)
{
    typen tmp;
    if(!empty(que))
    {
        tmp = front(que);
        que->_front = (que->_front + 1) % MAX_QUEUE_LENGTH;
        que->_size--;
        return tmp;
    }
    fprintf(stderr,"queue is empty!\n");
    return -1;
}

int main(int argc,char** argv)
{
    Queue q;
    init(&q);
    push_back(&q,1);
    printf("front:%d\n",front(&q));
    printf("pop_front:%d\n",pop_front(&q));
    push_back(&q,2);
    printf("front:%d\n",front(&q));
    printf("back:%d\n",back(&q));
    push_back(&q,3);
    printf("size:%d\n",size(&q));
    printf("front:%d\n",front(&q));
    printf("back:%d\n",back(&q));
    printf("pop_front:%d\n",pop_front(&q));
    printf("front:%d\n",front(&q));
    printf("back:%d\n",back(&q));
    return 0;
}