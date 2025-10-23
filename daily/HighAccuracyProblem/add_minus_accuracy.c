#include <stdio.h>  
#define MAX_SIZE 500
#define ll long long


typedef struct titan_number{
    int num[MAX_SIZE];
    int is_negative;
    int size;
} tn;
void save_number(tn* number,short input){
    number->size = 0;
    if (input < 0){
        number->is_negative = 1;
        input = -input;
    } else{
        number->is_negative = 0;
    }
    while (input > 0){
        number->num[number->size] = input % 10;
        input /= 10;
        number->size++;
    }

}
void print_number(tn* number){
    if (number->is_negative == 1){
        printf("-");
    }
    for (int i = number->size - 1; i >= 0; i--){
        printf("%d",number->num[i]);
    }
}
void add_numbers(tn* a,tn* b,tn* result){ 
    result->size = 0;
    short carry = 0;
    int max = a->size > b->size ? a->size : b->size;
    if (a->is_negative == b->is_negative){ 
        for (int i = 0; i < max; i++){

            short sum = a->num[i] + b->num[i] + carry;
            result->num[i] = sum % 10;
            carry = sum / 10;
            result->size++;
        }
        if (carry > 0){
            result->num[result->size] = carry;
            result->size++;
        }
        

    }
}
int main(){
    short input_1,input_2;
    scanf("%hd",&input_1);
    struct titan_number a,b,result,result_2;
    save_number(&a,input_1);
    add_numbers(&a,&a,&result);
    add_numbers(&result,&result,&result_2);
    print_number(&result); 
    printf("\n");  
    print_number(&result_2);


}