#include <unistd.h>
#include <stdio.h>

int main(int argc,char** argv){
	int opt;
	while((opt = getopt(argc,argv,":lf:r")) != -1){
		switch(opt){
			case 'l':
			//case 'f':
			case 'r':
				printf("options : %c\n",opt);
				break;
			case 'f':
				printf("filename = %s\n",optarg);
				break;
			case '?':
				printf("unkown option : %c\n",optopt);
				break;
			default:	//case ':':
				printf("option need a value\n");
				break;
		}
	}
	return 0;
}
