//gesture control using arduino uno

const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;

 

void setup() {
Serial.begin(9600);        
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

//Pause Modes -Hold
if ((distL >25 && distR>25) && (distL <50 && distR<50)) //Detect both hands
{Serial.println("Play/Pause"); delay (200);}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;


//Control Modes
//Lock Left - Control Mode
if (distL>=15 && distL<=30)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=20 && distL<=30)
  {
    Serial.println("Left Locked");
    while(distL<50)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<25)//Hand pushed in 
      {Serial.println ("Vup"); delay (100);}
      if (distL>25) //Hand pulled out
      {Serial.println ("Vdown"); delay (100);}
    }
  }
}

//Lock Right - Control Mode
if (distR>=15 && distR<=30)
{
  delay(100); //Hand Hold Time
   calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=20 && distR<=30)
  {
    Serial.println("Right Locked");
    while(distR<50)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<25) //Right hand pushed in
      {Serial.println ("Rewind"); delay (400);}
      if (distR>25) //Right hand pulled out
      {Serial.println ("Forward"); delay (400);}
    }
  }
}

//precise seek
 if(distL<15 && distR>30)
 {
  delay(100);
  calculate_distance(trigger1,echo1);
  distL=dist;
  calculate_distance(trigger2,echo2);
  distR=dist;
  while(distR<50)
  {
    calculate_distance(trigger2,echo2);
    distR=dist;
    if(distR<=20)
    {
      Serial.println("seek back");delay(500);
    }
    if(distR>20 && distR<50)
    {
      Serial.println("seek forward");delay(500);
    }
    
 }
 }

 //lock pc
if(distL<=5 && distR<=5)
{
  Serial.println("lock");
}

//new window session
if(distR<=5 && distL>10)
{
  Serial.println("new win");
}

//minimize all windows
if(distL<=5 && distR>10)
{
  Serial.println("minimize");
}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;

delay(200);
}
