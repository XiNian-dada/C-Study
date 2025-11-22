#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "Core.h"

int ****maxpool_index;  // 全局记录索引

// 带权重的初始化函数
convolution_core_with_weights convolution_init_with_weights(int size, int input_channels, 
                                                           int output_channels, int padding, 
                                                           int stride, float learning_rate) {
    convolution_core_with_weights core;
    core.size = size;
    core.input_channels = input_channels;
    core.output_channels = output_channels;
    core.padding = padding;
    core.stride = stride;
    core.learning_rate = learning_rate;
    
    printf("正在分配权重内存...\n");
    printf("权重数组形状: [%d][%d][%d][%d]\n", 
           output_channels, input_channels, size, size);
    
    core.weights = (float****)malloc(output_channels * sizeof(float***));
    for (int o = 0; o < output_channels; o++) {
        core.weights[o] = (float***)malloc(input_channels * sizeof(float**));
        for (int i = 0; i < input_channels; i++) {
            core.weights[o][i] = (float**)malloc(size * sizeof(float*));
            for (int h = 0; h < size; h++) {
                core.weights[o][i][h] = (float*)malloc(size * sizeof(float));
                
                // He初始化
                float std = sqrtf(2.0f / (input_channels * size * size));
                for (int w = 0; w < size; w++) {
                    core.weights[o][i][h][w] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f * std;
                }
            }
        }
    }
    
    core.biases = (float*)malloc(output_channels * sizeof(float));
    for (int o = 0; o < output_channels; o++) {
        core.biases[o] = 0.0f;
    }
    
    printf("权重分配完成！\n");
    return core;
}

fully_connected_layer init_fc_layer_with_weights(int input_size, int output_size, float learning_rate) {
    fully_connected_layer layer;
    layer.input_size = input_size;
    layer.output_size = output_size;
    layer.learning_rate = learning_rate;

    printf("正在分配全连接层权重内存...\n");
    printf("权重矩阵形状: [%d][%d]\n", output_size, input_size);
    
    layer.weights = (float **)malloc(output_size * sizeof(float *));
    
    // Xavier初始化
    float std = sqrtf(2.0f / (input_size + output_size));
    
    for(int o = 0; o < output_size; o++){
        layer.weights[o] = (float *)malloc(input_size * sizeof(float));
        for(int i = 0; i < input_size; i++){
            layer.weights[o][i] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f * std;
        }
    }
    
    printf("权重分配完成！\n");
    printf("正在分配偏置内存...\n");
    layer.biases = (float *)malloc(output_size * sizeof(float));
    for(int o = 0; o < output_size; o++){
        layer.biases[o] = 0.0f;
    }
    printf("偏置分配完成！\n");
    
    return layer;
}

int compute_output_size(int input_size, int kernel_size, int stride, int padding) {
    return (input_size - kernel_size + 2 * padding) / stride + 1;
}

float*** conv_forward(convolution_core_with_weights *conv, float ***input, 
                     int input_height, int input_width, int relu_mode) {
    
    int output_height = compute_output_size(input_height, conv->size, conv->stride, conv->padding);
    int output_width = compute_output_size(input_width, conv->size, conv->stride, conv->padding);
    
    printf("卷积输入: [%d][%d][%d]\n", conv->input_channels, input_height, input_width);
    printf("卷积输出: [%d][%d][%d]\n", conv->output_channels, output_height, output_width);
    
    float ***output = (float***)malloc(conv->output_channels * sizeof(float**));
    for (int o = 0; o < conv->output_channels; o++) {
        output[o] = (float**)malloc(output_height * sizeof(float*));
        for (int h = 0; h < output_height; h++) {
            output[o][h] = (float*)calloc(output_width, sizeof(float));
        }
    }
    
    for (int oc = 0; oc < conv->output_channels; oc++) {
        for (int oh = 0; oh < output_height; oh++) {
            for (int ow = 0; ow < output_width; ow++) {
                float sum = 0.0f;
                
                int start_h = oh * conv->stride - conv->padding;
                int start_w = ow * conv->stride - conv->padding;
                
                for (int ic = 0; ic < conv->input_channels; ic++) {
                    for (int kh = 0; kh < conv->size; kh++) {
                        for (int kw = 0; kw < conv->size; kw++) {
                            int input_h = start_h + kh;
                            int input_w = start_w + kw;
                            
                            if (input_h >= 0 && input_h < input_height && 
                                input_w >= 0 && input_w < input_width) {
                                sum += input[ic][input_h][input_w] * 
                                       conv->weights[oc][ic][kh][kw];
                            }
                        }
                    }
                }
                
                if(relu_mode == 1){
                    output[oc][oh][ow] = fmaxf(0.0f, sum + conv->biases[oc]);
                }else{
                    output[oc][oh][ow] = sum + conv->biases[oc];
                }
            }
        }
    }
    
    return output;
}

float* fc_forward(fully_connected_layer *fc, float *input) {
    
    printf("全连接输入: [%d]\n", fc->input_size);
    printf("全连接输出: [%d]\n", fc->output_size);
    
    float *output = (float*)malloc(fc->output_size * sizeof(float));
    
    for (int i = 0; i < fc->output_size; i++) {
        float sum = 0.0f;
        for (int j = 0; j < fc->input_size; j++) {
            sum += input[j] * fc->weights[i][j];
        }
        output[i] = sum + fc->biases[i];
    }
    return output;
}

// ⭐⭐⭐ 关键修改：返回输入梯度
float* fc_backward(fully_connected_layer *fc, float *input, float *output_gradient) {
    printf("fc_backward 开始\n");
    
    // 分配输入梯度数组
    float *input_gradient = (float*)calloc(fc->input_size, sizeof(float));
    
    // 1. 计算权重的梯度并更新权重，同时计算输入梯度
    for (int i = 0; i < fc->output_size; i++) {
        for (int j = 0; j < fc->input_size; j++) {
            // 权重的梯度 = 输出梯度 * 输入值
            float weight_gradient = output_gradient[i] * input[j];
            
            // 梯度裁剪
            if (weight_gradient > 1.0f) weight_gradient = 1.0f;
            if (weight_gradient < -1.0f) weight_gradient = -1.0f;
            
            // 更新权重
            fc->weights[i][j] -= fc->learning_rate * weight_gradient;
            
            // ⭐ 计算输入梯度（用于反向传播到前一层）
            input_gradient[j] += output_gradient[i] * fc->weights[i][j];
        }
        
        // 2. 更新偏置
        float bias_gradient = output_gradient[i];
        if (bias_gradient > 1.0f) bias_gradient = 1.0f;
        if (bias_gradient < -1.0f) bias_gradient = -1.0f;
        fc->biases[i] -= fc->learning_rate * bias_gradient;
    }
    
    printf("fc_backward 完成\n");
    return input_gradient;  // ⭐ 返回输入梯度
}

void conv_backward(convolution_core_with_weights *conv, float ***input, 
                  float ***output_gradient, int input_height, int input_width) {
    
    int output_height = compute_output_size(input_height, conv->size, conv->stride, conv->padding);
    int output_width = compute_output_size(input_width, conv->size, conv->stride, conv->padding);
    
    printf("卷积反向传播...\n");
    
    for (int oc = 0; oc < conv->output_channels; oc++) {
        for (int ic = 0; ic < conv->input_channels; ic++) {
            for (int kh = 0; kh < conv->size; kh++) {
                for (int kw = 0; kw < conv->size; kw++) {
                    
                    float weight_gradient = 0.0f;
                    
                    for (int oh = 0; oh < output_height; oh++) {
                        for (int ow = 0; ow < output_width; ow++) {
                            int input_h = oh * conv->stride - conv->padding + kh;
                            int input_w = ow * conv->stride - conv->padding + kw;
                            
                            if (input_h >= 0 && input_h < input_height && 
                                input_w >= 0 && input_w < input_width) {
                                weight_gradient += output_gradient[oc][oh][ow] * 
                                                  input[ic][input_h][input_w];
                            }
                        }
                    }
                    
                    // 梯度裁剪
                    if (weight_gradient > 1.0f) weight_gradient = 1.0f;
                    if (weight_gradient < -1.0f) weight_gradient = -1.0f;
                    
                    if (!isnan(weight_gradient) && !isinf(weight_gradient)) {
                        conv->weights[oc][ic][kh][kw] -= conv->learning_rate * weight_gradient;
                    }
                }
            }
        }
        
        float bias_gradient = 0.0f;
        for (int oh = 0; oh < output_height; oh++) {
            for (int ow = 0; ow < output_width; ow++) {
                bias_gradient += output_gradient[oc][oh][ow];
            }
        }
        
        if (bias_gradient > 1.0f) bias_gradient = 1.0f;
        if (bias_gradient < -1.0f) bias_gradient = -1.0f;
        
        if (!isnan(bias_gradient) && !isinf(bias_gradient)) {
            conv->biases[oc] -= conv->learning_rate * bias_gradient;
        }
    }
}

float cross_entropy_loss(float *output, float *target, int size) {
    float loss = 0.0f;
    for (int i = 0; i < size; i++) {
        float y_pred = fmaxf(output[i], 1e-15f);
        loss += target[i] * logf(y_pred);
    }
    return -loss;
}

float* cross_entropy_gradient_softmax(float *output, float *target, int size) {
    float *gradient = (float*)malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        gradient[i] = output[i] - target[i];
    }
    return gradient;
}

float* flatten(float ***input, int channels, int height, int width) {
    int size = channels * height * width;
    float *output = (float*)malloc(size * sizeof(float));

    int idx = 0;
    for (int c = 0; c < channels; c++) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                output[idx++] = input[c][h][w];
            }
        }
    }
    return output;
}

float*** unflatten_1d_to_3d(float *input, int channels, int height, int width) {
    float ***output = (float***)malloc(channels * sizeof(float**));
    
    int index = 0;
    for (int c = 0; c < channels; c++) {
        output[c] = (float**)malloc(height * sizeof(float*));
        for (int h = 0; h < height; h++) {
            output[c][h] = (float*)malloc(width * sizeof(float));
            for (int w = 0; w < width; w++) {
                output[c][h][w] = input[index++];
            }
        }
    }
    return output;
}

float*** max_pooling_with_index(float ***input, int channels,
                                int input_h, int input_w,
                                int pool_size, int stride) {

    int out_h = (input_h - pool_size) / stride + 1;
    int out_w = (input_w - pool_size) / stride + 1;

    float ***output = (float***)malloc(channels * sizeof(float**));
    maxpool_index = (int****)malloc(channels * sizeof(int***));

    for (int c = 0; c < channels; c++) {
        output[c] = (float**)malloc(out_h * sizeof(float*));
        maxpool_index[c] = (int***)malloc(out_h * sizeof(int**));

        for (int oh = 0; oh < out_h; oh++) {
            output[c][oh] = (float*)malloc(out_w * sizeof(float));
            maxpool_index[c][oh] = (int**)malloc(out_w * sizeof(int*));

            for (int ow = 0; ow < out_w; ow++) {
                float max_val = -FLT_MAX;
                int max_h = 0, max_w = 0;

                int start_h = oh * stride;
                int start_w = ow * stride;

                for (int kh = 0; kh < pool_size; kh++) {
                    for (int kw = 0; kw < pool_size; kw++) {
                        int ih = start_h + kh;
                        int iw = start_w + kw;

                        if (input[c][ih][iw] > max_val) {
                            max_val = input[c][ih][iw];
                            max_h = ih;
                            max_w = iw;
                        }
                    }
                }

                output[c][oh][ow] = max_val;
                maxpool_index[c][oh][ow] = (int*)malloc(2*sizeof(int));
                maxpool_index[c][oh][ow][0] = max_h;
                maxpool_index[c][oh][ow][1] = max_w;
            }
        }
    }
    return output;
}

float*** max_pooling_backward(float ***grad_out,
                              int channels,
                              int input_h, int input_w,
                              int out_h, int out_w) {

    float ***grad_in = (float***)malloc(channels*sizeof(float**));

    for (int c = 0; c < channels; c++) {
        grad_in[c] = (float**)malloc(input_h*sizeof(float*));
        for (int h = 0; h < input_h; h++)
            grad_in[c][h] = (float*)calloc(input_w, sizeof(float));
    }

    for (int c = 0; c < channels; c++) {
        for (int oh = 0; oh < out_h; oh++) {
            for (int ow = 0; ow < out_w; ow++) {
                int mh = maxpool_index[c][oh][ow][0];
                int mw = maxpool_index[c][oh][ow][1];
                grad_in[c][mh][mw] += grad_out[c][oh][ow];
            }
        }
    }
    return grad_in;
}

void softmax(float *input, float *output, int size) {
    float maxv = -FLT_MAX;
    for (int i = 0; i < size; i++)
        if (input[i] > maxv) maxv = input[i];

    float sum = 0.0f;
    for (int i = 0; i < size; i++)
        sum += expf(input[i] - maxv);

    for (int i = 0; i < size; i++) {
        output[i] = expf(input[i] - maxv) / sum;
    }
}