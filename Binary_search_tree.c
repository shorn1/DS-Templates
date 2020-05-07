#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

typedef struct BinNode BinNode;
typedef struct BinNode* BinNodepos;
typedef int typen;
struct BinNode
{
    int cnt,siz;
    typen key;
    BinNode* lch,*rch,*fa;
};

void swap(typen *a,typen *b)
{
    typen t = *a;
    *a = *b;
    *b = t;
}

BinNodepos insert(BinNodepos p,typen k,BinNodepos fa)
{
    if(!p)
    {
        p = (BinNodepos) malloc(sizeof(BinNode));
        p->key = k;
        p->lch = p->rch = NULL;
        p->fa = fa;
        p->cnt = p->siz = 1;
        return p;
    }
    ++p->siz;
    if(k == p->key) ++p->cnt;  
    else if(k < p->key)
    {
        p->lch = insert(p->lch,k,p);    
    }
    else
    {
        p->rch = insert(p->rch,k,p);
    }
    return p;
}

BinNodepos find(BinNodepos p,typen k)
{
    if(!p) return NULL;
    if(k == p->key) return p;
    else if(k < p->key) p = find(p->lch,k);
    else p = find(p->rch,k);
    return p;
}

BinNodepos succ(BinNodepos p)
{
    BinNodepos t = p;
    if(t->rch)
    {
        t = t->rch;
        while(t->lch) t = t->lch;
    }
    else
    {
        while(t->fa && t->fa->rch == t) t = t->fa;
        if(t->fa) t = t->fa;
    }
    return t;
}

BinNodepos prev(BinNodepos p)
{
    BinNodepos t = p;
    if(t->lch)
    {
        t = t->lch;
        while(t->rch) t = t->rch;
    }
    else
    {
        while(t->fa && t->fa->lch == t) t = t->fa;
        if(t->fa) t = t->fa;
    }
    return t;
}

typen findmin(BinNodepos p)
{
    if(!p->lch) return p->key;
    return findmin(p->lch);
}

typen findmax(BinNodepos p)
{
    if(!p->rch) return p->key;
    return findmax(p->rch);
}

BinNodepos deletemin(BinNodepos p)
{
    if(!p->lch)
    {
        if(p->fa->lch == p) p->fa->lch = p->rch;
        else p->fa->rch = p->rch;
        if(p->rch)            
            p->rch->fa = p->fa;
        return p;
    }
    BinNodepos tmp;
    tmp = deletemin(p->lch);
    p->siz -= tmp->cnt;
    return tmp;
}

BinNodepos del(BinNodepos p,typen k)
{
    if(!p) return p;
    --p->siz;
    if(p->key == k)
    {
        if(p->cnt > 1)
        {
            --p->cnt;
            return p;
        }
        if(p->lch && p->rch)
        {
            BinNodepos tmp= deletemin(p->rch);
            p->key = tmp->key;
            p->cnt = tmp->cnt;
            free(tmp);
            return p;
        }
        else if(p->lch)
        {
            BinNodepos tmp = p->lch;
            if(p == p->fa->lch) p->fa->lch = p->lch;
            else if(p == p->fa->rch) p->fa->rch = p->lch;
            p->lch->fa = p->fa;
            free(p);
            return tmp;
        }
        else if(p->rch)
        {
            BinNodepos tmp = p->rch;
            if(p == p->fa->lch) p->fa->lch = p->rch;
            else if(p == p->fa->rch) p->fa->rch = p->rch;
            p->rch->fa = p->fa;
            free(p);
            return tmp;
        }
        else
        {
            if(p == p->fa->lch) p->fa->lch = NULL;
            else if(p == p->fa->rch) p->fa->rch = NULL;
            free(p);
            return NULL;
        }
        
    }
    if(k < p->key) p->lch = del(p->lch,k);
    else p->rch = del(p->rch,k);
    return p;
}

int queryrnk(BinNodepos p,typen x)
{
    if(!p) return 0;
    if(x == p->key) return p->lch ? p->lch->siz + 1 : 1;
    if(x < p->key) return queryrnk(p->lch,x);
    if(x > p->key) return queryrnk(p->rch,x) + (p->lch ? p->lch->siz : 0) + p->cnt;
}

typen querykth(BinNodepos p,int k)
{
    int lchsz = (p->lch ? p->lch->siz : 0);
    if(lchsz >= k) return querykth(p->lch,k);
    if(lchsz < k - p->cnt && p->rch)
        return querykth(p->rch,k - lchsz - p->cnt);
    return p->key;
}

void inorder(BinNodepos p)
{
    if(!p) return;
    if(p->lch) inorder(p->lch);
    if(p) printf("k : %d cnt : %d fav : %d lcv : %d rcv : %d siz : %d\n",p->key,p->cnt,p->fa ? p->fa->key : -1,p->lch ? p->lch->key : -1 ,p->rch ? p->rch->key : -1,p->siz);
    if(p->rch) inorder(p->rch);
    return;
}

int n;
BinNodepos root;
BinNodepos vitu;

void init()
{
    root = NULL;
    vitu = (BinNodepos) malloc(sizeof(BinNode));
    vitu->key = 0;
    vitu->lch = vitu->rch = root;
    vitu->fa = NULL;
    vitu->cnt = vitu->siz = 0;
}

int main(int argc,char** argv)
{
    int i,op,x;
    init();
    scanf("%d",&n);
    for(i = 0;i < n;i++)
    {
        scanf("%d%d",&op,&x);
        if(op == 1)
        {
            root = insert(root,x,vitu);
        }
        else if(op == 2)
        {
            if(find(root,x))
                root = del(root,x);
        }
        else if(op == 3)
        {
            int t;
            root = insert(root,x,vitu);
            t = queryrnk(root,x);
            root = del(root,x);
            printf("%d\n",t);
        }
        else if(op == 4)
        {
            int t = querykth(root,x);
            printf("%d\n",t);
        }
        else if(op == 5)
        {
            BinNodepos t;
            root = insert(root,x,vitu);
            t = prev(find(root,x));
            root = del(root,x);
            printf("%d\n",t->key);
        }
        else if(op == 6)
        {
            BinNodepos t;
            root = insert(root,x,vitu);
            t = succ(find(root,x));
            root = del(root,x);
            printf("%d\n",t->key);
        }
    }
    return 0;
}