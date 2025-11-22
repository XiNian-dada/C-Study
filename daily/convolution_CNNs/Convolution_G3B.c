#include "stdio.h"
#include "convolution.h"

float input[96][96];
float output[12][90][90];
float pooling_output[12][22][22];


void init_input(){
    for(int i = 0; i < 96; i++){
        for(int j = 0; j < 96; j++){
            input[i][j] = 0.0f;
        }
    }
}
void start(){
    // 将二维数组转换为指针数组
    float** input_ptr = (float**)malloc(96 * sizeof(float*));
    for(int i = 0; i < 96; i++) {
        input_ptr[i] = input[i];
    }
    
    // 动态分配输出数组
    float*** output_ptr = (float***)malloc(12 * sizeof(float**));
    for(int k = 0; k < 12; k++) {
        output_ptr[k] = (float**)malloc(90 * sizeof(float*));
        for(int i = 0; i < 90; i++) {
            output_ptr[k][i] = (float*)malloc(90 * sizeof(float));
        }
    }
    
    start_convolution_12kernels(input_ptr, output_ptr, 96);
    for(int k = 0; k < 12; k++) {  
        for(int i = 0; i < 90; i++) {
            for(int j = 0; j < 90; j++) {
                output[k][i][j] = output_ptr[k][i][j];
            }
        }
    }
    
    
    // 释放内存
    free(input_ptr);
    for(int k = 0; k < 12; k++) {
        for(int i = 0; i < 90; i++) {
            free(output_ptr[k][i]);
        }
        free(output_ptr[k]);
    }
    free(output_ptr);
}
void start_pooling(){
    // 将output数组转换为指针数组格式（用于池化输入）
    float*** pooling_input = (float***)malloc(12 * sizeof(float**));
    for(int k = 0; k < 12; k++) {
        pooling_input[k] = (float**)malloc(90 * sizeof(float*));
        for(int i = 0; i < 90; i++) {
            pooling_input[k][i] = &output[k][i][0];  // 指向output的每一行
        }
    }
    
    // 动态分配池化输出数组
    float*** pooling_output_ptr = (float***)malloc(12 * sizeof(float**));
    for(int k = 0; k < 12; k++) {
        pooling_output_ptr[k] = (float**)malloc(22 * sizeof(float*));
        for(int i = 0; i < 22; i++) {
            pooling_output_ptr[k][i] = (float*)malloc(22 * sizeof(float));
        }
    }
    
    // 调用多轮池化函数
    multi_stage_pooling(pooling_input, pooling_output_ptr, 12, 90);
    
    // 将结果复制到预定义的数组中
    for(int k = 0; k < 12; k++) {
        for(int i = 0; i < 22; i++) {
            for(int j = 0; j < 22; j++) {
                pooling_output[k][i][j] = pooling_output_ptr[k][i][j];
            }
        }
    }
    
    // 释放内存
    for(int k = 0; k < 12; k++) {
        free(pooling_input[k]);
    }
    free(pooling_input);
    
    for(int k = 0; k < 12; k++) {
        for(int i = 0; i < 22; i++) {
            free(pooling_output_ptr[k][i]);
        }
        free(pooling_output_ptr[k]);
    }
    free(pooling_output_ptr);
}
void check_zero_in_convolution(){ 
    int zero_sum = 0;
        for(int k = 0; k < 12; k++){
            printf("There's %d convolution result:\n", k+1);
            int zero_count = 0;
            for(int i = 0; i < 90; i++){
                for(int j = 0; j < 90; j++){
                    if(output[k][i][j] < 1e-6 && output[k][i][j] > -1e-6){
                        zero_count++;
                        zero_sum++;
                    }
                }
            }
            printf("There's %d/8100 zeros in this convolution result\n", zero_count);
            printf("\n");
        }
    printf("There's %d/97200 zeros in total\n", zero_sum);
}
void check_zero_in_pooling(){ 
    int zero_sum = 0;
        for(int k = 0; k < 12; k++){
            printf("There's %d pooling result:\n", k+1);
            int zero_count = 0;
            for(int i = 0; i < 22; i++){
                for(int j = 0; j < 22; j++){
                    if(pooling_output[k][i][j] < 1e-6 && pooling_output[k][i][j] > -1e-6){
                        zero_count++;
                        zero_sum++;
                    }
                }
            }
            printf("There's %d/440 zeros in this pooling result\n", zero_count);
            printf("\n");
        }
    printf("There's %d/5808 zeros in total\n", zero_sum);
}
void mini_max_normalize(float input[12][22][22]){
    for(int i = 0; i < 12; i++){
        float min = input[i][0][0];
        float max = input[i][0][0];
        
        // 查找当前通道的最小值和最大值
        for(int k = 0; k < 22; k++){
            for(int l = 0; l < 22; l++){
                if(input[i][k][l] < min){
                    min = input[i][k][l];
                }
                if(input[i][k][l] > max){
                    max = input[i][k][l];
                }
            }
        }
        // 归一化处理
        if(max != min) {  // 防止除零错误
            for(int k = 0; k < 22; k++){
                for(int l = 0; l < 22; l++){
                    input[i][k][l] = (input[i][k][l] - min) / (max - min);
                }
            }
        } else {
            // 如果所有值相等，则归一化为0
            for(int k = 0; k < 22; k++){
                for(int l = 0; l < 22; l++){
                    input[i][k][l] = 0.0f;
                }
            }
        }
    }
}
int main(){
    printf("Welcome to use Convolution_G3B\n");
    printf("Please input your 96 * 96 matrix:\n");
    init_input();
    for(int i = 0; i < 96; i++){
        for(int j = 0; j < 96; j++){
            scanf("%f", &input[i][j]);
        }
    }
    start();
    check_zero_in_convolution();
    start_pooling();
    check_zero_in_pooling();
    int if_printf = 0;
    printf("Do you want to print the convolution result?(1/0)\n");
    scanf("%d", &if_printf);
    if(if_printf == 1){
        for(int k = 0; k < 12; k++){
            printf("The %d convolution result:\n", k+1);
            for(int i = 0; i < 22; i++){
                for(int j = 0; j < 22; j++){
                    printf("%.4f ", pooling_output[k][i][j]);
                }
            }
            printf("\n");
        }
    }
    mini_max_normalize(pooling_output);
    if_printf = 0;
    printf("Do you want to print the normalized pooling result?(1/0)\n");
    scanf("%d", &if_printf);
    if(if_printf == 1){
        for(int k = 0; k < 12; k++){
            printf("The %d normalized pooling result:\n", k+1);
            for(int i = 0; i < 22; i++){
                for(int j = 0; j < 22; j++){
                    printf("%.4f ", pooling_output[k][i][j]);
                }
            }
        }
    }
}