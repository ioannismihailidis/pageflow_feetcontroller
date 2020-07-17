#include <keyboard.h>

int buttonPinDown = 9; // Set a button to any pin, it doesn't matter all that much in this case
int buttonPinUp = 10; // Set a button to any pin, it doesn't matter all that much in this case
unsigned long timeLastPressed;
bool pressed = false;
unsigned int waitTime = 60*1000*5;

unsigned int forceResetTime = 3*1000;

bool needRefresh = true;


void setup()
{
  Serial.begin(38400);
  pinMode(buttonPinDown, INPUT); // Set the "buttonPin" as an input
  digitalWrite(buttonPinDown, HIGH); // Pull the button high (send power to that pin)

  pinMode(buttonPinUp, INPUT); // Set the "buttonPin" as an input
  digitalWrite(buttonPinUp, HIGH); // Pull the button high (send power to that pin)
  timeLastPressed = 0;
}

void loop()
{
  if(needRefresh && (millis()-timeLastPressed) > waitTime)
  {
    needRefresh = false;
    Keyboard.press(KEY_F5);
    Keyboard.release(KEY_F5);
    Serial.println("REFRESH");
  }
  
  if (!pressed && (digitalRead(buttonPinDown) == 0 || (digitalRead(buttonPinUp) == 0) ))  // if the button goes low
  {
      
      if(digitalRead(buttonPinDown) == 0)
      {
        Keyboard.press(KEY_DOWN);
        Serial.println("DOWN");
        //delay(100);
        Keyboard.release(KEY_DOWN);
      } else {
         Keyboard.press(KEY_UP);
         Serial.println("UP");
        //delay(100);
        Keyboard.release(KEY_UP);
      }
      
      delay(100);
      pressed = true;
      timeLastPressed = millis();
      needRefresh = true;
      //Keyboard.release(KEY_MEDIA_VOLUME_INC);
    //delay(1000);
    //Keyboard.write("g"); // send a 'g' to the computer (prepar3d in this case) via Keyboard HID
    //delay(1000); // delay so there aren't a kajillion g's
  } else if(pressed &&  digitalRead(buttonPinDown) == 1 && (digitalRead(buttonPinUp) == 1) ) {
    Serial.println("RELEASED");
    pressed = false;
  }

  if(pressed && millis()-timeLastPressed > forceResetTime)
  {
    Keyboard.press(KEY_F5);
    Keyboard.release(KEY_F5);
    Serial.println("FORCE REFRESH");
    timeLastPressed = millis();
  }
  
}
