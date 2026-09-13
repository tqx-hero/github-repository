#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node* next;
}Node;
Node* create_list(char** argv,int len);
Node* reverse(Node* node);
int main(int argc,char ** argv,char** env){
	if(argc ==1){
		printf("param count error\n");
		return EXIT_FAILURE;
	}
    //获取输入的参数列表中数值个数，放入数组
    int len = argc-1;
    Node* list = reverse(create_list(&argv[1],len));
	printf("链表:\n");
    while(len--){
        printf("%d ",list->val);
        Node* temp = list;
        list=list->next;
        free(temp);
    }
    fprintf(stdout,"\n");
	return 0;
}

Node* reverse(Node* node){
    Node* cur =node,* prev =NULL;
    while (cur){
        Node* next= cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    return prev;
}

Node* create_list(char** argv,int len){
    Node dummy = {0,NULL},*cur =&dummy;
    while(len--){
        Node* new_node= malloc(sizeof(int));
        new_node->val = atoi(*argv);
        new_node->next=NULL;
        cur->next = new_node;
        cur = cur->next;
        argv++;
    }
    return dummy.next;
}
