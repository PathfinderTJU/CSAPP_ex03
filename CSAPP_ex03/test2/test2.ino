#include <stdio.h>
#include <math.h>
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}

void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

void setup() {
      Serial.begin(115200);
      printf_begin();
      pinMode(3,OUTPUT);
      pinMode(5,OUTPUT);
      pinMode(6,OUTPUT);
      pinMode(9,OUTPUT);
      pinMode(10,OUTPUT);
}

void loop() {
      for(int i = 255; i > 0; i--){    
          analogWrite(3, i);
          analogWrite(5, i);
          analogWrite(6, i);
          analogWrite(9, i);
          analogWrite(10, i);     
          delay(10);   
        }

      delay(1000);
}
