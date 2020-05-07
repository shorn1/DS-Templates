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
void initq(Queue *que)
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

#define M 1111111
typedef struct Edge Edge;
struct Edge
{
    int tow,nxt,dat;
};
Edge e[2 * M];
int n,m,s,sume = 0,dis[2 * M],vis[2 * M],hea[2 * M];
Queue q;


void add(int u, int v, int w)
{
    sume++;
    e[sume].nxt = hea[u];
    hea[u] = sume;
    e[sume].tow = v;
    e[sume].dat = w;
}

void init()
{
    int i;
    for (i = 0; i <= 2 * m + 1; i++)
    {
        e[i].dat = dis[i] = 2147483647;
    }
    memset(vis, 0, sizeof(vis));
}

void spfa(int s)
{
    int now;
    dis[s] = 0;
    vis[s] = 1;
    initq(&q);
    push_back(&q,s);
    while(!empty(&q))
    {
        int x = front(&q);
        pop_front(&q);
        vis[x] = 0;
        for(now = hea[x];now;now = e[now].nxt)
        {
            int y = e[now].tow,z = e[now].dat;
            if(dis[y] > dis[x] + z)
            {
                dis[y] = dis[x]+z;
                if(!vis[y])
                {
                    vis[y] = 1;
                    push_back(&q,y);
                }
            }
        }
    }
}

void pans()
{
    int i;
    for(i = 1;i <= n;i++)
        printf("%d ", dis[i]);
}

int main()
{
    int i;
    scanf("%d%d%d",&n,&m,&s);
    init();
    for(i = 1;i <= m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        //add(b,a,c);
    }
    spfa(s);
    pans();
    return 0;
}
