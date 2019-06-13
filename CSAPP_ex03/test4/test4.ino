#include <stdio.h>
#define D1 36  
#define D2 38
#define D3 40
#define D4 41
#define D5 43
#define D6 45
#define D7 47

#define M1 48
#define M2 50
#define M3 52
#define M4 53
#define M5 55
#define M6 57
#define M7 59

#define H1 60 
#define H2 62
#define H3 64
#define H4 65
#define H5 67
#define H6 69
#define H7 71

int bpm = 78;

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void note4(){
  double gap = 60.0/bpm * 1000;
  delay((int)gap);
}

void note6(){
  double gap = 60.0/bpm/1.5 * 1000;
  delay((int)gap);
}

void note8(){
  double gap = 60.0/bpm/2 * 1000;
  delay((int)gap);
}

void note16(){
  double gap = 60.0/bpm/4 * 1000;
  delay((int)gap);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  //前奏
  noteOn(0x90, H7, 0x45);
  note16();
  noteOn(0x90, H6, 0x45);
  note16();
  noteOn(0x90, H5, 0x45);
  note4();
  note8();
  noteOn(0x90, H5, 0x45);
  note4();
  note4();

  noteOn(0x90, M7, 0x45);
  note16();
  noteOn(0x90, M6, 0x45);
  note16();
  noteOn(0x90, M5, 0x45);
  note4();
  noteOn(0x90, M2, 0x45);
  noteOn(0x90, H5, 0x10);
  note8();
  noteOn(0x90, M3, 0x45);
  noteOn(0x90, H5, 0x10);
  note4();
  note4();

  noteOn(0x90, M6, 0x45);
  note16();
  noteOn(0x90, M7, 0x45);
  note16();
  noteOn(0x90, H1, 0x45);
  note4();
  note8();
  noteOn(0x90, M5, 0x45);
  note4();
  noteOn(0x90, H3, 0x45);
  note8();
  noteOn(0x90, H2, 0x45);
  note16();
  noteOn(0x90, H1, 0x45);
  note16();
  noteOn(0x90, M7, 0x45);
  note4();
  note4();
  note4();

  noteOn(0x90, H3, 0x45);
  note16();
  noteOn(0x90, H4+1, 0x45);
  note16();
  noteOn(0x90, H5, 0x45);
  note4();
  note8();
  noteOn(0x90, M2, 0x45);
  noteOn(0x90, H5, 0x10);
  note8();
  note4();
  noteOn(0x90, H5, 0x45);
  note16();
  noteOn(0x90, H4+1, 0x45);
  note16();
  noteOn(0x90, H3, 0x45);
  note16();
  noteOn(0x90, H4+1, 0x45);
  note16();
  noteOn(0x90, H2, 0x45);
  note4();
  noteOn(0x90, M2, 0x45);
  noteOn(0x90, H5, 0x10);
  note8();
  noteOn(0x90, M6, 0x45);
  note8();
  noteOn(0x90, M5, 0x45);
  note4();
  note4();

  noteOn(0x90, M3, 0x45);
  note4();
  note8();
  noteOn(0x90, M1, 0x45);
  note8();
  noteOn(0x90, M7, 0x45);
  note6();
  noteOn(0x90, M6, 0x45);
  note6();
  noteOn(0x90, M5, 0x45);
  note8();
  noteOn(0x90, M6, 0x45);
  note4();
  note4();
  note4();
  note4();

  //               你问     我爱     你有    多深   我爱     你有
  int m1[6][2] = {{D5,M1},{M3,M5},{M1,D7},{M3,M5},{M5,M6},{M7,H1}};
  for(int i = 0 ; i < 6 ; i++){
    noteOn(0x90, m1[i][0], 0x45);
    note8();
    noteOn(0x90, m1[i][1], 0x45);
    if (i != 5){
      note8();
    }
    note4();
  }
  noteOn(0x90, M6, 0x45);//几
  note4();
  noteOn(0x90, M5, 0x45);//分
  note4();
  note4();
  note4();
  //               我的 情 也真       我的 爱 也真        月亮 代 表我
  int m2[3][5] = {{M3,M2,M1,M1,M1}, {M3,M2,M1,M1,M1}, {M2,M3,M2,M1,D6}};
  for(int i = 0 ; i < 3 ; i++){
    noteOn(0x90, m2[i][0], 0x45);
    note8();
    noteOn(0x90, m2[i][1], 0x45);
    note8();
    noteOn(0x90, m2[i][2], 0x45);
    note4();
    note8();
    noteOn(0x90, m2[i][3], 0x45);
    note8();
    noteOn(0x90, m2[i][4], 0x45);
    note4();
  }
  noteOn(0x90, M3, 0x45);//的
  note4();
  noteOn(0x90, M2, 0x45);//心
  note4();
  note4();
  note4();

  //               你问     我爱     你有    多深   我爱     你有
  int m3[6][2] = {{D5,M1},{M3,M5},{M1,D7},{M3,M5},{M5,M6},{M7,H1}};
  for(int i = 0 ; i < 6 ; i++){
    noteOn(0x90, m3[i][0], 0x45);
    note8();
    noteOn(0x90, m3[i][1], 0x45);
    if (i != 5){
      note8();
    }
    note4();
  }
  noteOn(0x90, M6, 0x45);//几
  note4();
  noteOn(0x90, M5, 0x45);//分
  note4();
  note4();
  note4();
  //               我的 情 不移       我的 爱 不变        月亮 代 表我
  int m4[3][5] = {{M3,M2,M1,M1,M1}, {M3,M2,M1,M1,M1}, {M2,M3,M2,D6,D7}};
  for(int i = 0 ; i < 3 ; i++){
    noteOn(0x90, m4[i][0], 0x45);
    note8();
    noteOn(0x90, m4[i][1], 0x45);
    note8();
    noteOn(0x90, m4[i][2], 0x45);
    note4();
    note8();
    noteOn(0x90, m4[i][3], 0x45);
    note8();
    noteOn(0x90, m4[i][4], 0x45);
    note4();
  }
  noteOn(0x90, M2, 0x45);//的
  note4();
  noteOn(0x90, M1, 0x45);//心
  note4();
  note4();
  note4();

  noteOn(0x90, M5, 0x45);//轻
  note4();
  noteOn(0x90, M3, 0x45);//轻
  note4();
  note8();
  noteOn(0x90, M2, 0x45);//的
  note8();
  noteOn(0x90, M1, 0x45);//一
  note4();
  noteOn(0x90, M5, 0x45);//个
  note4();
  noteOn(0x90, D7, 0x45);//吻
  note4();
  note4();
  note4();
  noteOn(0x90, D6, 0x45);//已
  note8();
  noteOn(0x90, D7, 0x45);//经
  note8();
  noteOn(0x90, D6, 0x45);//打
  note4();
  note8();
  noteOn(0x90, D7, 0x45);//动
  note8();
  noteOn(0x90, D6, 0x45);//我
  note4();
  noteOn(0x90, D5, 0x45);//的
  note4();
  noteOn(0x90, M3, 0x45);//心
  note4();
  note4();
  note4();

  noteOn(0x90, M5, 0x45);//深
  note4();
  noteOn(0x90, M3, 0x45);//深
  note4();
  note8();
  noteOn(0x90, M2, 0x45);//的
  note8();
  noteOn(0x90, M1, 0x45);//一
  note4();
  noteOn(0x90, M5, 0x45);//段
  note4();
  noteOn(0x90, D7, 0x45);//情
  note4();
  note4();
  note4();
  noteOn(0x90, D6, 0x45);//让
  note8();
  noteOn(0x90, D7, 0x45);//我
  note8();
  noteOn(0x90, M1, 0x45);//思
  note4();
  note8();
  noteOn(0x90, M1, 0x45);//念
  note8();
  noteOn(0x90, M1, 0x45);//到
  note4();
  noteOn(0x90, M2, 0x45);//如
  note8();
  noteOn(0x90, M3, 0x45);
  note8();
  noteOn(0x90, M2, 0x45);//今
  note4();
  note4();
  note4();

  //               你问     我爱     你有    多深   我爱     你有
  int m5[6][2] = {{D5,M1},{M3,M5},{M1,D7},{M3,M5},{M5,M6},{M7,H1}};
  for(int i = 0 ; i < 6 ; i++){
    noteOn(0x90, m5[i][0], 0x45);
    note8();
    noteOn(0x90, m5[i][1], 0x45);
    if (i != 5){
      note8();
    }
    note4();
  }
  noteOn(0x90, M6, 0x45);//几
  note4();
  noteOn(0x90, M5, 0x45);//分
  note4();
  note4();
  note4();
  
  //               你去 想 一想       你去 看 一看        月亮 代 表我
  int m6[3][5] = {{M3,M2,M1,M1,M1}, {M3,M2,M1,M1,M1}, {M2,M3,M2,D6,D7}};
  for(int i = 0 ; i < 3 ; i++){
    noteOn(0x90, m4[i][0], 0x45);
    note8();
    noteOn(0x90, m4[i][1], 0x45);
    note8();
    noteOn(0x90, m4[i][2], 0x45);
    note4();
    note8();
    noteOn(0x90, m4[i][3], 0x45);
    note8();
    noteOn(0x90, m4[i][4], 0x45);
    note4();
  }
  note4();
  note4();
  noteOn(0x90, M2, 0x45);//的
  note4();
  note4();
  note4();
  note4();
  noteOn(0x90, M1, 0x45);//心
  note4();
  note4();
  note4();
  note4();
  note4();
  note4();

  delay(5000);
}
