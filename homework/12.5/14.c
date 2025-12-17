#include "stdio.h"
#include "stdlib.h"

int main(){
    int n,m,q;
    scanf("%d %d %d",&n,&m,&q);
    
    int **prefix = (int**)malloc((n + 1) * sizeof(int*));
    for(int i = 0; i <= n; i++) {
        prefix[i] = (int*)calloc(m + 1, sizeof(int));
    }
    

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int value;
            scanf("%d", &value);
            prefix[i][j] = value + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }

    for(int i = 0; i < q; i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        
        int sum = prefix[x2][y2] - prefix[x1-1][y2] - prefix[x2][y1-1] + prefix[x1-1][y1-1];
        printf("%d\n",sum);
    }
}