enum display0 {a0 = 2, b0, c0, d0, e0, f0, g0};
enum display1 {a1 = 9, b1, c1, d1, e1, f1, g1};
int timeCounterLow = 0;
int timeCounterHigh = 0;
int timer2Counter = 0;
int chronometerStatus = 0;

void int0()//start/stop
{
  noInterrupts();
  Serial.println("start/stop");
  if(chronometerStatus == 0)
  {
    chronometerStatus = 1;
    disableTimer1();
    disableTimer2();
  }
  else
  {
    chronometerStatus = 0;
    enableTimer1();
    enableTimer2();  
  }
  interrupts();
}
void int1()//reset
{
  noInterrupts();
  timer2Counter = 0;
  timeCounterLow = 0;
  timeCounterHigh = 0;
  setDisplay0(-1);
  setDisplay1(-1);
  setDisplay0(0);
  setDisplay1(0);
    Serial.println("high");
  Serial.println(timeCounterHigh);
  Serial.println("low");
  Serial.println(timeCounterLow);
  interrupts();
}
void setup()
{
  Serial.begin(9600);
  for (int i = 2; i <= 15; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), int0, RISING);
  attachInterrupt(digitalPinToInterrupt(20), int1, RISING);
  enableTimer1();
  enableTimer2();
  setDisplay0(-1);
  setDisplay1(-1);
}

ISR(TIMER1_COMPA_vect) 
{
  if(timeCounterLow == 9)
  {
    timeCounterLow = 0;
    timeCounterHigh++;
    if(timeCounterHigh == 10)
    {
      timeCounterHigh = 0;
    }
  }
  else
  {
    timeCounterLow++;
  }
}

ISR(TIMER2_COMPA_vect)
{
  if(timer2Counter == 100)
  {
    timer2Counter = 0;
    setDisplay0(-1);
    setDisplay1(-1);
    setDisplay0(timeCounterHigh);
    setDisplay1(timeCounterLow);
  }
  else
  {
    timer2Counter++;
  }
}

void loop()
{
}

void enableTimer1()
{
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void disableTimer1()
{
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 0;
  // CTC
  TCCR1B |= (0 << WGM12);
  // Prescaler 1024
  TCCR1B |= (0 << CS12) | (0 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (0 << OCIE1A);
  interrupts();
}

void enableTimer2()
{
  noInterrupts();
  // Clear registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // 100.16025641025641 Hz (16000000/((155+1)*1024))
  OCR2A = 155;
  // CTC
  TCCR2A |= (1 << WGM21);
  // Prescaler 1024
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  // Output Compare Match A Interrupt Enable
  TIMSK2 |= (1 << OCIE2A);
  interrupts();
}

void disableTimer2()
{
  noInterrupts();
  // Clear registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // 100.16025641025641 Hz (16000000/((155+1)*1024))
  OCR2A = 0;
  // CTC
  TCCR2A |= (0 << WGM21);
  // Prescaler 1024
  TCCR2B |= (0 << CS22) | (0 << CS21) | (0 << CS20);
  // Output Compare Match A Interrupt Enable
  TIMSK2 |= (0 << OCIE2A);
  interrupts();
}

void setDisplay0(int option)
{
  switch(option)
  {
    case 0 : //0
    {
      digitalWrite(f0, 0);
      digitalWrite(b0, 0);
      digitalWrite(e0, 0);
      digitalWrite(c0, 0);
      digitalWrite(d0, 0);
      digitalWrite(a0, 0);
      break;
    }
    case 1 : //1
    {
      digitalWrite(b0, 0);
      digitalWrite(c0, 0);

      break;
    }
    case 2 : //2
    {
      digitalWrite(a0, 0);
      digitalWrite(b0, 0);
      digitalWrite(g0, 0);
      digitalWrite(e0, 0);
      digitalWrite(d0, 0);
      break;
    }
    case 3 : //3
    {
      digitalWrite(a0, 0);
      digitalWrite(b0, 0);
      digitalWrite(g0, 0);
      digitalWrite(c0, 0);
      digitalWrite(d0, 0);
      break;
    }
    case 4 : //4
    {
      digitalWrite(f0, 0);
      digitalWrite(g0, 0);
      digitalWrite(b0, 0);
      digitalWrite(c0, 0);
      break;
    }
    case 5 : //5
    {
      digitalWrite(a0, 0);
      digitalWrite(f0, 0);
      digitalWrite(g0, 0);
      digitalWrite(c0, 0);
      digitalWrite(d0, 0);
      break;
    }
    case 6 : //6
    {
      digitalWrite(a0, 0);
      digitalWrite(f0, 0);
      digitalWrite(g0, 0);
      digitalWrite(c0, 0);
      digitalWrite(d0, 0);
      digitalWrite(e0, 0);
      break;
    }
    case 7 : //7
    {
      digitalWrite(a0, 0);
      digitalWrite(b0, 0);
      digitalWrite(c0, 0);
      digitalWrite(c0, 0);
      break;
    }
    case 8 : //8
    {
      digitalWrite(g0, 0);
      for(int i = 2 ; i <= 8 ; i++)
        digitalWrite(i, 0);
      break;
    }
    case 9 : //9
    {
      digitalWrite(a0, 0);
      digitalWrite(f0, 0);
      digitalWrite(g0, 0);
      digitalWrite(b0, 0);
      digitalWrite(c0, 0);
      digitalWrite(d0, 0);
      break;
    }
    default :
    case -1 : //reset
    {
      digitalWrite(a0, 1);
      digitalWrite(b0, 1);
      digitalWrite(c0, 1);
      digitalWrite(d0, 1);
      digitalWrite(e0, 1);
      digitalWrite(f0, 1);
      digitalWrite(g0, 1);
      break;
    }
  }
}

void setDisplay1(int option)
{
  switch(option)
  {
    case 0 : //0
    {
      digitalWrite(f1, 0);
      digitalWrite(b1, 0);
      digitalWrite(e1, 0);
      digitalWrite(c1, 0);
      digitalWrite(d1, 0);
      digitalWrite(a1, 0);
      break;
    }
    case 1 : //1
    {
      digitalWrite(b1, 0);
      digitalWrite(c1, 0);

      break;
    }
    case 2 : //2
    {
      digitalWrite(a1, 0);
      digitalWrite(b1, 0);
      digitalWrite(g1, 0);
      digitalWrite(e1, 0);
      digitalWrite(d1, 0);
      break;
    }
    case 3 : //3
    {
      digitalWrite(a1, 0);
      digitalWrite(b1, 0);
      digitalWrite(g1, 0);
      digitalWrite(c1, 0);
      digitalWrite(d1, 0);
      break;
    }
    case 4 : //4
    {
      digitalWrite(f1, 0);
      digitalWrite(g1, 0);
      digitalWrite(b1, 0);
      digitalWrite(c1, 0);
      break;
    }
    case 5 : //5
    {
      digitalWrite(a1, 0);
      digitalWrite(f1, 0);
      digitalWrite(g1, 0);
      digitalWrite(c1, 0);
      digitalWrite(d1, 0);
      break;
    }
    case 6 : //6
    {
      digitalWrite(a1, 0);
      digitalWrite(f1, 0);
      digitalWrite(g1, 0);
      digitalWrite(c1, 0);
      digitalWrite(d1, 0);
      digitalWrite(e1, 0);
      break;
    }
    case 7 : //7
    {
      digitalWrite(a1, 0);
      digitalWrite(b1, 0);
      digitalWrite(c1, 0);
      digitalWrite(c1, 0);
      break;
    }
    case 8 : //8
    {
      digitalWrite(g1, 0);
      for(int i = 9 ; i <= 15 ; i++)
        digitalWrite(i, 0);
      break;
    }
    case 9 : //9
    {
      digitalWrite(a1, 0);
      digitalWrite(f1, 0);
      digitalWrite(g1, 0);
      digitalWrite(b1, 0);
      digitalWrite(c1, 0);
      digitalWrite(d1, 0);
      break;
    }
    default :
    case -1 : //reset
    {
      digitalWrite(a1, 1);
      digitalWrite(b1, 1);
      digitalWrite(c1, 1);
      digitalWrite(d1, 1);
      digitalWrite(e1, 1);
      digitalWrite(f1, 1);
      digitalWrite(g1, 1);
      break;
    }
  }
}
