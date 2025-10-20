#include <stdio.h>

/*
 * 合并两个已排序的子数组
 * arr: 待处理的数组
 * left: 左子数组的起始索引
 * mid: 左子数组的结束索引，也是右子数组的起始索引
 * right: 右子数组的结束索引
 */
void merge(int arr[], int left, int mid, int right){
     int i = left,j = mid;                    // i指向左子数组的起始位置，j指向右子数组的起始位置
     int temp[right - left];                  // 创建临时数组存储合并结果，大小为两个子数组长度之和
     int index = 0;                           // 临时数组的索引，从0开始
     
     // 比较两个子数组的元素，将较小的元素放入临时数组
     while(i < mid && j < right){
        if (arr[i] < arr[j]){                // 如果左子数组当前元素小于右子数组当前元素
            temp [index] = arr[i];           // 将左子数组元素放入临时数组
            i++;                             // 左子数组指针向后移动
        }else{                               // 否则（包括相等的情况）
            temp [index] = arr[j];           // 将右子数组元素放入临时数组
            j++;                             // 右子数组指针向后移动
        }
        index ++;                            // 临时数组索引向后移动
     }
     
     // 将左子数组剩余元素复制到临时数组
     while (i < mid){
        temp [index] = arr[i];
        i++;
        index ++;
     }
     
     // 将右子数组剩余元素复制到临时数组
     while (j < right){
        temp [index] = arr[j];
        j++;
        index ++;
     }
     
     // 将临时数组中的元素复制回原数组对应位置
     for (i = 0; i < index; i++){
        arr[left + i] = temp[i];
     }

}

/*
 * 归并排序主函数，使用分治法对数组进行排序
 * arr: 待排序的数组
 * left: 排序范围的起始索引
 * right: 排序范围的结束索引（不包含）
 */
void mergeSort(int arr[], int left,int right){
    if (right - left <= 1){                  // 如果子数组长度小于等于1
        return;                              // 直接返回，无需排序
    }else {                                  // 否则继续分治
        int mid = (left + right) / 2;        // 计算中间位置，将数组分为两部分
        mergeSort(arr, left, mid);           // 递归排序左半部分
        mergeSort(arr, mid, right);          // 递归排序右半部分
        merge(arr, left, mid, right);        // 合并两个已排序的部分
    }
}

// 主函数，程序入口
int main(){
    int arr[10] = {4,7,6,1,9,8,0,3,2,5};    // 初始化一个包含10个元素的数组
    mergeSort(arr, 0, 10);                   // 调用归并排序函数对整个数组排序
    for (int i = 0; i < 10; i++){            // 遍历排序后的数组
        printf("%d ", arr[i]);               // 打印每个元素
    }
    return 0;                                // 程序正常结束
}