#include <stdio.h>

//void swap(int* a, int* b) {
//    int t = *a;
//    *a = *b;
//    *b = t;
//}
//
//void bubble_sort(int a[], int n) {
//    int sorted = 0;
//    while (sorted < n - 1) {
//        int count = 0;
//        for (int j = 0; j < n - 1 - sorted; ++j) {
//            if (a[j + 1] < a[j]) {
//                swap(a + j, a + j + 1);
//                count = 0;
//            }
//            else {
//                ++count;
//            }
//        }
//        sorted += count;
//    }
//}
void swap(int a[],int n, int m)
{
    int temp = a[n];
    a[n] = a[m];
    a[m] = temp;
}
int main() {
    int a[10] = {6, 5, 4, 5, 7, 8, 99, 0, -1, 2};
 //   bubble_sort(a, 10);
    swap(a,1,2);
    for (int i = 0; i < 10; ++i) printf("%d ", a[i]);
    return 0;
}
