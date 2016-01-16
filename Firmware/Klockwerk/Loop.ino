void loop() {
  usbMIDI.read();                                                   // read all the incoming midi messages
  MIDI.read();
    int humDummy = map(analogRead(A0), 0, 1023, 0, 100);
    if (humanizeAmt != humDummy) {
      //humanizeAmt = humDummy;  
      //Serial.print("Humanize: ");
      //Serial.println(humanizeAmt);
    }
    float swingDummy = map(analogRead(A1), 0, 1023, 0, 1000)/10.0; 
    if (swingAmt != swingDummy) {
      //swingAmt = swingDummy;  
      //Serial.print("Swing:    ");
      //Serial.println(swingAmt);
      
    }
}


