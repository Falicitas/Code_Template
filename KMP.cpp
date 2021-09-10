#include<bits/stdc++.h>
using namespace std;

const int maxs = 1e4 + 5;
char p[maxs],s[maxs],nex[maxs];

void kmppre(char u[],int len)
{
    int i=1,j = nex[1] = 0;
    while(i<=len){
        while(j!=0&&u[i]!=u[j]) j = nex[j];
        nex[++i] = ++j;
    }
}

int kmp()
{
    int sLen = strlen(s+1),pLen = strlen(p+1);
    kmppre(p,pLen);
    int i,j;
    i = j = 1;
    while(i<=sLen && j<=pLen){
        if(j == 0 || s[i] == p[j]){
            i++;
            j++;
        }
        else j = nex[j];
    }
    if(j==pLen+1) return i - j + 1;
    else return -1;
}

int main()
{
    while(gets(s+1)&&gets(p+1)){
        printf("%d\n",kmp());
    }
    return 0;
}
