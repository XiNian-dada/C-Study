#include <stdio.h>
int main(){
    int n;
    int m[1000] = {-1};
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &m[i]);
    }
    for (int i = 1; i <= n; i++){
        double sum = 0.0;
        for (int j = 1; j <= m[i]; j++){
            sum += (double) (j / (j+1.0));
        }
        printf("%.4f\n", sum);

    }

}