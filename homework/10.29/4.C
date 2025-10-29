#include <stdio.h>

int main(){
    int n,a[1000];
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }
    for (int i = 0; i < n; i++){
        double sum = 0.0;
        int x = 1;
        for (int j = 1; j <= a[i]; j++){
            x++;
            if (j % 2 == 0){
                sum -= (double) j/ ((j * (j+1))/2 + 2);
            } else {
                sum += (double) j/ ((j * (j+1))/2 + 2);
            }

        }
        printf("%.4lf\n",sum);
    }
}