#include <stdio.h>  
#define MAX_SIZE 500
#define ll long long



typedef struct titan_number{
    int num[MAX_SIZE];
    int is_negative; //1表示负数，0表示正数
    int size;
} tn;
void save_number(tn* number, short input);
void print_number(tn* number);
void add_numbers(tn* a, tn* b, tn* result);
void minus_numbers(tn* a, tn* b, tn* result);  // 添加这一行声明
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
void add_numbers(tn* a, tn* b, tn* result) {
    result->size = 0;
    result->is_negative = 0;
    
    if (a->is_negative == b->is_negative) {  // 同号相加
        short carry = 0;
        int max = a->size > b->size ? a->size : b->size;
        result->is_negative = a->is_negative;
        
        for (int i = 0; i < max; i++) {
            int digit_a = (i < a->size) ? a->num[i] : 0;
            int digit_b = (i < b->size) ? b->num[i] : 0;
            short sum = digit_a + digit_b + carry;
            result->num[result->size] = sum % 10;
            carry = sum / 10;
            result->size++;
        }
        if (carry > 0) {
            result->num[result->size] = carry;
            result->size++;
        }
    } else {  // 异号相加，转换为减法
        tn temp;
        if (a->is_negative == 1) {  // a是负数
            temp = *a;
            temp.is_negative = 0;
            minus_numbers(b, &temp, result);
        } else {  // b是负数
            temp = *b;
            temp.is_negative = 0;
            minus_numbers(a, &temp, result);
        }
    }
}
void minus_numbers(tn* a, tn* b, tn *result) {
    result->size = 0;
    short carry = 0;
    
    // 处理不同符号的情况
    if (a->is_negative != b->is_negative) {
        // a是负数，b是正数: (-a) - b = -(a + b)
        if (a->is_negative == 1 && b->is_negative == 0) {
            tn temp_b = *b;
            temp_b.is_negative = 1;  // 转换为负数
            add_numbers(a, &temp_b, result);
            return;
        }
        // a是正数，b是负数: a - (-b) = a + b
        else if (a->is_negative == 0 && b->is_negative == 1) {
            tn temp_b = *b;
            temp_b.is_negative = 0;  // 转换为正数
            add_numbers(a, &temp_b, result);
            return;
        }
    }
    
    // 处理负数减负数: (-a) - (-b) = b - a
    if (a->is_negative == 1 && b->is_negative == 1) {
        tn temp_a = *a, temp_b = *b;
        temp_a.is_negative = 0;
        temp_b.is_negative = 0;
        minus_numbers(&temp_b, &temp_a, result);  // 计算 b - a
        return;
    }
    
    // 处理正数减正数的情况
    // 首先比较两个数的大小
    int is_a_larger = 0;
    if (a->size > b->size) {
        is_a_larger = 1;
    } else if (a->size < b->size) {
        is_a_larger = 0;
    } else {
        // 位数相同，逐位比较
        int i = a->size - 1;
        while (i >= 0) {
            if (a->num[i] > b->num[i]) {
                is_a_larger = 1;
                break;
            } else if (a->num[i] < b->num[i]) {
                is_a_larger = 0;
                break;
            }
            i--;
        }
        if (i < 0) {  // 两数相等
            result->is_negative = 0;
            result->num[0] = 0;
            result->size = 1;
            return;
        }
    }
    
    // 执行减法操作
    carry = 0;
    result->size = 0;
    
    if (is_a_larger) {
        // a >= b, 结果为正
        result->is_negative = 0;
        for (int i = 0; i < a->size; i++) {
            int digit_a = a->num[i];
            int digit_b = (i < b->size) ? b->num[i] : 0;
            int diff = digit_a - digit_b - carry;
            
            if (diff < 0) {
                diff += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            
            result->num[result->size++] = diff;
        }
    } else {
        // a < b, 结果为负
        result->is_negative = 1;
        for (int i = 0; i < b->size; i++) {
            int digit_b = b->num[i];
            int digit_a = (i < a->size) ? a->num[i] : 0;
            int diff = digit_b - digit_a - carry;
            
            if (diff < 0) {
                diff += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            
            result->num[result->size++] = diff;
        }
    }
    
    // 去除前导零
    while (result->size > 1 && result->num[result->size - 1] == 0) {
        result->size--;
    }
}
int main(){
    short input_1,input_2;
    scanf("%hd",&input_1);
    scanf("%hd",&input_2);
    struct titan_number a,b,result,result_2,result_3;
    save_number(&a,input_1);
    save_number(&b,input_2);

    add_numbers(&a,&a,&result);
    add_numbers(&result,&result,&result_2);
    minus_numbers(&result_2,&b,&result_3);
    print_number(&result); 
    printf("\n");  
    print_number(&result_2);
    printf("\n");
    print_number(&result_3);


}