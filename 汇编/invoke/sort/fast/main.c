#include <stdio.h>
extern void asm_sort(int arr[], int len);

int main(){
    int a[] = {5, -1, 3, -4, 2};
    asm_sort(a, 5);
    for(int i=0;i<5;i++) printf("%d ",a[i]);
    // 输出：-4 -1 2 3 5
    return 0;
}