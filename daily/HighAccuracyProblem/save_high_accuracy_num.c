#include <stdio.h>  
#define MAX_SIZE 500
#define ll long long
int num[MAX_SIZE];
int temp = 0;

void save_num(ll input, int num[]){
    temp = 0;
    int is_negative = 0;
    if (input < 0){
        input = -input;
        is_negative = 1;
    }
    while (input > 0 ){
        num[temp] = input % 10;
        input /= 10;
        temp++;
    }
    if (is_negative == 1){
        num[temp] = -99;
        temp++;
    }
}
void print_num(int num[]){
    for (int i = temp - 1 ; i >= 0 ; i--){
        if (num[i] == -99){
            printf("-");
        }else {
            printf("%d", num[i]);
        }
        
    }
}
int main(){
    ll input;
    scanf("%lld", &input);
    save_num(input, num);
    print_num(num);
}