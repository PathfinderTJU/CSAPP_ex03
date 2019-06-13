#include <stdio.h>
long error_code = 0xFA7F7F;
long ok_code = 0xFA5555;

int getTime() {
  int result = 0;
  int temp = (int)millis();
  temp = ((temp << 2) >> 2) & 0x3FFF;
  byte temp_1 = (byte)(temp & 0x7F); //low
  byte temp_2 = (byte)(temp >> 7);  //high
  result = (temp_1 << 8) | temp_2;
  return result;
}

int getTemperature() {
  int result = 0;
  int temp = 520;
  temp = ((temp << 2) >> 2) & 0x3FFF;
  byte temp_1 = (byte)(temp & 0x7F); //low
  byte temp_2 = (byte)((temp >> 7) & 0x7F);  //high
  result = (temp_1 << 8) | temp_2;
  return result;
}

int getLight() {
  int result = 0;
  int temp = (int)analogRead(1);
  temp = ((temp << 2) >> 2) & 0x3FFF;
  byte temp_1 = (byte)(temp & 0x7F); //low
  byte temp_2 = (byte)(temp >> 7);  //high
  result = (temp_1 << 8) | temp_2;
  return result;
}

int getPWM(byte number) {
  pinMode(number, INPUT);
  int result = 0;
  int temp = (int)analogRead(number);
  temp = ((temp << 2) >> 2) & 0x3FFF;
  byte temp_1 = (byte)(temp & 0x7F); //low
  byte temp_2 = (byte)(temp >> 7);  //high
  result = (temp_1 << 8) | temp_2;
  return result;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  byte temp = 0;
  byte command = 0;
  byte channel = 0;
  byte first_byte = 0;
  byte second_byte = 0;

  while (true) {
    Serial.println("Waiting command...");
    while (true) {
      if (Serial.available() > 0) {
        temp = Serial.read();
        break;
      }
    }
    command = (temp >> 4) & 0xF;
    channel = temp & 0xF;
    if (command == 0xE) { //读取AD值的命令
      if (channel == 0 || channel == 1) {
        Serial.println("Command checked. Waiting data");

        int start_time = millis();
        bool flag = true;
        while (true) {
          if (Serial.available() > 0) {
            first_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        start_time = millis();
        flag = true;
        while (true) {
          if (Serial.available() > 0) {
            second_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        if (first_byte == 0x11 && second_byte == 0x11) {
          if (channel == 0) {
            Serial.print("The AD number of temperature is: ");
            Serial.println(getTemperature());
            Serial.print("Return code: ");
            Serial.println(ok_code);
          } else {
            Serial.print("The AD number of Light is: ");
            Serial.println(getLight());
            Serial.print("Return code: ");
            Serial.println(ok_code);
          }
        } else {
          Serial.print("Illegal data. Return code: ");
          Serial.println(error_code);
          continue;
        }
      } else {
        Serial.print("Illegal channel. Return code: ");
        Serial.println(error_code);
        continue;
      }
    } else if (command == 0x9) { //设置电平
      Serial.println("Command checked. Waiting data");

      int start_time = millis();
      bool flag = true;
      while (true) {
        if (Serial.available() > 0) {
          first_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      start_time = millis();
      flag = true;
      while (true) {
        if (Serial.available() > 0) {
          second_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      if (first_byte == 0) {
        pinMode(channel, OUTPUT);
        digitalWrite(channel, LOW);
        Serial.print("New status: ");
        Serial.println(getPWM(channel));
        Serial.print("Return code: ");
        Serial.println(ok_code);
      } else if (first_byte == 1) {
        pinMode(channel, OUTPUT);
        digitalWrite(channel, HIGH);
        Serial.print("New status: ");
        Serial.println(getPWM(channel));
        Serial.print("Return code: ");
        Serial.println(ok_code);
      } else {
        Serial.print("Illegal data. Return code: ");
        Serial.println(error_code);
        continue;
      }
    } else if (command == 0xC) { //读取电平
      Serial.println("Command checked. Waiting data");

      int start_time = millis();
      bool flag = true;
      while (true) {
        if (Serial.available() > 0) {
          first_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      start_time = millis();
      flag = true;
      while (true) {
        if (Serial.available() > 0) {
          second_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      if (first_byte == 0x66) {
        Serial.print("The number of channel ");
        Serial.print(channel);
        Serial.print(" is: ");
        Serial.println(getPWM(channel));
        Serial.print("Return code: ");
        Serial.println(ok_code);
      } else {
        Serial.print("Illegal data. Return code: ");
        Serial.println(error_code);
        continue;
      }
    } else if (command == 0xD) { //设置或读取PWM值
      Serial.println("Command checked. Waiting data");

      int start_time = millis();
      bool flag = true;
      while (true) {
        if (Serial.available() > 0) {
          first_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      start_time = millis();
      flag = true;
      while (true) {
        if (Serial.available() > 0) {
          second_byte = Serial.read();
          break;
        }
        if (millis() - start_time > 5000) {
          Serial.print("Time out. Return code: ");
          Serial.println(error_code);
          flag = false;
          break;
        }
      }
      if (!flag) {
        continue;
      }

      byte f = second_byte >> 6;
      if (f == 1) { //读取
        Serial.print("The PWM number of channel ");
        Serial.print(channel);
        Serial.print(" is: ");
        Serial.println(getPWM(channel));
        Serial.print("Return code: ");
        Serial.println(ok_code);
      } else { //写
        int PWM = first_byte | (second_byte << 7);
        pinMode(channel, PWM);
        analogWrite(channel, PWM);
        Serial.print("Return code: ");
        Serial.println(ok_code);
      }
    } else if (command == 0xF) { 
      if (channel == 0xF) {//读取上电时间
        Serial.println("Command checked. Waiting data");

        int start_time = millis();
        bool flag = true;
        while (true) {
          if (Serial.available() > 0) {
            first_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        start_time = millis();
        flag = true;
        while (true) {
          if (Serial.available() > 0) {
            second_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        if (first_byte == 0x55 && second_byte == 0x55) {
          Serial.print("Time: ");
          Serial.print(getTime());
          Serial.println("ms");
          Serial.print("Return code: ");
          Serial.println(ok_code);
        } else {
          Serial.print("Illegal data. Return code: ");
          Serial.println(error_code);
          continue;
        }
      } else if (channel == 0x9){ //读取学号
        Serial.println("Command checked. Waiting data");

        int start_time = millis();
        bool flag = true;
        while (true) {
          if (Serial.available() > 0) {
            first_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        start_time = millis();
        flag = true;
        while (true) {
          if (Serial.available() > 0) {
            second_byte = Serial.read();
            break;
          }
          if (millis() - start_time > 5000) {
            Serial.print("Time out. Return code: ");
            Serial.println(error_code);
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }

        if (first_byte == 0x55 && second_byte == 0x55) {
          Serial.println("Student Number: 17218063");
          Serial.print("Return code: ");
          Serial.println(ok_code);
        } else {
          Serial.print("Illegal data. Return code: ");
          Serial.println(error_code);
          continue;
        }
      }else{
        Serial.print("Illegal channel. Return code: ");
        Serial.println(error_code);
        continue;
      }
    }else {
      Serial.print("Illegal command. Return code: ");
      Serial.println(error_code);
      continue;
    }
  }
}
