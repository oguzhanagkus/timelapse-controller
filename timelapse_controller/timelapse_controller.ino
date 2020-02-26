/*

  This project developed by Oguzhan Agkus.
  You can use it yourself.
  If you find a bug, you can contact me from "agkusoguzhan@gmail.com"
  Check readme file for necessary explanation.
  
*/

#include <LiquidCrystal.h>

#define POTENTIOMETER 8
#define CANCEL 39
#define ENTER 40
#define RELAY 6
#define RW 35
#define BACKLIGHT 31
#define TRIGGER 100
#define BUTTON 200
#define WAIT 3000
#define SECOND_TO_MILISECOND 1000

void menu();
void opening_screen();
void timelapse_mode();
void bulb_mode();
int check_buttons();
unsigned long set_interval();
unsigned long set_shot_count();
void show_summary(unsigned long interval, unsigned long shot_count);

LiquidCrystal lcd(36,37,26,27,28,29); // LCD Setup

byte arrow[8] = {B00000, B00100, B00010, B11111, B00010, B00100, B00000, B00000}; // Arrow in the menu

void setup()
{
  pinMode(POTENTIOMETER, INPUT);
  pinMode(CANCEL, INPUT);
  pinMode(ENTER, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT);

  digitalWrite(RW, LOW);
  digitalWrite(BACKLIGHT,HIGH);

  lcd.begin(16, 2);
  lcd.createChar(1, arrow);

  opening_screen();
}

void loop()
{
  menu();
}

/*

  This funtion make you use the menu.
  Show the modes, when any is chosen related function called.

*/

void menu()
{
  int choice = 0;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(" Timelapse Mode");
  lcd.setCursor(0, 1); lcd.print(" Bulb Mode");

  while(true)
  {
    choice = analogRead(POTENTIOMETER);

    if(choice > 511)
    {
      lcd.setCursor(0, 0); lcd.write(1);
      lcd.setCursor(0, 1); lcd.print(" ");
    }

    else
    {
      lcd.setCursor(0, 0); lcd.print(" ");
      lcd.setCursor(0, 1); lcd.write(1);
    }

    if(digitalRead(ENTER))
    {
      delay(BUTTON); break;
    }
  }

  if(choice > 511)
    timelapse_mode();

  else
   bulb_mode();
}

/*

  Opening screen messages.

*/

void opening_screen()
{
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("\"In A Timelapse\"");
  lcd.setCursor(0, 1); lcd.print("    Wellcome ");
  delay(WAIT);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Use buttons and");
  lcd.setCursor(0, 1); lcd.print("potentiometer.");
  delay(WAIT);
}

/*

  This funciton provide to use timelapse mode.
  Working principle is given on top.

*/

void timelapse_mode()
{
  unsigned long shot_count = 1, interval = 1;

  interval = set_interval();
  shot_count = set_shot_count();

  show_summary(interval, shot_count);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Enter to start.");
  lcd.setCursor(0, 1); lcd.print("Down to cancel.");

  if(check_buttons() == 1)
    return;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("It will start");
  lcd.setCursor(0, 1); lcd.print("in 3 seconds.");
  delay(WAIT);

  digitalWrite(BACKLIGHT, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Left: ");

  while(shot_count > 0)
  {
    digitalWrite(RELAY, HIGH);
    delay(TRIGGER);
    digitalWrite(RELAY, LOW);

    shot_count--;

    lcd.setCursor(6, 0); lcd.print("   ");
    lcd.setCursor(6, 0); lcd.print(shot_count);

    delay(interval * SECOND_TO_MILISECOND);
  }

  digitalWrite(BACKLIGHT, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Capture");
  lcd.setCursor(0, 1); lcd.print("finished.");
  lcd.setCursor(15, 1);

  check_buttons();
}

/*

  This funciton provide to use bulb mode.
  When you pressed enter, it starts.
  Until you press enter again, it continues.

*/

void bulb_mode()
{
  unsigned long start = 0, time = 0;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Enter to start.");
  lcd.setCursor(0, 1); lcd.print("Down to back.");

  if(check_buttons() == 1)
    return;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Capture started.");
  lcd.setCursor(0, 1); lcd.print("Enter to stop.");

  start = millis();
  digitalWrite(RELAY, HIGH);

  check_buttons();

  digitalWrite(RELAY, LOW);
  time =  millis() - start; Serial.print(time);
  time /= SECOND_TO_MILISECOND;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Capture lasted");
  lcd.setCursor(0, 1); lcd.print(time); lcd.print(" seconds.");

  check_buttons();
}

/*

  When this funciton is called. It wait for a button to push.
  If cancel is pushed it returns 1.
  If enter is pushed it returns 0.

*/

int check_buttons()
{
  while(true)
  {
    if(digitalRead(ENTER))
    {
      delay(BUTTON); return 0;
    }

    if(digitalRead(CANCEL))
    {
      delay(BUTTON); return 1;
    }
  }
}

/*

  This function help you to set interval.
  When you turn the potentiometer, the value in the screen will increase or decrease by 5.
  It increase or decrease by 1 between 1-5.
  When you pressed enter, it returns the interval you set.

*/

unsigned long set_interval()
{
  unsigned long interval = 1;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Interval: ");
  lcd.setCursor(0, 1); lcd.print(interval);
  lcd.setCursor(4, 1); lcd.print("seconds");

  while(true)
  {
    interval = map(analogRead(POTENTIOMETER), 0, 1023, 0, 60);
    interval = interval * 5;

    if(interval == 0)
      interval = map(analogRead(POTENTIOMETER), 0, 12, 1, 4);

    if(digitalRead(ENTER))
    {
      delay(BUTTON); break;
    }

    lcd.setCursor(0, 1); lcd.print("   ");
    lcd.setCursor(0, 1); lcd.print(interval);
    delay(BUTTON);
  }

  return interval;
}

/*

  This function help you to set shot count.
  When you turn the potentiometer, the value in the screen will increase or decrease by 5.
  When you pressed enter, it returns the shot count you set.

*/

unsigned long set_shot_count()
{
  unsigned long shot_count = 1;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Shot count:");
  lcd.setCursor(0, 1); lcd.print(shot_count);
  lcd.setCursor(4, 1); lcd.print("shots");

  while(true)
  {
    shot_count = map(analogRead(POTENTIOMETER), 0, 1023, 0, 100);
    shot_count *= 5;

    if(shot_count == 0)
      shot_count = 1;

    lcd.setCursor(0, 1); lcd.print("   ");
    lcd.setCursor(0, 1); lcd.print(shot_count);
    delay(BUTTON);

    if(digitalRead(ENTER))
    {
      delay(BUTTON); break;
    }
  }

  return shot_count;
}

/*

  This funciton gets interval and shot count informations.
  Then calculate the time the capturing will be lasted as day, hour, minute and second.
  Finally show all information about the capture to user.

*/

void show_summary(unsigned long interval, unsigned long shot_count)
{
  unsigned long day = 0, hour = 0, minute = 0, second = 0, estimated = 0;

  estimated = interval * shot_count;

  day = estimated / 86400;
  estimated %= 86400;
  hour = estimated / 3600;
  estimated %= 3600;
  minute = estimated / 60;
  estimated %= 60;
  second = estimated;

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Interval: "); lcd.print(interval);
  lcd.setCursor(0, 1); lcd.print("Shot count: "); lcd.print(shot_count);
  delay(WAIT);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Estimated time:");
  lcd.setCursor(0, 1);
  lcd.print(day); lcd.print("d ");
  lcd.print(hour); lcd.print("h ");
  lcd.print(minute); lcd.print("m ");
  lcd.print(second); lcd.print("s");
  delay(WAIT);
}
