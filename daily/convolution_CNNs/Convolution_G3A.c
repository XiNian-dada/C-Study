// cnn_digit_fixed.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
保留你原来的结构：
输入96×96 -> 每个kernel三次3x3卷积 -> 90×90 -> 池化 3x3 -> 30×30 -> 池化 3x3 -> 10×10 -> 池化 2x2 -> 5×5
12 个 5×5 展开为 300 维 -> 全连接 300->64 -> 每个数字占 6 个神经元 -> 通过平均取最大作为预测

主要修改：
- 移除 digit_vectors（模板匹配）相关函数和调用
- 推理使用 FC 输出的每组 6 个神经元平均值做 argmax 分类
- 训练仍然只更新 FC 层（保持你的设计）
- 保留保存/加载 model_weights（fc_weights, fc_biases）
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
float fc_weights[64][300];  // 64 neurons × 300 inputs
float fc_biases[64];        // 64 biases
float learning_rate = 0.01f;
int current_digit;

// kernels (unchanged)
float kernel_1[3][3] = {
    {-1.0f, 0.0f, 1.0f},
    {-2.0f, 0.0f, 2.0f},
    {-1.0f, 0.0f, 1.0f}
};
float kernel_2[3][3] = {
    {-1.0f, -2.0f, -1.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 2.0f, 1.0f}
};
float kernel_3[3][3] = {
    {-2.0f, -1.0f, 0.0f},
    {-1.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 2.0f}
};
float kernel_4[3][3] = {
    {0.0f, -1.0f, -2.0f},
    {1.0f, 0.0f, -1.0f},
    {2.0f, 1.0f, 0.0f}
};
float kernel_5[3][3] = {
    {0.0f, -1.0f, 0.0f},
    {-1.0f, 4.0f, -1.0f},
    {0.0f, -1.0f, 0.0f}
};
float kernel_6[3][3] = {
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 8.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
};
float kernel_7[3][3] = {
    {0.0f, -1.0f, 0.0f},
    {-1.0f, 5.0f, -1.0f},
    {0.0f, -1.0f, 0.0f}
};
float kernel_8[3][3] = {
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 9.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
};
float kernel_9[3][3] = {
    {1.0f, 2.0f, 1.0f},
    {2.0f, 4.0f, 2.0f},
    {1.0f, 2.0f, 1.0f}
};
float kernel_10[3][3] = {
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f}
};
float kernel_11[3][3] = {
    {-2.0f, -1.0f, 0.0f},
    {-1.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 2.0f}
};
float kernel_12[3][3] = {
    {0.0f, 1.0f, 0.0f},
    {1.0f, -4.0f, 1.0f},
    {0.0f, 1.0f, 0.0f}
};

void debug_convolution_output() {
    printf("=== Debug Convolution Output ===\n");
    int non_zero_count = 0;
    float max_val = 0.0f;
    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 90; j++) {
            if (convolution_1[i][j] > 1e-8f) non_zero_count++;
            if (convolution_1[i][j] > max_val) max_val = convolution_1[i][j];
        }
    }
    printf("Conv1 - Non-zero: %d/8100, Max value: %.6f\n", non_zero_count, max_val);
    non_zero_count = 0;
    max_val = 0.0f;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (pooling_matrix_1[i][j] > 1e-8f) non_zero_count++;
            if (pooling_matrix_1[i][j] > max_val) max_val = pooling_matrix_1[i][j];
        }
    }
    printf("Pool1 - Non-zero: %d/25, Max value: %.6f\n", non_zero_count, max_val);
}

void debug_flattened_features(float flattened[300]) {
    printf("=== Debug Flattened Features ===\n");
    int non_zero_count = 0;
    float max_val = 0.0f;
    for (int i = 0; i < 300; i++) {
        if (flattened[i] > 1e-8f) non_zero_count++;
        if (flattened[i] > max_val) max_val = flattened[i];
    }
    printf("Flattened - Non-zero: %d/300, Max value: %.6f\n", non_zero_count, max_val);
    printf("First 20 features: ");
    for (int i = 0; i < 20; i++) {
        printf("%.4f ", flattened[i]);
    }
    printf("\n");
}

void debug_fc_layer(float input[300]) {
    printf("=== Debug FC Layer ===\n");
    int zero_features = 0;
    for (int i = 0; i < 300; i++) {
        if (fabs(input[i]) < 1e-8f) zero_features++;
    }
    printf("Zero input features: %d/300\n", zero_features);
    // Show some weight/bias info (min/max not computed to keep simple)
    printf("FC sample weight fc_weights[0][0]=%.6f, fc_weights[63][299]=%.6f\n", fc_weights[0][0], fc_weights[63][299]);
    printf("FC sample biases fc_biases[0]=%.6f, fc_biases[63]=%.6f\n", fc_biases[0], fc_biases[63]);
}

void convolution_3x3_1(float input[96][96], float output[94][94], float kernel[3][3]) {
    for (int i = 0; i < 94; i++) {
        for (int j = 0; j < 94; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            float alpha = 0.01f; // 可以调节，通常 0.01~0.1
            output[i][j] = (sum > 0) ? sum : alpha * sum;
        }
    }
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
            float alpha = 0.01f; // 可以调节，通常 0.01~0.1
            output[i][j] = (sum > 0) ? sum : alpha * sum;
        }
    }
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
            float alpha = 0.01f; // 可以调节，通常 0.01~0.1
            output[i][j] = (sum > 0) ? sum : alpha * sum;
        }
    }
}

void pooling_3x3_1(float input[90][90], float output[30][30]) {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            float max = input[i * 3][j * 3];
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    float temp = input[i * 3 + ki][j * 3 + kj];
                    if (temp > max) max = temp;
                }
            }
            output[i][j] = max;
        }
    }
}

void pooling_3x3_2(float input[30][30], float output[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            float max = input[i * 3][j * 3];
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    float temp = input[i * 3 + ki][j * 3 + kj];
                    if (temp > max) max = temp;
                }
            }
            output[i][j] = max;
        }
    }
}

void pooling_2x2_3(float input[10][10], float output[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            float max = input[i * 2][j * 2];
            for (int ki = 0; ki < 2; ki++) {
                for (int kj = 0; kj < 2; kj++) {
                    float temp = input[i * 2 + ki][j * 2 + kj];
                    if (temp > max) max = temp;
                }
            }
            output[i][j] = max;
        }
    }
}

void start_convolution(float input[96][96], float output[90][90], float kernel[3][3]){
    float temp_1[94][94];
    float temp_2[92][92];
    convolution_3x3_1(input, temp_1, kernel);
    convolution_3x3_2(temp_1, temp_2, kernel);
    convolution_3x3_3(temp_2, output, kernel);
}

void start_pooling(float input[90][90], float output[5][5]){
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
        float scale = 1.0f;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                output[index++] = pool[i][j] * scale;
            }
        }
    }
}

void initialize_weights() {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            // 使用更小的初始化范围
            fc_weights[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.01f;
        }
        fc_biases[i] = 0.01f; // 初始化偏置为0
    }
}

void fully_connected_layer(float input[300], float output[64]) {
    for (int i = 0; i < 64; i++) {
        float sum = 0.0f;
        for (int j = 0; j < 300; j++) {
            sum += fc_weights[i][j] * input[j];
        }
        sum += fc_biases[i];
        float alpha = 0.05f; // 可以调节，通常 0.01~0.1
        output[i] = (sum > 0) ? sum : alpha * sum;
    }
}

// 3. 改进权重更新函数，添加梯度裁剪
void improved_weight_update(float network_output[64], int true_label, float flattened_input[300]) {
    printf("Updating weights for digit %d...\n", true_label);

    int zero_count = 0;
    for (int i = 0; i < 300; i++) {
        if (fabs(flattened_input[i]) < 1e-8f) zero_count++;
    }
    printf("Zero features in input: %d/300\n", zero_count);
    if (zero_count == 300) {
        printf("Warning: All input features are zero, skipping weight update\n");
        return;
    }

    float target[64];
    for (int i = 0; i < 64; i++) {
        int start_neuron = true_label * 6;
        if (i >= start_neuron && i < start_neuron + 6) target[i] = 1.0f;
        else target[i] = 0.0f;
    }

    int updated_weights = 0;
    for (int neuron = 0; neuron < 64; neuron++) {
        float error = target[neuron] - network_output[neuron];
        
        // 梯度裁剪，防止梯度爆炸
        if (error > 1.0f) error = 1.0f;
        if (error < -1.0f) error = -1.0f;
        
        if (fabs(error) > 0.001f) { // 降低更新阈值
            for (int input_idx = 0; input_idx < 300; input_idx++) {
                if (fabs(flattened_input[input_idx]) > 1e-8f) {
                    float gradient = error * flattened_input[input_idx];
                    
                    // 对梯度进行裁剪
                    if (gradient > 10.0f) gradient = 10.0f;
                    if (gradient < -10.0f) gradient = -10.0f;
                    
                    fc_weights[neuron][input_idx] += learning_rate * gradient;
                    updated_weights++;
                }
            }
            // 对偏置的梯度也进行裁剪
            float bias_gradient = error;
            if (bias_gradient > 1.0f) bias_gradient = 1.0f;
            if (bias_gradient < -1.0f) bias_gradient = -1.0f;
            
            fc_biases[neuron] += learning_rate * bias_gradient;
        }
    }
    printf("Updated %d weight connections\n", updated_weights);
}

void save_weights(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return;
    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            fprintf(file, "%.8f ", fc_weights[i][j]);
        }
        fprintf(file, "\n");
    }
    for (int i = 0; i < 64; i++) {
        fprintf(file, "%.8f ", fc_biases[i]);
    }
    fprintf(file, "\n");
    fclose(file);
    printf("Weights saved to %s\n", filename);
}

void load_weights(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s for reading\n", filename);
        return;
    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 300; j++) {
            if (fscanf(file, "%f", &fc_weights[i][j]) != 1) {
                printf("Error reading weights from file\n");
                fclose(file);
                return;
            }
        }
    }
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

// 训练一个样本（只更新 FC 层）
void train_digit_sample(int digit) {
    printf("\n=== Training digit %d ===\n", digit);
    // 检查输入范围
    float min_val = input_matrix[0][0], max_val = input_matrix[0][0];
    for (int i = 0; i < 96; i++) for (int j = 0; j < 96; j++) {
        if (input_matrix[i][j] < min_val) min_val = input_matrix[i][j];
        if (input_matrix[i][j] > max_val) max_val = input_matrix[i][j];
    }
    printf("Input range: min=%.4f, max=%.4f\n", min_val, max_val);

    // 前向
    init_convolution();
    debug_convolution_output();
    init_pooling();
    float flattened_matrix[300];
    flatten_matrix(flattened_matrix);
    debug_flattened_features(flattened_matrix);

    debug_fc_layer(flattened_matrix);
    float output_vector[64];
    fully_connected_layer(flattened_matrix, output_vector);

    printf("Current output (before update) for digit %d:\n", digit);
    int non_zero_count = 0;
    for (int i = 0; i < 64; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%.6f ", output_vector[i]);
        if (output_vector[i] > 1e-8f) non_zero_count++;
    }
    printf("\nNon-zero outputs: %d/64\n", non_zero_count);

    // 更新权重（仅 FC）
    improved_weight_update(output_vector, digit, flattened_matrix);

    // 用更新后的权重重新计算并显示
    fully_connected_layer(flattened_matrix, output_vector);
    printf("After weight update - sample output:\n");
    non_zero_count = 0;
    for (int i = 0; i < 64; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%.6f ", output_vector[i]);
        if (output_vector[i] > 1e-8f) non_zero_count++;
    }
    printf("\nNon-zero outputs after update: %d/64\n", non_zero_count);

    printf("Digit %d training completed\n", digit);
}

// 推理：用 FC 输出按每个数字 6 个神经元取平均选最大
int infer_digit() {
    printf("\n=== Inference Mode ===\n");
    init_convolution();
    init_pooling();
    float flattened_matrix[300];
    flatten_matrix(flattened_matrix);

    float output_vector[64];
    fully_connected_layer(flattened_matrix, output_vector);

    printf("Current output vector:\n");
    for (int i = 0; i < 64; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%.3f ", output_vector[i]);
    }
    printf("\n");

    int best_digit = -1;
    float best_score = -INFINITY;
    for (int digit = 0; digit < 10; digit++) {
        int start_neuron = digit * 6;
        float sum = 0.0f;
        int count = 0;
        for (int i = start_neuron; i < start_neuron + 6 && i < 64; i++) {
            sum += output_vector[i];
            count++;
        }
        float avg = (count > 0) ? sum / count : 0.0f;
        printf("Digit %d average output: %.6f\n", digit, avg);
        if (avg > best_score) {
            best_score = avg;
            best_digit = digit;
        }
    }

    if (best_digit >= 0) {
        printf("Predicted digit: %d (score %.6f)\n", best_digit, best_score);
        return best_digit;
    } else {
        printf("No valid prediction, returning 0\n");
        return 0;
    }
}

// 在文件顶部添加新的函数声明
int load_training_data_from_file(const char* filename, int digit);

// 在 main 函数中添加新的菜单选项
int main() {
    srand(42);

    FILE* weight_file = fopen("model_weights.txt", "r");
    if (weight_file != NULL) {
        fclose(weight_file);
        load_weights("model_weights.txt");
        printf("Loaded existing weights.\n");
    } else {
        initialize_weights();
        printf("Initialized new weights.\n");
    }

    while (1) {
        int mode;
        printf("\nChoose mode:\n");
        printf("1. Train a digit (manual input)\n");
        printf("2. Train from file (digit_0.txt to digit_9.txt)\n");
        printf("3. Test/Predict a digit (manual input)\n");
        printf("4. Test/Predict from file\n");
        printf("5. Exit and save\n");
        printf("Enter your choice: ");
        if (scanf("%d", &mode) != 1) {
            // 清理错误输入
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        if (mode == 5) break;

        if (mode == 1) {
            // 原有的手动输入训练代码
            int train_digit;
            printf("Enter the digit you want to train (0-9): ");
            if (scanf("%d", &train_digit) != 1) { int c; while ((c=getchar())!= '\n' && c!=EOF){} continue; }
            if (train_digit >= 0 && train_digit <= 9) {
                printf("Please input 96x96 matrix for digit %d (row-major floats):\n", train_digit);
                for (int i = 0; i < 96; i++) {
                    for (int j = 0; j < 96; j++) {
                        if (scanf("%f", &input_matrix[i][j]) != 1) {
                            // 如果输入不足，提前退出输入循环，清空 stdin
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF) {}
                            printf("Input aborted or invalid number detected.\n");
                            goto after_input_train;
                        }
                    }
                }
                train_digit_sample(train_digit);
            } else {
                printf("Invalid digit!\n");
            }
            after_input_train: ;
        }
        else if (mode == 2) {
            // 从文件批量训练
            printf("Training from files digit_0.txt to digit_9.txt...\n");
            int trained_count = 0;
            for (int digit = 0; digit < 10; digit++) {
                char filename[20];
                sprintf(filename, "digit_%d.txt", digit);
                if (load_training_data_from_file(filename, digit)) {
                    trained_count++;
                }
            }
            printf("Training completed. %d digits trained from files.\n", trained_count);
        }
        else if (mode == 3) {
            // 原有的手动测试代码
            printf("Please input 96x96 matrix for recognition (row-major floats):\n");
            int bad = 0;
            for (int i = 0; i < 96; i++) {
                for (int j = 0; j < 96; j++) {
                    if (scanf("%f", &input_matrix[i][j]) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) {}
                        printf("Input aborted or invalid number detected.\n");
                        bad = 1;
                        break;
                    }
                }
                if (bad) break;
            }
            if (bad) continue;

            int predicted_digit = infer_digit();
            printf("Final prediction: %d\n", predicted_digit);

            int correction;
            printf("Is this correct? (1=yes, 0=no): ");
            if (scanf("%d", &correction) != 1) { int c; while((c=getchar())!= '\n' && c!=EOF){} continue; }
            if (correction == 0) {
                int real_digit;
                printf("Please enter the real digit: ");
                if (scanf("%d", &real_digit) != 1) { int c; while((c=getchar())!= '\n' && c!=EOF){} continue; }
                if (real_digit >= 0 && real_digit <= 9) {
                    train_digit_sample(real_digit);
                    printf("Model corrected with the real digit %d\n", real_digit);
                } else {
                    printf("Invalid digit!\n");
                }
            }
        }
        else if (mode == 4) {
            // 从文件测试
            int test_digit;
            printf("Enter the digit you want to test (0-9): ");
            if (scanf("%d", &test_digit) != 1) { 
                int c; 
                while ((c=getchar())!= '\n' && c!=EOF){} 
                continue; 
            }
            if (test_digit >= 0 && test_digit <= 9) {
                char filename[20];
                sprintf(filename, "digit_%d.txt", test_digit);
                
                if (load_training_data_from_file(filename, -1)) { // -1表示仅测试不训练
                    int predicted_digit = infer_digit();
                    printf("Prediction for %s: %d\n", filename, predicted_digit);
                    if (predicted_digit == test_digit) {
                        printf("Correct prediction!\n");
                    } else {
                        printf("Wrong prediction. Expected: %d\n", test_digit);
                    }
                }
            } else {
                printf("Invalid digit!\n");
            }
        }
        else {
            printf("Unknown mode. Choose 1, 2, 3, 4 or 5.\n");
        }
    }

    save_weights("model_weights.txt");
    printf("Weights saved. Goodbye!\n");
    return 0;
}

// 添加从文件加载训练数据的函数
int load_training_data_from_file(const char* filename, int digit) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return 0;
    }

    // 读取96x96矩阵数据
    for (int i = 0; i < 96; i++) {
        for (int j = 0; j < 96; j++) {
            if (fscanf(file, "%f", &input_matrix[i][j]) != 1) {
                printf("Error reading data from %s at position (%d,%d)\n", filename, i, j);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    
    // 如果digit为-1，表示只测试不训练
    if (digit == -1) {
        return 1;
    }
    
    // 训练该数字
    printf("Training digit %d from file %s...\n", digit, filename);
    train_digit_sample(digit);
    return 1;
}