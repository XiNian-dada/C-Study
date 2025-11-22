#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <stdio.h>
#include "Core.h"

void save_model(fully_connected_layer *fc, convolution_core_with_weights *conv) {

    FILE *f = fopen("model.bin", "wb");
    if (!f) {
        printf("无法创建模型文件 model.bin\n");
        return;
    }

    // 保存卷积核
    for (int oc=0; oc<conv->output_channels; oc++)
        for (int ic=0; ic<conv->input_channels; ic++)
            for (int h=0; h<conv->size; h++)
                fwrite(conv->weights[oc][ic][h], sizeof(float), conv->size, f);

    fwrite(conv->biases, sizeof(float), conv->output_channels, f);

    // 保存 FC
    for (int o=0; o<fc->output_size; o++)
        fwrite(fc->weights[o], sizeof(float), fc->input_size, f);

    fwrite(fc->biases, sizeof(float), fc->output_size, f);

    fclose(f);
    printf("模型保存成功\n");
}

void load_model(fully_connected_layer *fc, convolution_core_with_weights *conv) {
    FILE *f = fopen("model.bin", "rb");
    if (!f) {
        printf("❌ 找不到 model.bin，请先训练模型！\n");
        exit(1);  // ⭐ 强制退出
    }

    // 检查文件大小
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    printf("模型文件大小: %ld 字节\n", file_size);
    
    // 计算预期大小
    long expected_size = 0;
    // 卷积层权重
    expected_size += conv->output_channels * conv->input_channels * conv->size * conv->size * sizeof(float);
    // 卷积层偏置
    expected_size += conv->output_channels * sizeof(float);
    // 全连接层权重
    expected_size += fc->output_size * fc->input_size * sizeof(float);
    // 全连接层偏置
    expected_size += fc->output_size * sizeof(float);
    
    printf("预期文件大小: %ld 字节\n", expected_size);
    
    if (file_size != expected_size) {
        printf("❌ 模型文件大小不匹配，可能已损坏！\n");
        fclose(f);
        exit(1);
    }

    // 加载卷积层
    size_t read_count;
    for (int oc=0; oc<conv->output_channels; oc++) {
        for (int ic=0; ic<conv->input_channels; ic++) {
            for (int h=0; h<conv->size; h++) {
                read_count = fread(conv->weights[oc][ic][h], sizeof(float), conv->size, f);
                if (read_count != conv->size) {
                    printf("❌ 读取卷积权重失败\n");
                    fclose(f);
                    exit(1);
                }
            }
        }
    }

    read_count = fread(conv->biases, sizeof(float), conv->output_channels, f);
    if (read_count != conv->output_channels) {
        printf("❌ 读取卷积偏置失败\n");
        fclose(f);
        exit(1);
    }

    // 加载全连接层
    for (int o=0; o<fc->output_size; o++) {
        read_count = fread(fc->weights[o], sizeof(float), fc->input_size, f);
        if (read_count != fc->input_size) {
            printf("❌ 读取全连接权重失败\n");
            fclose(f);
            exit(1);
        }
    }

    read_count = fread(fc->biases, sizeof(float), fc->output_size, f);
    if (read_count != fc->output_size) {
        printf("❌ 读取全连接偏置失败\n");
        fclose(f);
        exit(1);
    }

    fclose(f);
    printf("✅ 模型加载成功！\n");
}

#endif