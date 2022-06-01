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

float aux;
RTC_DS3231 rtc;
dht senzor;
char zileleSapt[7][12] = {
  "Dum",
  "Lun",
  "Mar",
  "Mie",
  "Joi",
  "Vin",
  "Sam"
};
 
void setup(){
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
  Serial.setTimeout(10000);
  Serial.println("Introduceti temperatura minima (grade Celsius):");
  aux = Serial.parseFloat();
  if(aux <=60 && aux >= 0)
  {
    lim_inf_temp = aux;
  }
  delay(10000);
  Serial.println("Introduceti temperatura maxima (grade Celsius):");
  aux=Serial.parseFloat();
  if(aux <=60 && aux >= 0 && lim_sup_temp >= lim_inf_temp)
  {
    lim_sup_temp=aux;
  }
  delay(10000);
  Serial.println("Introduceti umiditatea minima (procente):");
  aux = Serial.parseFloat();
  if(aux <=90 && aux >= 20)
  {
    lim_inf_umid = aux;
  }
  delay(10000);
  Serial.println("Introduceti umiditatea maxima (procente):");
  aux=Serial.parseFloat();
  if(aux <=90 && aux >= 20 && lim_sup_umid >= lim_inf_umid)
  {
    lim_sup_umid=aux;
  }
  delay(10000);
  
}
 
void loop(){
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
  Serial.println("Parametrii de functionare:");
  Serial.print(" T_min: ");
  Serial.print(lim_inf_temp);
  Serial.println(" C ");
  Serial.print(" T_max: ");
  Serial.print(lim_sup_temp);
  Serial.println(" C ");
  Serial.print(" Humid_min: ");
  Serial.print(lim_inf_umid);
  Serial.println("% ");
  Serial.print(" Humid_max: ");
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
    delay(500); 
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