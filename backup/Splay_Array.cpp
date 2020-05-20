#include<cmath>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

#define ns namespace
#define lol long long
using ns std;

template<typename T = int,typename cmp = std::less<T> >
struct Splay
{
    const static int MAX_SPLAY_SIZE = 222222;
    int root,tot;
    int fa[MAX_SPLAY_SIZE],ch[MAX_SPLAY_SIZE][2],siz[MAX_SPLAY_SIZE],cnt[MAX_SPLAY_SIZE];
    T key[MAX_SPLAY_SIZE];
    cmp cmpfn;
    Splay():root(0),tot(0){memset(fa,0,sizeof(fa));memset(ch,0,sizeof(ch));memset(siz,0,sizeof(siz));memset(cnt,0,sizeof(cnt));memset(key,0,sizeof(key));}

    void maintain(int x) {siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];}
    int get(int x) {return x == ch[fa[x]][1];}
    void clear(int x) {ch[x][0] = ch[x][1] = fa[x] = siz[x] = cnt[x] = 0;key[x] = 0;}

    void rotate(int x)
    {
        int y = fa[x],z = fa[y],chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^1] = y;
        fa[y] = x;
        fa[x] = z;
        if(z) ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }
    void splay(int x)
    {
        if(x == root) return;
        for(int f = fa[x];f = fa[x],f;rotate(x) )
            if(fa[f]) rotate(get(x) == get(f) ? f : x);
        root = x;
    }
    void insert(T k)
    {
        if(!root)
        {
            key[++tot] = k;
            ++cnt[tot];
            root = tot;
            maintain(root);
            return;
        }
        int cnr = root,f = 0;
        while(1)
        {
            if(!cmpfn(key[cnr],k) && !cmpfn(k,key[cnr]))
            {
                ++cnt[cnr];
                maintain(cnr);
                maintain(f);
                splay(cnr);
                break;
            }
            f = cnr;
            cnr = ch[cnr][cmpfn(key[cnr],k)];
            if(!cnr)
            {
                key[++tot] = k;
                ++cnt[tot];
                fa[tot] = f;
                ch[f][cmpfn(key[f],k)] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                break;
            }
        }
    }
    int queryrnk(T k)
    {
        int res = 0,cnr = root;
        while(1)
        {
            if(cmpfn(k,key[cnr]))
            {
                cnr = ch[cnr][0];
            }
            else
            {
                res += siz[ch[cnr][0]];
                if(!cmpfn(key[cnr],k) && !cmpfn(k,key[cnr]))
                {
                    splay(cnr);
                    return res + 1;
                }
                res += cnt[cnr];
                cnr = ch[cnr][1];
            }
        }
    }
    T querykth(int k)
    {
        int cnr = root;
        while(1)
        {
            if(ch[cnr][0] && k <= siz[ch[cnr][0]])
            {
                cnr = ch[cnr][0];
            }
            else
            {
                k -= cnt[cnr] + siz[ch[cnr][0]];
                if(k <= 0)
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
        while(ch[cnr][1]) cnr = ch[cnr][1];
        splay(cnr);
        return cnr;
    }
    int succ()
    {
        int cnr = ch[root][1];
        while(ch[cnr][0]) cnr = ch[cnr][0];
        splay(cnr);
        return cnr;
    }
    int find(T k)
    {
        int cnr = root;
        while(cnr)
        {
            if(cmpfn(k,key[cnr])) cnr = ch[cnr][0];
            else if(cmpfn(key[cnr],k)) cnr = ch[cnr][1];
            else
            {
                splay(cnr);
                return 1;
            }
        }
        return 0;
    }
    void del(T k)
    {
        if(!find(k)) return;
        if(cnt[root] > 1)
        {
            --cnt[root];
            maintain(root);
            return;
        }
        if(!ch[root][0] && !ch[root][1])
        {
            clear(root);
            root = 0;
            return;
        }
        else if(!ch[root][0] || !ch[root][1])
        {
            int cnr = root;
            root = ch[root][0] ? ch[root][0] : ch[root][1];
            fa[root] = 0;
            clear(cnr);
            return;
        }
        else
        {
            int cnr = root,x = succ();
            splay(x);
            fa[ch[cnr][0]] = x;
            ch[x][0] = ch[cnr][0];
            clear(cnr);
            maintain(root);
        }        
    }
    void inorder(int cnr)
    {
        if(!cnr) return;
        if(ch[cnr][0]) inorder(ch[cnr][0]);
        if(cnr) printf("k : %d cnt : %d fav : %d lcv : %d rcv : %d siz : %d\n",key[cnr],cnt[cnr],key[fa[cnr]],key[ch[cnr][0]],key[ch[cnr][1]],siz[cnr]);
        if(ch[cnr][1]) inorder(ch[cnr][1]);
        return;
    }
};

Splay<int> tr;
int n;

int main(int argc,char** argv)
{
    scanf("%d",&n);
    for(int i = 0;i < n;i++)
    {
        int op,x;
        scanf("%d%d",&op,&x);
        if(op == 1)
        {
            tr.insert(x);
        }
        else if(op == 2)
        {
            tr.del(x);
        }
        else if(op == 3)
        {
            printf("%d\n",tr.queryrnk(x));
        }
        else if(op == 4)
        {
            printf("%d\n",tr.querykth(x));
        }
        else if(op == 5)
        {
            tr.insert(x);
            printf("%d\n",tr.key[tr.prev()]);
            tr.del(x);
        }
        else if(op == 6)
        {
            tr.insert(x);
            printf("%d\n",tr.key[tr.succ()]);
            tr.del(x);
        }
        //tr.inorder(tr.root);
    }
    return 0;
}