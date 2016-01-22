# MDMA - Multi Duty MIDI Aid

The MDMA hardware and software are designed in a modular fashion, so you can choose which functionalities are important to you and if, as well as how, you want to implement them:

Based on the Teensy 3.1 development platform, the MDMA sports MIDI over USB, an EEPROM to load/save data, and a status LED directly out of the box without any soldering required. However, multiple extensions (MIDI Din, CV/Gate, buttons, potentiometers, etc) are already under development and will be published here: [Electronic Sound Creation - MDMA][mdma]

The real Multi Duty part, comes from the different firmwares which are hand-tailored for the various hardware extensions. The employ your existing hardware configuration in a, simple to configure, way, and are easy to upload through the official Arduino IDE. Maybe the different firmwares will be combined, and a small GUI will allow configuration and enabling/disabling of functions, any time in the future, but it is not high on my priority list, yet. Immediate future plans include a firmware to determine accuracy and precision of MIDI clocks, a drum roller, a general purpose midi controller, and some bonus firmwares.


### Version
1.2.1

### Hardware features
- [Base][mdma] - MIDI over USB
- [Base][mdma] - load/save (eeprom)
- [Base][mdma] - Status LED
- [DIN extension][midification] - MIDI DIN in
- [DIN extension][midification] - MIDI DIN out

### Firmwares
- [Klockwerk][klockwerk] - MIDI clock generator
- [Kommunikator][kommunikator] - A MIDI bridge between DIN and USB with note/clock/channel filtering
- [Kontroller][kontroller] - Play the Korg Kaossilator Pro(+) and Kaoss Pad 3(+) with any midi equipment

**Use, test, modify to your likings. If you have further ideas for extensions or firmwares, let me know :)**

   [mdma]: <http://karg-music.blogspot.de/p/multi-duty-midi-aid.html>
   [midification]: <http://karg-music.blogspot.de/2016/01/midification.html>
   [klockwerk]: <http://karg-music.blogspot.de/2016/01/klockwerk-midi-clock-generator.html>
   [kommunikator]: <http://karg-music.blogspot.de/p/multi-duty-midi-aid.html>
   [kontroller]: <http://karg-music.blogspot.de/2015/11/play-kaossilator-pro-with-standard-midi.html>
