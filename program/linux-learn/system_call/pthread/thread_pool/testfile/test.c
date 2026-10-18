#include <stdio.h>
#include "ArrayDeque.h"

ArrayDeque* msgque;
int main(){
	arrayDeque_initQueue(&msgque,0);
	printf("empty = %d\n",arrayDeque_isEmpty(msgque));
	printf("empty = %d\n",arrayDeque_isFull(msgque));
	arrayDeque_destory(msgque);
	return 0;
}
