#include "stdio.h"
typedef struct{
    int startX;
    int startY;
    int lenX;
    int lenY;
} carpet;
int main(){
    int n;
    carpet c[10002];
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d",&c[i].startX,&c[i].startY,&c[i].lenX,&c[i].lenY);
    }
    int x,y;
    scanf("%d %d",&x,&y);
    int founded=-1;
    for(int i=n-1;i>=0;i--){
        if(x>=c[i].startX && x<=c[i].startX+c[i].lenX 
            && y>=c[i].startY && y<=c[i].startY+c[i].lenY){
            founded = i+1;
            break;
        }
    }
    printf("%d",founded);
}