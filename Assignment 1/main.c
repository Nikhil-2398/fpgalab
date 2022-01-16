#include <stdio.h>
#include <stdlib.h>

int main()
{unsigned char Out = 0x01;
unsigned char G; 
    unsigned char X[8] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};
    unsigned char Y[8] = { 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01};
    unsigned char Z[8] = { 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01};
    unsigned char a, b, expression_ans;

    for (int i = 0; i < 8; i++) {

    
            G=!((!(X[i]&&Y[i]))&&(!(X[i]&&Z[i]))&&(!(Y[i]&&(!(Z[i])))));
             printf("%x%x%x",Out&X[i],Out&Y[i],Out&Z[i]);
    printf(" ");
    printf("%x\n" ,Out&G);
   
    }
    return 0;


}
