#include <AccelStepper.h>
//This software is pre version of final version. So it is not including advanced improvements.
//potans =potansiyometre

int potansPin1 = A0;
int potansVspeed = 0;
int potansDeger = 0;

#define BUTTON_PIN 4 //button 4. pine baglı 
#define BUTTON_PIN2 3 //ileri geri vites buton
int sayac =-1; //counter eklenip ciftse ileri mod - tekse geri mod olabilir

AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 3, 4, 5); //drive
//AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);//drive

void setup() {
      Serial.begin(9600);
     pinMode(BUTTON_PIN, INPUT_PULLUP);//butondan veri gelceğini ifade ediyor-on off
    pinMode(BUTTON_PIN2, INPUT_PULLUP);//butondan veri gelceğini ifade ediyor-vites

    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper1.moveTo(1000000);
}


void loop() {
 byte buttonState = digitalRead(BUTTON_PIN);//start stop
 byte buttonState2 = digitalRead(BUTTON_PIN2);//ileri geri vites
Serial.print("Sayac ileri geri vites durum degeri "); Serial.println(sayac);
  if (buttonState == HIGH) {
Serial.print("Acil Durdurma"); 
    stepper1.setMaxSpeed(0);
    stepper1.run();
delay(2000);
//step hız 0 seyı ekle
sayac++;//ileri geri vites
  }
 else {
 Serial.print("Arac hareket edebilir ");
 //gaz potansyiometre yoksa arac durur
if(sayac %2 == 0) 
{ 
    Serial.print("Step motor ileri gidiyor: ");
potansDeger = analogRead(potansPin1);//potansiyometre deger okumak
potansVspeed = map(potansDeger, 50, 1023, 20, 500);//0la 1023 aralığında gelen analog değeri 50-500rpm hız degerine ceviriyoruz
Serial.print("Potans hiz degeri: "); Serial.println(potansVspeed); 
    stepper1.setMaxSpeed(potansVspeed);
    stepper1.run();
delay(500);
//step.Run kodu olacak burada

}

else if(sayac %2 == 1){
Serial.print("Arac geri gidiyor: ");    
potansDeger = analogRead(potansPin1);//potansiyometre deger okumak
potansVspeed = map(potansDeger, 20, 1023, 20, 200);//0la 1023 aralığında gelen analog değeri 50-200rpm hız degerine ceviriyoruz
Serial.print("Potans hiz degeri: "); Serial.println(potansVspeed); 
    stepper1.setMaxSpeed(potansVspeed);
    stepper1.run();
delay(500);
}
//burada 10 adım ve set.Speed() olayı olmalı ama simdilik prınt yazdır ile
}

  if (buttonState2 == HIGH) {
    sayac++;
  }
delay(200);
 
}
