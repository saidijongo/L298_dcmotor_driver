
#define PS2_DAT        12      
#define PS2_CMD        11  
#define PS2_SEL        10  
#define PS2_CLK        9  

#define leftm1     3
#define leftm2     4
#define rightm1    5
#define rightm2    6
#define left_EN    2
#define right_EN   7

  //analog values read from PS2 joysticks
int LX = 0;                   
int LY = 0;
int RX = 0;
int RY = 0;
/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
#define pressures   true
//#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;


void setup() {

  Serial.begin(9600);

  pinMode(leftm1,  OUTPUT);
  pinMode(leftm2,  OUTPUT);
  pinMode(rightm1, OUTPUT);
  pinMode(rightm2, OUTPUT);
  pinMode(left_EN, OUTPUT);
  pinMode(right_EN, OUTPUT);

  digitalWrite(left_EN, LOW);
  digitalWrite(right_EN, LOW);

  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it


  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
  }
  else if (error == 1)
    Serial.print("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.print("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.print("Controller refusing to enter Pressures mode, may not support it. ");

    Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}

void loop() {
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
  
delay(50);
  if (ps2x.Button(PSB_L1))
  {
    LY = ps2x.Analog(PSS_LY);    //receive values from p22 joystick
    LX = ps2x.Analog(PSS_LX);
  }
  if (ps2x.Button(PSB_R1))
  {
    RY = ps2x.Analog(PSS_RY);
    RX = ps2x.Analog(PSS_RX);
  }

  if (LY > 200 || RY > 200)  //check if the joystick pushed up side
  {
    REV();
  }
  if (LY < 100 || RY < 100)
  {
    forward();
  }
  if (LX < 100 || RX < 100)
  {
    left();
  }
  if (LX > 200 || RX > 200)
  {
    right();
  }
  if(LX == 128 && LY == 128 && RX == 128 && RY == 128)
  {
    waithere();
  }

LY = LX = 128;   //return to default vlaues
RY = RX = 128;  //return to default values
}

void forward()
{
  //Serial.print("forward");
  digitalWrite(left_EN, HIGH);
  digitalWrite(right_EN, HIGH);

  digitalWrite(leftm1, HIGH);
  digitalWrite(leftm2, LOW);
  digitalWrite(rightm1, HIGH);
  digitalWrite(rightm2, LOW);

}
void REV()
{
  //Serial.print("rev");
  digitalWrite(left_EN, HIGH);
  digitalWrite(right_EN, HIGH);

  digitalWrite(leftm1, LOW);
  digitalWrite(leftm2, HIGH);
  digitalWrite(rightm1, LOW);
  digitalWrite(rightm2, HIGH);
}
void left()
{
  //Serial.print("left");
  digitalWrite(left_EN, LOW);
  digitalWrite(right_EN, HIGH);

  digitalWrite(leftm1, LOW);
  digitalWrite(leftm2, LOW);
  digitalWrite(rightm1, HIGH);
  digitalWrite(rightm2, LOW);
}
void right()
{
  //Serial.print("right");
  digitalWrite(left_EN, HIGH);
  digitalWrite(right_EN, LOW);

  digitalWrite(rightm1, LOW);
  digitalWrite(rightm2, LOW);
  digitalWrite(leftm1, HIGH);
  digitalWrite(leftm2, LOW);
}
void waithere()
{
  //Serial.print("stop");
  digitalWrite(left_EN, LOW);
  digitalWrite(right_EN, LOW);
  digitalWrite(rightm1, LOW);
  digitalWrite(rightm2, LOW);
  digitalWrite(leftm1, LOW);
  digitalWrite(leftm2, LOW);
}

//**************END**************************
