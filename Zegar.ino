
int leds[]={3,4,5,6,7,8,9,10,11,12};
#define SIZE 10

void setup(){
  Serial.begin(57600);
  for(int i=0;i<SIZE;i++)
  pinMode(leds[i],OUTPUT);
  
  pinMode(A3, INPUT);    //restart sekund
  digitalWrite(A3,LOW);
}

int i,sek=0,odczyt=0;
int hh=13,mm=12,ss=45;

bool keydown(int key)
{
  if(digitalRead(key) == LOW)
  {
    while(digitalRead(key) == LOW)
      ss = 0;
    return true;
  }
  return false;
}

void loop(){   

if(odczyt == 0)
{
    //Obliczanie czasu    
    if(ss == 60)
      { 
       ++mm;
       ss = 0;
      }
    if(mm == 60)
      {
       ++hh;
       mm = 0;
      }
    if(hh > 12) hh = hh%12;
 
    //Godzina (na pinach 1-4):
    for(i=0;i<4;++i)
      digitalWrite(leds[i], (1<<i) & hh?HIGH:LOW);
     
   //Minuta (na pinach 5-10): 
    for(i=4;i<11;i++)
      digitalWrite(leds[i], (1<<(i-4)) & mm?HIGH:LOW);
          
    
   //Wypisanie na porcie szeregowym czasu postaci hh:mm:ss
   // przy prędkości: 57600 [baud == bit/sec. ]
    if(hh<10)
    {
      Serial.print("0");
      Serial.print(hh);
    }
    else  Serial.print(hh);
      Serial.print(":");
    if(mm<10)
    {
      Serial.print("0");
      Serial.print(mm);
    }
    else  Serial.print(mm);
      Serial.print(":");
    if(ss<10)
    {
      Serial.print("0");
      Serial.println(ss);
    }
    else  Serial.println(ss);

   
}
odczyt = 1;


//Timer (czas oczekiwania: 1[s] )
delay(1);
++sek;
if(sek == 1000) 
    {
      sek = 0;
      odczyt = 0;
      ++ss;
    }
 


if(keydown(A3)) 
  {
    ss = 0;
    odczyt = 0;
  }


}
