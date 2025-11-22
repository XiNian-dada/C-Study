#include <stdlib.h>
#include <math.h>
#include <string.h>
// 在 convolution.h 文件开头添加函数声明
void convolution_3x3_flexible(float** input, float** output, float** kernel, int input_size, float act_multiply, float kernel_multiply);
void pooling_2x2_flexible(float** input, float** output, int input_size);
void pooling_3x3_flexible(float** input, float** output, int input_size);
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
void start_convolution(float** input, float** output, float** kernel, int input_size) {
    // 动态分配临时数组
    float** temp_1 = (float**)malloc((input_size-2) * sizeof(float*));
    for(int i = 0; i < input_size-2; i++) {
        temp_1[i] = (float*)malloc((input_size-2) * sizeof(float));
    }
    
    float** temp_2 = (float**)malloc((input_size-4) * sizeof(float*));
    for(int i = 0; i < input_size-4; i++) {
        temp_2[i] = (float*)malloc((input_size-4) * sizeof(float));
    }
    
    convolution_3x3_flexible(input, temp_1, kernel, input_size, 0.0f, 1.0f);
    convolution_3x3_flexible(temp_1, temp_2, kernel, input_size-2, 0.0f, 1.0f);
    convolution_3x3_flexible(temp_2, output, kernel, input_size-4, 0.0f, 1.0f);
    
    // 释放内存
    for(int i = 0; i < input_size-2; i++) {
        free(temp_1[i]);
    }
    free(temp_1);
    
    for(int i = 0; i < input_size-4; i++) {
        free(temp_2[i]);
    }
    free(temp_2);
}
void start_convolution_12kernels(float** input, float*** outputs, int input_size) {
    // 定义所有12个kernel
    float kernels[12][3][3] = {
        {{-1.0f, 0.0f, 1.0f}, {-2.0f, 0.0f, 2.0f}, {-1.0f, 0.0f, 1.0f}},     // kernel_1
        {{-1.0f, -2.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 2.0f, 1.0f}},      // kernel_2
        {{-2.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 2.0f}},      // kernel_3
        {{0.0f, -1.0f, -2.0f}, {1.0f, 0.0f, -1.0f}, {2.0f, 1.0f, 0.0f}},      // kernel_4
        {{0.0f, -1.0f, 0.0f}, {-1.0f, 4.0f, -1.0f}, {0.0f, -1.0f, 0.0f}},     // kernel_5
        {{-1.0f, -1.0f, -1.0f}, {-1.0f, 8.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}}, // kernel_6
        {{0.0f, -1.0f, 0.0f}, {-1.0f, 5.0f, -1.0f}, {0.0f, -1.0f, 0.0f}},     // kernel_7
        {{-1.0f, -1.0f, -1.0f}, {-1.0f, 9.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}}, // kernel_8
        {{1.0f, 2.0f, 1.0f}, {2.0f, 4.0f, 2.0f}, {1.0f, 2.0f, 1.0f}},         // kernel_9
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},         // kernel_10
        {{-2.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 2.0f}},      // kernel_11
        {{0.0f, 1.0f, 0.0f}, {1.0f, -4.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}         // kernel_12
    };

    // 动态分配临时数组
    float** temp_1 = (float**)malloc((input_size-2) * sizeof(float*));
    for(int i = 0; i < input_size-2; i++) {
        temp_1[i] = (float*)malloc((input_size-2) * sizeof(float));
    }
    
    float** temp_2 = (float**)malloc((input_size-4) * sizeof(float*));
    for(int i = 0; i < input_size-4; i++) {
        temp_2[i] = (float*)malloc((input_size-4) * sizeof(float));
    }
    
    // 为每个kernel计算三层卷积
    for(int k = 0; k < 12; k++) {
        // 将3x3数组转换为指针数组
        float* kernel_array[3];
        for(int i = 0; i < 3; i++) {
            kernel_array[i] = kernels[k][i];
        }
        
        convolution_3x3_flexible(input, temp_1, (float**)kernel_array, input_size, 0.0f, 1.0f);
        convolution_3x3_flexible(temp_1, temp_2, (float**)kernel_array, input_size-2, 0.0f, 1.0f);
        convolution_3x3_flexible(temp_2, outputs[k], (float**)kernel_array, input_size-4, 0.0f, 1.0f);
    }
    
    // 释放临时数组内存
    for(int i = 0; i < input_size-2; i++) {
        free(temp_1[i]);
    }
    free(temp_1);
    
    for(int i = 0; i < input_size-4; i++) {
        free(temp_2[i]);
    }
    free(temp_2);
}
void convolution_3x3_flexible(float** input, float** output, float** kernel, int input_size, float act_multiply, float kernel_multiply) {
    int output_size = input_size - 2;
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj] * kernel_multiply;
                }
            }
            float alpha = act_multiply;
            output[i][j] = (sum > 0) ? sum : alpha * sum;
        }
    }
}
void pooling_3x3_flexible(float** input, float** output, int input_size) {
    int output_size = input_size / 3;
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
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
void pooling_2x2_flexible(float** input, float** output, int input_size) {
    int output_size = input_size / 2;
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
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
void multi_pooling_3d(float*** input, float*** output, int channels, int input_size, int pool_size) {
    // 根据池化核大小选择相应的池化函数
    if (pool_size == 2) {
        for (int c = 0; c < channels; c++) {
            pooling_2x2_flexible(input[c], output[c], input_size);
        }
    } else if (pool_size == 3) {
        for (int c = 0; c < channels; c++) {
            pooling_3x3_flexible(input[c], output[c], input_size);
        }
    }
}

// 更通用的多轮池化函数
void multi_stage_pooling(float*** input, float*** final_output, int channels, int initial_size) {
    // 第一次池化: 90x90 -> 45x45 (2x2池化)
    float*** temp_output1 = (float***)malloc(channels * sizeof(float**));
    for (int c = 0; c < channels; c++) {
        temp_output1[c] = (float**)malloc(45 * sizeof(float*));
        for (int i = 0; i < 45; i++) {
            temp_output1[c][i] = (float*)malloc(45 * sizeof(float));
        }
    }
    
    multi_pooling_3d(input, temp_output1, channels, initial_size, 2);
    
    // 第二次池化: 45x45 -> 22x22 (2x2池化，向下取整)
    float*** temp_output2 = (float***)malloc(channels * sizeof(float**));
    for (int c = 0; c < channels; c++) {
        temp_output2[c] = (float**)malloc(22 * sizeof(float*));
        for (int i = 0; i < 22; i++) {
            temp_output2[c][i] = (float*)malloc(22 * sizeof(float));
        }
    }
    
    multi_pooling_3d(temp_output1, temp_output2, channels, 45, 2);
    
    // 将最终结果复制到输出数组
    for (int c = 0; c < channels; c++) {
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 22; j++) {
                final_output[c][i][j] = temp_output2[c][i][j];
            }
        }
    }
    
    // 释放临时内存
    for (int c = 0; c < channels; c++) {
        for (int i = 0; i < 45; i++) {
            free(temp_output1[c][i]);
        }
        free(temp_output1[c]);
    }
    free(temp_output1);
    
    for (int c = 0; c < channels; c++) {
        for (int i = 0; i < 22; i++) {
            free(temp_output2[c][i]);
        }
        free(temp_output2[c]);
    }
    free(temp_output2);
}

void init_fc_weights(float** fcweights, float* fcbiases, int neurons, int inputs) {
    for (int i = 0; i < neurons; i++) {
        for (int j = 0; j < inputs; j++) {
            fcweights[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.01f;
        }
        fcbiases[i] = 0.01f;
    }
}