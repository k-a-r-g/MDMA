void loop() {
  #ifdef USB
    usbMIDI.read();                                                   // read all the incoming midi messages
  #endif
  #ifdef DIN
    MIDI.read();
  #endif
}


