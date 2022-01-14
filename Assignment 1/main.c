#include <stdio.h>

int main(){
    unsigned char G; 
    unsigned char Out = 0x01;
    unsigned char  X=0x00,Y=0x01,Z=0x00; 

    G = (X | Y)&(X |(~Z))&((~X) | (~Y)|Z);

    printf("%x%x%x",Out&X,Out&Y,Out&Z);
    printf(" ");
    printf("%x\n" ,Out&G);
    return 0;
}
