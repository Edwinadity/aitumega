/*
  Servo controller arduino nano
  Author: Edwin Aditya S P
  Date : 10 Feb 2021

  Source code sepenuhnya milik AITUMEGA
  Tidak diperuntukan untuk resfrensi pemrograman,
  Tidak mengambil sebagian atau seluruhnya dan 
  Tidak memperjual belikan source code ini.
*/

#include <Servo.h>
Servo c;
Servo l;
Servo r;
int in_id='X';

void program(){
while (Serial.available() > 0) {
int inchar = Serial.read();
if(inchar==in_id){//ambil
 c.write(40);
delay(1000);
l.write(170);
r.write(110);
delay(2000);
c.write(180);
Serial.print('B');
}
if(inchar=='S'){
c.write(180);
delay(100);
l.write(80);
r.write(180);
}  
else{if(inchar=='Y'){//taruh
 c.write(40);
delay(1000);
l.write(80);
r.write(180);
delay(100);
Serial.print('B');
}
}
}
}  


void setup() {
Serial.begin(9600);
c.attach(6);//servo japit di pin D6
l.attach(5);//servo tengah di pin D5
r.attach(7);

/* 
logika standby servo :
saat robot di hidupkan posisi griper harus tengah naik kebelakang ,capit renggang
jika tidak seperti itu perbaiki dengan menyesuaikan posisi baut servo bukan merubah program
 */ 

 
c.write(180);
delay(500);
l.write(80);
r.write(180);
}

void loop() {
 program();
}
