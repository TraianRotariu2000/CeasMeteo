#include <EEPROM.h>
#include <RTClib.h>
#include <dht.h>

#define LED1_TEMP 12
#define LED2_TEMP 13
#define LED1_UMID 9
#define LED2_UMID 10
#define pin_senzor A0
//default parametrii vor fi initializati cu capetele domeniului de masurare al senzorului DHT11
float lim_sup_temp=60;
float lim_inf_temp=0;
float lim_sup_umid=90;
float lim_inf_umid=20;

RTC_DS3231 rtc;
dht senzor;
char zileleSapt[7][4] = {
  "Dum",
  "Lun",
  "Mar",
  "Mie",
  "Joi",
  "Vin",
  "Sam"
};
void memSave(){
  
}
void setup(){
  float aux=-1;
  int adr=0;
  int optiune=0;
  pinMode(LED1_TEMP, OUTPUT);
  pinMode(LED2_TEMP, OUTPUT);
  pinMode(LED1_UMID, OUTPUT);
  pinMode(LED2_UMID, OUTPUT);
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Eroare: Modulul RTC nu a fost gasit. Se vor afisa doar temperatura si umiditatea!");
    Serial.flush();
  }
  else{
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } 
  
  Serial.setTimeout(5000);
  Serial.println("Selectati o actiune sau astepati initializarea sistemului:\n 1.Resetare limite (tastati 1)\n 2.Modificare limite (tastati 2)");
  optiune=Serial.parseInt();
  delay(5000);
  Serial.println(optiune);
  if(optiune == 1){
    Serial.println("-------Resetare limite--------- ");
    EEPROM.put(adr, lim_inf_temp);
    adr=adr+sizeof(float);
    EEPROM.put(adr, lim_sup_temp);
    adr=adr+sizeof(float);
    EEPROM.put(adr, lim_inf_umid);
    adr=adr+sizeof(float);
    EEPROM.put(adr, lim_sup_umid);
  }
  else if(optiune==2){
      Serial.println("-------Setare limite--------- \n Introduceti temperatura minima (grade Celsius):");
      aux = Serial.parseFloat();
      if(aux <=60 && aux >= 0.01)
      {
        lim_inf_temp = aux;
        EEPROM.put(adr, lim_inf_temp);
         adr=adr+sizeof(float);
      } 
      delay(5000);
      Serial.println("Introduceti temperatura maxima (grade Celsius):");
      aux=Serial.parseFloat();
      if(aux <=60 && aux >= 0.01 && aux >= lim_inf_temp)
      {
        lim_sup_temp = aux;
        EEPROM.put(adr, lim_sup_temp);
        adr=adr+sizeof(float);
      }
      delay(5000);
      Serial.println("Introduceti umiditatea minima (procente):");
      aux = Serial.parseFloat();
      if(aux <=90 && aux >= 20)
      {
        lim_inf_umid = aux;
        EEPROM.put(adr, lim_inf_umid);
        adr=adr+sizeof(float);
      }
  
      delay(5000);
      Serial.println("Introduceti umiditatea maxima (procente):");
      aux=Serial.parseFloat();
      if(aux <=90 && aux >= 20 && aux >= lim_inf_umid)
      {
        lim_sup_umid=aux;
        EEPROM.put(adr, lim_sup_umid);
      }
  }

  delay(5000);
}
 
void loop(){
  int adr=3*sizeof(float);
  EEPROM.get(adr, lim_sup_umid);
  adr=adr-sizeof(float);
  EEPROM.get(adr, lim_inf_umid);
  adr=adr-sizeof(float);
  EEPROM.get(adr, lim_sup_temp);
  adr=adr-sizeof(float);
  EEPROM.get(adr, lim_inf_temp);
  DateTime now = rtc.now();
  Serial.print("Data si ora masuratorii: ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" (");
  Serial.print(zileleSapt[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  //Afisare temperatura si umiditate
  senzor.read11(pin_senzor);
  Serial.print("Unmiditate: ");
  Serial.print(senzor.humidity);
  Serial.print("%  ");
  Serial.print("Temperatura: ");
  Serial.print(senzor.temperature); 
  Serial.println(" C ");
  Serial.println("Limitele setate:");
  Serial.print(" temperatura: ");
  Serial.print(lim_inf_temp);
  Serial.print(" C ");
  Serial.print(" - ");
  Serial.print(lim_sup_temp);
  Serial.println(" C ");
  Serial.print(" umiditate: ");
  Serial.print(lim_inf_umid);
  Serial.print("% ");
  Serial.print(" - ");
  Serial.print(lim_sup_umid);
  Serial.println("% ");
  Serial.println("\n");
 
  if((senzor.temperature >= lim_inf_temp) && (senzor.temperature <= lim_sup_temp))
  {
    digitalWrite(LED1_TEMP, LOW);
    delay(500);
    digitalWrite(LED2_TEMP, HIGH); 
  }
  else{
    digitalWrite(LED2_TEMP, LOW);
    delay(1000); 
    digitalWrite(LED1_TEMP, HIGH);
    
  }
 
  if((senzor.humidity >= lim_inf_umid) && (senzor.humidity <= lim_sup_umid)){
    digitalWrite(LED1_UMID, LOW);
    delay(500);
    digitalWrite(LED2_UMID, HIGH); 
  }
  else{
    digitalWrite(LED2_UMID, LOW);
    delay(500);
    digitalWrite(LED1_UMID, HIGH);
  }
  delay(30000);//Masuratorile se vor efectua la 30 secunde
}
