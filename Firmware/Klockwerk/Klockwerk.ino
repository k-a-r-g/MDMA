// MDMA - Mutli Duty MIDI Aid
// Kontroller Firmware
// by Karg (Timm Schlegelmilch)
//
// A clock generator with sub millisecond precicion and accuracy
// Note: at 140 bpm, a MIDI clock pulse is 17.86 ms long (at 300 bpm it is still 8.33 ms), so we are very good
//
// Detailed instructions are published on:
// http://karg-music.blogspot.de/p/multi-duty-midi-aid.html
//
// Licenced under Creative Commons Attribution-ShareAlike 4.0
// http://creativecommons.org/licenses/by-sa/4.0/

/*
       (d): dotted time, one and half note length
       (tr) tripplet time, two thirds of duration
     
       0:  32th notes   - 3 ticks
       1:  16th (tr)    - 4 ticks
       2:  16th         - 6 ticks
       3:  8th (tr)     - 8 ticks
       4:  16th (d)     - 9 ticks
       5:  8th          - 12 ticks
       6:  quarter (tr) - 16 ticks
       7:  8th (d)      - 18 ticks
       8:  quarter      - 24 ticks
       9:  half (tr)    - 32 ticks
       10: quarter (d)  - 36 ticks
       11: half         - 48 ticks
*/


/* ---( Config Start - change to your likings )-------------------------------------------------------------------------------- */

// un-/comment to enable/disable MIDI DINs and USB
#define DIN
#define USB

float                 bpm                        = 120.0;             // the bpm for the clock (30.0-300.0)

/* ---( Config End - from here on it is better if you know what you are doing )------------------------------------------------ */


#ifdef DIN
  #include <MIDI.h>
  using namespace midi;
  MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
#endif 

#define               LED_PIN                      13

#define               CLOCK                        0xF8            
#define               START                        0xFA
#define               CONTINUE                     0xFB
#define               STOP                         0xFC

IntervalTimer         clockTimer;
unsigned int          clockInterval;                                  // the intervall for each MIDI clock tick


