/*
2. P1464 Function（视频中提到的记忆化搜索）
https://www.luogu.com.cn/problem/P1464
*/
#include <stdio.h>
#include <math.h>
#define ll long long


ll memo[21][21][21];


void init_memo() {
    for(int i = 0; i <= 20; i++) {
        for(int j = 0; j <= 20; j++) {
            for(int k = 0; k <= 20; k++) {
                memo[i][j][k] = -1; 
            }
        }
    }
}
ll w(ll x,ll y,ll z){
    if(x <=0 ||  y <=0 || z <=0 ){
        return 1;
    }
    if (x > 20 || y > 20 || z > 20) {
        return w(20, 20, 20);
    }
    if(memo[x][y][z] != -1){
        return memo[x][y][z];
    }
    if (x < y && y < z) {
        return memo[x][y][z] = w(x, y, z - 1) + w(x, y - 1, z - 1) - w(x, y - 1, z);
    }
    else {
        return memo[x][y][z] = w(x - 1, y, z) + w(x - 1, y - 1, z) + w(x - 1, y, z - 1) - w(x - 1, y - 1, z - 1);
    }
    
}
int main(){
    ll a,b,c;
    init_memo();
    while (1){
        scanf("%lld %lld %lld",&a,&b,&c);
        if (a==-1 && b==-1 && c==-1){
            break;
        }

        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
    }

    return 0;
    
}