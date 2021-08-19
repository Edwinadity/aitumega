#include "Arduino.h"
#include "setting.h"

#include <EEPROM.h>
#include <Wire.h>


const byte slek1=A1;//selektor a
const byte slek2=A2;//selektor b
const byte slek3=A3;//selektor c 
const byte start_addres=5;
byte timerun,index,kabur,cp;
const byte maze=1,kdgain=50,kpgain=10,line_pwm=255;
int cacah,time_lop;
//--------------------------
byte max_jump=150;
byte slow;
byte speed_step=110;
#define ldir       7
#define lpwm_pin   6
#define rpwm_pin   5
#define rdir       4
#define led_timer 2
#define switching 13
#define butonenter 8
#define butonup 10
#define butondwn 3
//==================================== variable ==========================================
int peka[15],mripat;
int er,pv,salp,sald,lastcild,lpwm,rpwm;

const byte barlow[]   U8G_PROGMEM={0x00,0x00};
const byte barhigh[]   U8G_PROGMEM={
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff,
 0xff,0xff
 };
//===================================================
void save_sensor(){
for(int c=0;c<15;c++){
 EEPROM.write(start_addres+c,peka[c]);} 
}

void baca_sens(){
 for(int c=0;c<15;c++){
peka[c] = EEPROM.read(start_addres+c);} 
} 

//======================================================
boolean swdwn(){
 boolean data=1;
  if(digitalRead(butondwn)==LOW)data=0;
  else data=1;
  return data; 
}
boolean swup(){
 boolean data=1;
  if(digitalRead(butonup)==LOW)data=0;
  else data=1;
  return data; 
}
boolean swen(){
 boolean data=1;
  if(digitalRead(butonenter)==LOW)data=0;
  else data=1;
  return data; 
}
boolean swtab(){
boolean data=1;
  if(digitalRead(9)==LOW)data=0;
  else data=1;
  return data; 
}

unsigned char read_adc(unsigned char adc_input)
{
byte data=map(analogRead(adc_input),0,1023,0,255);
return data;
}
void aktife(int c,int b,int a){
  digitalWrite(slek1,a);
  digitalWrite(slek2,b); 
  digitalWrite(slek3,c);
}
int read_mux(int input){
int data;
switch(input){
case 0:  aktife(0,0,0);  break;  //X0
case 1:  aktife(0,0,1);  break;  //X1
case 4:  aktife(0,1,0);  break;  //X2
case 5:  aktife(0,1,1);  break;  //X3
case 2:  aktife(1,0,0);  break; //X4
case 3:  aktife(1,0,1);  break; //X5
case 6:  aktife(1,1,0);  break;  //x6

case 7:   aktife(0,0,0);  break;  //X0
case 8:   aktife(0,0,1);  break;  //X1
case 11:   aktife(0,1,0);  break;  //X2
case 12:  aktife(0,1,1);  break;  //X3
case 9:  aktife(1,0,0);  break; //X4
case 10:  aktife(1,0,1);  break; //X5
case 13:  aktife(1,1,0);  break;  //x6
delayMicroseconds(80);
}
if(input<7) data=read_adc(A6);
else data=read_adc(A7);
return data;
}
void bar_lcd(unsigned char input,unsigned char x){
if(input==0){u8g.drawBitmapP(x,33,1,1,barlow);}
else{u8g.drawBitmapP(x,20,1,13,barhigh);}
}  
void scansensor(){
int in=0,x;
for(int adc=0;adc<14;adc++){
x=adc;
in=read_mux(adc);  
if(adc==0){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}
}
if(adc==1){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==2){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==3){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==4){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==5){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==6){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==7){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==8){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==9){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==10){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==11){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==12){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
if(adc==13){if(in>peka[adc]){bar_lcd(1,x*9);}
else{bar_lcd(0,x*9);}}
}
}
void aut(unsigned char kecc,unsigned int k,unsigned int d){
er=0-pv;
salp=(int)er*k;
sald=(int)(er-lastcild)*d;
lastcild=er;
rpwm=(int)kecc+salp+sald;
lpwm=(int)kecc-salp-sald;
}
unsigned int read_sensor(){
unsigned int input=0,x=0;
int pecah=0;
int in=0;
for(int adc=0;adc<14;adc++){
in=read_mux(adc);     
if(adc==0){if(in>peka[adc]){pecah=pecah+1;}}
if(adc==1){if(in>peka[adc]){pecah=pecah+2;}}
if(adc==2){if(in>peka[adc]){pecah=pecah+4;}}
if(adc==3){if(in>peka[adc]){pecah=pecah+8;}}
if(adc==4){if(in>peka[adc]){pecah=pecah+16;}}
if(adc==5){if(in>peka[adc]){pecah=pecah+32;}}
if(adc==6){if(in>peka[adc]){pecah=pecah+64;}}
if(adc==7){if(in>peka[adc]){pecah=pecah+128;}}  
if(adc==8){if(in>peka[adc]){pecah=pecah+256;}}
if(adc==9){if(in>peka[adc]){pecah=pecah+512;}}
if(adc==10){if(in>peka[adc]){pecah=pecah+1024;}}
if(adc==11){if(in>peka[adc]){pecah=pecah+2048;}}
if(adc==12){if(in>peka[adc]){pecah=pecah+4096;}}
if(adc==13){if(in>peka[adc]){pecah=pecah+8192;}}
delayMicroseconds(80);
}
dep=pecah;
mripat=dep;
return pecah;
}
void error_in(byte color){
 int byte_byte=read_sensor();
if(color==1){
byte_byte=16383-dep;
mripat=16383-dep;
}
switch(byte_byte){
 case 0b00000000000001:       pv=-20;   break;
 case 0b00000000000011:       pv=-19;   break; 
 case 0b00000000000010:       pv=-18;   break;
 case 0b00000000000110:       pv=-16;   break;
 case 0b00000000000100:       pv=-14;   break;
 case 0b00000000001100:       pv=-12;   break;
 case 0b00000000001000:       pv=-8;   break;
 case 0b00000000011000:       pv=-6;   break;
 case 0b00000000010000:       pv=-5;   break;
 case 0b00000000110000:       pv=-4;   break;
 case 0b00000000100000:       pv=-3;   break;
 case 0b00000001100000:       pv=-2;    break;
 case 0b00000001000000:       pv=-1;    break;
 case 0b00000011000000:       pv=0;    break;

 case 0b00000010000000:       pv=1;    break; 
 case 0b00000110000000:       pv=2;    break; 
 case 0b00000100000000:       pv=3;    break; 
 case 0b00001100000000:       pv=4;    break;
 case 0b00001000000000:       pv=5;    break;
 case 0b00011000000000:       pv=6;    break;
 case 0b00010000000000:       pv=8;   break; 
 case 0b00110000000000:       pv=12;   break;
 case 0b00100000000000:       pv=14;   break;
 case 0b01100000000000:       pv=16;   break;
 case 0b01000000000000:       pv=18;   break;
 case 0b11000000000000:       pv=19;   break;
 case 0b10000000000000:       pv=20;   break;


case 0b00000111100000:       pv=0;     break;
}
}
void motor(int LPWM,int RPWM,int MAXPWM){
  if(MAXPWM>255)MAXPWM=255;
  if(MAXPWM<0)MAXPWM=0;
  if(LPWM>MAXPWM)LPWM=MAXPWM;
  if(LPWM<-MAXPWM)LPWM=-MAXPWM;
  if(RPWM>MAXPWM)RPWM=MAXPWM;
  if(RPWM<-MAXPWM)RPWM=-MAXPWM;
     
if(LPWM==0){ 
analogWrite(lpwm_pin,0); 
digitalWrite(ldir, LOW); 
}
if(LPWM>0){ 
analogWrite(lpwm_pin,LPWM); 
digitalWrite(ldir, LOW); 
}
if(LPWM<0){ 
analogWrite(lpwm_pin,+LPWM); 
digitalWrite(ldir, HIGH); 
}

if(RPWM==0){ 
analogWrite(rpwm_pin,0); 
digitalWrite(rdir, LOW); 
}
if(RPWM>0){ 
analogWrite(rpwm_pin,RPWM);
digitalWrite(rdir, LOW); 
}
if(RPWM<0){ 
analogWrite(rpwm_pin,+RPWM); 
digitalWrite(rdir, HIGH); 
}
}
void sensor_calibrate(int del){
int i,delcek=0;
uint8_t h;
unsigned char high[16],low[16],adc_input;
for(i=0;i<16;i++){
        peka[i]=0;
        low[i]=255;
        high[i]=0;
        }
u8g.firstPage();
    do{
     h = u8g.getFontAscent()-u8g.getFontDescent();
     u8g.setFont(u8g_font_ncenB10);
     u8g.drawStr(10,4*h,"Calibrating..");
    }
    while(u8g.nextPage());
    
while(1){
for(i=0;i<14;i++){
adc_input=read_mux(i);   

if(adc_input<low[i]){
low[i]=adc_input;           
}
if(adc_input>high[i]){
high[i]=adc_input;        
}
delayMicroseconds(10);
}
for(int b=0;b<16;b++){
peka[b]=(high[b]-low[b])/2+low[b];
}
delcek++;   
if(delcek>=del){
save_sensor();
break;
}
}
}
void bersih(){
er=0;
pv=0;
lastcild=0;
motor(0,0,0);  
}
void io(){
Wire.begin();
Serial.begin(9600);
u8g.setRot180();

pinMode(slek1,OUTPUT);
pinMode(slek2,OUTPUT);
pinMode(slek3,OUTPUT);
digitalWrite(slek1,HIGH);  
digitalWrite(slek2,HIGH);  
digitalWrite(slek3,HIGH);
pinMode(butonenter,INPUT);
pinMode(butonup,INPUT);
pinMode(butondwn,INPUT);
pinMode(9,INPUT);
pinMode(led_timer,OUTPUT);
digitalWrite(led_timer,LOW);
digitalWrite(butonenter, HIGH);
digitalWrite(butonup, HIGH);
digitalWrite(butondwn, HIGH);
digitalWrite(9, HIGH);

pinMode( ldir, OUTPUT);
pinMode( lpwm_pin, OUTPUT);
pinMode( rpwm_pin, OUTPUT);
pinMode( rdir, OUTPUT);
digitalWrite( ldir, LOW);
digitalWrite( lpwm_pin, LOW);
digitalWrite( rpwm_pin, LOW);
digitalWrite( rdir, LOW);
pinMode(switching,OUTPUT);
digitalWrite(switching,HIGH);
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x07;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;
TIMSK2=0x02;
cacah=time_lop=index=0;
syart=0;
cp=0;
u8g.setFont(u8g_font_ncenB10);
}
void jalan(byte kecepatan1,byte kp,byte kd,byte linex,byte pwms){
error_in(line[index]);
aut(kecepatan1,kp,kd);
if(lpwm>255)lpwm=255;
if(rpwm>255)rpwm=255;
if(lpwm<-255)lpwm=-255;
if(rpwm<-255)rpwm=-255;
motor(lpwm,rpwm,pwms);
}
void loop_stop(){
uint8_t h;
timerun=0;
cacah=0;
time_lop=0;
lpwm=0;
rpwm=0;
motor(0,0,0);
while(1){
u8g.firstPage(); 
do{
   h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.setPrintPos(0,2*h);
  u8g.print("MISION COMPLITED");
  u8g.setPrintPos(0,3*h);
  u8g.print("STOP");
}
while(u8g.nextPage());
}
}

void run_program(){
if(slow==1)speedgo=speed_step;
if(slow==0&&time_lop<timer[index]){speedgo=speed1[index];}
if(slow==0&&time_lop>=timer[index]){
speedgo=speed2[index];
}

jalan(speedgo,kp[index],kdgain,line[index-1],255);

int LL = mripat & 0b00000000000111;
int CC = mripat & 0b00000111100000;
int RR = mripat & 0b11100000000000;

int L = mripat &  0b00000000000011;
int R = mripat &  0b11000000000000;

if(sensor[index+1]==1){// xor pertigaan kiri
if(LL&&CC&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==2){// xor pertigaan kanan
if(RR&&CC&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==3){// prempatan/ T
if(LL&&RR&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==4){// or kiri
if(L&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==5){ // or kanan
if(R&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==6){// bleng
if(mripat==0&&time_lop>=timer[index]){syart=1;
index++;
}
}
if(sensor[index+1]==7){// time out
if(time_lop>=timer[index]){syart=1;
index++;
}
}
if(syart==1){
if(aksi[index]==0){
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==1){
  int vll,vrr;
   motor(0,0,0);
  delay(tunda[index]);
vll=vl[index];vrr=vr[index];
motor(-vll,vrr,line_pwm);
int del2=dels[index]*10;
delay(del2);
bersih();
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==2){
  int vll,vrr;
   motor(0,0,0);
  delay(tunda[index]);
vll=vl[index];vrr=vr[index];
motor(vll,-vrr,line_pwm);
int del2=dels[index]*10;
delay(del2);
bersih();
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==3){
  int vll,vrr;
vll=vl[index];vrr=vr[index];
motor(vll,vrr,line_pwm);
int del2=dels[index]*10;
delay(del2);
bersih();
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==4){
int vll,vrr;
vll=vl[index];vrr=vr[index];
motor(-vll,-vrr,line_pwm);
int del2=dels[index]*10;
delay(del2);
bersih();
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==5){
motor(0,0,0);
bersih();
loop_stop();
cacah=0;
time_lop=0;syart=0;
}

if(aksi[index]==6){//pick up
motor(0,0,0);
delay(1000);
Serial.print('U');
int del2=dels[index]*10;
delay(del2);
bersih();
loop_stop();
cacah=0;
time_lop=0;syart=0;
}
if(aksi[index]==7){//drop
motor(0,0,0);
delay(1000);
Serial.print('D');
int del2=dels[index]*10;
delay(del2);
bersih();
loop_stop();
cacah=0;
time_lop=0;syart=0;
}

}

}


ISR(TIMER2_COMPA_vect) {
if(speed1>max_jump&&time_lop<=2){
  slow=1;
}
if(speed1<max_jump||speed1>max_jump&&time_lop>2){
  slow=0;
}

if(timerun==1){
if(cacah++>=5){
time_lop++;cacah=0;
}
}
if(time_lop<timer[index]){timerun=1;digitalWrite(led_timer,HIGH);}
else if(time_lop>=timer[index]){timerun=0;digitalWrite(led_timer,LOW);}
}
