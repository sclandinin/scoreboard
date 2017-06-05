//sound effect order on SD card
#define Airhorn1 0x01
#define Airhorn2 0x02
#define AwwFuck 0x03
#define bulls 0x04
#define simple 0x05
#define Fail1 0x06
#define Fail2 0x07 
#define Fail3 0x08
#define Fire 0x09
#define Goat 0x0A
#define HotRightNow 0x0B
#define Loser 0x0C
#define MyMan 0x0D
#define NFL 0x0E
#define One 0x0F
#define Pierre 0x10
#define Pokemon 0x11
#define pump 0x12
#define rumble 0x13
#define sarumon 0x14
#define sloth 0x15
#define spacejam 0x16
#define SuddenDeath 0x17
#define Victory 0x18
#define UglyShot 0x19
#define try 0x1A


#include <IRremote.h>


const int RECV_PIN = 12;

//led drivers
const int right_A = 2;   
const int right_B = 3;  
const int right_C = 4;   
const int right_D = 5;     
const int left_A = 6;   
const int left_B = 7;  
const int left_C = 8;   
const int left_D = 9;

const int left_button = 11;
const int right_button = 10;

IRrecv irrecv(RECV_PIN);
decode_results results;

int left_score = 0;
int right_score = 0;
int left_state = 0;
int right_state = 0;
int random_number;

void setup() 
{     
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Start the receiver   

  //right LED driver
  pinMode(right_A, OUTPUT);
  pinMode(right_B, OUTPUT);
  pinMode(right_C, OUTPUT);
  pinMode(right_D, OUTPUT);

  //left LED driver
  pinMode(left_A, OUTPUT);
  pinMode(left_B, OUTPUT);
  pinMode(left_C, OUTPUT);
  pinMode(left_D, OUTPUT);

  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);

  randomSeed(analogRead(0)); //seed for random  nunmber generation

  //initialize audio to max
  Serial.write(0x7E);
  Serial.write(0xFF);
  Serial.write(0x06);
  Serial.write(0x06);
  Serial.write(0x00);
  Serial.write(0x00); 
  Serial.write(0X1E);
  Serial.write(0xEF);
  Serial.println();
}


void loop() 
{

  right_state = digitalRead(right_button);
  left_state = digitalRead(left_button);

  //clear display
  if(right_state == LOW && left_state == LOW)
  {
      right_score = 0;
      left_score = 0;
  }

  //right button increment
  if(right_state == LOW && left_state == HIGH)
  {
    right_score++;

    if (right_score == 1)
    {   
      playSound(Airhorn1);
    }
    
    if (right_score == 2 && left_score != 2)
    {   
      playSound(Airhorn2);
    }

    if (right_score == 2 && left_score == 2)
    {   
      playSound(SuddenDeath);
    }
    
    if(right_score == 3)
    {
      playSound(Victory);
    }  

    if(right_score > 3)
    {
      right_score = 3;
    }
    
  }

  //left button increment
  if(left_state == LOW && right_state == HIGH)
  {
    left_score++;

    if (left_score == 1)
    {   
      playSound(Airhorn1);
    }
    
    if (left_score == 2 && right_score != 2)
    {   
      playSound(Airhorn2);
    }

    if (left_score == 2 && right_score == 2)
    {   
      playSound(SuddenDeath);
    }
    
    if(left_score == 3)
    {
      playSound(Victory);    
    } 

    if(left_score > 3)
    {
      left_score = 3;
    }

    
    displayLeftDigit(left_score);
    
  }

    displayRightDigit(right_score);
    displayLeftDigit(left_score);
    delay(400);


  if (irrecv.decode(&results)) 
  {
    //Serial.println(results.value, HEX);
    

  switch (results.value) 
  {
    //**************************************************************************************************************
    //left_up
    case 0x2C2E80FF:

    left_score++;
    
    if (left_score == 1)
    {   
      playSound(Airhorn1);
    }
    
    if (left_score == 2 && right_score != 2)
    {   
      playSound(Airhorn2);
    }

    if (left_score == 2 && right_score == 2)
    {   
      playSound(SuddenDeath);
    }
    
    if(left_score == 3)
    {
      playSound(Victory);
    }  if(left_score > 3)
    {
      left_score = 3;
    }

    
    displayLeftDigit(left_score);

    

    break;

    //**************************************************************************************************************
   //left_down
    case 0x5A1A483D:

    left_score--;

    if(left_score < 0)
      {
        left_score = 0;
      }
    
    displayLeftDigit(left_score);
      //Serial.println(left_score);
    break;

    //**************************************************************************************************************
    //right_up
    case 0x8A67822 :

    right_score++;

    if (right_score == 1)
    {   
      playSound(Airhorn1);
    }
    
    if (right_score == 2 && left_score != 2)
    {   
      playSound(Airhorn2);
    }

    if (right_score == 2 && left_score == 2)
    {   
      playSound(SuddenDeath);
    }
    
    if(right_score == 3)
    {
      playSound(Victory);
    }  

    if(right_score > 3)
    {
      right_score = 3;
    }
    
    displayRightDigit(right_score);
      
    
    break;


    //**************************************************************************************************************
   //right_down
    case 0xFBACE420:

    right_score--;

    if(right_score < 0)
      {
        right_score = 0;
      }
    
      displayRightDigit(right_score);
      //Serial.println(right_score);

      
    break;

 //*************************************
//    Power Button   
    case 0x736ED82E:
      playSound(Airhorn1);
    break;
//*************************************
//    Guide   
    case 0xE9C74319:
      playSound(sloth);
    break;
//*************************************
//    Menu 
    case 0x19EB3488:
      playSound(sarumon);
    break;
 //*************************************
//    Go Back   
    case 0xE28725E3:
      playSound(One);
    break;
//*************************************
//    Mute Button  
    case 0x864E5C5E:
      playSound(Airhorn2);
    break;
 //*************************************
//    1 Button   
    case 0x92DF9279:
      playSound(AwwFuck);
    break;
//*************************************
//    2  
    case 0x87CDD0EF:
      playSound(simple);
    break;
//*************************************
//    3   
    case 0x37788763:
      playSound(HotRightNow);
    break;
//*************************************
//    4
    case 0xA519853B:
      playSound(Fail1);
    break;
//*************************************
//    5    
    case 0x5CDD8FBD:
      playSound(Fail2);
    break;
//*************************************
//    6 
    case 0x42DD49:
      playSound(Fail3);
    break;
//*************************************
//    7    
    case 0x31BB009F:
      playSound(Loser);
    break;
//*************************************
//    8 
    case 0x153F90A7:
      playSound(Pierre);
    break;
 //*************************************
//    9 Button   
    case 0x6872B60C:
      playSound(UglyShot);
    break;
//*************************************
//    0 Button 
    case 0x6E56F924:
     playSound(Goat);
    break;
//*************************************
//    Enter 
    case 0x3AACEF83:
      playSound(MyMan);
    break;

  

    case 0x9578646A:
      //Serial.println("Left");
    break;
   
    case 0xDC18602C:
      //Serial.println("Right");
    break;
    
//*************************************
//    Enter
    case 0xFEF03E2C:
      playSound(try);
    break;

    
//*************************************
//    Play Button   
    case 0x3875B722:

   random_number = random(7);     //random value between 0 and 6

   if (random_number == 0)
   {
    playSound(Pokemon);
   }
   
   if (random_number == 1)
   {
    playSound(bulls);
   }
   
   if (random_number == 2)
   {
    playSound(spacejam);
   }
   
   if (random_number == 3)
   {
    playSound(NFL);
   }
   
   if (random_number == 4)
   {
    playSound(rumble);
   }

   if (random_number == 5)
   {
    playSound(pump);
   }

   if (random_number == 6)
   {
    playSound(Fire);
   }
   
    
    break;

  
 //*************************************
//       
    case 0x66E97044:
      //Serial.println("FF");
    break;
   
    case 0xCB3CC07F:
      //Serial.println("OK");
    break;

    case 0xFAE193FF:
      //Serial.println("Input");
    break;
   
    case 0xF16DB763:
      //Serial.println("Rec");
    break;


//*************************************
//    Stop Button
    case 0x401C2B6C:

    Serial.write(0x7E);
    Serial.write(0xFF);
    Serial.write(0x06);
    Serial.write(0x0F);
    Serial.write(0x00);
    Serial.write(0x01); 
    Serial.write(0X02);
    Serial.write(0xEF);
    Serial.println();

   
  
    break;
   
    case 0xD922D768:
      //Serial.println("Pause");
    break;
    
    case 0x4666CC0D:
      //Serial.println("Info");
    break;
   
    case 0x2935B9A7:

    right_score = 0; 

    left_score = 0; 
       
      //Serial.println(right_score);
      //Serial.println(left_score);
    
    break;

  
    default:
      // Code
    break;

    
}
  irrecv.resume(); // Receive the next value
}
  
  delay(100);
}


/******************************************************************************
 * displayRightDigit: Send out data for the number passed to the function
 * 
 *****************************************************************************/
void displayRightDigit(int digit)
{

switch (digit) 
  {
    //zero
    case 0:
      digitalWrite(right_A, LOW);
      digitalWrite(right_B, LOW);
      digitalWrite(right_C, LOW); 
      digitalWrite(right_D, LOW);
    
    break;
  
    //one
    case 1:
      digitalWrite(right_A, HIGH);
      digitalWrite(right_B, LOW);
      digitalWrite(right_C, LOW); 
      digitalWrite(right_D, LOW);
    break;
      
     //two
    case 2:
      digitalWrite(right_A, LOW);
      digitalWrite(right_B, HIGH);
      digitalWrite(right_C, LOW); 
      digitalWrite(right_D, LOW);
    break;

    //three
    case 3:
      digitalWrite(right_A, HIGH);
      digitalWrite(right_B, HIGH);
      digitalWrite(right_C, LOW); 
      digitalWrite(right_D, LOW);
    break;

  
    default:

    break;

  }

}


/******************************************************************************
 * displayLeftDigit: Send out data for the number passed to the function
 * 
 *****************************************************************************/
void displayLeftDigit(int digit)
{

switch (digit) 
  {
    //zero
    case 0:
      digitalWrite(left_A, LOW);
      digitalWrite(left_B, LOW);
      digitalWrite(left_C, LOW); 
      digitalWrite(left_D, LOW);
    break;
  
    //one
    case 1:
      digitalWrite(left_A, HIGH);
      digitalWrite(left_B, LOW);
      digitalWrite(left_C, LOW); 
      digitalWrite(left_D, LOW);
    break;
      
     //two
    case 2:
      digitalWrite(left_A, LOW);
      digitalWrite(left_B, HIGH);
      digitalWrite(left_C, LOW); 
      digitalWrite(left_D, LOW);
    break;

    //three
    case 3:
      digitalWrite(left_A, HIGH);
      digitalWrite(left_B, HIGH);
      digitalWrite(left_C, LOW); 
      digitalWrite(left_D, LOW);
    break;

  
    default:

    break;

  }

}

/******************************************************************************
 * playSound: Select which audio track to play on the MP3 module
 * 
 *****************************************************************************/
void playSound(int sound)
{
    Serial.write(0x7E);
    Serial.write(0xFF);
    Serial.write(0x06);
    Serial.write(0x03);
    Serial.write(0x00);
    Serial.write(0x00); 
    Serial.write(sound);
    Serial.write(0xEF);
    Serial.println();
  
}

/*
Code         
Power       736ED82E       
Guide       E9C74319
Menu        19EB3488
Go Back     E28725E3
Mute        864E5C5E
1           92DF9279
2           87CDD0EF
3           37788763
4           A519853B
5           5CDD8FBD
6           42DD49
7           31BB009F
8           153F90A7
9           6872B60C
0           6E56F924
Enter       3AACEF83
TV-VCR      FAE193FF 
Up          2C2E80FF
Down        5A1A483D
Left        9578646A
Right       DC18602C
CHUp        8A67822 
CHDown      FBACE420
VUp         B570F1C8
VDown       58D63F54
Rewind      FEF03E2C
Play        3875B722
FF          66E97044
OK          CB3CC07F
Input       FAE193FF
Rec         F16DB763
Stop        401C2B6C
Pause       D922D768
Info        4666CC0D
Clear       2935B9A7

 */
