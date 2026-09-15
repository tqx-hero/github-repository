#include <stdio.h>

extern int asm_binary_search(int arr[], int len, int target);

int main() {
    // 已排序数组
    int arr[] = {-5, 2, 7, 12, 19, 25, 33};
    int len = 7;
    
    // 测试：查找存在的值
    int idx1 = asm_binary_search(arr, len, 12);
    printf("找到 12，索引：%d\n", idx1);  // 输出 3
    
    // 测试：查找不存在的值
    int idx2 = asm_binary_search(arr, len, 100);
    printf("没找到 100，返回：%d\n", idx2);  // 输出 -1
    
    return 0;
}