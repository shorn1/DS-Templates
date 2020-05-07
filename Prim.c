#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define M 233333
typedef struct Edge Edge;
struct Edge
{
    int tow,nxt,dat;
};
Edge e[2 * M];
int n, m, s, a, b, c, sume = 0, vis[2 * M],hea[2 * M],dis[2 * M];

void add(int u, int v, int w)
{
    sume++;
    e[sume].nxt = hea[u];
    hea[u] = sume;
    e[sume].tow = v;
    e[sume].dat = w;
}

int prim(int st)
{
    int i,j,now;
    int cur = st;
    long long res = 0LL;
    for(i = 1;i <= n;i++)
    {
        dis[i] = 2147483647;
    }
    memset(vis, 0, sizeof(vis));
    for(now = hea[st];now;now = e[now].nxt)
    {
        int t = e[now].tow;
        dis[t] = dis[t] < e[now].dat ? dis[t] : e[now].dat;
    }
    for(i = 1;i < n;i++)
    {
        int mi = 2147483647;
        vis[cur] = 1;
        for(j = 1;j <= n;j++)
        {
            if(!vis[j] && mi > dis[j])
            {
                mi = dis[j];
                cur = j;
            }
        }
        res += mi;
        for(now = hea[cur];now;now = e[now].nxt)
        {
            int t = e[now].tow;
            if(dis[t] > e[now].dat && !vis[t])
            {
                dis[t] = e[now].dat;
            }
        }
    }
    return res >= 2147483647 ? -1 : res;
}

int main(int argc,char** argv)
{
    int i,r;
    scanf("%d%d",&n,&m);
    for(i = 1;i <= m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    r = prim(1);
    if(r == -1) printf("orz\n");
    else printf("%d\n",r);
    return 0;
}