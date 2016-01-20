// Kommunikator by Karg (Timm Schlegelmilch)
// A MIDI bridge between DIN and USB with basic filter options
//
// Detailed instructions are published on:
// http://karg-music.blogspot.de
//
// Licenced under Creative Commons Attribution-ShareAlike 4.0
// http://creativecommons.org/licenses/by-sa/4.0/

// SysEx forwarding not implemented yet (working on that)
// AfterTouchPoly, SongPosition, SongSelect, TuneRequest not implemented yet (not supported by usb library, and currently no means to test my own implementation)


/* ---( Config Start - change to your likings )-------------------------------------------------------------------------------- */

// un-/comment to enable/disable MIDI DINs and USB
#define ALLOW_NOTES                   // allow/disallow note forwarding
#define ALLOW_CLOCK                   // allow/disallow RealTime message forwarding (clock, start, stop, continue, MTC)
#define MIDI_THRU                     // MIDI TRHU for the DINs

byte    channelRemap    = 0;          // remaps all midi channels; 0=off

// CHANNEL FILTER, true= channel is enabled; false= channel is disabled
//                      1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16     
boolean channels[16] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};



/* ---( Config End - from here on it is better if you know what you are doing )------------------------------------------------ */

#include <MIDI.h>

using namespace midi;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);





