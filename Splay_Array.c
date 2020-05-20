#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPLAY_SIZE 222222
typedef struct Splay Splay;
typedef int T;
struct Splay
{
    int root, tot;
    int fa[MAX_SPLAY_SIZE], ch[MAX_SPLAY_SIZE][2], siz[MAX_SPLAY_SIZE], cnt[MAX_SPLAY_SIZE];
    T key[MAX_SPLAY_SIZE];
    int (*cmpfn)(T, T);
};

int lessT(T a, T b) { return a < b; }

void init(Splay *spl)
{
    spl->root = spl->tot = 0;
    memset(spl->fa, 0, sizeof(spl->fa));
    memset(spl->ch, 0, sizeof(spl->ch));
    memset(spl->siz, 0, sizeof(spl->siz));
    memset(spl->cnt, 0, sizeof(spl->cnt));
    memset(spl->key, 0, sizeof(spl->key));
    spl->cmpfn = lessT;
}
void maintain(Splay *spl, int x) { spl->siz[x] = spl->siz[spl->ch[x][0]] + spl->siz[spl->ch[x][1]] + spl->cnt[x]; }
int get(Splay *spl, int x) { return x == spl->ch[spl->fa[x]][1]; }
void clear(Splay *spl, int x)
{
    spl->ch[x][0] = spl->ch[x][1] = spl->fa[x] = spl->siz[x] = spl->cnt[x] = 0;
    spl->key[x] = 0;
}

void rotate(Splay *spl, int x)
{
    int y = spl->fa[x], z = spl->fa[y], chk = get(spl, x);
    spl->ch[y][chk] = spl->ch[x][chk ^ 1];
    spl->fa[spl->ch[x][chk ^ 1]] = y;
    spl->ch[x][chk ^ 1] = y;
    spl->fa[y] = x;
    spl->fa[x] = z;
    if (z)
        spl->ch[z][y == spl->ch[z][1]] = x;
    maintain(spl, y);
    maintain(spl, x);
}
void splay(Splay *spl, int x)
{
    int f;
    if (x == spl->root)
        return;
    for (f = spl->fa[x]; f = spl->fa[x], f; rotate(spl, x))
        if (spl->fa[f])
            rotate(spl, get(spl, x) == get(spl, f) ? f : x);
    spl->root = x;
}
void insert(Splay *spl, T k)
{
    if (!spl->root)
    {
        spl->key[++spl->tot] = k;
        ++spl->cnt[spl->tot];
        spl->root = spl->tot;
        maintain(spl, spl->root);
        return;
    }
    int cnr = spl->root, f = 0;
    while (1)
    {
        if (!spl->cmpfn(spl->key[cnr], k) && !spl->cmpfn(k, spl->key[cnr]))
        {
            ++spl->cnt[cnr];
            maintain(spl, cnr);
            maintain(spl, f);
            splay(spl, cnr);
            break;
        }
        f = cnr;
        cnr = spl->ch[cnr][spl->cmpfn(spl->key[cnr], k)];
        if (!cnr)
        {
            spl->key[++spl->tot] = k;
            ++spl->cnt[spl->tot];
            spl->fa[spl->tot] = f;
            spl->ch[f][spl->cmpfn(spl->key[f], k)] = spl->tot;
            maintain(spl, spl->tot);
            maintain(spl, f);
            splay(spl, spl->tot);
            break;
        }
    }
}
int queryrnk(Splay *spl, T k)
{
    int res = 0, cnr = spl->root;
    while (1)
    {
        if (spl->cmpfn(k, spl->key[cnr]))
        {
            cnr = spl->ch[cnr][0];
        }
        else
        {
            res += spl->siz[spl->ch[cnr][0]];
            if (!spl->cmpfn(spl->key[cnr], k) && !spl->cmpfn(k, spl->key[cnr]))
            {
                splay(spl, cnr);
                return res + 1;
            }
            res += spl->cnt[cnr];
            cnr = spl->ch[cnr][1];
        }
    }
}
T querykth(Splay *spl, int k)
{
    int cnr = spl->root;
    while (1)
    {
        if (spl->ch[cnr][0] && k <= spl->siz[spl->ch[cnr][0]])
        {
            cnr = spl->ch[cnr][0];
        }
        else
        {
            k -= spl->cnt[cnr] + spl->siz[spl->ch[cnr][0]];
            if (k <= 0)
            {
                splay(spl, cnr);
                return spl->key[cnr];
            }
            cnr = spl->ch[cnr][1];
        }
    }
}
int prev(Splay *spl)
{
    int cnr = spl->ch[spl->root][0];
    while (spl->ch[cnr][1])
        cnr = spl->ch[cnr][1];
    splay(spl, cnr);
    return cnr;
}
int succ(Splay *spl)
{
    int cnr = spl->ch[spl->root][1];
    while (spl->ch[cnr][0])
        cnr = spl->ch[cnr][0];
    splay(spl, cnr);
    return cnr;
}
int find(Splay *spl, T k)
{
    int cnr = spl->root;
    while (cnr)
    {
        if (spl->cmpfn(k, spl->key[cnr]))
            cnr = spl->ch[cnr][0];
        else if (spl->cmpfn(spl->key[cnr], k))
            cnr = spl->ch[cnr][1];
        else
        {
            splay(spl, cnr);
            return 1;
        }
    }
    return 0;
}
void del(Splay *spl, T k)
{
    if (!find(spl, k))
        return;
    if (spl->cnt[spl->root] > 1)
    {
        --spl->cnt[spl->root];
        maintain(spl, spl->root);
        return;
    }
    if (!spl->ch[spl->root][0] && !spl->ch[spl->root][1])
    {
        clear(spl, spl->root);
        spl->root = 0;
        return;
    }
    else if (!spl->ch[spl->root][0] || !spl->ch[spl->root][1])
    {
        int cnr = spl->root;
        spl->root = spl->ch[spl->root][0] ? spl->ch[spl->root][0] : spl->ch[spl->root][1];
        spl->fa[spl->root] = 0;
        clear(spl, cnr);
        return;
    }
    else
    {
        int cnr = spl->root, x = succ(spl);
        splay(spl, x);
        spl->fa[spl->ch[cnr][0]] = x;
        spl->ch[x][0] = spl->ch[cnr][0];
        clear(spl, cnr);
        maintain(spl, spl->root);
    }
}
void inorder(Splay *spl, int cnr)
{
    if (!cnr)
        return;
    if (spl->ch[cnr][0])
        inorder(spl, spl->ch[cnr][0]);
    if (cnr)
        //printf("k : %d cnt : %d fav : %d lcv : %d rcv : %d siz : %d\n", key[cnr], cnt[cnr], key[fa[cnr]], key[ch[cnr][0]], key[ch[cnr][1]], siz[cnr]);
        if (spl->ch[cnr][1])
            inorder(spl, spl->ch[cnr][1]);
    return;
}

Splay tr;
int n;

int main(int argc, char **argv)
{
    int i;
    scanf("%d", &n);
    init(&tr);
    for (i = 0; i < n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            insert(&tr, x);
        }
        else if (op == 2)
        {
            del(&tr, x);
        }
        else if (op == 3)
        {
            printf("%d\n", queryrnk(&tr, x));
        }
        else if (op == 4)
        {
            printf("%d\n", querykth(&tr, x));
        }
        else if (op == 5)
        {
            insert(&tr, x);
            printf("%d\n", tr.key[prev(&tr)]);
            del(&tr, x);
        }
        else if (op == 6)
        {
            insert(&tr, x);
            printf("%d\n", tr.key[succ(&tr)]);
            del(&tr, x);
        }
    }
    return 0;
}