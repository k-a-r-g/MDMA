// K-Ossillator by Karg (Timm Schlegelmilch)
//
// licenced under Creative Commons Attribution-ShareAlike 4.0
// http://creativecommons.org/licenses/by-sa/4.0/


// uncomment to quantize your notes to the MIDI clock
#define QUANTIZE

// uncomment to enable Y-Axis modulations
#define VELOCITY
#define CHANNEL       80

// uncommment to select Aftertouch mode
// #define AFTERTOUCH_X
#define AFTERTOUCH_Y




void OnNoteOn(byte channel, byte note, byte velocity) {}
void OnNoteOff(byte channel, byte note, byte velocity) {}
void OnPitchBend(byte channel, int bend) {}
void OnControlChange(byte channel, byte control, byte value) {}
void OnAfterTouch(byte channel, byte value) {}

void setup() {
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
//  usbMIDI.setHandlePitchBend(OnPitchBend);

#ifdef CHANNEL
  usbMIDI.setHandleControlChange(OnControlChange);
#endif

#ifdef AFTERTOUCH
  usbMIDI.setHandleAfterTouch(OnAfterTouch);
//  usbMIDI.setHandleAfterTouchPoly();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
