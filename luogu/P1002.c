#include "stdio.h"
long long r[21][21],map[21][21],x,y,pos_x,pos_y;
long long process(int x, int y){
    r[0][0] = 1;
    if(x < 0 || y < 0) return 0;
    if(map[x][y] != 1 ){
        if(r[x][y] != -1) return r[x][y];
        else return (r[x][y] = process(x-1,y) + process(x,y-1));
    }else return 0;
}
int main(){
    memset(map,0,sizeof(map));
    memset(r,-1,sizeof(r));
    scanf("%d %d %d %d",&x,&y,&pos_x,&pos_y);
    map[pos_x][pos_y] = 1;
    int dx[18]={0,-2,-1,1,2,2,1,-1,-2,0,1,2,2,1,-1,-2,-2,-1};
    for(int i=0;i<9;i++){
        if(pos_x + dx[i]>=0 && pos_x + dx[i]<21 && pos_y + dx[i+9]>=0 && pos_y + dx[i+9]<21) map[pos_x + dx[i]][pos_y + dx[i+9]] = 1;
    }
    printf("%lld", process(x,y));
}