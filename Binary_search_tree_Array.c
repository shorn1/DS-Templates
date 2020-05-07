#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

#define MAX_BST_LENGTH 222222
typedef struct Bst Bst;
typedef int typen;
struct Bst
{
    int sum,st;
    int cnt[MAX_BST_LENGTH],siz[MAX_BST_LENGTH];
    typen key[MAX_BST_LENGTH];
    int lch[MAX_BST_LENGTH],rch[MAX_BST_LENGTH],fa[MAX_BST_LENGTH];
};

int insert(Bst *tr,int p,typen k,int fa)
{
    if(!p)
    {
        tr->key[++tr->sum] = k;
        tr->cnt[tr->sum] = tr->siz[tr->sum] = 1;
        tr->fa[tr->sum] = fa;
        tr->lch[tr->sum] = tr->rch[tr->sum] = 0;
        return tr->sum;
    }
    ++tr->siz[p];
    if(k == tr->key[p]) ++tr->cnt[p];
    else if(k < tr->key[p]) tr->lch[p] = insert(tr,tr->lch[p],k,p);    
    else tr->rch[p] = insert(tr,tr->rch[p],k,p); 
    return p;
}

int find(Bst *tr,int p,typen k)
{
    if(!p) return 0;
    if(k == tr->key[p]) return p;
    else if(k < tr->key[p]) p = find(tr,tr->lch[p],k);
    else p = find(tr,tr->rch[p],k);
    return p;
}

int succ(Bst *tr,int p)
{
    if(tr->rch[p])
    {
        p = tr->rch[p];
        while(tr->lch[p]) p = tr->lch[p];
    }
    else
    {
        while(tr->fa[p] && tr->rch[tr->fa[p]] == p) p = tr->fa[p];
        if(tr->fa[p]) p = tr->fa[p];
    }
    return p;
}

int prev(Bst *tr,int p)
{
    if(tr->lch[p])
    {
        p = tr->lch[p];
        while(tr->rch[p]) p = tr->rch[p];
    }
    else
    {
        while(tr->fa[p] && tr->lch[tr->fa[p]] == p) p = tr->fa[p];
        if(tr->fa[p]) p = tr->fa[p];
    }
    return p;
}

int findmin(Bst *tr,int p)
{
    if(!tr->lch[p]) return tr->key[p];
    return findmin(tr,tr->lch[p]);
}

int findmax(Bst *tr,int p)
{
    if(!tr->rch[p]) return tr->key[p];
    return findmax(tr,tr->rch[p]);
}

int deletemin(Bst *tr,int p)
{
    int tmp;
    if(!tr->lch[p])
    {
        if(tr->lch[tr->fa[p]] == p) tr->lch[tr->fa[p]] = tr->rch[p];
        else tr->rch[tr->fa[p]] = tr->rch[p];
        if(tr->rch[p])            
            tr->fa[tr->rch[p]] = tr->fa[p];
        return p;
    }    
    tmp = deletemin(tr,tr->lch[p]);
    tr->siz[p] -= tr->cnt[tmp];
    return tmp;
}

int del(Bst *tr,int p,typen k)
{
    if(!p) return p;
    --tr->siz[p];
    if(tr->key[p] == k)
    {
        if(tr->cnt[p] > 1)
        {
            --tr->cnt[p];
            return p;
        }
        if(tr->lch[p] && tr->rch[p])
        {
            int tmp = deletemin(tr,tr->rch[p]);
            tr->key[p] = tr->key[tmp];
            tr->cnt[p] = tr->cnt[tmp];
            return p;
        }
        else if(tr->lch[p])
        {
            int tmp = tr->lch[p];
            if(p == tr->lch[tr->fa[p]]) tr->lch[tr->fa[p]] = tr->lch[p];
            else if(p == tr->rch[tr->fa[p]]) tr->rch[tr->fa[p]] = tr->lch[p];
            tr->fa[tr->lch[p]] = tr->fa[p];
            return tmp;
        }
        else if(tr->rch[p])
        {
            int tmp = tr->rch[p];
            if(p == tr->lch[tr->fa[p]]) tr->lch[tr->fa[p]] = tr->rch[p];
            else if(p == tr->rch[tr->fa[p]]) tr->rch[tr->fa[p]] = tr->rch[p];
            tr->fa[tr->rch[p]] = tr->fa[p];
            return tmp;
        }
        else
        {
            if(p == tr->lch[tr->fa[p]]) tr->lch[tr->fa[p]] = 0;
            else if(p == tr->rch[tr->fa[p]]) tr->rch[tr->fa[p]] = 0;
            return 0;
        }
        
    }
    if(k < tr->key[p]) tr->lch[p] = del(tr,tr->lch[p],k);
    else tr->rch[p] = del(tr,tr->rch[p],k);
    return p;
}

int queryrnk(Bst *tr,int p,typen x)
{
    if(!p) return 0;
    if(x == tr->key[p]) return tr->siz[tr->lch[p]] + 1;
    if(x < tr->key[p]) return queryrnk(tr,tr->lch[p],x);
    if(x > tr->key[p]) return queryrnk(tr,tr->rch[p],x) + tr->siz[tr->lch[p]]  + tr->cnt[p];
}

typen querykth(Bst *tr,int p,int k)
{
    int lchsz = tr->siz[tr->lch[p]];
    if(lchsz >= k) return querykth(tr,tr->lch[p],k);
    if(lchsz < k - tr->cnt[p] && tr->rch[p])
        return querykth(tr,tr->rch[p],k - lchsz - tr->cnt[p]);
    return tr->key[p];
}

void inorder(Bst *tr,int p)
{
    if(!p) return;
    if(tr->lch[p]) inorder(tr,tr->lch[p]);
    if(p) printf("k : %d cnt : %d fav : %d lcv : %d rcv : %d siz : %d\n",tr->key[p],tr->cnt[p],tr->key[tr->fa[p]],tr->key[tr->lch[p]],tr->key[tr->rch[p]],tr->siz[p]);
    if(tr->rch[p]) inorder(tr,tr->rch[p]);
    return;
}

int n;
Bst tre;

void init(Bst *tr)
{
    tr->sum = 0;
    tr->st = 0;
}

int main(int argc,char** argv)
{
    int i,op,x;
    init(&tre);
    scanf("%d",&n);
    for(i = 0;i < n;i++)
    {
        scanf("%d%d",&op,&x);
        if(op == 1)
        {
            tre.st = insert(&tre,tre.st,x,0);
        }
        else if(op == 2)
        {
            if(find(&tre,tre.st,x))
                tre.st = del(&tre,tre.st,x);
        }
        else if(op == 3)
        {
            int t;
            tre.st = insert(&tre,tre.st,x,0);
            t = queryrnk(&tre,tre.st,x);
            tre.st = del(&tre,tre.st,x);
            printf("%d\n",t);
        }
        else if(op == 4)
        {
            int t = querykth(&tre,tre.st,x);
            printf("%d\n",t);
        }
        else if(op == 5)
        {
            int t;
            tre.st = insert(&tre,tre.st,x,0);
            t = prev(&tre,find(&tre,tre.st,x));
            tre.st = del(&tre,tre.st,x);
            printf("%d\n",tre.key[t]);
        }
        else if(op == 6)
        {
            int t;
            tre.st = insert(&tre,tre.st,x,0);
            t = succ(&tre,find(&tre,tre.st,x));
            tre.st = del(&tre,tre.st,x);
            printf("%d\n",tre.key[t]);
        }
    }
    return 0;
}