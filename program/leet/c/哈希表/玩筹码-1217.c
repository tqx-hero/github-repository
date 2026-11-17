#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(x,y)    x <= y ? x : y
int minCostToMoveChips(int* position, int positionSize) {
    int odd = 0,even = 0;
    int i;
    for(i = 0 ; i < positionSize ; ++i ){
        if(position[i] % 2)
            odd++;
        else
            even++;
    }
    return MIN(odd,even);
}

int main(int argc,char **argv){
    int position[] = {1,1000000000};
    fprintf(stdout,"%d\n",minCostToMoveChips(position,sizeof(position) / sizeof(int)));
    exit(0);
}
