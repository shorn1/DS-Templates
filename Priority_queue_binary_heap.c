#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define MAX_PQ_LENGTH 511111
typedef struct Priority_queue Priority_queue;
typedef int typen;
struct Priority_queue
{
    int _top,_bk;
    typen _pq[MAX_PQ_LENGTH];
};
/*大根堆*/
void _swap(Priority_queue *pque,int x,int y)
{
    typen tmp = pque->_pq[x];
    pque->_pq[x] = pque->_pq[y];
    pque->_pq[y] = tmp;
}
void init(Priority_queue *pque)
{
    pque->_top = 1;
    pque->_bk = 0;
}
typen top(const Priority_queue *pque){return pque->_pq[pque->_top];}
int full(const Priority_queue *pque){return pque->_bk == MAX_PQ_LENGTH - 1;}
int empty(const Priority_queue *pque){return pque->_bk == 0;}
int size(const Priority_queue *pque){return pque->_bk;}
void up(Priority_queue *pque,int x)
{
    while(x > 1 && pque->_pq[x] > pque->_pq[x / 2])
    {
        _swap(pque,x,x / 2);
        x /= 2;
    }
}

void down(Priority_queue *pque,int x)
{
    int t;
    while(x * 2 <= pque->_bk)
    {
        t = x * 2;
        if(t + 1 <= pque->_bk && pque->_pq[t] < pque->_pq[t + 1]) ++t;
        if(pque->_pq[t] < pque->_pq[x]) break;
        _swap(pque,x,t);
        x = t;
    }
}

void push(Priority_queue *pque,typen x)
{
    if(!full(pque))
    {
        pque->_pq[++pque->_bk] = x; 
        up(pque,pque->_bk);
        return;
    }
    fprintf(stderr,"priority queue is full!\n");
}

void pop(Priority_queue *pque)
{
    if(!empty(pque))
    {
        _swap(pque,pque->_top,pque->_bk);
        --pque->_bk;
        down(pque,pque->_top);
        return;
    }
    fprintf(stderr,"priority queue is empty!\n");
}

void build_1(Priority_queue *pque,typen a[],int n)
{
    int i;
    for(i = 1; i <= n; i++) pque->_pq[++pque->_bk] = a[i];
    for(i = 1; i <= n; i++) up(pque,i);
}

void build_2(Priority_queue *pque,typen a[],int n)
{
    int i;
    for(i = 1; i <= n; i++) pque->_pq[++pque->_bk] = a[i];
    for(i = n; i >= 1; i--) down(pque,i);
}

#define M 555555
Priority_queue pq;
int n;

int main(int argc,char** argv)
{
    int i;
    init(&pq);
    scanf("%d",&n);
    for(i = 1;i <= n;i++) 
    {
        int t,v;
        scanf("%d",&t);
        if(t == 1)
        {
            scanf("%d",&v);
            push(&pq,-v);
        }
        else if(t == 2)
        {
            printf("%d\n",top(&pq) * -1);
        }
        else
        {
            pop(&pq);
        }
    }
    /*int a[233] = {1, 4 ,5 ,1 ,2,9};
    build_1(&pq,a,5);
    build_2(&pq,a,5);
    for(i = 1;i <= 5;i++) 
    {
        printf("%d\n",top(&pq));
        pop(&pq);
    }*/
    return 0;
}