#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define lol long long

int * buildNxt(char *P)
{
    int m = strlen(P),j = 0;
    int *N = (int*)malloc(sizeof(int) * m);
    int t = -1;
    N[0] = -1;
    while(j < m)
    {
        if(t < 0 || P[j] == P[t])
        {
            j++;t++;
            N[j] = (P[j] != P[t]) ? t : N[t];
        }
        else
        {
            t = N[t];
        }        
    }
    return N;
}

int kmp(char *P,char *T)
{
    int *nxt = buildNxt(P);
    int n = strlen(T);
    int m = strlen(P);
    int i = 0, j = 0;
    while(j < m && i < n)
    {
        if(j < 0 || T[i] == P[j])
        {
            ++i;++j;
        }
        else
        {
            j = nxt[j];
        }    
    }
    free(nxt);
    return i - j;
}

int kmpsum(char *P,char *T)
{
    int *nxt = buildNxt(P);
    int n = strlen(T);
    int m = strlen(P);
    int i = 0, j = 0;
    int sum = 0;
    while(i < n)
    {
        if(j < 0 || T[i] == P[j])
        {
            if(j == m - 1)
            {
                ++sum;                               
            }
            ++i;++j;            
        }
        else
        {
            j = nxt[j];
        }    
        
    }
    free(nxt);
    return sum;
}

int T,r,l;
char p[1111111],t[1111111];

int main(int argc,char** argv)
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s%s",p,t);
        printf("%d\n",kmpsum(p,t));
    }
    return 0;
}