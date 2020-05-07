#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define M 211111
typedef struct Edge Edge;
struct Edge
{
    int u,v,w;
};
Edge e[M];
int n,m;
int fa[M],size[M];
long long res,sumed;

int getfa(int x)
{
	if(fa[x]==x) return x;
	return fa[x] = getfa(fa[x]);
}
void merge(int x,int y)
{
	int s1 = size[getfa(x)];
	int s2 = size[getfa(y)];
	if(s1>s2)
	{
		fa[getfa(y)] = getfa(x);
		size[getfa(x)] = s1 + s2;
	}
	else
	{
		fa[getfa(x)]= getfa(y);
		size[getfa(y)] = s1 + s2;
	}
}

int cmp(const void *_a,const void *_b)
{
    Edge *a = (Edge *)(_a);
    Edge *b = (Edge *)(_b);
    return a->w > b->w ? 1 : -1;
}

void kruskal()
{
    int i;
    qsort(e + 1,m,sizeof(e[0]),cmp);
    for(i = 1;i <= m && sumed < n;i++)
    {
        if(getfa(e[i].u) != getfa(e[i].v))
        {
            res += e[i].w;
            sumed++;
            merge(e[i].u,e[i].v);
        }
    }
}

void init()
{
    int i;
    for(i = 1;i <= n;i++)
    {
        fa[i] = i;
        size[i] = 1;
    }
    for(i = 1;i <= m;i++)
    {
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
}

int main(int argc,char** argv)
{
    scanf("%d%d",&n,&m);
    init();    
    kruskal();    
    printf("%lld",sumed == n - 1 ? res : -1LL);
    return 0;
}