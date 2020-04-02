#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
struct Food;typedef struct Node* List;typedef struct Node* P;char *G(int len,int wide);void Delta(P p);struct Node{int x,y;char dt;P next;};struct Food {int x,y;};