#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lol long long
#define MAX_SPLAY_SIZE 222222
int root, tot;
int fa[MAX_SPLAY_SIZE], ch[MAX_SPLAY_SIZE][2], siz[MAX_SPLAY_SIZE], cnt[MAX_SPLAY_SIZE];
int key[MAX_SPLAY_SIZE];

void maintain(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x]; }
int get(int x) { return x == ch[fa[x]][1]; }
void clear(int x)
{
    ch[x][0] = ch[x][1] = fa[x] = siz[x] = cnt[x] = 0;
    key[x] = 0;
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], chk = get(x);
    ch[y][chk] = ch[x][chk ^ 1];
    fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z)
        ch[z][y == ch[z][1]] = x;
    maintain(y);
    maintain(x);
}
void splay(int x)
{
    int f;
    if (x == root)
        return;
    for (f = fa[x]; f = fa[x], f; rotate(x))
        if (fa[f])
            rotate(get(x) == get(f) ? f : x);
    root = x;
}
void insert(int k)
{
    int cnr = root, f = 0;
    if (!root)
    {
        key[++tot] = k;
        ++cnt[tot];
        root = tot;
        maintain(root);
        return;
    }
    while (1)
    {
        if (key[cnr] == k)
        {
            ++cnt[cnr];
            maintain(cnr);
            maintain(f);
            splay(cnr);
            break;
        }
        f = cnr;
        cnr = ch[cnr][key[cnr] < k];
        if(!cnr)
        {
            key[++tot] = k;
            ++cnt[tot];
            fa[tot] = f;
            ch[f][key[f] < k] = tot;
            maintain(tot);
            maintain(f);
            splay(tot);
            break;
        }
    }
}
int queryrnk(int k)
{
    int res = 0, cnr = root;
    while (1)
    {
        if (k < key[cnr])
        {
            cnr = ch[cnr][0];
        }
        else
        {
            res += siz[ch[cnr][0]];
            if (key[cnr] == k)
            {
                splay(cnr);
                return res + 1;
            }
            res += cnt[cnr];
            cnr = ch[cnr][1];
        }
    }
}
int querykth(int k)
{
    int cnr = root;
    while (1)
    {
        if (ch[cnr][0] && k <= siz[ch[cnr][0]])
        {
            cnr = ch[cnr][0];
        }
        else
        {
            k -= cnt[cnr] + siz[ch[cnr][0]];
            if (k <= 0)
            {
                splay(cnr);
                return key[cnr];
            }
            cnr = ch[cnr][1];
        }
    }
}
int prev()
{
    int cnr = ch[root][0];
    while (ch[cnr][1])
        cnr = ch[cnr][1];
    splay(cnr);
    return cnr;
}
int succ()
{
    int cnr = ch[root][1];
    while (ch[cnr][0])
        cnr = ch[cnr][0];
    splay(cnr);
    return cnr;
}
int find(int k)
{
    int cnr = root;
    while (cnr)
    {
        if (k < key[cnr])
            cnr = ch[cnr][0];
        else if (key[cnr] < k)
            cnr = ch[cnr][1];
        else
        {
            splay(cnr);
            return 1;
        }
    }
    return 0;
}
void del(int k)
{
    if (!find(k))
        return;
    if (cnt[root] > 1)
    {
        --cnt[root];
        maintain(root);
        return;
    }
    if (!ch[root][0] && !ch[root][1])
    {
        clear(root);
        root = 0;
        return;
    }
    else if (!ch[root][0] || !ch[root][1])
    {
        int cnr = root;
        root = ch[root][0] ? ch[root][0] : ch[root][1];
        fa[root] = 0;
        clear(cnr);
        return;
    }
    else
    {
        int cnr = root, x = succ();
        splay(x);
        fa[ch[cnr][0]] = x;
        ch[x][0] = ch[cnr][0];
        clear(cnr);
        maintain(root);
    }
}
void inorder(int cnr)
{
    if (!cnr)
        return;
    if (ch[cnr][0])
        inorder(ch[cnr][0]);
    if (cnr)
        printf("k : %d cnt : %d fav : %d lcv : %d rcv : %d siz : %d\n", key[cnr], cnt[cnr], key[fa[cnr]], key[ch[cnr][0]], key[ch[cnr][1]], siz[cnr]);
    if (ch[cnr][1])
        inorder(ch[cnr][1]);
    return;
}

int n;

int main(int argc, char **argv)
{
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            insert(x);
        }
        else if (op == 2)
        {
            del(x);
        }
        else if (op == 3)
        {
            printf("%d\n", queryrnk(x));
        }
        else if (op == 4)
        {
            printf("%d\n", querykth(x));
        }
        else if (op == 5)
        {
            insert(x);
            printf("%d\n", key[prev()]);
            del(x);
        }
        else if (op == 6)
        {
            insert(x);
            printf("%d\n", key[succ()]);
            del(x);
        }
        //inorder(tr.root);
    }
    return 0;
}