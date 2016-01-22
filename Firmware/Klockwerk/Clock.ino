// bpm = quarter notes per minute
// MIDI beat clock: triggered 24 ppqn (pulses per quarter note)
// we run the clock at 100x the required speed, to have room for more precise swing and humanize settings


void clockTick(){                                             // triggered by interrupt if internal clock is used, triggered by MIDI if external clock is used
  #ifdef DIN
    MIDI.sendRealTime(Clock);
  #endif
  #ifdef USB
    usbMIDI.sendRealTime(CLOCK);
  #endif
}


