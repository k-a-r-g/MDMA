// bpm = quarter notes per minute
// MIDI beat clock: triggered 24 ppqn (pulses per quarter note)
// we run the clock at 100x the required speed, to have room for more precise swing and humanize settings


void clockTick(){                                             // triggered by interrupt if internal clock is used, triggered by MIDI if external clock is used
  // clockCounter / 600 is the time for the normal midi clock
  // humanizeFactor is a modifier of that, however, do not forget the master counter
  clockMaster++;
  if (clockMaster == 28800) clockMaster = 0;
 

  if (!(clockMaster % swingDiv)) {                            // process swing
    swingPhase = !swingPhase;
    if (swingPhase) swingFactor = (int)(swingAmt-50);
    else swingFactor = 0;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));     // we run 10x faster

  }

  if (!(clockMaster % humanizeDiv))                           // process swing
    humanizeFactor = normalDist(random(-4999997, 4999997));   // process humanize

  
  clockCounter++;                                             // the midi clock, 24x each quarternote
  if (clockCounter >= (100 + humanizeFactor + CALIBRATOR)) { // + swingFactor) {

    clockCounter = 0 + humanizeFactor;
    #ifdef DIN
      //MIDI.sendRealTime(Clock);
    #endif
    #ifdef USB
      usbMIDI.sendRealTime(Clock);
    #endif

  }  
}


int normalDist(int val) {
  if (val <= normalIn[0]) return normalOutAdjusted[0];                // take care the value is within range
  if (val >= normalIn[normalArraySize-1]) return normalOutAdjusted[normalArraySize-1];
  uint8_t pos = 1;                                // search correct interval
  while(val > normalIn[pos]) pos++;
  if (val == normalIn[pos]) return normalOutAdjusted[pos];            // this will handle all exact "points" in the _in array
  return (val - normalIn[pos-1]) * (normalOutAdjusted[pos] - normalOutAdjusted[pos-1]) / (normalIn[pos] - normalIn[pos-1]) + normalOutAdjusted[pos-1];   // interpolate in the corresponding segment for the rest
}
