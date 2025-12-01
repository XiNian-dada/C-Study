#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAXN 10
int matrix[MAXN][MAXN];
int memo[MAXN][MAXN][MAXN][MAXN];
int n;

int max_num(int a,int b){
    return a>b?a:b;
}
int dfs(int i,int j,int k,int l){
    if(i >= n || j >= n || k >= n || l >= n) return -9999999;
    if(memo[i][j][k][l] != -1) return memo[i][j][k][l];
    if(i == n-1 && j == n-1 && k == n-1 && l == n-1) return matrix[i][j];
    int value = matrix[i][j];
    if((i!=k && j!=l)) value += matrix[k][l];
    int temp1 = dfs(i+1,j,k+1,l);
    int temp2 = dfs(i+1,j,k,l+1);
    int temp3 = dfs(i,j+1,k+1,l);
    int temp4 = dfs(i,j+1,k,l+1);
    int max = max_num(max_num(temp1,temp2),max_num(temp3,temp4));
    memo[i][j][k][l] = max + value;
    return memo[i][j][k][l];


}
int main(){
    memset(memo,-1,sizeof(memo));
    memset(matrix,0,sizeof(matrix));
    scanf("%d",&n);
    while(1){
        int x,y,num;
        scanf("%d %d %d",&x,&y,&num);
        if(x==0&&y==0&&num==0) break;
        matrix[x-1][y-1]=num;
    }
    printf("%d\n",dfs(0,0,0,0));
}