# Kontroller
A Teensy based "USB stick", that modulates MIDI messages to facilitate playing the Korg Kaossilator Pro (+) with standard equipment, e.g. MIDI keyboards
Implementation is solder free and is designed for stock Teensy development boards.

Note that we are translating notes into coordinates on the touch pad's XY-axis of your Kaossilator Pro (+)
This means: - the scale set on the Kaossilator will be respected
            - the octave range set on the Kaossilator will will modulate the notes played
            - for a one-to-one mapping between key pressed and note played, set the octave range to full on your Kaossilator

Configureable options are:
            - enable/disable modulation of the X-axis (the note's pitch) by your keyboard's pitch wheel
            - enable/disable notes velocity to define the Y-axis (often a filter or delay)
            - enable/disable a control change # (which can be freely chosen) to define the Y-axis
            - enable/disable aftertouch to modify the Y-axis value
            - enable/disable indication of played notes on the built-in LED of the Teeensy (Why not?)
            
