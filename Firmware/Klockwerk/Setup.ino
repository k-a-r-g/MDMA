void setup()   {                
  // initialize status led
  pinMode(LED_PIN, OUTPUT);
  
  // initialize MIDI
  #ifdef DIN
    MIDI.begin(MIDI_CHANNEL_OMNI);                    // setup midi and listen to all channels
    MIDI.turnThruOff();                               // don't broadcast everything
  #endif

  // are all values in good limits?
  bpm = constrain(bpm, 30.0, 300.0);
  
  // initialize clock interrupt
  clockInterval= (60000.0/bpm/24.0)*10;             // we run 100 times faster than the clock pulses are sent
  clockTimer.begin(clockTick, clockInterval);
}

