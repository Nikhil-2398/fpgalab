#include<Arduino.h>
unsigned char num ;                             //input number
unsigned char _A=0x00,_B=0x00,_C=0x00,_D=0x00;      //binary inputs
unsigned char one = 0x01;
unsigned char Org, Nor;                         //outputs
char buffer[40];

void disp_num(unsigned char A, unsigned char B, unsigned char C, unsigned char D){

  unsigned char a,b,c,d,e,f,g;
  A=0;
  a = ~( ((A)&(~B)&(~C)) | ((~A)&(B)&(D)) | ((A)&(~D)) | ((~A)&(C)) | ((B)&(C)) | ((~B)&(~D)) );
  b = ~( ((~A)&(~C)&(~D)) | ((~A)&(C)&(D)) | ((A)&(~C)&(D)) | ((~B)&(~C)) | ((~B)&(~D)) );
  c = ~( ((~B)&(~C)) | ((~A)&(D)) | ((D)&(~C)) | ((~A)&(B)) | ((A)&(~B)) );
  d = ~( ((~A)&(~B)&(~D)) | ((~B)&(C)&(D)) | ((B)&(~C)&(D)) | ((B)&(C)&(~D)) | ((A)&(~C)) );
  e = ~( ((~D)&(~B)) | ((C)&(~D)) | ((A)&(C)) | ((A)&(B)) );
  f = ~( ((~A)&(B)) | ((~C)&(~D)) | ((B)&(~D)) | ((A)&(~B)) | ((A)&(C)) );
  g = ~( ((~A)&(B)&(~C)) | ((C)&(~B)) | ((C)&(~D)) | ((A)&(~B)) | ((A)&(D)) );

  digitalWrite(2,one&a);
  digitalWrite(3,one&b);
  digitalWrite(4,one&c);
  digitalWrite(5,one&d);
  digitalWrite(6,one&e);
  digitalWrite(7,one&f);
  digitalWrite(8,one&g);

}

void setup() {
  pinMode(2,OUTPUT);    //a
  pinMode(3,OUTPUT);    //b
  pinMode(4,OUTPUT);    //c
  pinMode(5,OUTPUT);    //d
  pinMode(6,OUTPUT);    //e
  pinMode(7,OUTPUT);    //f
  pinMode(8,OUTPUT);    //g
  pinMode(11,OUTPUT);   //org output
  pinMode(12,OUTPUT);   //Nor output
  Serial.begin(9600);

}



void loop() {

  Serial.println("\n\nBinary Input  (A+B)(C+D)  NOR Equivalent");

  for (num = 0x00; num<0x10; num++){
        //loop to iterate through all usecases
        delay(1000);

           _B = num>>2;    _C = num>>1;    _D = num>>0;
        disp_num(_A, _B, _C, _D);
        unsigned char p= ~(_B&_D);
        unsigned char r= ~((~(_B))&(_C&(~(_D))));
        unsigned char q= ~(_B&(~(_C)));
        unsigned char G=~(p&q&r);
                

        digitalWrite(11,one&G);
        

    
    }
}
