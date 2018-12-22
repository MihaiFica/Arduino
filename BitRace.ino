  #include <LedControl.h> 
  #include <LiquidCrystal.h>
  LedControl lc = LedControl(12, 11, 10, 1); 
  LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
  #define BUTTONSTART A0
  #define V0_PIN      9
  const int buttonLeft = 8;
  const int buttonRight = 13;

  
  bool buttonState;
  bool buttonStateRight = 0 ;
  bool buttonStateLeft = 0 ;
  bool gameState = 1;
  bool lastButtonState = 0;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 25;
  int v[46];
  int b[62];
  int c[32];
  int pozy = 4;
  int stepGame = 0;
  int count = 0;
  int score = 0;
  int nivel = 1;
  unsigned long periodAnimation = 100;
  unsigned long periodGame = 400;
  unsigned long startMillis;
  unsigned long currentMillis;
  
  
  bool logo[8][8]
  {
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0}
  };
  
  
  bool countDownAnimation[32][8]
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1, 0}
  };
  
  
  bool mapGame[45][8]
  { 
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1}
  };
  
  
  bool endAnimation[8][62]
  {
   {0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
   {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
   {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
   {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 ,0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
   {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
   {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
   {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
   {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0}
  };
  
  
  void setup()
  {  
       lc.shutdown(0, false); 
       lc.setIntensity(0, 15);
       lc.clearDisplay(0);
       lcd.begin(16, 2);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Level: ");
       lcd.print(nivel);  
       lcd.setCursor(0, 1); 
       lcd.print("Score: ");
       lcd.print(score);        
       pinMode(V0_PIN, OUTPUT); 
       analogWrite(V0_PIN, 90);
       pinMode(BUTTONSTART, INPUT);
       pinMode(buttonLeft, INPUT);
       pinMode(buttonRight, INPUT);    
       for (int i = 0; i <= 44; i++)
       {
            v[i] = i;
       }
       for (int j = 0; j < 62; j++)
       {
            b[j] = j;
       }
       for (int t = 0; t < 31; t++)
       {
            c[t] = t;
       }
       startMillis = millis();   
  }


  void spinMapGame()
  {
       for (int i = 44; i >= 1; i--)
       {
            int aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
       }
  }
  
  
  void spinEndAnimation()
  {
       for (int i = 0; i < 61 ; i++)
       {
            int aux = b[i];
            b[i] = b[i+1];
            b[i+1] = aux;
       }
  }
  
   
  void spinFirstAnimation()
  {
       for (int i = 0; i < 31; i++)
       {
            int aux = c[i];
            c[i] = c[i+1];
            c[i+1] = aux;
       }
  }
  
  
  
  void moveBit()
  {
       buttonStateLeft = digitalRead(buttonLeft);
       buttonStateRight = digitalRead(buttonRight); 
       if (buttonStateLeft == HIGH) 
       {
            pozy--;
       } 
       if (buttonStateRight == HIGH)
       {
            pozy++;
       }
  }
  
  
  void level()
  {    
       if (periodGame >= 350 && periodGame <= 400)
       {
            nivel = 1;
       }
       if (periodGame >= 300 && periodGame < 350)
       {
            nivel = 2;
       }
       if (periodGame >= 250 && periodGame < 300)
       {
            nivel = 3;
       }
       if (periodGame >= 200 && periodGame < 250)
       {
            nivel = 4;
       }
       if (periodGame >= 150 && periodGame < 200)
       {
            nivel = 5;
       }
       if (periodGame >= 90 && periodGame < 150)
       {
            nivel = 6;
       }
  }
  
  
  void printScore()
  {
       lcd.begin(16, 2);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Level:");
       level();
       lcd.print(nivel);
       lcd.setCursor(0, 1); 
       lcd.print("Score:");
       lcd.print(score);
  }

  
  void printLogo()
  {
       for (int i = 0; i <= 7; i++)
       {
            for (int j = 0; j <= 7; j++)
            {
                 lc.setLed(0, i, j, logo[i][j]);
            }       
       }
  }

  
  void printCountDown()
  {
       for (int i = 0; i <= 7; i++)
       {
            for (int j = 0; j <= 7; j++)
            {
                 lc.setLed(0, i, j, countDownAnimation[c[i]][j]);  
            }
       }
  }
  
  
  void printMapGame()
  {
       for (int i = 44; i >= 37; i--)
       {
            for (int j = 0; j <= 7; j++)
            {
                 lc.setLed(0, i-37, j, mapGame[v[i]][j]);                                            
            }
    
       }    
  }
  
  
  void printEndAnimation()
  {
       for (int i = 0; i <= 7; i++)
       {
            for (int j = 0; j <= 7; j++)
            {
                 lc.setLed(0, i, j, endAnimation[i][b[j]]);  
            }
       }
  }
  
  
  void velocityMap()
  {
       if (periodGame >= 100)
       {
            periodGame = periodGame - 1;      
       }  
  }
  
  
  void endStepOne()
  {
       if(mapGame[v[44]][pozy] == 1)
       {                                     
            stepGame = 2;
       }   
  }

  
  void resetGame()
  {
       for (int i = 0; i <= 62; i++)
       {
            if (b[0] != 0)
            {
                 spinEndAnimation();
            }
            if (v[0] != 0)
            {
                 spinMapGame();
            }
            if (c[0] != 0)
            {
                 spinFirstAnimation();
            }
        }
        count = 0;
        stepGame = 0;
        pozy = 4;
        periodGame = 400;
        score = 0;
   }

   
   void endStepZero()
   {
        count = count + 1;
        if (count == 25)
        {
             stepGame = 1;
             count = 0;
        }
   }

   
   void endStepTwo()
   {
        count = count + 1;
        if (count == 55)
        {
             count = 0;
             stepGame = 0;
             gameState =! gameState;
        }
   }
   
   
   void addScore()
   {
        score = score + 10;
   } 


  void loop() 
  {  
      int reading = digitalRead(BUTTONSTART);
      if (reading != lastButtonState)
      {
           lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay)
      {
           if (reading != buttonState)
           {
                buttonState = reading;
                if (buttonState == HIGH)
                {
                     gameState =! gameState;
                } 
           }
      }
      int currentMillis = millis();
      if (gameState != 1)      
      {                        
           if (stepGame == 0)
           {                 
                if (currentMillis - startMillis >= periodAnimation)
                {
                     printCountDown();
                     endStepZero();
                     spinFirstAnimation(); 
                     printScore();                         
                     startMillis = currentMillis;                             
                }                                  
           }   
           else
           {
                if (stepGame == 1)
                {
                     if (currentMillis - startMillis >= periodGame)
                     {       
                          moveBit();          
                          printMapGame();
                          endStepOne();
                          lc.setLed(0, 7, pozy, 1);                       
                          spinMapGame();
                          addScore();
                          printScore();
                          velocityMap();
                          startMillis = currentMillis;           
                     }
                                                
                }
                else
                {
                     if (stepGame == 2)
                     {
                          if (currentMillis - startMillis >= periodAnimation)
                          {
                               printEndAnimation();
                               spinEndAnimation();
                               endStepTwo();
                               startMillis = currentMillis;
                          }
                                        
                      }
                }
           }     
      }                                                                                                                                         
      else                          
      {                                 
           printLogo();
           resetGame();
                                             
      }           
      lastButtonState = reading;
  }

      
