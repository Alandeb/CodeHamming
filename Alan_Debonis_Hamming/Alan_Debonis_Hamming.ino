#include <LiquidCrystal.h>

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_SELECT 4
#define BUTTON_NONE 5
/*********** Declaración de variables ********/
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int D1=-1;
int D2=-1;
int D3=-1;
int D4=-1;
int P1= 0;
int P2=0;
int P3=0;
int Display=0;
int select=0;
int leds[7]={13,12,11,10,A3,A4,A5};



int readButtons();
void printSelect();
void binaryData();
void Leds();
void showLeds();
void setup()
{
    for(int i=0; i<7; i++)
    {
      pinMode(leds[i], OUTPUT);
    }
    lcd.begin(16, 2);
}
int previousButton=BUTTON_NONE;
void loop()
{
      
   int currentButton = readButtons();
   if(currentButton==BUTTON_SELECT && previousButton==BUTTON_NONE)
   {
       select++;
       if(select == 3)
       {
          select = 0;
          digitalWrite(leds[0],0);
          digitalWrite(leds[1],0);
          digitalWrite(leds[2],0);
          digitalWrite(leds[3],0);
          digitalWrite(leds[4],0);
          digitalWrite(leds[5],0);
          digitalWrite(leds[6],0);
       }
   }
   previousButton = currentButton;
   switch (select)
   {
   case 0:
       printSelect();
       break;
   case 1:
       showDate();
       binaryData();
       break;
   case 2:
       if(D1==-1||D2==-1||D3==-1||D4==-1)
       {
         select=1;
         break;
       }
       Leds();
       showLeds();
       break;
   }
}
void printSelect()
{
  lcd.setCursor(0, 0);
  lcd.print("Precione Select.");
  D1=-1;
  D2=-1;
  D3=-1;
  D4=-1;
  P1=0;
  P2=0;
  P3=0;
  Display=0;
}

void showDate()
{
  lcd.setCursor(0,1);
  lcd.print("          ");
  lcd.setCursor(0,0);
  if(D1==-1)
  {
    lcd.print("*");
  }else
  {
    lcd.print(D1);
  }
  if(D2==-1)
  {
    lcd.print("*");
  }else
  {
    lcd.print(D2);
  }
  if(D3==-1)
  {
    lcd.print("*");
  }else
  {
    lcd.print(D3);
  }
  if(D4 == -1)
  {
    lcd.print("*");
  }else
  {
    lcd.print(D4);
  }
  lcd.print("                     ");
  lcd.setCursor(Display, 1);
  lcd.print("^");
}
int readButtons()
{
    int value = analogRead(0); // Leemos A0
    // Mis botones dan:  0, 145, 329,507,743
    // Y ahora los comparamos con un margen comodo
    if (value > 900)
        return BUTTON_NONE; // Ningun boton pulsado
    if (value < 50)
        return BUTTON_RIGHT;
    if (value < 250)
        return BUTTON_UP;
    if (value < 450)
        return BUTTON_DOWN;
    if (value < 650)
        return BUTTON_LEFT;
    if (value < 850)
        return BUTTON_SELECT;
    return BUTTON_NONE; // Por si todo falla
}
int previousButtonData=BUTTON_NONE;
void binaryData()
{
    int currentButton = readButtons();
    if (previousButtonData == BUTTON_NONE && currentButton != BUTTON_NONE)
    {
        switch (currentButton)
        {
        case BUTTON_UP:
            switch (Display)
            {
              case 0:
                D1++;
                if (D1==2)
                  D1=0;
                break;
              case 1:
                D2++;
                if (D2==2)
                  D2=0;
                break;
              case 2:
                D3++;
                if(D2==2)
                  D3=0;
                break;
              case 3:
                D4++;
                if(D4==2)
                  D4=0;
                break;
            }
           break;
        case BUTTON_DOWN:
            switch (Display)
            {
              case 0:
                D1--;
                if(D1==-2){
                  D1=1;
                }else if(D1==-1)
                  D1=1;
                break;
              case 1:
                D2--;
                if(D2==-2){
                  D2= 1;
                }else if(D2==-1)
                  D2=1;
                break;
              case 2:
                D3--;
                if(D3==-2){
                  D3=1;
                }else if(D3==-1)
                  D3=1;
                break;
              case 3:
                D4--;
                if(D4==-2){
                  D4=1;
                }else if(D4==-1)
                  D4=1;
                break;
            }
            break;
        case BUTTON_LEFT:
            Display--;
            if(Display==-1)
              Display=3;
            break;
        case BUTTON_RIGHT:
            Display++;
            if (Display==4)
              Display=0;
            break;
        }
    }
    previousButtonData=currentButton;
}

void Leds()
{
  if ((D1==0&&D2==0&&D4==1)
    ||(D1==0&&D2==1&&D4==0)
    ||(D1==1&&D2==1&&D4==1)
    ||(D1==1&&D2==0&&D4==0))
  {
    P1= 1;
  }
  if ((D1==0&&D3==0&&D4==1) 
    ||(D1==0&&D3==1&&D4==0) 
    ||(D1==1&&D3==1&&D4==1) 
    ||(D1==1&&D3==0&&D4==0))
  {
    P2=1;
  }
  if ((D2==0&&D3==0&&D4==1)
    ||(D2==0&&D3==1&&D4==0) 
    ||(D2==1&&D3==1&&D4==1) 
    ||(D2==1&&D3==0&&D4==0))
  {
    P3=1;
  }
}
void showLeds()
{
  lcd.setCursor(0,0);
  lcd.print(P1);
  lcd.print(P2);
  lcd.print(D1);
  lcd.print(P3);
  lcd.print(D2);
  lcd.print(D3);
  lcd.print(D4);
  lcd.setCursor(0,1);
  lcd.print("        ");
  digitalWrite(leds[0],P1);
  digitalWrite(leds[1],P2);
  digitalWrite(leds[2],D1);
  digitalWrite(leds[3],P3);
  digitalWrite(leds[4],D2);
  digitalWrite(leds[5],D3);
  digitalWrite(leds[6],D4);
}
