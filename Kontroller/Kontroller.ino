// Kontroller by Karg (Timm Schlegelmilch)
// Control your Kaossilator Pro (+) with standard midi notes
//
// licenced under Creative Commons Attribution-ShareAlike 4.0
// http://creativecommons.org/licenses/by-sa/4.0/

//
//  Note that we are translating notes into coordinates on the touch pad's XY-axis of your Kaossilator Pro (+)
//  This means: - the scale set on the Kaossilator will be respected
//              - the octave range set on the Kaossilator will will modulate the notes played
//              - for a one-to-one musical mapping between key pressed and note played, set the octave range to full on your Kaossilator
//


/* ---( Config Start - change to your likings )-------------------------------------------------------------------------------- */

// change the numbers according to the settings in your Kaoss device
#define KAOSS_MIDI_CHANNEL 2            // MIDI channel for the Kaoss device
#define KAOSS_CC_PAD       92           // pad on/off control change # (check the manual for more information)
#define KAOSS_CC_X         12           // pad on/off control change # (check the manual for more information)
#define KAOSS_CC_Y         13           // pad on/off control change # (check the manual for more information)


// uncomment to enable, comment to disable
#define X_PITCH_CHANGE                  // pitch bend wheel modulates the note
// #define Y_VELOCITY                   // touch pad Y-axis: note velocity is translated into Y axis value
#define Y_CONTROL_CHANGE   1            // touch pad Y-axis: chontrol change # that is translated into Y axes value (e.g. 1 for Modulation Wheel)
#define Y_AFTERTOUCH                    // touch pad Y-axis: aftertouch modulates Y axis value

#define NOTE_INDICATION                 // lights up the LED while a note is played


/* ---( Config End - from here on it is better if you know what you are doing )------------------------------------------------ */


#define CLOCK              0xF8            
#define START              0xFA
#define CONTINUE           0xFB
#define STOP               0xFC


byte  xPad  = 0;
byte  yPad  = 0;
int   pitchChange = 0;
int   afterTouch  = 0;

void OnNoteOn(byte channel, byte note, byte velocity) {
  if (channel == KAOSS_MIDI_CHANNEL) {
    xPad = note;
#ifdef Y_VELOCITY
    yPad = velocity;
#endif
   
    if (velocity) { 
#ifdef NOTE_INDICATION
      digitalWrite(13, HIGH);
#endif
      usbMIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);
      usbMIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
      usbMIDI.sendControlChange(KAOSS_CC_PAD, 127, 2);
    } else {
      OnNoteOff(channel, constrain(xPad + pitchChange, 0, 127), velocity);    
    }
  }
}


void OnNoteOff(byte channel, byte note, byte velocity) {
  if (channel == KAOSS_MIDI_CHANNEL) {
    if (note == xPad) {
#ifdef NOTE_INDICATION
      digitalWrite(13, LOW);  
#endif
      usbMIDI.sendControlChange(KAOSS_CC_PAD, 0, 2);
    }
  }
}

  
void OnPitchChange(byte channel, int pitch) {
#ifdef X_PITCH_CHANGE
  pitchChange = round(pitch/64.0)-128;
  usbMIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);        
#endif
}


void OnControlChange(byte channel, byte control, byte value) {
  if (channel == KAOSS_MIDI_CHANNEL) {
#ifdef Y_CONTROL_CHANGE
    if (control == Y_CONTROL_CHANGE) {
      yPad = value;
      usbMIDI.sendControlChange(KAOSS_CC_Y, yPad, KAOSS_MIDI_CHANNEL);        
    }
#endif
  }
}

  
void OnAfterTouch(byte channel, byte value) {
#ifdef Y_AFTERTOUCH
  afterTouch = value;
  usbMIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
#endif
}



void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
#ifdef X_PITCH_CHANGE
  usbMIDI.setHandlePitchChange(OnPitchChange);
#endif
#ifdef Y_CONTROL_CHANGE
  usbMIDI.setHandleControlChange(OnControlChange);
#endif
#ifdef Y_AFTERTOUCH
  usbMIDI.setHandleAfterTouch(OnAfterTouch);
#endif
}

void loop() {
  usbMIDI.read();                                                   // read all the incoming midi messagesmain code here, to run repeatedly:
}
