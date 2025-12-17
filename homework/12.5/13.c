#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int node[1000005];
void init(int n){ 
    for(int i = 1; i <=n; i++){
        node[i] = i;
    }
}
int find(int x){ 
    return x == node[x] ? x : (node[x] = find(node[x]));
}
void merge(int a,int b){
    node[find(a)] = find(b);
}

int main(){
    int q,n;
    scanf("%d %d",&q,&n);
    init(n);
    for(int i = 0; i < q; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(a == 1){
            merge(b,c);
        }else{
            if(find(b) == find(c)){
                printf("YES\n");
            }else{
                printf("NO\n");
            }

        }
    }
}