 ///////////////////////////////////////////////////////////////////////////
 /////////////////////// IOT ROBOT-ARM Project /////////////////////////////
 ///////////////////////////////////////////////////////////////////////////

 // This code has been created by the groupe 4 (Loris, Gideon and Djouzar) 
 // for a project in the IOT course in Heriot Watt University

 // The librairy we use to control the servos 
 #include <Servo.h>

 // We initialise the state we receive in Bluetooth at 0
  byte state = 0;     

 // We create 4 objects "Servo" (include in the library Servo.h)
  Servo servo01;      
  Servo servo02;
  Servo servo03;
  Servo servo04;
  
 // set initial positions
  int servo1PPos= 130, servo2PPos= 150, servo3PPos= 35, servo4PPos= 140; 

 // for storing positions/steps
  int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50]; 


 void setup() {
  
 // Initialise the serial port 
  Serial.begin(9600);   
  
 // Attach the Servo variables to the pin indicated
  servo01.attach(3);    
  servo02.attach(5);
  servo03.attach(6);
  servo04.attach(9);

 // Set the initial position of each Servo    
  servo01.write(servo1PPos);  
  servo02.write(servo2PPos);  
  servo03.write(servo3PPos);
  servo04.write(servo4PPos);}
  
 void loop() {

 // Checks whether data is comming from the serial port
  if(Serial.available() > 0){ 
    // Reads and print the data from the serial port
    state = Serial.read(); 
    Serial.println(state);

 // Here we send the right command for the right joint with respect to the app
 // Grip pin3
    if (state==1){servo01.write(90);}
    if (state==2){servo01.write(170);}

 // Shlouder pin5    
    if (state==11){servo02.write(95);}
    if (state==12){servo02.write(100);}
    if (state==13){servo02.write(110);}
    if (state==14){servo02.write(120);}
    if (state==15){servo02.write(130);}
    if (state==16){servo02.write(150);}
    if (state==17){servo02.write(170);}
    if (state==18){servo02.write(180);}
    
 // Elbow pin6       
    if (state==21){servo03.write(70);}
    if (state==22){servo03.write(80);}
    if (state==23){servo03.write(90);}
    if (state==24){servo03.write(100);}
    if (state==25){servo03.write(110);}
    if (state==26){servo03.write(120);}
    if (state==27){servo03.write(130);}
    if (state==28){servo03.write(140);}

 // Waist pin9
    if (state==31){servo04.write(170);}
    if (state==32){servo04.write(150);}
    if (state==33){servo04.write(130);}
    if (state==34){servo04.write(125);}
    if (state==35){servo04.write(100);}
    if (state==36){servo04.write(75);}
    if (state==37){servo04.write(50);}
    if (state==38){servo04.write(25);}
    
    }
  }
  
