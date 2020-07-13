#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define pi 3.1415926535
#define square(x) x*x
struct Complex 
{
    long double re,im;
};
void JuliaSetPlot(struct Complex *c,char *FileName,int iteration)
{
       FILE *file=fopen(FileName,"w");
       struct Complex z;
       long double re,im,r,k;
       char str[200];
       fputs("Image[Partition[{",file);
       for(long double y=1.5;y>=-1.5;y-=0.01)
       {
           for(long double x=-1.5;x<=1.5;x+=0.01)
           {
                   z.re=x;
                   z.im=y;
                   for(int i=0;i<iteration;i++)
                   {
                           re=c->re+square(z.re)-square(z.im);
                           im=c->im+2*z.re*z.im;
                           z.re=re;z.im=im;
                           if((r=square(z.re)+square(z.im))>4)
                           {
                             k=i+2-log2l(log2l(r));
                             sprintf(str,"{%Lf,%Lf,%Lf},",0.5*(1+sinl(k)),0.5*(1+sinl(k+2.*pi/3.)),0.5*(1+sinl(k+4*pi/3.)));
                             fputs(str,file);
                               break;
                           }
                   }
                    if(r<=4){fputs("{0,0,0},",file);}
           }
       }
       fputs("Nothing},300],ImageResolution -> 1000, ColorSpace -> RGB]",file);
      fclose(file);
}
void MandelbrotSetPlot(struct Complex *z,char *FileName,int iteration)
{
     FILE *file=fopen(FileName,"w");
     struct Complex zn;
       long double re,im,r,k;
        char str[200];
       fputs("Image[Partition[{",file);
       for(long double y=1.5;y>=-1.5;y-=0.01)
       {
           for(long double x=-2;x<=1;x+=0.01)
           {
                  zn.re=z->re;zn.im=z->im;
                   for(int i=0;i<iteration;i++)
                   {
                           re=x+square(zn.re)-square(zn.im);
                           im=y+2*zn.re*zn.im;
                           zn.re=re;zn.im=im;
                           if((r=square(zn.re)+square(zn.im))>4)
                           {
                             k=i+2-log2l(log2l(r));
                             sprintf(str,"{%Lf,%Lf,%Lf},",0.5*(1+sinl(k)),0.5*(1+sinl(k+2.*pi/3.)),0.5*(1+sinl(k+4*pi/3.)));
                             fputs(str,file);
                               break;
                           }
                   }
                   if(r<=4){fputs("{0,0,0},",file);}
           }
       }
       fputs("Nothing},300],ImageResolution -> 1000, ColorSpace -> RGB]",file);
      fclose(file);
}
int main(int argc,char *argv[],char **env)
{
    if(argc==5)
    {
        if(strcmp("JuliaSetPlot",argv[1])==0)
        {
            struct Complex c;
            int n;
            sscanf(argv[2],"%Lf+%Lf*i",&c.re,&c.im);
            sscanf(argv[3],"%d",&n);
            JuliaSetPlot(&c,argv[4],n);
        }else if(strcmp("MandelbrotSetPlot",argv[1])==0)
        {
            struct Complex z;
            int n;
            sscanf(argv[2],"%Lf+%Lf*i",&z.re,&z.im);
            sscanf(argv[3],"%d",&n);
           MandelbrotSetPlot(&z,argv[4],n);
        }
    }
}