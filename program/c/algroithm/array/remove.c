#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int remove_elem(int arr[], int n, int val);
int* build_array(char** argv,int len);
int main(int argc,char ** argv,char** env){
    if(argc <= 2){
		printf("param count error\n");
		return EXIT_FAILURE;
	}
    int len = argc-2;
    int*array =  build_array(&argv[2],len);
    printf("原数组：\n");
    for(int i=0;i<len;++i){
        printf("%d ",array[i]);
    }
    printf("\n");
    len = remove_elem(array,len,atoi(argv[1]));
    printf("去重后数组: \n");
    while(len--){
        printf("%d ",*array);
        ++array;
    }
    printf("\n");
    return 0;
}

int* build_array(char** argv,int len){
    int* array_ptr = malloc(sizeof(int) * len);
    int* array = array_ptr;
    while(len--){
        *array = atoi(*argv);
        array++;
        argv++;
    }
    return array_ptr;
}

int remove_elem(int arr[], int n, int val){
    int cnt=0,right=0;
    while(n--){
        if(arr[right] != val)
            arr[cnt++] = arr[right];
        right++;
    }
    return cnt;
}