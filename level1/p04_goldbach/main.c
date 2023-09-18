#include <stdio.h>

/*
 * 验证100以内哥德巴赫猜想
 * 先给出100内质数表 p02跑出数据
 * 再参考leetcode第一题
 * */

int bs(int* arr, int len, int target){
    // 二分查找, 返回下标
    int left = 0;
    int right = len;
    while(1){
        int mid = (left + right)/2;
        if(target > arr[mid]){
            left = mid;
        }else if(target < arr[mid]){
            right = mid;
        }else if(target == arr[mid]){
            return mid;
        }
        if(left + 1 == right){
            return -1;
        }
    }
}

void func(){
    int arr[] = {2, 3, 5, 7, 11,
                 13, 17, 19, 23, 29,
                 31, 37, 41, 43, 47,
                 53, 59, 61, 67, 71,
                 73, 79, 83, 89, 97};
    int len = sizeof(arr)/sizeof(arr[0]);
    for(int i = 8; i <= 100; i += 2){
        for(int j = 0; j < len; j ++){
            // 计算差值, 遍历查找 O(n)
            if(arr[j] << 1 > i){
                // 去除重复项
                break;
            }
            int di = i - arr[j];
            // 二分查找 O(lgn)
            int index = bs(arr, len, di);
            if(index == -1){
                continue;
            }
            printf("%d = %d + %d\n", i, arr[j], arr[index]);
        }
    }
}

int main() {
    func();
    return 0;
}