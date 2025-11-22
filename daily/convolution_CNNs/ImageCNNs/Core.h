#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

extern int ****maxpool_index;

// ===== 结构体 =====

typedef struct convolution_core {
    int size;
    int input_channels;
    int output_channels;
    int padding;
    int stride;
    float learning_rate;
} convolution_core;

typedef struct convolution_core_with_weights {
    int size;
    int input_channels;
    int output_channels;
    int padding;
    int stride;
    float learning_rate;

    float ****weights;
    float *biases;
} convolution_core_with_weights;

typedef struct fully_connected_layer {
    int input_size;
    int output_size;
    float learning_rate;

    float **weights;
    float *biases;
} fully_connected_layer;


// ===== 函数声明 =====

convolution_core convolution_init(
    int size, int input_channels, int output_channels,
    int padding, int stride, float learning_rate
);

convolution_core_with_weights convolution_init_with_weights(
    int size, int input_channels, int output_channels,
    int padding, int stride, float learning_rate
);

fully_connected_layer init_fc_layer_with_weights(
    int input_size, int output_size, float learning_rate
);

float*** conv_forward(convolution_core_with_weights *conv, float ***input,
                      int input_height, int input_width, int relu_mode);

float*** max_pooling_with_index(float ***input, int channels,
                                int input_h, int input_w,
                                int pool_size, int stride);

float*** max_pooling_backward(float ***grad_out,
                              int channels,
                              int input_h, int input_w,
                              int out_h, int out_w);

float* flatten(float ***input, int channels, int height, int width);
float*** unflatten_1d_to_3d(float *input, int channels, int height, int width);

float* fc_forward(fully_connected_layer *fc, float *input);

// ⭐ 修改：返回输入梯度
float* fc_backward(fully_connected_layer *fc, float *input, float *output_gradient);

void fc_backward_relu(fully_connected_layer *fc, float *input,
                      float *output, float *output_gradient);

void conv_backward(convolution_core_with_weights *conv, float ***input,
                   float ***output_gradient, int input_height, int input_width);

void conv_backward_relu(convolution_core_with_weights *conv, float ***input,
                        float ***output, float ***output_gradient,
                        int input_height, int input_width);

void softmax(float *input, float *output, int size);

float mse_loss(float *output, float *target, int size);
float* mse_loss_gradient(float *output, float *target, int size);

float cross_entropy_loss(float *output, float *target, int size);
float* cross_entropy_gradient_softmax(float *output, float *target, int size);

#endif