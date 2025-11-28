#include "stdio.h"
#include "stdlib.h"
int main(){
    int n,m,command_num;
    scanf("%d %d", &n, &m);
    char** map = (char**)malloc(n*sizeof(char*));
    for(int i = 0; i < n;map[i] = (char*)malloc(m*sizeof(char)) , i++);
    for(int i = 0; i < n; i++){
        getchar();
        for(int j = 0; j < m; j++){
            scanf("%c", &map[i][j]);
        }
    }
    scanf("%d", &command_num);
    for(int i = 0; i < command_num; i++){
        int x,y,step;
        scanf("%d %d %d", &x, &y, &step);
        x-=1;y-=1;
        while(step--){
            switch(map[x][y]){
                case 'U': x = x-1>=0?x-1:n-1; break;
                case 'D': x = x+1<n?x+1:0; break;
                case 'L': y = y-1>=0?y-1:m-1; break;
                case 'R': y = y+1<m?y+1:0; break;
            }
        }
        printf("%d %d\n",x+1,y+1);
    }
}