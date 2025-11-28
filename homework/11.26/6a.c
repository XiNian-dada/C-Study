#include "stdio.h"
#include "stdlib.h"
char** map;
int n,m;
void process(int x,int y,int step){
    if(step==0){
        printf("%d %d\n",x+1,y+1);
        return;
    }
    step--;
    switch(map[x][y]){
        case 'U':{
            if(x-1>=0){
                process(x-1,y,step);
            }else{
                process(n-1,y,step);
            }
            break;
        }
        case 'D':{
            if(x+1<n){
                process(x+1,y,step);
            }else{
                process(0,y,step);
            }
            break;
        }
        case 'L':{
            if(y-1>=0){
                process(x,y-1,step);
            }else{
                process(x,m-1,step);
            }
            break;
        }
        case 'R':{
            if(y+1<m){
                process(x,y+1,step);
            }else{
                process(x,0,step);
            }
            break;
        }
    }
}
int main(){
    scanf("%d %d", &n, &m);
    map = (char**)malloc(n*sizeof(char*));
    for(int i = 0; i < n; i++){
        map[i] = (char*)malloc(m*sizeof(char));
    }
    for(int i = 0; i < n; i++){
        getchar();
        for(int j = 0; j < m; j++){
            scanf("%c", &map[i][j]);
        }
    }
    int command_num;
    scanf("%d", &command_num);
    for(int i = 0; i < command_num; i++){
        int x,y,step;
        scanf("%d %d %d", &x, &y, &step);
        process(x-1,y-1,step);
    }
}