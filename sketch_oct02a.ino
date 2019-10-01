//Ben Katz
//Tree Climbing Robot Code
//
//Please don't copy this for anything other than person use
//without my permission, or I'll have to set my robots on you.  Thanks!

void setup(){
 // Serial.begin(9600);
 for(int i = 0 ; i <= 6 ; i++){
    pinMode(i, OUTPUT);
  }
 for(int i = 8 ; i <= 13 ; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(6,INPUT);
  digitalWrite(1, HIGH);    //enable motors
  
}

unsigned long currentTime;          //Everything in this segment is used for leg tracking
unsigned long pastTime = 0;
int legPosition;
int oldPosition = 0;
int legSpeed;
int legPosition2;
int oldPosition2 = 0;
int legSpeed2;
int mins = 1;

void loop(){
  int moveSwitch = digitalRead(6);
//  //Serial.println(moveSwitch);
  if(moveSwitch == 1){                  //When you flip the controll switch, the robot grabs into the tree
    closeBottom();
    closeTop();
  }

  while(moveSwitch == 1){        //Movement pattern for climbing up
    closeTop();
    delay(100);
    openBottom();
    delay(100);
    Lift();
    delay(100);
    closeBottom();
    delay(100);
    openTop();
    delay(100);
    Push();
    delay(100);
    moveSwitch = digitalRead(6);
    }
  if(moveSwitch == 0){          //Flip the switch back, and the legs open up once the climb cycle ends
     openTop();  
     openBottom(); 
  }

  }


void openTop(){
  int L1 = analogRead(A0);
  int L2 = analogRead(A1);
  while( L1 > 80 || L2 < 1005){      //Values of the pots when the legs are open.  These values were found experimentally
    if(L2 < 1005){
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
    }
    else{
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }

    if(L1 > 80){
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
    }
    else{
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
    }
    L1 = analogRead(A0);
    L2 = analogRead(A1);

  }
   digitalWrite(8, LOW);
   digitalWrite(9, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);

}


void openBottom(){
  int L3 = analogRead(A2);
  int L4 = analogRead(A3);
  while( L3 < 900 || L4 > 65){       //Values of the pots when the legs are open.  These values were found experimentally
    if(L4 > 65){
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
    }
    else{
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
    }

    if(L3 < 900){
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    }
    else{
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
    L3 = analogRead(A2);
    L4 = analogRead(A3);

  }
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);    
}


void closeTop(){
  unsigned long startTime = millis();
  oldPosition = 0;
  oldPosition2 = 0;
  legPosition = analogRead(A0);
  legPosition2 = analogRead(A1);
  legSpeed = 10;
  legSpeed2 = 10;
  
  while( legSpeed2 > mins || legSpeed > mins){        //When the legspeed drops below a certain point ("minimum speed," or mins) the motor is cut off to prevent it from burning out
    
    if(legSpeed2 > mins){
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
    }
    else{
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }

    if(legSpeed > mins){
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
    }
    else{
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
    }



    currentTime = millis();
    if (currentTime - pastTime > 50 && currentTime - startTime > 250){    // 1/4 second delay to let the motors get up to speed
      pastTime = currentTime;
      legPosition = analogRead(A0);
      legPosition2 = analogRead(A1);
      legSpeed = abs(legPosition - oldPosition);
      legSpeed2 = abs(legPosition2 - oldPosition2);
      oldPosition = legPosition;
      oldPosition2 = legPosition2;
    }
  }
   digitalWrite(8, LOW);
   digitalWrite(9, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);
}

void closeBottom(){
  unsigned long startTime = millis();
  oldPosition = 0;
  oldPosition2 = 0;  
  legPosition = analogRead(A2);
  legPosition2 = analogRead(A3);
  legSpeed = 10;
  legSpeed2 = 10;
  while( legSpeed > mins || legSpeed2 > mins){
    

    
    if(legSpeed2 > mins){
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
    }
    else{
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
    }

    if(legSpeed > mins){
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
    else{
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }



    currentTime = millis();
    if (currentTime - pastTime > 50 && currentTime - startTime > 250){      // 1/4 second delay to let the motors get up to speed
      pastTime = currentTime;
      legPosition = analogRead(A2);
      legPosition2 = analogRead(A3);
      legSpeed = abs(legPosition - oldPosition);
      legSpeed2 = abs(legPosition2 - oldPosition2);
      oldPosition = legPosition;
      oldPosition2 = legPosition2;
    }
  }
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);  
}


void Lift(){
  int limit = digitalRead(A4);
    //Serial.println(limit);
  while(limit == 0){
    digitalWrite(12, HIGH);
    limit = digitalRead(A4);
  }
  digitalWrite(12, LOW);
}


void Push(){
  int limit = digitalRead(A5);
  //Serial.println(limit);
  while(limit == 1){
    digitalWrite(13, HIGH);
    limit = digitalRead(A5);
  }
  digitalWrite(13, LOW);  
}
