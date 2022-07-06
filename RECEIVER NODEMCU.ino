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
