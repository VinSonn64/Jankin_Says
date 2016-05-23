
const int buttonPin = 7;
const int buttonGreen = 6;
const int buttonYellow = 5;
const int buttonRed = 4;
const int ledPin =  13;      
const int ledPin2 =  12;
const int ledPin3 =  11;
const int WinLight =  10;
const int LoseLight =  9;

int timer;


int LightCheck;
int PinPosition;

bool LightPressed; 
bool Stop;  
bool StartUp;
bool Respond;



 //Set Pattern Here
int PinSequence[] = {
  ledPin,ledPin2, ledPin3, ledPin   //Sequence of Lights
  };
 int SequenceLength =4;            //Length of Sequence
//End Set Pattern


void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(WinLight, OUTPUT);
  pinMode(LoseLight, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonYellow, INPUT);
  pinMode(buttonRed, INPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

//StarUp Begins
   if (digitalRead(buttonPin) == HIGH)
{
  StartUp=true;
  PinPosition=0;
  timer=0;
  Respond=false;
}

//Loop through PinSequence
if(StartUp)    
{
  timer++;
    if(timer > 0 && timer < 30000)
    {
    digitalWrite(PinSequence[PinPosition], HIGH);
    }
    if(timer >30000)
    {
     digitalWrite(PinSequence[PinPosition], LOW);
     timer=0; 
     PinPosition++;
     
       if(PinPosition >=SequenceLength)//Start Response State will Sequence is done
      {
      StartUp=false;
      timer=0; 
      PinPosition=0;
      Respond=true;
      }
    }
    
    
 }
//StartUp Ends

//Respond Begins
if(Respond)
{
  //Store Pin that was entered in LightCheck
  if (digitalRead(buttonGreen)==HIGH )
  {
    LightPressed = true;
    LightCheck = ledPin;
    timer=0;
  }

  if (digitalRead(buttonYellow)==HIGH )
  {
    LightPressed = true;
    LightCheck = ledPin2;
    timer=0;
  }

 if (digitalRead(buttonRed)==HIGH )
  {
    LightPressed = true;
    LightCheck = ledPin3;
    timer=0;
  }


   
  if(LightPressed) //Loop to turn on Correct Light or Lose Light
  {
    timer++;
     if(PinSequence[PinPosition]==LightCheck)
     {
        digitalWrite(LightCheck, HIGH); 
        if(!Stop)
        {
          PinPosition++;
          Stop=true;    
        }
     }
     
    else if(PinSequence[PinPosition]!=LightCheck && !Stop)
     {
   digitalWrite(ledPin, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);
   digitalWrite(LoseLight, HIGH);
   if(timer > 9000)
   {
    
    digitalWrite(LoseLight, LOW); //Turn off Lose Light if turned on and Reset
    LightPressed=false;
    Stop= false;
    timer=0;
    PinPosition=0;
    Respond = false;
   }
   
     }

   if(PinPosition>=SequenceLength)//Turn on Win Light if sequence completed correctly
   {
    digitalWrite(WinLight, HIGH);
   }
   
   if(timer >= 10000)//Turn off light after being selected
     {
   digitalWrite(ledPin, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);
   timer=0;
   LightPressed=false;
   Stop= false;
   if (PinPosition >=SequenceLength) //Turn off Win Light if turned on and Reset
   {
    digitalWrite(WinLight, LOW);
    PinPosition=0;
    Respond = false;
   }
     }
 }
  }


//Respond Ends

}
