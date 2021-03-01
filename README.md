# Chord Player
Creative Embedded Systems HW 2, by Claire Jenkins

### Description
A 4-voice instrument with three states: solo pitch, solo volume, and global volume adjustment. Values for pitch and volume can be increased or decreased using a joystick. Each voice has a corresponding red LED which lights up when voice is selected, meaning it will be affected by joystick input. Two yellow LEDs correspond to to volume adjustment and pitch adjustment. Pressing a red button cycles through the four voices, and pressing a yellow button toggles between volume and pitch adjustment. A switch toggles between solo pitch/volume and global volume adjustment.

### Materials
- Raspberry Pi 4
- ESP-32
- Joystick
- DPST Switch
- Two buttons (1 red, 1 yellow)
- 6 LEDs (4 red, 1 green, 1 blue)
- 6 220Ω resistors
- 2 10kΩ resistors
- connecting wires

### ESP-32 Setup
Connect red button ESP-32 GPIO pin 13 using 10kΩ resistor. Repeat with yellow button and GPIO 14.

Connect red LEDs to GPIO pins 4, 0, 5, 15 using 220Ω resistors. Connect yellow LEDs to GPIO 18 and 19 with 220Ω resistors.

Connect joystick VRY pin to GPIO 26.

Connect DPST switch to GPIO 32.

Connect ESP-32 to computer. Download `combined_hardware.ino` from this repository, and upload it to ESP-32.

Plug ESP-32 into Raspberry Pi.

### Pi Setup
Install Sonic-Pi on your Raspberry Pi.

Install pythonosc by entering 
` pip3 install python-osc`
on the command line.

Download `control.py` from this repository. Make sure that the Serial port in line 8 matches the port being used by the ESP-32.

Run control.py by entering
` python3 /[INSERT PATH]/control.py`
on the command line.

Open Sonic Pi on Raspberry Pi. Copy code from `player.rb` in this repository into Sonic-Pi, and click 'Run.'

A demo of the instrument can be found [here](https://youtu.be/eMmP__pVcMY).
