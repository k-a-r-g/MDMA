//################################################################
#ifdef ALLOW_NOTES
  void OnDinNoteOn(byte channel, byte note, byte velocity) {
    if (channels[channel-1]) {
      if (channelRemap) usbMIDI.sendNoteOn(note, velocity, channelRemap);
      else usbMIDI.sendNoteOn(note, velocity, channel);
     #ifdef MIDI_THRU
        if (channelRemap) MIDI.sendNoteOn(note, velocity, channelRemap);
        else MIDI.sendNoteOn(note, velocity, channel);
      #endif
    }
  }

  void OnUsbNoteOn(byte channel, byte note, byte velocity) {
    if (channels[channel-1]) {
      if (channelRemap) MIDI.sendNoteOn(note, velocity, channelRemap);
      else MIDI.sendNoteOn(note, velocity, channel);
    }
  }

//################################################################
  void OnDinNoteOff(byte channel, byte note, byte velocity) {
    if (channels[channel-1]) {
      if (channelRemap) usbMIDI.sendNoteOff(note, velocity, channelRemap);
      else usbMIDI.sendNoteOff(note, velocity, channel);
      #ifdef MIDI_THRU
        if (channelRemap) MIDI.sendNoteOff(note, velocity, channelRemap);
        else MIDI.sendNoteOff(note, velocity, channel);
      #endif
    }
  }
  
  void OnUsbNoteOff(byte channel, byte note, byte velocity) {
    if (channels[channel-1]) {
      if (channelRemap) MIDI.sendNoteOff(note, velocity, channelRemap);
      else MIDI.sendNoteOff(note, velocity, channel);
    }
  }
#endif


//################################################################
void OnDinPitchBend(byte channel, int pitch) {
  if (channels[channel-1]) {
    if (channelRemap) usbMIDI.sendPitchBend(pitch, channelRemap);   
    else usbMIDI.sendPitchBend(pitch, channel);  
    #ifdef MIDI_THRU
      if (channelRemap) MIDI.sendPitchBend(pitch, channelRemap);       
      else MIDI.sendPitchBend(pitch, channel);  
    #endif
  }
}

void OnUsbPitchBend(byte channel, int pitch) {
  if (channels[channel-1]) {
    if (channelRemap) MIDI.sendPitchBend(pitch, channelRemap);       
    else MIDI.sendPitchBend(pitch, channel);  
  }
}


//################################################################
void OnDinControlChange(byte channel, byte control, byte value) {
  if (channels[channel-1]) {
    if (channelRemap) usbMIDI.sendControlChange(control, value, channelRemap);
    else usbMIDI.sendControlChange(control, value, channel);
    #ifdef MIDI_THRU
      if (channelRemap) MIDI.sendControlChange(control, value, channelRemap);
      else MIDI.sendControlChange(control, value, channel);
    #endif
  }
}

void OnUsbControlChange(byte channel, byte control, byte value) {
  if (channels[channel-1]) {
    if (channelRemap) MIDI.sendControlChange(control, value, channelRemap);
    else MIDI.sendControlChange(control, value, channel);
  }
}


//################################################################  
void OnDinAfterTouchCh(byte channel, byte value) {
  if (channels[channel-1]) {
    if (channelRemap) usbMIDI.sendAfterTouch(value, channelRemap);
    else usbMIDI.sendAfterTouch(value, channel);
    #ifdef MIDI_THRU
      if (channelRemap) MIDI.sendAfterTouch(value, channelRemap);
      else MIDI.sendAfterTouch(value, channel);
    #endif
  }
}

void OnUsbAfterTouchCh(byte channel, byte value) {
  if (channels[channel-1]) {
    if (channelRemap) MIDI.sendAfterTouch(value, channelRemap);
    else MIDI.sendAfterTouch(value, channel);
  }
}


//################################################################
void OnDinAfterTouchPoly(byte channel, byte note, byte pressure) {
  if (channels[channel-1]) {
    if (channelRemap) usbMIDI.sendPolyPressure(note, pressure, channelRemap); 
    else usbMIDI.sendPolyPressure(note, pressure, channel);   
    #ifdef MIDI_THRU
      if (channelRemap) MIDI.sendPolyPressure(note, pressure, channelRemap);  
      else MIDI.sendPolyPressure(note, pressure, channel);  
    #endif
  }
}


//################################################################
void OnDinProgramChange(byte channel, byte number) {
  if (channels[channel-1]) {
    if (channelRemap) usbMIDI.sendProgramChange(number, channelRemap);
    else usbMIDI.sendProgramChange(number, channel);  
    #ifdef MIDI_THRU
      if (channelRemap) MIDI.sendProgramChange(number, channelRemap); 
      else MIDI.sendProgramChange(number, channel); 
    #endif
  }
}

void OnUsbProgramChange(byte channel, byte number) {
  if (channels[channel-1]) {
    if (channelRemap) MIDI.sendProgramChange(number, channelRemap);
    else MIDI.sendProgramChange(number, channel);  
  }
}


//################################################################
#ifdef ALLOW_CLOCK
  void OnDinClock() {
    usbMIDI.sendRealTime(Clock);
    #ifdef MIDI_TRHU
      MIDI.sendRealTime(Clock);
    #endif
  }

  void OnDinStart() {
    usbMIDI.sendRealTime(Start);  
    #ifdef MIDI_TRHU
      MIDI.sendRealTime(Start);
    #endif
  }

  void OnDinStop() {
    usbMIDI.sendRealTime(Stop);
    #ifdef MIDI_TRHU
      MIDI.sendRealTime(Stop);
    #endif
  }

  void OnDinContinue() {
    usbMIDI.sendRealTime(Continue);  
    #ifdef MIDI_TRHU
      MIDI.sendRealTime(Continue);
    #endif

  }

  void OnUsbRealTimeSystem(byte realtimebyte) { 
    if (realtimebyte == Clock) MIDI.sendRealTime(Clock);
    else if (realtimebyte == Start) MIDI.sendRealTime(Start);
    else if (realtimebyte == Continue) MIDI.sendRealTime(Continue);
    else if (realtimebyte == Stop) MIDI.sendRealTime(Stop);
    else if (realtimebyte == ActiveSensing) MIDI.sendRealTime(ActiveSensing);
    else if (realtimebyte == SystemReset) MIDI.sendRealTime(SystemReset);  
  }

  void OnDinTimeCode(byte value) {
    usbMIDI.sendTimeCodeQuarterFrame(value);  
    #ifdef MIDI_TRHU
      MIDI.sendTimeCodeQuarterFrame(value);  
    #endif
  }
  
  void OnUsbTimeCode(uint16_t value) {
    MIDI.sendTimeCodeQuarterFrame(value);  
  }
  
#else
  void OnUsbRealTimeSystem(byte realtimebyte) { 
    if (realTimebyte == ActiveSensing) MIDI.sendRealTime(ActiveSensing);
    else if (realTimebyte == SystemReset) MIDI.sendRealTime(SystemReset);  
  }
#endif

//################################################################

void OnDinActiveSensing() {
  usbMIDI.sendRealTime(ActiveSensing);  
    #ifdef MIDI_TRHU
      MIDI.sendRealTime(ActiveSensing);
    #endif

}

//################################################################

void OnDinSystemReset() {
  usbMIDI.sendRealTime(SystemReset);    
  #ifdef MIDI_TRHU
      MIDI.sendRealTime(SystemReset);
  #endif

}


//OnDinSysEx() {}

