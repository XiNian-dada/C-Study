#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define FC_INPUT_1 28
#define IMG_INPUT 28
#define IMG_OUTPUT 26
#define POOL_OUTPUT 13

typedef struct{
    float kernel[3][3];
    float bias;
} conv_kernel;

float fcLayer_1[64][1690];
float fcLayer_2[10][64];
float fcLayer_1_bias[64];
float fcLayer_2_bias[10];
conv_kernel conv_kernels[10];

// 添加梯度变量用于反向传播
float conv_grad[10][3][3];
float conv_bias_grad[10];
float fc1_grad[64][1690];
float fc1_bias_grad[64];
float fc2_grad[10][64];
float fc2_bias_grad[10];

// 函数声明
void save_model();
void backward_pass(float loss_gradient);
void test_mode();

void init_conv_kernels() {
    FILE *file = fopen("conv_kernels.txt", "r");
    
    if (file == NULL) {
        // 文件不存在，创建新文件并写入随机值
        file = fopen("conv_kernels.txt", "w");
        if (file == NULL) {
            printf("Error: Cannot create conv_kernels.txt\n");
            return;
        }
        
        srand(time(NULL));
        
        for (int i = 0; i < 10; i++) {
            // 写入3x3卷积核参数
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    conv_kernels[i].kernel[j][k] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f; // 随机值范围[-1, 1]
                    fprintf(file, "%.6f ", conv_kernels[i].kernel[j][k]);
                }
            }
            // 初始化偏置
            conv_kernels[i].bias = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
            fprintf(file, "%.6f\n", conv_kernels[i].bias);
        }
        fclose(file);
        printf("conv_kernels.txt created with random values.\n");
    } else {
        // 文件存在，读取参数
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    fscanf(file, "%f", &conv_kernels[i].kernel[j][k]);
                }
            }
            fscanf(file, "%f", &conv_kernels[i].bias);
        }
        fclose(file);
        printf("conv_kernels.txt loaded successfully.\n");
    }
}
// 全连接层1初始化函数
void init_fc_layer_1() {
    FILE *file = fopen("fc_layer_1.txt", "r");
    
    if (file == NULL) {
        // 文件不存在，创建新文件并写入随机值
        file = fopen("fc_layer_1.txt", "w");
        if (file == NULL) {
            printf("Error: Cannot create fc_layer_1.txt\n");
            return;
        }
        
        srand(time(NULL));
        
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 1690; j++) {
                fcLayer_1[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
                fprintf(file, "%.6f ", fcLayer_1[i][j]);
            }
            // 初始化偏置
            fcLayer_1_bias[i] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
            fprintf(file, "%.6f\n", fcLayer_1_bias[i]);
        }
        fclose(file);
        printf("fc_layer_1.txt created with random values.\n");
    } else {
        // 文件存在，读取参数
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 1690; j++) {
                fscanf(file, "%f", &fcLayer_1[i][j]);
            }
            // 读取偏置
            fscanf(file, "%f", &fcLayer_1_bias[i]);
        }
        fclose(file);
        printf("fc_layer_1.txt loaded successfully.\n");
    }
}

// 全连接层2初始化函数
void init_fc_layer_2() {
    FILE *file = fopen("fc_layer_2.txt", "r");
    
    if (file == NULL) {
        // 文件不存在，创建新文件并写入随机值
        file = fopen("fc_layer_2.txt", "w");
        if (file == NULL) {
            printf("Error: Cannot create fc_layer_2.txt\n");
            return;
        }
        
        srand(time(NULL));
        
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 64; j++) {
                fcLayer_2[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
                fprintf(file, "%.6f ", fcLayer_2[i][j]);
            }
            // 初始化偏置
            fcLayer_2_bias[i] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
            fprintf(file, "%.6f\n", fcLayer_2_bias[i]);
        }
        fclose(file);
        printf("fc_layer_2.txt created with random values.\n");
    } else {
        // 文件存在，读取参数
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 64; j++) {
                fscanf(file, "%f", &fcLayer_2[i][j]);
            }
            // 读取偏置
            fscanf(file, "%f", &fcLayer_2_bias[i]);
        }
        fclose(file);
        printf("fc_layer_2.txt loaded successfully.\n");
    }
}
void conv(float input[28][28], float output[10][26][26]){
    // 使用所有十个卷积核进行卷积计算
    for(int k = 0; k < 10; k++){
        conv_kernel kernel = conv_kernels[k];
        
        // 执行3x3卷积操作，输入28x28，输出26x26
        for(int i = 0; i < 26; i++){
            for(int j = 0; j < 26; j++){
                float sum = 0.0f;
                
                // 3x3卷积核滑动计算
                for(int ki = 0; ki < 3; ki++){
                    for(int kj = 0; kj < 3; kj++){
                        sum += input[i + ki][j + kj] * kernel.kernel[ki][kj];
                    }
                }
                
                // 加上偏置项
                output[k][i][j] = sum + kernel.bias;
            }
        }
    }
}
void max_pooling(float input[10][26][26], float output[10][13][13]){
    for(int k = 0; k < 10; k++){
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < 13; j++){ 
                // 在2x2窗口内找到最大值
                float max_val = input[k][2 * i][2 * j];
                
                if(input[k][2 * i][2 * j + 1] > max_val)
                    max_val = input[k][2 * i][2 * j + 1];
                if(input[k][2 * i + 1][2 * j] > max_val)
                    max_val = input[k][2 * i + 1][2 * j];
                if(input[k][2 * i + 1][2 * j + 1] > max_val)
                    max_val = input[k][2 * i + 1][2 * j + 1];
                
                output[k][i][j] = max_val;
            }
        }
    }
}
void fc_layer_1(float input[10][13][13], float output[64]){ 
    float flattened_input[10*13*13];
    int index = 0;
    for(int k = 0; k < 10; k++){
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < 13; j++){
                flattened_input[index] = input[k][i][j];
                index++;
            }
        }
    }
    for(int i = 0; i < 64; i++){ 
        float sum = 0.0f;
        for(int j = 0; j < 10*13*13; j++){
            sum += flattened_input[j] * fcLayer_1[i][j];
        }
        output[i] = sum + fcLayer_1_bias[i];
    }

}

void fc_layer_2(float input[64], float output[10]){ 
    for(int i = 0; i < 10; i++){ 
        float sum = 0.0f;
        for(int j = 0; j < 64; j++){
            sum += input[j] * fcLayer_2[i][j];
        }
        output[i] = sum + fcLayer_2_bias[i];
    }
}
void train_mode(){ 
    int train_rounds = 100;
    float learning_rate = 0.01;
    for (int i = 0; i < train_rounds; i++) { 
        



    }


}
int main(){
    srand(time(NULL));
    init_conv_kernels();
    init_fc_layer_1();
    init_fc_layer_2();

    int mode = 1;
    printf("请选择模式：\n1. 训练模式\n2. 测试模式\n");
    scanf("%d", &mode);
    switch(mode){
        case 1:
            train_mode();
            break;
        case 2:
            test_mode();
            break;
        default:
            printf("Invalid mode!\n");

    }
}