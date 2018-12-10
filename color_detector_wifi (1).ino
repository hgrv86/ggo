  ///////////////////////////////////////////////////////////////////////////
  /////////////////////// IOT ROBOT-ARM Project /////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  
  // This code has been created by the groupe 4 (Loris, Gideon and Djouzar) 
  // for a project in the IOT course in Heriot Watt University
  // The entire project is here: https://ggo162.wixsite.com/dglhwu18
  // We have use for the Firebase part: https://github.com/FirebaseExtended/firebase-arduino/blob/master/examples/FirebaseDemo_ESP8266/FirebaseDemo_ESP8266.ino
  // and for color detection part: https://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
   
  #include <ESP8266WiFi.h>
  #include <FirebaseArduino.h>
  
  // FIREBASE INITALISATION
  #define FIREBASE_HOST "iot-arm.firebaseio.com"
  #define FIREBASE_AUTH "Hpqj3M2GSaAJBx17IrT0M3SsnZd4QDW6zty6DGlD"
  #define WIFI_SSID "HWU_Research"
  #define WIFI_PASSWORD "Her1ot-W@tt"
  
  // Initialisation of the color sensor
  #define S0 D0
  #define S1 D1
  #define S2 D2
  #define S3 D3
  #define sensorOut D4
  
  // Initialisation of the LEDs
  #define green D7
  #define blue D6
  #define LED D5
  
  // Other initialisations
  int red_frequency = 0;
  int red_frequency_map = 0;
  int blue_frequency = 0;
  int green_frequency = 0;
  int green_frequency_map = 0;
  int blue_frequency_map=0;
  int n = 0;
  float color = 4;
    
  
  void setup() {

    // Set up the different ports we used
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(sensorOut, INPUT);
    
    // Setting frequency-scaling to 20%
    digitalWrite(S0,HIGH);
    digitalWrite(S1,LOW);

    // Initialisation of the Serial Port
    Serial.begin(9600);
    
    // connect to WIFI
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());

    //Start the connection with the Firebase cloud platform
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   // digitalWrite(LED,HIGH);
  }
  
  void loop() {

    //-------------------- Red Colour --------------------------
    
    // Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    
    // Reading the output frequency
    red_frequency = pulseIn(sensorOut, LOW);
    
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    red_frequency_map = map(red_frequency, 0, 10000,  0, 255);
    
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(red_frequency);//printing RED color frequency
    Serial.print("  ");
    delay(100);


    //-------------------- Green Colour --------------------------
    
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    green_frequency = pulseIn(sensorOut, LOW);
    
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    //  green_frequency_map = map(green_frequency, 0, 10000,  0, 255);
   
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(green_frequency);//printing GREEN color frequency
    Serial.print("  ");
    delay(100);


    //-------------------- Blue Colour --------------------------
    
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    blue_frequency = pulseIn(sensorOut, LOW);
   
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(blue_frequency);//printing BLUE color frequency
    Serial.println("  " );
    delay(100);

    //-------------------- Other Colour --------------------------
    
    color = 4;
    StColor = "other";
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);


    //------- Sending the right value corresponding to the colour detected ------------------
    
    if ( red_frequency < 0.5* green_frequency && red_frequency < 0.5*blue_frequency  )
      {
        color = 1;
        StColor = "red";
        digitalWrite(red, HIGH);
        delay(500);  
      }


    if ( green_frequency <   0.7*blue_frequency && green_frequency <  1.4*red_frequency)
      {
        color = 2;
        StColor = "green";
        digitalWrite(green, HIGH);
        delay(500);
      }
  
    if ( blue_frequency <  0.8*green_frequency && blue_frequency < 1.4*red_frequency  )
      {
        color = 3;
        StColor = "blue";
        digitalWrite(blue, HIGH);
        delay(500);
      }
  
     
     //----------------- Update value in Firebase --------------------  
     
    Firebase.setFloat("number", color);
    
    // handle error
    if (Firebase.failed()) 
    {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());  
        return;
     } 
  }
