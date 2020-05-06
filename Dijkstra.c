#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define MAX_PQ_LENGTH 1111111
typedef struct Priority_queue Priority_queue;
typedef struct pii pii;
struct pii
{
    int fi,sc;
};
typedef pii typen;

struct Priority_queue
{
    int _top,_bk;
    typen _pq[MAX_PQ_LENGTH];
    int (*_cmp)(typen,typen);
};
int greatertypen(typen a, typen b){return a.fi > b.fi;}/*小根堆*/
void _swap(Priority_queue *pque,int x,int y)
{
    typen tmp = pque->_pq[x];
    pque->_pq[x] = pque->_pq[y];
    pque->_pq[y] = tmp;
}
void initq(Priority_queue *pque)
{
    pque->_top = 1;
    pque->_bk = 0;
    pque->_cmp = greatertypen;
}
typen top(const Priority_queue *pque)
{
    return pque->_pq[pque->_top];
}
int full(const Priority_queue *pque){return pque->_bk == MAX_PQ_LENGTH - 1;}
int empty(const Priority_queue *pque){return pque->_bk == 0;}
void up(Priority_queue *pque,int x)
{
    while(x > 1 && pque->_cmp(pque->_pq[x / 2],pque->_pq[x]))
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
        if(t + 1 <= pque->_bk && pque->_cmp(pque->_pq[t] , pque->_pq[t + 1])) ++t;
        if(pque->_cmp(pque->_pq[t] , pque->_pq[x])) break;
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
#define M 533333
typedef struct Edge Edge;
struct Edge
{
    int tow,nxt,dat;
};
Edge e[2 * M];
Priority_queue q;
int n, m, s, a, b, c, sume = 0, vis[2 * M],hea[2 * M],dis[2 * M];

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

void dij(int s)
{
    pii tmp;
    initq(&q);
    dis[s] = 0;
    tmp.fi = 0;
    tmp.sc = s;
    push(&q,tmp);
    while (!empty(&q))
    {
        int now;
        pii x = top(&q);
        pop(&q);
        int u = x.sc;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (now = hea[u]; now; now = e[now].nxt)
        {
            int t = e[now].tow;
            if (!vis[t])
                if (dis[u] + e[now].dat < dis[t])
                {
                    dis[t] = dis[u] + e[now].dat;
                    tmp.fi = dis[t];tmp.sc = t;
                    push(&q,tmp);
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
    scanf("%d%d%d", &n, &m, &s);
    init();
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        //add(b, a, c);
    }
    dij(s);
    pans();
    return 0;
}
