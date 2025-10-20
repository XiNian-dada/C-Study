#include <stdio.h>

void merge(int arr[], int left , int mid , int right){
    int i = left;
    int j = mid;
    int index = 0;
    int temp[right - left];
    while (i < mid && j < right){
        if (arr [i] < arr[j]){
            temp[index] = arr[i];
            i++;
        }
        else {
            temp[index] = arr[j];
            j++;
        }
        index++;
    }
    while (i < mid){
        temp[index] = arr[i];
        i++;
        index++;
    }
    while (j < right){
        temp[index] = arr[j];
        j++;
        index++;

    }
    for (int i = left; i < right; i++){
        arr[i] = temp[i - left];
    }
}
void merge_sort(int arr[] , int left, int right){
    if(right - left <= 1){
        return;
    }else {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid, right);
        merge(arr, left, mid, right);
    }
}


int main(){  
    int arr[]={2,7,4,6,9,1,5,8,0,3};

    merge_sort(arr, 0, 10);
    for (int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    
}