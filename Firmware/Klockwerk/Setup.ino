void setup()   {                
  // initialize Serial port (DEBUGGING ONLY)
    Serial.begin(115200);

  // initialize status led
  pinMode(LED_PIN, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // initialize Random generator
  randomSeed(analogRead(A11));
  
  // initialize MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);                    // setup midi and listen to all channels
  MIDI.turnThruOff();                               // don't broadcast everything

    delay(500);

  // are all values in good limits?
  bpm = constrain(bpm, 30.0, 300.0);
  swingAmt = constrain(swingAmt, 50.0, 90.0);
  swingSpeed = constrain(swingSpeed, 0, 11);
  swingDiv = clockDivs[swingSpeed]*100;
  humanizeAmt = constrain(humanizeAmt, 0, 100);
  humanizeDiv = clockDivs[humanizeSpeed]*100;
  for (int i=0; i<normalArraySize; i++) normalOutAdjusted[i] = round(normalOut[i]*humanizeAmt);


  // initialize clock interrupt
  clockInterval= (60000.0/bpm/24.0)*10;             // we run 100 times faster than the clock pulses are sent
  clockTimer.begin(clockTick, clockInterval);

}

