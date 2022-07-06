# ESP8266 PORJECT FOR OLD PEOPLE WHO ARE BED-SICK

## DESCRIPTION

Here we going to make a project which will help old people to get there daily need-full things, like there walking stick,coffee,specs,tea,water,medicine right from there bed they dont need to get up, we are going to use a sender nodemcu and a receiver nodemcu ,sender nodemcu will have a 4x4 keypad connected and receiver nodemcu will have 16x2 lcd connected, when we will press for example 1 on keypad of sender nodemcu then we will get medecine as output on lcd of receiver nodemcu same we will assign all numbers of keypad some particular value as output. this way if a person wants some things he can have sender nodemcu and he can give reciver nodemcu with lcd to a nurse or his care-taker who will provide him that particular things which is written on the lcd of receiver nodemcu.This project have a range of 90meters, so it can be installed far away from each other like in a big hospital or at big facility

## COMPONENTS REQUIRED
1.ESP8266 MODULES 2 PIECES
2.LCD 16x2 WITH I2C MODULE SOLDERED
3.KEYPAD 4x4
4.POWER SUPPLY FOR OUR ESP8266 MODULES

## CIRCUIT DIAGRAM

## FOR RECEIVER ESP8266 

![esp8266_LCD (1)](https://user-images.githubusercontent.com/102857010/177605413-c00c968d-4527-47e4-a747-cb0f5894ace1.jpg)

## FOR SENDER ESP8266

![8-2-420x420](https://user-images.githubusercontent.com/102857010/177605923-80738012-f760-4263-b30b-13a190c57f18.jpg)

## RECEIVER NODEMCU CODE

````
/*
ESP8266 NodeMCU Receiver Sketch (ESP-NOW)
Upload the following code to your ESP8266 NodeMCU receiver board.*/

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal_I2C.h>
String a;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    int d;
    String e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
    lcd.begin(16,2);     // The begin call takes the width and height. This
 lcd.init();          // Should match the number provided to the constructor.
 lcd.backlight();     // Turn on the backlight.
 lcd.setCursor(0, 0); 

 // Turn on the blacklight and print a message.

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
    
}


void loop() {
    lcd.setCursor(0, 0);
  // print message
  
    if(myData.b==1)
    {
    a="FOOD";
       
}
    if(myData.b==2)
    {
    a="WATER";
  
}
    if(myData.b==3)
    {
    a="MEDICINE";
      
}
    if(myData.b==4)
    {
    a="WALKING STICK";
    
}
    if(myData.b==5)
    {
    a="TEA";
    
}
    if(myData.b==6)
    {
    a="SPECS";
    
}
    
    Serial.println(myData.b);
    lcd.print(a);
    delay(1000);
    lcd.clear();
}
````
## SENDER NODEMCU CODE

````
/*
ESP8266 NodeMCU Receiver Sketch (ESP-NOW)
Upload the following code to your ESP8266 NodeMCU receiver board.*/

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal_I2C.h>
String a;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    int d;
    String e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
    lcd.begin(16,2);     // The begin call takes the width and height. This
 lcd.init();          // Should match the number provided to the constructor.
 lcd.backlight();     // Turn on the backlight.
 lcd.setCursor(0, 0); 

 // Turn on the blacklight and print a message.

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
    
}


void loop() {
    lcd.setCursor(0, 0);
  // print message
  
    if(myData.b==1)
    {
    a="FOOD";
       
}
    if(myData.b==2)
    {
    a="WATER";
  
}
    if(myData.b==3)
    {
    a="MEDICINE";
      
}
    if(myData.b==4)
    {
    a="WALKING STICK";
    
}
    if(myData.b==5)
    {
    a="TEA";
    
}
    if(myData.b==6)
    {
    a="SPECS";
    
}
    
    Serial.println(myData.b);
    lcd.print(a);
    delay(1000);
    lcd.clear();
}
````
