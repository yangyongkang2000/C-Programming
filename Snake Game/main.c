#include "Snake.h"
#define len 79
#define wide 24
#define xr rand()%(len-4)+2
#define yr rand()%(wide-3)+2
#define subst(cm) p->dt=(cm=='w'||cm=='x')?(cm=='x'?'S':'N'):(cm=='d'?'E':'W');
#define pos s[I(h->x,h->y)]
#define Do if(l>1){List p=(List)malloc(sizeof(struct Node));p->x=h->x;p->y=h->y;subst(cm) ah->next=p;p->next=h;ah=p;}
int I(x,y) {return (y-1)*(len+1)+x-1;};int main()
{int cm,l=1;char *s=G(len,wide);
srand((unsigned int)time(NULL));struct Food f={xr,yr};
s[I(f.x,f.y)]='*';List t=(List)malloc(sizeof(struct Node));
t->x=xr;t->y=yr;t->dt='E';List h=(List)malloc(sizeof(struct Node));
h->x=t->x;h->y=t->y;h->next=NULL;
h->dt=t->dt;t->next=h;P ah=t;initscr();noecho(); nodelay(stdscr, 1);curs_set(0);while((cm=getch())!=27)
{if((cm=='w'||cm=='x')&&h->dt!='N'&&h->dt!='S')
{Do h->dt=cm=='w'?'N':'S';}else if((cm=='a'||cm=='d')&&(h->dt=='N'||h->dt=='S'))
{Do h->dt=cm=='a'?'W':'E'; }Delta(h);if(pos=='@'||pos=='-'||pos=='|') 
{break;}else{pos='@';}s[I(t->x,t->y)]=' ';
if(t->next->next!=NULL){if(t->x==t->next->x&&t->y==t->next->y){
P Tm=t->next;t->dt=Tm->dt;t->next=Tm->next;
free(Tm);Tm=NULL;if(t->next->next==NULL){ah=t;}}}
l==1?t->dt=h->dt:1;int x=t->x,y=t->y;Delta(t);if(h->x==f.x&&h->y==f.y)
{l++;while(s[I(f.x=xr,f.y=yr)]=='@'){};s[I(f.x,f.y)]='*';t->x=x;t->y=y;
s[I(x,y)]='@';}clear();move(0,0);printw("%s\n",s);refresh();usleep(100000);}endwin();}


