#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

/*
输入96*96矩阵，3*3卷积三次（12种卷积核），得到90*90矩阵
3*3池化得到30*30矩阵，3*3池化得到10*10矩阵
10*10矩阵进行2*2池化得到5*5矩阵
12种5*5矩阵展开为300维度向量
输入到一个64神经元的全连接层计算得到64维度向量

*/
float convolution_1[90][90],convolution_2[90][90],convolution_3[90][90],
    convolution_4[90][90],convolution_5[90][90],convolution_6[90][90],
    convolution_7[90][90],convolution_8[90][90],convolution_9[90][90],
    convolution_10[90][90],convolution_11[90][90],convolution_12[90][90];
float pooling_matrix_1[5][5],pooling_matrix_2[5][5],pooling_matrix_3[5][5],
    pooling_matrix_4[5][5],pooling_matrix_5[5][5],pooling_matrix_6[5][5],
    pooling_matrix_7[5][5],pooling_matrix_8[5][5],pooling_matrix_9[5][5],
    pooling_matrix_10[5][5],pooling_matrix_11[5][5],pooling_matrix_12[5][5];
float input_matrix[96][96];
float fc_weights[64][300];  // 64神经元 × 300输入
float fc_biases[64];        // 64个偏置
float fc_output[64];        // 64维输出
float learning_rate = 0.01f;
int current_digit;

// 12种3x3卷积核定义
float kernel_1[3][3] = {  // 垂直边缘检测
    {-1.0f, 0.0f, 1.0f},
    {-2.0f, 0.0f, 2.0f},
    {-1.0f, 0.0f, 1.0f}
};

float kernel_2[3][3] = {  // 水平边缘检测
    {-1.0f, -2.0f, -1.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 2.0f, 1.0f}
};

float kernel_3[3][3] = {  // 45度边缘检测
    {-2.0f, -1.0f, 0.0f},
    {-1.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 2.0f}
};

float kernel_4[3][3] = {  // 135度边缘检测
    {0.0f, -1.0f, -2.0f},
    {1.0f, 0.0f, -1.0f},
    {2.0f, 1.0f, 0.0f}
};

float kernel_5[3][3] = {  // 拉普拉斯边缘检测
    {0.0f, -1.0f, 0.0f},
    {-1.0f, 4.0f, -1.0f},
    {0.0f, -1.0f, 0.0f}
};

float kernel_6[3][3] = {  // 强拉普拉斯
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 8.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
};

float kernel_7[3][3] = {  // 锐化滤波器
    {0.0f, -1.0f, 0.0f},
    {-1.0f, 5.0f, -1.0f},
    {0.0f, -1.0f, 0.0f}
};

float kernel_8[3][3] = {  // 强锐化
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 9.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
};

float kernel_9[3][3] = {  // 高斯模糊(轻微)
    {1.0f, 2.0f, 1.0f},
    {2.0f, 4.0f, 2.0f},
    {1.0f, 2.0f, 1.0f}
};

float kernel_10[3][3] = { // 均值模糊
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f}
};

float kernel_11[3][3] = { // 浮雕效果
    {-2.0f, -1.0f, 0.0f},
    {-1.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 2.0f}
};

float kernel_12[3][3] = { // 轮廓增强
    {0.0f, 1.0f, 0.0f},
    {1.0f, -4.0f, 1.0f},
    {0.0f, 1.0f, 0.0f}
};

// 卷积核数组，便于循环使用
float* kernels[12] = {
    (float*)kernel_1, (float*)kernel_2, (float*)kernel_3,
    (float*)kernel_4, (float*)kernel_5, (float*)kernel_6,
    (float*)kernel_7, (float*)kernel_8, (float*)kernel_9,
    (float*)kernel_10, (float*)kernel_11, (float*)kernel_12
};
int training_mode = 1; // 1表示训练模式，0表示推理模式

void convolution_3x3_1(float input[96][96], float output[94][94], float kernel[3][3]) {
    for (int i = 0; i < 94; i++) {   
        for (int j = 0; j < 94; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = (sum > 0) ? sum : 0;  // ReLU激活函数
        }
    }
    printf("Convolution stage 1 completed: 96×96 → 94×94\n");
}

void convolution_3x3_2(float input[94][94], float output[92][92], float kernel[3][3]) {
    for (int i = 0; i < 92; i++) {   
        for (int j = 0; j < 92; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = (sum > 0) ? sum : 0;  // ReLU激活函数
        }
    }
    printf("Convolution stage 2 completed: 94×94 → 92×92\n");
}

void convolution_3x3_3(float input[92][92], float output[90][90], float kernel[3][3]) {
    for (int i = 0; i < 90; i++) {    
        for (int j = 0; j < 90; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++){
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = (sum > 0) ? sum : 0;  // ReLU激活函数
        }
    }
    printf("Convolution stage 3 completed: 92×92 → 90×90\n");
}
void pooling_3x3_1(float input[90][90], float output[30][30]) {
    for (int i = 0; i < 30; i++) {    
        for (int j = 0; j < 30; j++) {
            float max = input[i * 3][j * 3];  // 3x3池化，步长3
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    float temp = input[i * 3 + ki][j * 3 + kj];
                    if (temp > max) {
                        max = temp;
                    }
                }
            }
            output[i][j] = max;  // 重要：赋值给输出！
        }
    }
    printf("Pooling stage 1 completed: 90×90 → 30×30\n");
}

void pooling_3x3_2(float input[30][30], float output[10][10]) {
    for (int i = 0; i < 10; i++) {    
        for (int j = 0; j < 10; j++) {
            float max = input[i * 3][j * 3];  // 3x3池化，步长3
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    float temp = input[i * 3 + ki][j * 3 + kj];
                    if (temp > max) {
                        max = temp;
                    }
                }
            }
            output[i][j] = max;
        }
    }
    printf("Pooling stage 2 completed: 30×30 → 10×10\n");
}

void pooling_2x2_3(float input[10][10], float output[5][5]) {
    for (int i = 0; i < 5; i++) {    
        for (int j = 0; j < 5; j++) {
            float max = input[i * 2][j * 2];  // 2x2池化，步长2
            for (int ki = 0; ki < 2; ki++) {
                for (int kj = 0; kj < 2; kj++) {
                    float temp = input[i * 2 + ki][j * 2 + kj];
                    if (temp > max) {
                        max = temp;
                    }
                }
            }
            output[i][j] = max;
        }
    }
    printf("Pooling stage 3 completed: 10×10 → 5×5\n");
}
void start_convolution(float input[96][96], float output[90][90],float kernel[3][3]){
    printf("Starting convolution...\n"); 
    float temp_1[94][94];
    float temp_2[92][92];
    convolution_3x3_1(input, temp_1, kernel);
    convolution_3x3_2(temp_1, temp_2, kernel);
    convolution_3x3_3(temp_2, output, kernel);
}
void start_pooling(float input[90][90], float output[5][5]){
    printf("Starting pooling...\n"); 
    float temp_1[30][30];
    float temp_2[10][10];
    pooling_3x3_1(input, temp_1);
    pooling_3x3_2(temp_1, temp_2);
    pooling_2x2_3(temp_2, output);
}
void init_convolution(){ 
        start_convolution(input_matrix,convolution_1,kernel_1);
        start_convolution(input_matrix,convolution_2,kernel_2);
        start_convolution(input_matrix,convolution_3,kernel_3);
        start_convolution(input_matrix,convolution_4,kernel_4);
        start_convolution(input_matrix,convolution_5,kernel_5);
        start_convolution(input_matrix,convolution_6,kernel_6);
        start_convolution(input_matrix,convolution_7,kernel_7);
        start_convolution(input_matrix,convolution_8,kernel_8);
        start_convolution(input_matrix,convolution_9,kernel_9);
        start_convolution(input_matrix,convolution_10,kernel_10);
        start_convolution(input_matrix,convolution_11,kernel_11);
        start_convolution(input_matrix,convolution_12,kernel_12);

}
void init_pooling(){ 
        start_pooling(convolution_1,pooling_matrix_1);
        start_pooling(convolution_2,pooling_matrix_2);
        start_pooling(convolution_3,pooling_matrix_3);
        start_pooling(convolution_4,pooling_matrix_4);
        start_pooling(convolution_5,pooling_matrix_5);
        start_pooling(convolution_6,pooling_matrix_6);
        start_pooling(convolution_7,pooling_matrix_7);
        start_pooling(convolution_8,pooling_matrix_8);
        start_pooling(convolution_9,pooling_matrix_9);
        start_pooling(convolution_10,pooling_matrix_10);
        start_pooling(convolution_11,pooling_matrix_11);
        start_pooling(convolution_12,pooling_matrix_12);
}
void flatten_matrix(float output[300]){ 
    int index = 0;
    for(int k = 0; k < 12; k++){
        float (*pool)[5];
        switch(k){
            case 0: pool = pooling_matrix_1; break;
            case 1: pool = pooling_matrix_2; break;
            case 2: pool = pooling_matrix_3; break;
            case 3: pool = pooling_matrix_4; break;
            case 4: pool = pooling_matrix_5; break;
            case 5: pool = pooling_matrix_6; break;
            case 6: pool = pooling_matrix_7; break;
            case 7: pool = pooling_matrix_8; break;
            case 8: pool = pooling_matrix_9; break;
            case 9: pool = pooling_matrix_10; break;
            case 10: pool = pooling_matrix_11; break;
            case 11: pool = pooling_matrix_12; break;
        }
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                output[index++] = pool[i][j];
            }
        }
    }
}
void initialize_weights() {
    // 随机初始化全连接层权重
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            fc_weights[i][j] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        }
        fc_biases[i] = 0.1f;
    }
}
void fully_connected_layer(float input[300], float output[64]) {
    for (int i = 0; i < 64; i++) {
        float sum = 0.0f;
        for (int j = 0; j < 300; j++) {
            sum += fc_weights[i][j] * input[j];
        }
        sum += fc_biases[i];
        output[i] = (sum > 0) ? sum : 0;  // ReLU激活函数
    }
    printf("Fully connected layer completed: 300 → 64\n");
}
// 最简单的权重更新
void simple_weight_update(float network_output[64], int true_label, float flattened_input[300]) {
    printf("Updating 64×300 weights and 64 biases...\n");
    
    // 为每个数字分配6个专属神经元（10×6=60，接近64）
    int start_neuron = true_label * 6;
    
    for (int neuron = start_neuron; neuron < start_neuron + 6 && neuron < 64; neuron++) {
        // 我们希望这个神经元的输出增加（简单目标）
        float error = 1.0f - network_output[neuron];
        
        // 更新这个神经元的所有300个权重
        for (int input_idx = 0; input_idx < 300; input_idx++) {
            fc_weights[neuron][input_idx] += learning_rate * error * flattened_input[input_idx];
        }
        
        // 更新偏置
        fc_biases[neuron] += learning_rate * error;
    }
    
    printf("Updated weights for digit %d (neurons %d-%d)\n", 
           true_label, start_neuron, start_neuron + 5);
}
// 保存权重到文件
void save_weights(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return;
    }
    
    // 保存全连接层权重 (64×300)
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            fprintf(file, "%.8f ", fc_weights[i][j]);
        }
        fprintf(file, "\n");
    }
    
    // 保存偏置 (64)
    for (int i = 0; i < 64; i++) {
        fprintf(file, "%.8f ", fc_biases[i]);
    }
    fprintf(file, "\n");
    
    fclose(file);
    printf("Weights saved to %s\n", filename);
}

// 从文件加载权重
void load_weights(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Cannot open file %s for reading\n", filename);
        return;
    }
    
    // 加载全连接层权重 (64×300)
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            if (fscanf(file, "%f", &fc_weights[i][j]) != 1) {
                printf("Error reading weights from file\n");
                fclose(file);
                return;
            }
        }
    }
    
    // 加载偏置 (64)
    for (int i = 0; i < 64; i++) {
        if (fscanf(file, "%f", &fc_biases[i]) != 1) {
            printf("Error reading biases from file\n");
            fclose(file);
            return;
        }
    }
    
    fclose(file);
    printf("Weights loaded from %s\n", filename);
}

// 保存数字对应的64维向量到文件
void save_digit_vectors(const char* filename, int digit, float vector[64]) {
    FILE* file = fopen(filename, "a");  // 追加模式
    if (file == NULL) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return;
    }
    
    // 格式: 数字,向量值1,向量值2,...,向量值64
    fprintf(file, "%d", digit);
    for (int i = 0; i < 64; i++) {
        fprintf(file, ",%.8f", vector[i]);
    }
    fprintf(file, "\n");
    
    fclose(file);
    printf("Digit %d vector saved to %s\n", digit, filename);
}

// 从文件加载数字向量（用于推理模式）
void load_digit_vectors(const char* filename, float digit_vectors[10][64]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s for reading\n", filename);
        return;
    }
    
    char line[1024];
    int digit;
    int loaded_count = 0;
    
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        if (token == NULL) continue;
        
        digit = atoi(token);
        if (digit < 0 || digit > 9) continue;
        
        for (int i = 0; i < 64; i++) {
            token = strtok(NULL, ",");
            if (token == NULL) break;
            digit_vectors[digit][i] = atof(token);
        }
        loaded_count++;
    }
    
    fclose(file);
    printf("Loaded %d digit vectors from %s\n", loaded_count, filename);
}

// 训练模式：处理单个数字样本
void train_digit_sample(int digit) {
    printf("\n=== Training digit %d ===\n", digit);
    
    // 步骤1: 前向传播（使用当前权重）
    init_convolution();
    init_pooling();
    float flattened_matrix[300];
    flatten_matrix(flattened_matrix);
    float output_vector[64];
    fully_connected_layer(flattened_matrix, output_vector);

    // 步骤2: 反向传播更新权重
    simple_weight_update(output_vector, digit, flattened_matrix);
    
    // 步骤3: 用更新后的权重重新计算特征并保存
    fully_connected_layer(flattened_matrix, output_vector);  // 重新计算
    save_digit_vectors("digit_vectors.txt", digit, output_vector);
    
    printf("Digit %d training completed\n", digit);
}

// 推理模式：找到最匹配的数字
int infer_digit() {
    printf("\n=== Inference Mode ===\n");
    
    // 加载预训练的数字向量
    float digit_vectors[10][64];
    load_digit_vectors("digit_vectors.txt", digit_vectors);
    
    // 卷积 + 池化
    init_convolution();
    init_pooling();
    
    // 展平特征
    float flattened_matrix[300];
    flatten_matrix(flattened_matrix);
    
    // 全连接层
    float output_vector[64];
    fully_connected_layer(flattened_matrix, output_vector);
    
    // 计算与每个数字向量的相似度（使用余弦相似度）
    int best_digit = -1;
    float best_similarity = -1.0f;
    
    for (int digit = 0; digit < 10; digit++) {
        float dot_product = 0.0f;
        float norm_output = 0.0f;
        float norm_digit = 0.0f;
        
        for (int i = 0; i < 64; i++) {
            dot_product += output_vector[i] * digit_vectors[digit][i];
            norm_output += output_vector[i] * output_vector[i];
            norm_digit += digit_vectors[digit][i] * digit_vectors[digit][i];
        }
        
        norm_output = sqrtf(norm_output);
        norm_digit = sqrtf(norm_digit);
        
        if (norm_output > 0 && norm_digit > 0) {
            float similarity = dot_product / (norm_output * norm_digit);
            printf("Digit %d similarity: %.4f\n", digit, similarity);
            
            if (similarity > best_similarity) {
                best_similarity = similarity;
                best_digit = digit;
            }
        }
    }
    
    printf("Predicted digit: %d (similarity: %.4f)\n", best_digit, best_similarity);
    return best_digit;
}

int main() {
    // 初始化随机种子
    srand(42);
    
    if (training_mode) {
        // 训练模式
        printf("=== Training Mode ===\n");
        
        // 初始化权重
        initialize_weights();
        
        // 这里您需要循环处理每个数字的多个样本
        // 示例：处理数字0
        printf("Please input 96x96 matrix for digit 0:\n");
        for (int i = 0; i < 96; i++) {
            for (int j = 0; j < 96; j++) {
                scanf("%f", &input_matrix[i][j]);
            }
        }
        
        train_digit_sample(0);
        
        // 保存训练好的权重
        save_weights("model_weights.txt");
        
        printf("Training completed!\n");
        
    } else {
        // 推理模式
        printf("=== Inference Mode ===\n");
        
        // 加载预训练权重
        load_weights("model_weights.txt");
        
        printf("Please input 96x96 matrix for recognition:\n");
        for (int i = 0; i < 96; i++) {
            for (int j = 0; j < 96; j++) {
                scanf("%f", &input_matrix[i][j]);
            }
        }
        
        int predicted_digit = infer_digit();
        printf("Final prediction: %d\n", predicted_digit);
    }
    
    return 0;
}