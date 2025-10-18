#include <stdio.h>

int num(int n){
    int reversed = 0;
    int original = n;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed == original;
}

int main(){
    int a,b,x;
    scanf("%d %d",&a,&b);
    for (int i=a;i<=b;i++){
        if (num(i)) {
            int is_prime=1;
            for(x=2;x*x<=i;x++){
                if(i%x==0) {
                    is_prime=0;
                    break;
                }
                
            }
            if (is_prime && i!=1) printf("%d\n",i);
        }
    }
    return 0;
}