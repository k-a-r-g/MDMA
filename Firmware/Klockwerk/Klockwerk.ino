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

// Comments ...
//

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
//#define DIN
#define USB

float                 bpm                        = 120;               // the bpm for the clock (30.0-300.0)
float                 swingAmt                   = 50.0;             // AKAI MPC format: 50% is no swing
byte                  swingSpeed                 = 8;                // possible speeds as indicated above (0-11)          
byte                  humanizeAmt                = 0;              // 0%: off, 100% extreme
byte                  humanizeSpeed              = 8;                // possible speeds as indicated above (0-11)          

/* ---( Config End - from here on it is better if you know what you are doing )------------------------------------------------ */

#include <MIDI.h>

using namespace midi;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

#define               CALIBRATOR                   0                  // empirically determined calibration factor

#define               LED_PIN                      13

#define               CLOCK                        0xF8            
#define               START                        0xFA
#define               CONTINUE                     0xFB
#define               STOP                         0xFC




// MIDI: clock

IntervalTimer         clockTimer;
unsigned int          clockInterval;                                  // the intervall for each MIDI clock tick
volatile unsigned int clockMaster                = 0;
volatile int          clockCounter               = 0;                 // the clock is sent 24x per quarter note...
byte                  clockDivs[14]              = {3, 4, 6, 8, 9, 12, 16, 18, 24, 32, 36, 48, 72, 96};               // in clock pulses
unsigned int          swingDiv                   = 0;
int                   swingFactor                = 0;
boolean               swingPhase                 = false;
unsigned int          humanizeDiv                = 0;
int                   humanizeFactor             = 0;                

const int             normalArraySize = 101;
int                   normalIn[normalArraySize]  = { -4999997, -4999995, -4999992, -4999987, -4999979, -4999966, -4999946, -4999915, -4999867, -4999793, 
                                                     -4999683, -4999519, -4999277, -4998922, -4998409, -4997674, -4996631, -4995166, -4993129, -4990324, 
                                                     -4986501, -4981342, -4974449, -4965330, -4953388, -4937903, -4918025, -4892759, -4860966, -4821356, 
                                                     -4772499, -4712834, -4640697, -4554345, -4452007, -4331928, -4192433, -4031995, -3849303, -3643339, 
                                                     -3413447, -3159399, -2881446, -2580363, -2257469, -1914625, -1554217, -1179114, -792597, -398278, 
                                                     0, 398278, 792597, 1179114, 1554217, 1914625, 2257469, 2580363, 2881446, 3159399, 
                                                     3413447, 3643339, 3849303, 4031995, 4192433, 4331928, 4452007, 4554345, 4640697, 4712834, 
                                                     4772499, 4821356, 4860966, 4892759, 4918025, 4937903, 4953388, 4965330, 4974449, 4981342, 
                                                     4986501, 4990324, 4993129, 4995166, 4996631, 4997674, 4998409, 4998922, 4999277, 4999519, 
                                                     4999683, 4999793, 4999867, 4999915, 4999946, 4999966, 4999979, 4999987, 4999992, 4999995, 
                                                     4999997 };

float                   normalOut[normalArraySize]  = { -0.5, -0.49, -0.48, -0.47, -0.46, -0.45, -0.44, -0.43, -0.42, -0.41, 
                                                     -0.4, -0.39, -0.38, -0.37, -0.36, -0.35, -0.34, -0.33, -0.32, -0.31, 
                                                     -0.3, -0.29, -0.28, -0.27, -0.26, -0.25, -0.24, -0.23, -0.22, -0.21, 
                                                     -0.2, -0.19, -0.18, -0.17, -0.16, -0.15, -0.14, -0.13, -0.12, -0.11, 
                                                     -0.1, -0.09, -0.08, -0.07, -0.06, -0.05, -0.04, -0.03, -0.02, -0.01, 
                                                     0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 
                                                     0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 
                                                     0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 
                                                     0.3, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 
                                                     0.4, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 
                                                     0.5 };

int                   normalOutAdjusted[normalArraySize ];

