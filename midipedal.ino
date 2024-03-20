/*
created by Marco Perazzolo

v1 - 20/03/2024

USB midi pedal

requisites:
-Arduino Leonardo (or other arduino board with native USB connection);
-universal pedal for piano (you can also use a switch if you want but it won't be a midi pedal)

optional:
-if you want to be sure that it works you can download any midi tester or use an online one.

backstory of the project:
I was using a yamaha portatone ps-6100 as a midi piano, but the signal from the sustain pedal connected to the keyboard wasn't sent to the pc throught the midi interface so I decided to make my own midi sustain pedal. after trying many projects found on internet(none of them really worked for more than a day :( ), I decided to create one from scratch.

sources from where I stol- BORROWED some of this code:
-https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino
-https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_read/MIDIUSB_read.ino
*/

/**************************************************************
                      !!!!!!!!!!!!!!!!!!!
          PEDAL HAS TO BE IN NORMALLY CLOSED MODE (NC)
**************************************************************/

#include <MIDIUSB.h>

void setup(){
    Serial.begin(115200);
    pinMode(5, INPUT);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop(){
    static int lastPedalState = HIGH;  // Assuming the pedal is normally HIGH when not pressed
    
    int pedalState = digitalRead(5);
    
    if(pedalState != lastPedalState) {
        if(pedalState == LOW) {
            controlChange(0, 64, 127); // Pedal pressed
        } else {
            controlChange(0, 64, 0);   // Pedal released
        }
        lastPedalState = pedalState;
    }
}



//this section of code is here to do absolutely nothing but me trying not to switch tab every five seconds

// controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 

/*
midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
    }
  } while (rx.header != 0);
*/
