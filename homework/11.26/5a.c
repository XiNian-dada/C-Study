#include <stdio.h>
int fn(int n) {
    if (n == 1) return 0; 
    return (fn(n - 1) + 3) % n;
}
int main(){
    int n, people;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){ 
        scanf("%d", &people); 
        printf("%d\n", fn(people) + 1);
    }
}