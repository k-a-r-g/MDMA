void setup() {
  if (channelRemap > 16) channelRemap = 0;
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
  #ifdef ALLOW_NOTES
    MIDI.setHandleNoteOn(OnDinNoteOn);
    MIDI.setHandleNoteOff(OnDinNoteOff);
  #endif
  MIDI.setHandlePitchBend(OnDinPitchBend);
  MIDI.setHandleControlChange(OnDinControlChange);
  MIDI.setHandleAfterTouchChannel(OnDinAfterTouchCh);
  MIDI.setHandleAfterTouchPoly(OnDinAfterTouchPoly);
  MIDI.setHandleProgramChange(OnDinProgramChange);
  //MIDI.setHandleSongPosition(OnDinSongPosition);            // not yet implemented by USB MIDI library
  //MIDI.setHandleSongSelect(OnDinSongSelect);                // not yet implemented by USB MIDI library
  //MIDI.setHandleTuneRequest(OnDinTuneRequest);              // not yet implemented by USB MIDI library
  #ifdef ALLOW_CLOCK
    MIDI.setHandleClock(OnDinClock);
    MIDI.setHandleStart(OnDinStart);
    MIDI.setHandleStop(OnDinStop);
    MIDI.setHandleContinue(OnDinContinue);
    MIDI.setHandleTimeCodeQuarterFrame(OnDinTimeCode);
  #endif
  MIDI.setHandleActiveSensing(OnDinActiveSensing);
  MIDI.setHandleSystemReset(OnDinSystemReset);
  //MIDI.setHandleSystemExclusive(OnDinSysEx);

  #ifdef ALLOW_NOTES
    usbMIDI.setHandleNoteOn(OnUsbNoteOn);
    usbMIDI.setHandleNoteOff(OnUsbNoteOff);
  #endif
  usbMIDI.setHandlePitchChange(OnUsbPitchBend);
  usbMIDI.setHandleControlChange(OnUsbControlChange);
  usbMIDI.setHandleAfterTouch(OnUsbAfterTouchCh);   
  //usbMIDI.setHandleAfterTouchPoly(OnUsbAfterTouchPoly);     // not yet implemented by USB MIDI library
  usbMIDI.setHandleProgramChange(OnUsbProgramChange);
  //usbMIDI.setHandleSongPosition(OnUsbSongPosition);         // not yet implemented by USB MIDI library
  //usbMIDI.setHandleSongSelect(OnUsbSongSelect);             // not yet implemented by USB MIDI library
  //usbMIDI.setHandleTuneRequest(OnUsbTuneRequest);           // not yet supported by USB MIDI library
  usbMIDI.setHandleRealTimeSystem(OnUsbRealTimeSystem);
  #ifdef ALLOW_CLOCK
    usbMIDI.setHandleTimeCodeQuarterFrame(OnUsbTimeCode);
  #endif
  //usbMIDI.setHandleSystemExclusive(OnUsbSysEx);
}


