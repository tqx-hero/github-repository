#include <stdio.h>
extern void *asm_memcpy(void *dst, const void *src, int n);
int main(){
    char buf[20] = {0};
    asm_memcpy(buf, "hello", 3);
    printf("%s\n", buf); // hel
    return 0;
}