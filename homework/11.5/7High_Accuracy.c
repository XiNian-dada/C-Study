#include <stdio.h>
typedef struct{
    int number[1000];
    int length;
} BigNumber;

void multiply(BigNumber a, int b, BigNumber *result){
    int carry = 0;
    for(int i = 0; i < 1000; i++) {
        result->number[i] = 0;
    }
    for (int i = 0; i < a.length; i++){
        int product = a.number[i] * b + carry;
        result->number[i] = product % 10;
        carry = product / 10;
    }
    int pos = a.length;
    while(carry > 0) {
        result->number[pos] = carry % 10;
        carry /= 10;
        pos++;
    }
    result->length = pos;
}

int main(){
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        int n;
        scanf("%d", &n);
         
        BigNumber factorial;
        factorial.number[0] = 1;
        factorial.length = 1;
        
        BigNumber result;
        for(int i = 1; i <= n; i++) {
            multiply(factorial, i, &result);
            factorial = result;
        }
        
        int count = 0;
        int index = 0;
        while(index < result.length && result.number[index] == 0){
            count++;
            index++;
        }
        printf("%d\n", count);

    }
    return 0;
}