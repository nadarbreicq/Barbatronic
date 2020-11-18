#include <TimeLib.h>
#include <avr/sleep.h>

int hourPin[12] = {2,1,0,13,12,11,10,9,6,5,4,3};
const int button = 14;

void displayHour(int hours, int minutes);
void flushDisplay();

ISR(PORTA_PORT_vect) {
  PORTA.INTFLAGS = PORT_INT1_bm;
}

void setup() 
{
  pinMode(button,INPUT_PULLUP);
  for(int i = 0; i<=11;i++)
  {
    pinMode(hourPin[i],OUTPUT);
  }
  hourFormat12();
  setTime(11,52,0,20,8,2020);
  
  set_sleep_mode(SLEEP_MODE_STANDBY);
  sleep_enable();
}

void loop()
{
  if(!digitalRead(button))
  {
    displayHour(hour(),minute(),1000);
    flushDisplay();
  }
  PORTA.PIN1CTRL = PORT_PULLUPEN_bm | PORT_ISC_LEVEL_gc;
  sleep_cpu();
  PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
}

void displayHour(int hours, int minutes, int displayTime)
{
  int recalMinutes = minutes/5 ;
  int blinkNum  = displayTime/100;
  int blinkTime = displayTime/(blinkNum*2);
  
  //Affichage des heures
  if(hours==0)digitalWrite(hourPin[12],HIGH);
  else digitalWrite(hourPin[hours-1],HIGH);

  //Affichage des minutes
  if(recalMinutes==0) recalMinutes = 13;

  for(int i = 0;i<=blinkNum;i++)
    {
      digitalWrite(hourPin[recalMinutes-1],HIGH);
      delay(blinkTime);
      digitalWrite(hourPin[recalMinutes-1],LOW);
      delay(blinkTime);
    }
}

void flushDisplay()
{
  for(int i = 0; i<=11;i++)digitalWrite(hourPin[i],LOW);
}
