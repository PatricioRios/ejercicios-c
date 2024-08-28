#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getRand(int bottom,int top){
    return rand() % (top-bottom+1) + bottom;
}

int getRandBit(){
    int random = rand()%2 == 0 ? 0:1;
    return random;
}

//int main(){
//    for(int i=0;i<10;i++){
//        printf("Rand %d \n", getRandBit());
//    }
//    
//}