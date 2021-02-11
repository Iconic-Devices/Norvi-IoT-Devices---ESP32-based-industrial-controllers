void setup()
{
 //const int I1=18;  
 //const int I2=39;  
 //const int I3=34;
 //const int I4=35;
 //const int I5=19;
 //const int I6=21;   
 //const int I7=22;
 //const int I8=23;  
 //const int O1=14;
 //const int O2=13;
 //const int O3=12;
 //const int O4=15;  
 //const int O5=2;
 //const int O6=33;
 //const int TO1=26;
 //const int TO2=27;   
     
  Serial.begin(115200);     
  pinMode(18, INPUT);
  pinMode(39, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(19, INPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
 
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

}

void loop() 
{
        if(digitalRead(18)== LOW && digitalRead(39)== HIGH && digitalRead(34)== HIGH && digitalRead(35)== HIGH && digitalRead(19)==HIGH && digitalRead(21)== HIGH && digitalRead(22)== HIGH && digitalRead(23)== HIGH)
        {   
            digitalWrite(14, HIGH);
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            digitalWrite(15, LOW);
            digitalWrite(2, LOW);
            digitalWrite(33, LOW);
            digitalWrite(26, LOW);
            digitalWrite(27, LOW);
        }
         else
         {
            digitalWrite(14,LOW);
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            digitalWrite(15, LOW);
            digitalWrite(2, LOW);
            digitalWrite(33,LOW);
            digitalWrite(26, LOW);
            digitalWrite(27, LOW);
         }      
}
