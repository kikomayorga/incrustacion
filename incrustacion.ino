#include <LowPower.h>

int gatillo_n = 0;
boolean cerebro = 0; 
boolean habil = 0; 



// entre 44 y 48 debe estar el mínimo. 

void setup() {
  // AO entrada gatillo
  // D10 salida PWM
  // D2 habilitador DOUT de GPS
  // D6 status energía cerebro
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  gatillo_n = analogRead(0) / 4;


  if(gatillo_n <= 48){
    gatillo_n = 48;
  }


  
  if(gatillo_n > 48){
    gatillo_n = 48 + ((gatillo_n - 48) * 3)/2; 
  }

  if(gatillo_n > 255){
    gatillo_n = 255; 
  }

  cerebro = digitalRead(3);
  habil = digitalRead(2);

  if(habil == 0){
    gatillo_n = 46;    
  }
  
  if(cerebro == 0){
    gatillo_n = 0;
    delay(50);
    Serial.println("entrando a sleep mode");
    delay(100);
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);   
  }


    
  analogWrite(10, gatillo_n);
  
  Serial.print("Gatillo n: ");
  Serial.print(gatillo_n);
  Serial.print("    Energía en Cerebro:    ");
  Serial.print(cerebro);
  Serial.print("    Habilitado por GPS:    ");
  Serial.println(habil);
  
}
