#include <stdio.h>

int main(){
    int n ,a[100],b[100],c[100];
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
    }
    for (int i=0;i<n;i++){
        if (a[i] <= 0 || b[i] <= 0 || c[i] <= 0){
            printf("No\n");
            continue;
        }
        if (a[i] + b[i] <= c[i] || a[i] + c[i] <= b[i] || b[i] + c[i] <= a[i]){
            printf("No\n");
            continue;
        }
        int temp_a = a[i] * a[i];
        int temp_b = b[i] * b[i];
        int temp_c = c[i] * c[i];
        if (temp_a + temp_b == temp_c || temp_a + temp_c == temp_b || temp_b + temp_c == temp_a){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}