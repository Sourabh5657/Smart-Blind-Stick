//initialize all pins
int trigpin1 =5;
int echopin1=6;

int trigpin2=9;
int echopin2=10;

int trigpin3 =3;
int echopin3=11;

int BUZZpin=A0;

//decide therir pinmode and setup them properly
void setup() {
  Serial.begin(9600);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);

  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);

  pinMode(trigpin3,OUTPUT);
  pinMode(echopin3,INPUT);

  analogWrite(BUZZpin,LOW);

}
//initiailize the fuction for operating frequency at different distance
void setfreq(int freq,int delay1){
  analogWrite(BUZZpin,freq);
  delay(delay1);
  analogWrite(BUZZpin,0);
  delay(delay1);
}

void loop() {
  //first ultra-sonic sensor 
  long duration1,distance1;
  digitalWrite(trigpin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1,LOW);
  duration1=pulseIn(echopin1,HIGH);
  distance1=(duration1/2)/29.1;
  //second ultra-sonic sensor
  long duration2,distance2;
  digitalWrite(trigpin2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin2,LOW);
  duration2=pulseIn(echopin2,HIGH);
  distance2=(duration2/2)/29.1;
  //third ultra-sonic sensor
  long duration3,distance3;
  digitalWrite(trigpin3,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin3,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin3,LOW);
  duration3=pulseIn(echopin3,HIGH);
  distance3=(duration3/2)/29.1;
  //decide distance for which it act and buzzer beep for alerting blind people
  if((distance1>=0) && (distance1<=30) ||
  (distance2>=0) && (distance2<=30) ||
  (distance3>=0) && (distance3<=30) ){
    //find minimum distance from all three sensor data
    long distance=min(min(distance1,distance2),distance3);
    Serial.print("distance:");
    Serial.println(distance);
    //set freqency for different close distances
    if((distance>=0) && (distance<=5)){
      setfreq(255,50);
    }
    else if ((distance>5) && (distance<=10)){
      setfreq(230,150);
    }
    else if((distance>10) && (distance<=15)){
      setfreq(205,250);
    }
    else if((distance>15) && (distance<=20)){
      setfreq(180,350);
    }
    else if((distance>20) && (distance<=25)){
      setfreq(155,450);
    }
    else{
       setfreq(130,550);
    }
    
  }
  else{
      analogWrite(BUZZpin,0);
    }

}