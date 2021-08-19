/*
  AITUMEGA Maze Solving
  Author: Edwin Aditya S P
  AIOS AINO Rev 1.2

  Source code sepenuhnya milik AITUMEGA
  Tidak diperuntukan untuk resfrensi pemrograman,
  Tidak mengambil sebagian atau seluruhnya dan 
  Tidak memperjual belikan source code ini.
*/


#include "Aitumega.h"
#include <Wire.h>


// Mode garis
const byte white=1;
const byte black=2;

// Mode aksi
const byte lost=0;
    // Mode Mengabaikan Percabangan  
    
const byte left=1;
    // Mode Belok Kiri 
    
const byte right=2;
    // Mode Belok Kanan
    
const byte forward=3;
    // Mode Jalan Bebas kedepan
    
const byte back=4;
    // Mode Mundur kebelakang

const byte stop =5;
    // Mode Berhenti berjalan
    
const byte pickup=6;
    // Mode Angkat (Gripper)
    
const byte drop=7;
    // Mode Taruh (Gripper)


//Mode Sensor
const byte xorLL = 1;
  //Sensor Baca Per3an Kiri       XOR  11100111100000

const byte xorRR = 2;
  //Sensor Baca Per3an Kanan      XOR  00000111100111
  
const byte per4an = 3;
  //Sensor Baca Per4an            XOR  11100000000111
  
const byte orLL  = 4;
  //Sensor Baca SIKU Kiri         OR   111000000000000

const byte orRR  = 5;
 //Sensor Baca SIKU Kanan         OR   000000000000111

const byte bleng = 6;
 //Sensor Baca Kosong             =    00000000000000

const byte timeout = 7;
  //Baca Timer => Mode Baca dengan accuan durasi timer

byte mypwm=255;
char not_set="SS";

void file(){
//============================SETTING=============================================
//seting (kecepatan1, kecepatan2, perintah, sensor, delay, timer, kp, kecepatanbelokL, kecepatanbelokR, warna garis,index/plan/nomer mulai dari 0-255)
setting(120,80,not_set,not_set,10,5,kpgain,100,100,black,0);//index 0

//================================================================================
//==========================CONTOH PROGRAM========================================
/*
  Per3an Kanan
  setting(150,120,right,xorLL,12,5,kpgain,180,120,black,1);

  Per4an Kanan
  setting(150,120,right,per4an,12,5,kpgain,180,120,black,1);

  Siku Kanan
  setting(150,120,right,orLL,12,5,kpgain,180,120,black,1);

  Lancip Kanan
  setting(150,120,right,orLL,25,5,kpgain,180,120,black,1);

  Garis buntu putar balik Kanan
  setting(150,120,right,bleng,45,5,kpgain,180,120,black,1);

 

  Per3an Kiri
  setting(150,120,left,xorLL,12,5,kpgain,120,180,black,1);

  Per4an Kiri
  setting(150,120,left,per4an,12,5,kpgain,120,180,black,1);

  Siku Kiri
  setting(150,120,left,orLL,12,5,kpgain,120,180,black,1);

  Lancip Kiri
  setting(150,120,left,orLL,25,5,kpgain,120,180,black,1);

  Garis buntu putar balik Kiri
  setting(150,120,left,bleng,45,5,kpgain,180,120,black,1);

  Per4an Lurus 
  setting(150,120,lost,per4an,12,5,kpgain,180,120,black,1);

  Berhenti
  setting(150,120,stop,timeout,12,5,kpgain,180,120,black,1);

  Transisi dari garis hitam ke Putih
  setting(150,120,lost,per4an,12,5,kpgain,180,120,white,1);

  Transisi dari garis putih ke Hitam
  setting(150,120,lost,per4an,12,5,kpgain,180,120,black,1);
  
*/
}

void home(){
  int timescan=2000;
uint8_t h;
while(1){
u8g.firstPage(); 
do{
   h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.setPrintPos(5,1*h);
 u8g.print(" Chekpoint : ");
u8g.print(cp);
  u8g.setPrintPos(10,40*h);
  u8g.print("Aitunega AINO");
  
  scansensor();
}
while(u8g.nextPage());
if(swup()==0){delay(50);cp++; Serial.print("U");}
if(swdwn()==0){delay(50);cp--; Serial.print("D");}
if(cp>max_index){cp=0;}
if(cp<0){cp=max_index;}
if(swtab()==0){sensor_calibrate(timescan);}  
if(swen()==0){
file();
index=cp;
 u8g.firstPage();
do{
   h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.setPrintPos(25,2*h);
  u8g.print("Bismillah");
  u8g.setPrintPos(10,40*h);
  u8g.print("For Everything");
}
while(u8g.nextPage()); 
delay(50);
break;
}
}
}
void setup() {
io();
 u8g.firstPage();
  do{
    u8g.drawBitmapP(0,0,8,64,w2k);
    u8g.drawStr(70,20,"OS 1.2");
  }
  while(u8g.nextPage());
  delay(2000);
if(digitalRead(butonenter)==LOW){
set_serial();
}
baca_sens();
home();
}

void loop() {
run_program();


}
