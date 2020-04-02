#include "Snake.h"
char *G(int len,int w)
{int size=(len+1)*w+1;char *s=(char *)malloc(size*sizeof(char));char *mid=(char *)malloc((len+1)*sizeof(char));memset(s,'-',len);
strcat(s,"\n");for(int i=0;i<w-2;i++)
{strcat(s,"|");strcat(s,(char *)memset(mid,' ',len-2));memset(mid,0,len-2);strcat(s,"|\n");}
    strcat(s,(char *)memset(mid,'-',len));s[size-1]='\0';return s;}
void Delta(P p)
{if(p->dt=='N'||p->dt=='S'){
p->y+=(p->dt=='S'?1:-1);}else{p->x+=(p->dt=='E'?1:-1);}}
