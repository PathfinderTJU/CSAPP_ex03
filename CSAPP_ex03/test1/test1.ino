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

double getTemperature(){
  return analogRead(0);
}

double getLight(){
  return analogRead(1);
}

void setup() {
    Serial.begin(115200);
    printf_begin();
}

void loop() {
    printf("Test 1: \n");
    Serial.print("Temperature ADC: ");
    Serial.println(getTemperature());
    Serial.print("Light ADC: "); 
    Serial.println(getLight());

    delay(10000);
}
