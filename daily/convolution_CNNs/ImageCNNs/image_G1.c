#include <stdio.h>
#include <stdlib.h>
#include "Core.h"
#include "image_loader.h"
#include "dataset_loader.h"
#include "save_load.h"
#include "time.h"

int main() {
    system("chcp 65001 > nul");
    srand(time(NULL));  // ⭐ 添加随机种子

    printf("选择模式:\n");
    printf("1 = 训练猫狗模型\n");
    printf("2 = 预测图片\n");
    int mode;
    scanf("%d", &mode);

    if (mode == 1) {
        // ⭐ 增加卷积核数量和调高学习率
        convolution_core_with_weights conv = 
            convolution_init_with_weights(3, 1, 32, 1, 1, 0.001);  // 4->32核，lr提高到0.001

        fully_connected_layer fc = 
            init_fc_layer_with_weights(32 * 32 * 32, 2, 0.001);  // 输入变大，lr提高

        Dataset ds = load_dataset("./cats", "./dogs");
        
        // ⭐ 打乱数据集
        for (int i = ds.count - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            // 交换paths
            char *temp_path = ds.paths[i];
            ds.paths[i] = ds.paths[j];
            ds.paths[j] = temp_path;
            // 交换labels
            int temp_label = ds.labels[i];
            ds.labels[i] = ds.labels[j];
            ds.labels[j] = temp_label;
        }
        
        printf("数据集已打乱，开始训练\n");

        for (int epoch = 0; epoch < 20; epoch++) {  // ⭐ 增加到20个epoch
            float total_loss = 0;
            int correct = 0;
            int processed = 0;

            for (int i = 0; i < ds.count; i++) {
                
                float **img = load_image_64(ds.paths[i]);
                if (img == NULL) continue;

                float ***img3d = malloc(sizeof(float**));
                img3d[0] = img;

                float ***c1 = conv_forward(&conv, img3d, 64, 64, 1);
                float ***p1 = max_pooling_with_index(c1, 32, 64, 64, 2, 2);  // ⭐ 通道数改为32
                float *flat = flatten(p1, 32, 32, 32);
                float *fc_out = fc_forward(&fc, flat);

                float prob[2];
                softmax(fc_out, prob, 2);

                int label = ds.labels[i];
                int predicted = (prob[1] > prob[0]) ? 1 : 0;
                if (predicted == label) correct++;

                float target[2] = {0, 0};
                target[label] = 1;

                float loss = cross_entropy_loss(prob, target, 2);
                total_loss += loss;
                processed++;

                float *grad_fc = cross_entropy_gradient_softmax(prob, target, 2);
                float *grad_flat = fc_backward(&fc, flat, grad_fc);
                float ***grad3d = unflatten_1d_to_3d(grad_flat, 32, 32, 32);
                float ***grad_pool = max_pooling_backward(grad3d, 32, 64, 64, 32, 32);
                conv_backward(&conv, img3d, grad_pool, 64, 64);

                // 每100张图片打印一次
                if (i % 100 == 0 && i > 0) {
                    printf("[Epoch %d | %d/%d] Loss: %.4f | 准确率: %.2f%%\n",
                           epoch, i, ds.count, total_loss/processed, 
                           (float)correct/processed*100);
                }

                // 释放内存
                free(grad_fc);
                free(grad_flat);
                free(flat);
                free(fc_out);
                
                for (int c = 0; c < 32; c++) {
                    for (int h = 0; h < 32; h++) free(grad3d[c][h]);
                    free(grad3d[c]);
                }
                free(grad3d);
                
                for (int c = 0; c < 32; c++) {
                    for (int h = 0; h < 64; h++) free(grad_pool[c][h]);
                    free(grad_pool[c]);
                }
                free(grad_pool);
                
                for (int c = 0; c < 32; c++) {
                    for (int h = 0; h < 32; h++) free(p1[c][h]);
                    free(p1[c]);
                }
                free(p1);
                
                for (int c = 0; c < 32; c++) {
                    for (int h = 0; h < 64; h++) free(c1[c][h]);
                    free(c1[c]);
                }
                free(c1);
                
                for (int h = 0; h < 64; h++) free(img[h]);
                free(img);
                free(img3d);
            }

            float accuracy = (float)correct / processed * 100;
            printf("\n========== Epoch %d 完成 ==========\n", epoch);
            printf("平均损失: %.4f | 准确率: %.2f%%\n", total_loss/processed, accuracy);
            
            save_model(&fc, &conv);
            
            // ⭐ 如果准确率超过70%就可以停止了
            if (accuracy > 70.0) {
                printf("✅ 达到目标准确率，训练完成！\n");
                break;
            }
        }
    }

    else if (mode == 2) {
        // ⭐ 注意：要和训练时的参数一致！
        convolution_core_with_weights conv = 
            convolution_init_with_weights(3, 1, 32, 1, 1, 0.001);

        fully_connected_layer fc = 
            init_fc_layer_with_weights(32 * 32 * 32, 2, 0.001);
        
        load_model(&fc, &conv);

        printf("输入图片路径: ");
        char path[256];
        scanf("%s", path);

        float **img = load_image_64(path);
        if (img == NULL) {
            printf("无法加载图片\n");
            return -1;
        }

        float ***img3d = malloc(sizeof(float**));
        img3d[0] = img;

        float ***c1 = conv_forward(&conv, img3d, 64, 64, 1);
        float ***p1 = max_pooling_with_index(c1, 32, 64, 64, 2, 2);
        float *flat = flatten(p1, 32, 32, 32);
        float *fc_out = fc_forward(&fc, flat);

        float prob[2];
        softmax(fc_out, prob, 2);

        printf("\n========== 预测结果 ==========\n");
        printf("猫的概率: %.2f%%\n", prob[0] * 100);
        printf("狗的概率: %.2f%%\n", prob[1] * 100);
        printf("最终判断: %s (置信度: %.2f%%)\n", 
               prob[1] > prob[0] ? "🐕 狗" : "🐱 猫",
               fmax(prob[0], prob[1]) * 100);
        
        // 释放内存...
        free(flat);
        free(fc_out);
        for (int c = 0; c < 32; c++) {
            for (int h = 0; h < 32; h++) free(p1[c][h]);
            free(p1[c]);
        }
        free(p1);
        for (int c = 0; c < 32; c++) {
            for (int h = 0; h < 64; h++) free(c1[c][h]);
            free(c1[c]);
        }
        free(c1);
        for (int h = 0; h < 64; h++) free(img[h]);
        free(img);
        free(img3d);
    }

    return 0;
}