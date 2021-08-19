#include<Arduino.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

const byte max_index = 30;
int syart=0,speedgo,dep;
byte kp[max_index],speed1[max_index],speed2[max_index],dels[max_index],sensor[max_index],aksi[max_index];
byte line[max_index],timer[max_index],vl[max_index],vr[max_index];


void setting(byte kec1,byte kec2,byte act,byte sens,byte dell,byte timers,byte kkp,byte turnL,byte turnR,byte garis,byte x){
speed1[x]=kec1;
speed2[x]=kec2;
aksi[x]=act;
sensor[x]=sens;
dels[x]=dell;
kp[x]=kkp;
timer[x]=timers;
vl[x]=turnL;
vr[x]=turnR;
line[x]=garis;
}
void set_serial(){
int lock=1,data=0;
char inchar="";
uint8_t h;
while(1){
u8g.firstPage();
do{
   h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.setPrintPos(0,1*h);
  u8g.print("SET serial Mode");
  u8g.setPrintPos(0,3*h);
  u8g.print("index : ");
  u8g.print(data);
  u8g.setPrintPos(0,6*h);
  u8g.print("set : ");
  u8g.print(inchar); 
}
while(u8g.nextPage());

while (Serial.available() > 0) {
if(lock==1){data = Serial.read();lock=0;}
if(lock==0){inchar =  Serial.read();}
}
if(inchar=="delay"){
dels[data]=inchar;  
delay(200);
break;
}
if(inchar=="timer"){
timer[data]=inchar;  
delay(200);
break;
}
}
}

const uint8_t w2k []  PROGMEM= {

0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFD, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x01, 0xFF, 0xFC, 0x00,
0x00, 0x1F, 0xF0, 0x00, 0x00, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x0F, 0xFF, 0x00,
0x00, 0x00, 0xFC, 0x0F, 0xFE, 0x07, 0xFF, 0x80, 0x00, 0x01, 0xF8, 0x30, 0x0F, 0x81, 0xFF, 0x80,
0x00, 0x03, 0xF0, 0xC2, 0x01, 0xE0, 0xFF, 0xC0, 0x00, 0x07, 0xE1, 0x07, 0x00, 0x78, 0x7F, 0xE0,
0x00, 0x07, 0xC4, 0x0F, 0x80, 0x3C, 0x3F, 0xE0, 0x00, 0x0F, 0x80, 0x1F, 0x80, 0x1E, 0x1E, 0x00,
0x00, 0x0F, 0x00, 0x1F, 0xC0, 0x0F, 0x1F, 0x00, 0x00, 0x1F, 0x00, 0x3F, 0xE0, 0x07, 0x1F, 0x00,
0x00, 0x1E, 0x00, 0x7F, 0xF0, 0x03, 0x80, 0x00, 0x00, 0x3C, 0x00, 0xFF, 0xF0, 0x03, 0xC0, 0x00,
0x00, 0x3C, 0x01, 0xF8, 0xF8, 0x01, 0xC0, 0x00, 0x01, 0xF0, 0x03, 0xF0, 0x78, 0x01, 0x3F, 0xF0,
0x01, 0xF0, 0x07, 0xE0, 0x78, 0x00, 0x3F, 0xF0, 0x01, 0xF0, 0x0F, 0xE0, 0xF9, 0x00, 0xE1, 0xFE,
0x01, 0xF0, 0x0F, 0xC1, 0xF3, 0x80, 0x71, 0xFE, 0x00, 0x70, 0x1F, 0x03, 0xF3, 0xC0, 0x71, 0xFE,
0x00, 0x70, 0x1E, 0x03, 0xE3, 0xC0, 0x70, 0xFE, 0x00, 0x70, 0x1E, 0x07, 0xC3, 0xC0, 0x70, 0xFE,
0x00, 0xF0, 0x1C, 0x0F, 0xC1, 0xE0, 0x70, 0xFF, 0x00, 0xF0, 0x18, 0x1F, 0x81, 0xE0, 0x70, 0xFF,
0x00, 0xE0, 0x00, 0x3F, 0x03, 0xC0, 0x38, 0xFF, 0x00, 0xE0, 0x00, 0x7E, 0x07, 0xC0, 0x38, 0xFF,
0x00, 0xC0, 0x00, 0x7C, 0x1F, 0xC0, 0x70, 0xFF, 0x0F, 0xC0, 0x00, 0xF8, 0x3F, 0x80, 0x70, 0xFF,
0x0F, 0xC0, 0x01, 0xF0, 0x3F, 0x00, 0x70, 0xFF, 0x00, 0x00, 0x00, 0xE0, 0x3E, 0x00, 0x70, 0xFF,
0x00, 0x00, 0x00, 0x60, 0x7C, 0x00, 0x70, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x70, 0xFE,
0x00, 0xC0, 0x00, 0x01, 0xF8, 0x00, 0xE1, 0xFC, 0x00, 0x70, 0x00, 0x03, 0xF0, 0x00, 0xE3, 0xF8,
0x00, 0x78, 0x00, 0x07, 0xE0, 0x01, 0xE3, 0xF8, 0x00, 0x38, 0x40, 0x07, 0xE0, 0x01, 0xC3, 0xF8,
0x00, 0x38, 0x40, 0x0E, 0x70, 0x03, 0xC3, 0xFC, 0x00, 0x3C, 0x20, 0x0C, 0x30, 0x03, 0x83, 0xFC,
0x00, 0x3C, 0x10, 0x0C, 0x30, 0x07, 0x87, 0xFC, 0x00, 0x1E, 0x10, 0x0C, 0x30, 0x0F, 0x07, 0xF8,
0x00, 0x1E, 0x08, 0x0F, 0xF0, 0x1E, 0x0F, 0xF8, 0x00, 0x0F, 0x06, 0x07, 0xE0, 0x3C, 0x0F, 0xF0,
0x00, 0x0F, 0x83, 0x03, 0xC0, 0xF8, 0x1F, 0xF0, 0x00, 0x07, 0x80, 0xC0, 0x03, 0xF0, 0x3F, 0xE0,
0x00, 0x07, 0xC0, 0x78, 0x1E, 0x6F, 0xFC, 0x00, 0x00, 0x03, 0xE0, 0x1F, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x01, 0xF0, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x07, 0xF8, 0x00,
0x03, 0xFF, 0xFE, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x03, 0xFF, 0x80, 0x00, 0x1F, 0xFE, 0x00,
0x00, 0x03, 0xFF, 0xE0, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x07, 0xFF, 0xF8, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00
};