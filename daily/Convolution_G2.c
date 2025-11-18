#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*
卷积 激活 LRN 池化
*/
float y_filter[3][3]={
    {-1,0.0,1},
    {-1,0.0,1},
    {-1,0.0,1}
};
float x_filter[3][3]={
    {1,1,1},
    {0.0,0.0,0.0},
    {-1,-1,-1}
};
float f_45_filter[3][3]={
    {-1,-1,0},
    {-1,0,1},
    {0,1,1}
};
float f_135_filter[3][3]={
    {0,1,1},
    {-1,0,1},
    {-1,-1,0}
};
float laplacian[3][3]={
    {0,1,0},
    {1,-4,1},
    {0,1,0}
};
float sobel_x[3][3]={
    {-1,0,1},
    {-2,0,2},
    {-1,0,1}
};
float sobel_y[3][3]={
    {-1,-2,-1},
    {0,0,0},
    {1,2,1}
};
float sharpen_filter[3][3]={
    {0,-1,0},
    {-1,5,-1},
    {0,-1,0}
};
float corner_filter[3][3]={
    {-1,-1,-1},
    {-1,8,-1},
    {-1,-1,-1}
};
float cross_filter[3][3]={
    {0,-1,0},
    {-1,4,-1},
    {0,-1,0}
};
float circle_filter[3][3]={
    {1,1,1},
    {1,1,1},
    {1,1,1}
};

void convolution(float input[18][18],float filter[3][3],float output[16][16]){
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            output[i][j]=0;
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    output[i][j]+=input[i+k][j+l]*filter[k][l];
                }
            }
        }
    }
}
//LRN FREE 其实是我不会
void active(float input[16][16]){
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            if(input[i][j]<0){
                input[i][j]=0;
            }
        }
    }
}
void pooling(float input[16][16],float output[8][8]){ 
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            float max = input[2*i][2*j];
            for(int k=0; k<2; k++) {
                for(int l=0; l<2; l++) {
                    if(input[2*i+k][2*j+l] > max) {
                        max = input[2*i+k][2*j+l];
                    }
                }
            }
            output[i][j] = max;
        }
    }
}
void scd_pooling(float input[8][8],float output[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            float max = input[2*i][2*j];
            for(int k=0; k<2; k++) {
                for(int l=0; l<2; l++) {
                    if(input[2*i+k][2*j+l] > max) {
                        max = input[2*i+k][2*j+l];
                    }
                }
            }
            output[i][j] = max;
        }
    }
}
void multiple2single(int start_pos,float input[4][4],float output[]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            output[start_pos++]=input[i][j];
        }
    }
}

// 计算特征向量的函数
void calculate_features(float input[18][18], float final_answer[178]) {
    float x_output[16][16];
    float y_output[16][16];
    float laplacian_output[16][16];
    float sobel_x_output[16][16];
    float sobel_y_output[16][16];
    float sharpen_output[16][16];
    float corner_output[16][16];
    float cross_output[16][16];
    float circle_output[16][16];
    float f_45_output[16][16];
    float f_135_output[16][16];
    
    convolution(input,x_filter,x_output);
    convolution(input,y_filter,y_output);
    convolution(input,laplacian,laplacian_output);
    convolution(input,sobel_x,sobel_x_output);
    convolution(input,sobel_y,sobel_y_output);
    convolution(input,sharpen_filter,sharpen_output);
    convolution(input,corner_filter,corner_output);
    convolution(input,cross_filter,cross_output);
    convolution(input,circle_filter,circle_output);
    convolution(input,f_45_filter,f_45_output);
    convolution(input,f_135_filter,f_135_output);
    active(x_output);
    active(y_output);
    active(laplacian_output);
    active(sobel_x_output);
    active(sobel_y_output);
    active(sharpen_output);
    active(corner_output);
    active(cross_output);
    active(circle_output);
    active(f_45_output);
    active(f_135_output);
    
    float x_pooling_output[8][8];
    float y_pooling_output[8][8];
    float laplacian_pooling_output[8][8];
    float sobel_x_pooling_output[8][8];
    float sobel_y_pooling_output[8][8];
    float sharpen_pooling_output[8][8];
    float corner_pooling_output[8][8];
    float cross_pooling_output[8][8];
    float circle_pooling_output[8][8];
    float f_45_pooling_output[8][8];
    float f_135_pooling_output[8][8];
    
    pooling(x_output,x_pooling_output);
    pooling(y_output,y_pooling_output);
    pooling(laplacian_output,laplacian_pooling_output);
    pooling(sobel_x_output,sobel_x_pooling_output);
    pooling(sobel_y_output,sobel_y_pooling_output);
    pooling(sharpen_output,sharpen_pooling_output);
    pooling(corner_output,corner_pooling_output);
    pooling(cross_output,cross_pooling_output);
    pooling(circle_output,circle_pooling_output);
    pooling(f_45_output,f_45_pooling_output);
    pooling(f_135_output,f_135_pooling_output);
    
    float x_scd_pooling_output[4][4];
    float y_scd_pooling_output[4][4];
    float laplacian_scd_pooling_output[4][4];
    float sobel_x_scd_pooling_output[4][4];
    float sobel_y_scd_pooling_output[4][4];
    float sharpen_scd_pooling_output[4][4];
    float corner_scd_pooling_output[4][4];
    float cross_scd_pooling_output[4][4];
    float circle_scd_pooling_output[4][4];
    float f_45_scd_pooling_output[4][4];
    float f_135_scd_pooling_output[4][4];

    scd_pooling(x_pooling_output,x_scd_pooling_output);
    scd_pooling(y_pooling_output,y_scd_pooling_output);
    scd_pooling(laplacian_pooling_output,laplacian_scd_pooling_output);
    scd_pooling(sobel_x_pooling_output,sobel_x_scd_pooling_output);
    scd_pooling(sobel_y_pooling_output,sobel_y_scd_pooling_output);
    scd_pooling(sharpen_pooling_output,sharpen_scd_pooling_output);
    scd_pooling(corner_pooling_output,corner_scd_pooling_output);
    scd_pooling(cross_pooling_output,cross_scd_pooling_output);
    scd_pooling(circle_pooling_output,circle_scd_pooling_output);
    scd_pooling(f_45_pooling_output,f_45_scd_pooling_output);
    scd_pooling(f_135_pooling_output,f_135_scd_pooling_output);

    //177参数
    multiple2single(0,x_scd_pooling_output,final_answer);
    multiple2single(16,y_scd_pooling_output,final_answer);
    multiple2single(32,laplacian_scd_pooling_output,final_answer);
    multiple2single(48,sobel_x_scd_pooling_output,final_answer);
    multiple2single(64,sobel_y_scd_pooling_output,final_answer);
    multiple2single(80,sharpen_scd_pooling_output,final_answer);
    multiple2single(96,corner_scd_pooling_output,final_answer);
    multiple2single(112,cross_scd_pooling_output,final_answer);
    multiple2single(128,circle_scd_pooling_output,final_answer);
    multiple2single(144,f_45_scd_pooling_output,final_answer);
    multiple2single(160,f_135_scd_pooling_output,final_answer);
}

int main(){
    int mode;
    printf("请选择模式: 1-训练模式 0-测试模式\n");
    scanf("%d", &mode);
    
    if(mode == 1) {
        // 训练模式
        FILE *fp = fopen("training_data.txt", "a");
        if(fp == NULL) {
            printf("无法创建或打开训练数据文件\n");
            return -1;
        }
        
        int continue_training = 1;
        while(continue_training) {
            float input[18][18];
            printf("请输入18*18的图像数据:\n");
            for(int i=0;i<18;i++){
                for(int j=0;j<18;j++){
                    scanf("%f",&input[i][j]);
                }
            }
            
            int input_number;
            printf("请输入对应的数字标签(0-9): ");
            scanf("%d", &input_number);
            
            // 计算特征向量
            float final_answer[178];
            calculate_features(input, final_answer);
            final_answer[176] = input_number;
            final_answer[177] = 1; // 训练标记
            
            // 写入文件
            for(int i=0; i<178; i++) {
                fprintf(fp, "%.2f ", final_answer[i]);
            }
            fprintf(fp, "\n");
            fflush(fp);
            
            printf("是否继续训练? 1-继续 0-结束: ");
            scanf("%d", &continue_training);
        }
        
        fclose(fp);
        printf("训练数据已保存到 training_data.txt 文件中\n");
    } 
    else {
        // 测试模式
        FILE *fp = fopen("training_data.txt", "r");
        if(fp == NULL) {
            printf("无法打开训练数据文件，请先进行训练\n");
            return -1;
        }
        
        int continue_testing = 1;
        while(continue_testing) {
            // 读取测试图像
            float input[18][18];
            printf("请输入18*18的测试图像数据:\n");
            for(int i=0;i<18;i++){
                for(int j=0;j<18;j++){
                    scanf("%f",&input[i][j]);
                }
            }
            
            // 计算当前输入的特征向量
            float test_features[178];
            calculate_features(input, test_features);
            
            // 为每个数字类别维护最小距离
            float min_distances[10];  // 0-9十个数字
            for(int i=0; i<10; i++) {
                min_distances[i] = 999999.0;  // 初始化为很大的数
            }
            
            // 读取训练数据并比较
            float train_data[178];
            int has_training_data = 0;
            
            // 回到文件开始
            fseek(fp, 0, SEEK_SET);
            
            // 遍历所有训练样本
            while(fscanf(fp, "%f", &train_data[0]) != EOF) {
                // 读取完整的一行数据（178个数）
                for(int i=1; i<178; i++) {
                    fscanf(fp, "%f", &train_data[i]);
                }
                
                has_training_data = 1;
                // 获取该训练样本的标签
                int label = (int)train_data[176];
                
                // 确保标签在有效范围内
                if(label >= 0 && label <= 9) {
                    // 计算与当前测试样本的欧氏距离
                    float distance = 0.0;
                    for(int i=0; i<176; i++) {
                        float diff = test_features[i] - train_data[i];
                        distance += diff * diff;
                    }
                    distance = sqrt(distance);
                    
                    // 如果这个样本与测试样本的距离小于该类别之前的最小距离，则更新
                    if(distance < min_distances[label]) {
                        min_distances[label] = distance;
                    }
                }
            }
            
            // 显示识别结果
            if(has_training_data) {
                // 找到距离最小的类别作为识别结果
                int recognized_digit = 0;
                float overall_min_distance = min_distances[0];
                for(int i=1; i<10; i++) {
                    if(min_distances[i] < overall_min_distance) {
                        overall_min_distance = min_distances[i];
                        recognized_digit = i;
                    }
                }
                
                
                
                // 显示所有数字类别的最小距离
                printf("各类别最小距离:\n");
                for(int i=0; i<10; i++) {
                    if(min_distances[i] < 999999.0) {  // 只显示有训练数据的类别
                        printf("数字 %d: %.2f\n", i, min_distances[i]);
                    }
                }
                printf("系统识别结果: 数字 %d (距离: %.2f)\n", recognized_digit, overall_min_distance);
            } else {
                printf("暂无训练数据\n");
            }
            
            // 询问用户实际数字
            int actual_digit;
            printf("请输入实际数字(0-9): ");
            scanf("%d", &actual_digit);
            
            // 将当前测试数据作为新的训练数据保存
            FILE *fp_append = fopen("training_data.txt", "a");
            if(fp_append != NULL) {
                test_features[176] = actual_digit;
                test_features[177] = 1;
                
                for(int i=0; i<178; i++) {
                    fprintf(fp_append, "%.2f ", test_features[i]);
                }
                fprintf(fp_append, "\n");
                fclose(fp_append);
                printf("已将该数据作为数字 %d 的样本添加到训练集中\n", actual_digit);
            }
            
            printf("是否继续测试? 1-继续 0-结束: ");
            scanf("%d", &continue_testing);
        }
        
        fclose(fp);
    }
    
    return 0;
}