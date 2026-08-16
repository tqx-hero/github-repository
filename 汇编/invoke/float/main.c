#include <stdio.h>
extern float asm_circle_area(float r);
int main(){
    printf("%f\n", asm_circle_area(2.0f)); // 12.566...
    return 0;
}