#include "stdio.h"
#include "math.h"
char a[8][8];
double process_1[8][8];
double result_x[6][6];
double result_y[6][6];
double result_xy[6][6];
double result_sharpen[6][6];
double result_sobel_x[6][6];
double result_sobel_y[6][6];
double result_laplacian[6][6];
double result_gaussian[6][6];
double result_diag45[6][6];
double result_diag_neg45[6][6];

double result_circle[6][6];
double result_cross[6][6];
double result_corner[6][6];

//分别是speciala avg;corner;cross;circle;
/* 
0:The special avg is-6.666667
The corner_feature is-20.000000
The cross_feature is0.000000
The circle_feature is 0.000000

1:
The special avg is5.495238
The corner_feature is6.000000
The cross_feature is3.485714
The circle_feature is 7.000000
2:
The special avg is-2.977778
The corner_feature is-10.333333
The cross_feature is3.400000
The circle_feature is -2.000000
3:
The special avg is-2.977778
The corner_feature is-10.333333
The cross_feature is3.400000
The circle_feature is -2.000000
4:
The special avg is-1.033333
The corner_feature is-3.500000
The cross_feature is3.400000
The circle_feature is -3.000000
5:
The special avg is-2.977778
The corner_feature is-10.333333
The cross_feature is3.400000
The circle_feature is -2.000000
6:
The special avg is-4.033333
The corner_feature is-12.500000
The cross_feature is3.400000
The circle_feature is -3.000000
7:
The special avg is3.400000
The corner_feature is-3.000000
The cross_feature is1.200000
The circle_feature is 12.000000

8:
The special avg is-5.088889
The corner_feature is-14.666667
The cross_feature is3.400000
The circle_feature is -4.000000
9:
The special avg is-4.033333
The corner_feature is-12.500000
The cross_feature is3.400000
The circle_feature is -3.000000
*/
//
int cpr(double result){
    int temp = (int)(result * 1000000);
    
    int digit_templates[10] = {
        -117361,  // 0
         17361,   // 1
        -74653,   // 2
         61458,   // 3
         54861,   // 4
        -24653,   // 5
        -97743,   // 6
        -98090,   // 7
        -74306,   // 8
        -1215     // 9
    };
    
    // 寻找最匹配的数字
    int closest_digit = 0;
    int smallest_difference = abs(temp - digit_templates[0]);
    
    for(int digit = 1; digit < 10; digit++) {
        int difference = abs(temp - digit_templates[digit]);
        if(difference < smallest_difference) {
            smallest_difference = difference;
            closest_digit = digit;
        }
    }
    
    return closest_digit;
}
/*
8*8 Matrix Input
make a kernal in 3*3 size
*/
/*
Test data
数字0:
########
#******#
#******#
#******#
#******#
#******#
#******#
########
0.960417
-0.117361

数字1:
********
***##***
****#***
****#***
****#***
****#***
****#***
********
0.617045
0.017361
数字2:
########
*******#
*******#
########
#*******
#*******
#*******
########

*#######
#******#
*******#
*######*
#*******
#*******
#******#
#######*
0.929779
-0.074653

数字3:
########
*******#
*******#
########
*******#
*******#
*******#
########
0.961842
0.061458

数字4:
#******#
#******#
#******#
########
*******#
*******#
*******#
*******#
0.860096
0.054816
数字5:
########
#*******
#*******
########
*******#
*******#
*******#
########

########
#*******
#*******
#*******
########
*******#
*******#
########
0.975000
-0.024653
数字6:
########
#*******
#*******
########
#******#
#******#
#******#
########
0.912500
-0.097743
数字7:
########
*******#
*******#
******#*
*****#**
****#***
***#****
**#*****
0.700893
-0.098090
数字8:
########
#******#
#******#
########
#******#
#******#
#******#
########
0.913971
-0.074306
数字9:
########
#******#
#******#
########
*******#
*******#
*******#
########
0.976417
-0.001215
*/
void input(){
    for (int i=0; i<8; i++){
        for(int j =0; j<8; j++){
            scanf("%c",&a[i][j]);
        }
        getchar();
    }

}
void process(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(a[i][j]=='#'){
                process_1[i][j]=1.0;
            }else if(a[i][j]=='*'){
                process_1[i][j]=0.0;
            }
        }
    }
}
void x_convolution(){
    double kernel[3][3]={
        {-1,-1,-1},
        {0,0,0},
        {1,1,1}
    };
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_x[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_x[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }

}
void y_convolution(){
    double kernel[3][3]={
        {-1,0,1},
        {-1,0,1},
        {-1,0,1}
    };
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_y[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_y[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }

}
void xy_convolution(){
    double kernel[3][3]={
    {-1, -1,  0},
    {-1,  0,  1},
    { 0,  1,  1}
    };
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_xy[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_xy[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}
void sharpen_convolution(){
    double kernel[3][3]={
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_sharpen[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_sharpen[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void sobel_x_convolution(){
    // Sobel X方向边缘检测（增强版）
    double kernel[3][3]={
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_sobel_x[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_sobel_x[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void sobel_y_convolution(){
    // Sobel Y方向边缘检测（增强版）
    double kernel[3][3]={
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_sobel_y[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_sobel_y[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void laplacian_convolution(){
    // 拉普拉斯算子（用于边缘增强）
    double kernel[3][3]={
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_laplacian[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_laplacian[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void gaussian_blur_convolution(){
    // 高斯模糊（用于降噪）
    double kernel[3][3]={
        {1.0/16, 2.0/16, 1.0/16},
        {2.0/16, 4.0/16, 2.0/16},
        {1.0/16, 2.0/16, 1.0/16}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_gaussian[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_gaussian[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void diagonal_45_convolution(){
    // 45度对角线边缘检测
    double kernel[3][3]={
        {-1, -1, 0},
        {-1,  0, 1},
        { 0,  1, 1}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_diag45[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_diag45[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void diagonal_neg45_convolution(){
    // -45度对角线边缘检测
    double kernel[3][3]={
        {0, -1, -1},
        {1,  0, -1},
        {1,  1,  0}
    };
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_diag_neg45[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_diag_neg45[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

// 添加特殊卷积核
void corner_convolution(){
    // 角点检测卷积核
    double kernel[3][3]={
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
    
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_corner[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_corner[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
    
    // 保存角点检测的结果用于后续处理
}

void cross_convolution(){
    // 十字形特征检测
    double kernel[3][3]={
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    };

    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_cross[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_cross[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}

void circle_convolution(){
    // 环形特征检测
    double kernel[3][3]={
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
    
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            result_circle[i][j]=0.0;
            for(int ki=0; ki<3; ki++){
                for(int kj=0; kj<3; kj++){
                    result_circle[i][j] += process_1[i+ki][j+kj] * kernel[ki][kj];
                }
            }
        }
    }
}
void merge_results(double merged[6][6]) {
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            merged[i][j] = (result_x[i][j] + result_y[i][j] + result_xy[i][j] 
            + result_sharpen[i][j] + result_sobel_x[i][j] + result_sobel_y[i][j]
            + result_diag45[i][j] + result_diag_neg45[i][j] + result_gaussian[i][j]
            + result_laplacian[i][j]) / 10.0;
        }
    }
}
double average_pooling(double input[6][6]) {
    double sum = 0.0;
    //int count = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            sum += input[i][j];
            //if(input[i][j] > 0){
            //    sum += input[i][j];
            //    count++;
            //}
            
        }
    }
    return sum / 36.0;
    //return (count > 0 ? sum / count : 0.0);
}
// 三个特殊特征的池化函数
double corner_pooling() {
    double sum = 0.0;
    int positive_count = 0;
    
    // 角点特征池化：重点关注四个角的响应
    double corners = 0.0;
    corners += result_corner[0][0];  // 左上角
    corners += result_corner[0][5];  // 右上角
    corners += result_corner[5][0];  // 左下角
    corners += result_corner[5][5];  // 右下角
    
    // 同时考虑所有正值
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(result_corner[i][j] > 0) {
                sum += result_corner[i][j];
                positive_count++;
            }
        }
    }
    
    // 返回角点响应和平均正值的组合
    return corners + (positive_count > 0 ? sum / positive_count : 0);
}

double cross_pooling() {
    double sum = 0.0;
    double center_sum = 0.0;
    int positive_count = 0;
    
    // 十字特征池化：关注中心区域和整体响应
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(result_cross[i][j] > 0) {
                sum += result_cross[i][j];
                positive_count++;
                // 特别关注中心区域
                if(i >= 2 && i <= 3 && j >= 2 && j <= 3) {
                    center_sum += result_cross[i][j];
                }
            }
        }
    }
    
    // 返回中心响应加权和整体平均值
    return 0.7 * center_sum + 0.3 * (positive_count > 0 ? sum / positive_count : 0);
}

double circle_pooling() {
    double edge_sum = 0.0;
    double center_sum = 0.0;
    
    // 环形特征池化：区分边缘和中心响应
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(result_circle[i][j] > 0) {
                // 区分边缘和中心
                if(i == 0 || i == 5 || j == 0 || j == 5) {
                    edge_sum += result_circle[i][j];  // 边缘响应
                } else if(i >= 2 && i <= 3 && j >= 2 && j <= 3) {
                    center_sum += result_circle[i][j];  // 中心响应
                }
            }
        }
    }
    
    // 环形特征：边缘强而中心弱（或相反）更有意义
    return edge_sum - center_sum;  // 差值更能体现环形特征
}

// 综合特殊特征池化
double special_features_combined() {
    double corner_feat = corner_pooling();
    double cross_feat = cross_pooling();
    double circle_feat = circle_pooling();
    
    // 简单平均组合
    return (corner_feat + cross_feat + circle_feat) / 3.0;
}
int get_possible_by_special_avg(double test_value) {
    // 根据你提供的数据范围进行分类
    if (test_value > 5.0) {
        return 1;  // 1的special_avg是5.495238
    } else if (test_value > 3.0) {
        return 7;  // 7的special_avg是3.400000
    } else if (test_value > -1.5) {
        return 4;  // 4的special_avg是-1.033333
    } else if (test_value > -3.5) {
        return 4;  // 6和9的special_avg约为-4.033333，但4更接近-1.5到-3.5的范围边界
    } else if (test_value > -4.5) {
        return 6;  // 6的special_avg是-4.033333
    } else if (test_value > -5.5) {
        return 9;  // 9的special_avg是-4.033333，但和6很接近
    } else if (test_value > -6.0) {
        return 0;  // 0的special_avg是-6.666667
    } else {
        return 8;  // 8的special_avg是-5.088889，但这里处理更负的值
    }
}

// 基于corner_feature特征的可能数字推测
int get_possible_by_corner(double test_value) {
    if (test_value > 5.0) {
        return 1;  // 1的corner_feature是6.000000
    } else if (test_value > -4.0) {
        return 7;  // 7的corner_feature是-3.000000
    } else if (test_value > -11.0) {
        return 4;  // 4的corner_feature是-3.500000
    } else if (test_value > -13.0) {
        return 6;  // 6的corner_feature是-12.500000
    } else if (test_value > -15.0) {
        return 0;  // 0的corner_feature是-20.000000
    } else {
        return 8;  // 8的corner_feature是-14.666667
    }
}

// 基于cross_feature特征的可能数字推测
int get_possible_by_cross(double test_value) {
    // 观察数据发现大部分数字的cross_feature都是3.400000，只有1和7不同
    if (test_value > 3.4) {
        return 1;  // 1的cross_feature是3.485714
    } else if (test_value < 2.0) {
        return 7;  // 7的cross_feature是1.200000
    } else {
        // 对于大多数数字，返回最常见的
        return 2;  // 2,3,4,5,6,8,9的cross_feature都是3.400000
    }
}

// 基于circle_feature特征的可能数字推测
int get_possible_by_circle(double test_value) {
    if (test_value > 10.0) {
        return 7;  // 7的circle_feature是12.000000
    } else if (test_value > 6.0) {
        return 1;  // 1的circle_feature是7.000000
    } else if (test_value > -2.5) {
        return 4;  // 4的circle_feature是-3.000000
    } else if (test_value > -3.5) {
        return 6;  // 6的circle_feature是-3.000000
    } else if (test_value > -4.5) {
        return 0;  // 0的circle_feature是0.000000
    } else {
        return 8;  // 8的circle_feature是-4.000000
    }
}
int final_weighted_decision(double regular_avg, double special_avg, 
                           double corner_feature, double cross_feature, double circle_feature) {
    // 获取每种方法的预测结果
    int regular_result = cpr(regular_avg);
    int special_result = get_possible_by_special_avg(special_avg);
    int corner_result = get_possible_by_corner(corner_feature);
    int cross_result = get_possible_by_cross(cross_feature);
    int circle_result = get_possible_by_circle(circle_result);
    
    // 投票统计数组
    int votes[10] = {0};
    
    // 根据权重分配票数（权重*100以便使用整数）
    votes[regular_result] += 40;   // 常规方法 40% 权重
    votes[special_result] += 15;   // 特殊平均 15% 权重
    votes[corner_result] += 15;    // 角点特征 15% 权重
    votes[cross_result] += 10;     // 十字特征 10% 权重
    votes[circle_result] += 20;    // 环形特征 20% 权重
    
    // 找到得票最多的数字
    int final_prediction = 0;
    int max_votes = votes[0];
    
    for(int i = 1; i < 10; i++) {
        if(votes[i] > max_votes) {
            max_votes = votes[i];
            final_prediction = i;
        }
    }
    
    return final_prediction;
}

// 简化版的最终决策函数（如果你想要更简单的方法）
int simple_final_decision(double regular_avg, double special_avg, 
                         double corner_feature, double cross_feature, double circle_feature) {
    // 获取预测结果
    int r = cpr(regular_avg);           // 常规方法
    int s = get_possible_by_special_avg(special_avg);     // 特殊平均
    int c1 = get_possible_by_corner(corner_feature);      // 角点
    int c2 = get_possible_by_cross(cross_feature);        // 十字
    int c3 = get_possible_by_circle(circle_feature);      // 环形
    
    // 简单多数投票（如果相同结果多，则更可信）
    int predictions[5] = {r, s, c1, c2, c3};
    int count[10] = {0};
    
    // 统计每个数字出现次数
    for(int i = 0; i < 5; i++) {
        count[predictions[i]]++;
    }
    
    // 找出出现次数最多的数字
    int best_digit = 0;
    int max_count = count[0];
    
    for(int i = 1; i < 10; i++) {
        if(count[i] > max_count) {
            max_count = count[i];
            best_digit = i;
        }
    }
    
    // 如果所有数字都不同（没有多数），则信任常规方法
    if(max_count == 1) {
        return r;
    }
    
    return best_digit;
}


int main(){
    input();
    process();

    //进行一般卷积计算 10种特征值取平均获得1特征值
    x_convolution();
    y_convolution();
    xy_convolution();
    sharpen_convolution();
    sobel_x_convolution();
    sobel_y_convolution();
    laplacian_convolution();
    gaussian_blur_convolution();
    diagonal_45_convolution();
    diagonal_neg45_convolution();

    corner_convolution();
    cross_convolution();
    circle_convolution();
    //进行特殊卷积计算，针对一个特征获得
    double merged[6][6];
    merge_results(merged);
    double regular_avg = average_pooling(merged);
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%f ",merged[i][j]);
        }
        printf("\n");
    }
    double special_avg = special_features_combined();
    // 特殊特征池化
    double corner_feature = corner_pooling();
    double cross_feature = cross_pooling();
    double circle_feature = circle_pooling();

    // 获取各种方法的预测结果
    int regular_result = cpr(regular_avg);
    int special_result = get_possible_by_special_avg(special_avg);
    int corner_result = get_possible_by_corner(corner_feature);
    int cross_result = get_possible_by_cross(cross_feature);
    int circle_result = get_possible_by_circle(circle_feature);
    
    // 使用最终决策方法
    int final_result = final_weighted_decision(regular_avg, special_avg, 
                                             corner_feature, cross_feature, circle_feature);
    
    // 或者使用简单决策方法
    int simple_result = simple_final_decision(regular_avg, special_avg,
                                            corner_feature, cross_feature, circle_feature);

    printf("======= 特征值 =======\n");
    printf("常规特征值: %f\n", regular_avg);
    printf("特殊平均值: %f\n", special_avg);
    printf("角点特征值: %f\n", corner_feature);
    printf("十字特征值: %f\n", cross_feature);
    printf("环形特征值: %f\n", circle_feature);
    
    printf("======= 预测结果 =======\n");
    printf("常规方法预测: %d\n", regular_result);
    printf("特殊平均预测: %d\n", special_result);
    printf("角点特征预测: %d\n", corner_result);
    printf("十字特征预测: %d\n", cross_result);
    printf("环形特征预测: %d\n", circle_result);
    printf("======= 最终决策 =======\n");
    printf("加权决策结果: %d\n", final_result);
    printf("简单决策结果: %d\n", simple_result);
    
    return 0;
}