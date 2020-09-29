#include"expr.h"
#include<stdio.h>
char b[25];
int count=0;
void dfs(char n)
{
    if(n<0)
    {
        count+=(det)!=0?1:0;
        return ;
    }
    for(b[n]=0;b[n]<=1;b[n]++)
       dfs(n-1);
}
int main()
{
    dfs(24);
    printf("count=%d\n",count);
}