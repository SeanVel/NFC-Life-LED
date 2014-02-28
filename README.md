NFC-Life-LED
============

Game of life displayed on a LED matrix controlled by an Arduino Uno, with living cells 
added based on UID numbers of detected FeliCa-format NFC cards.

# Overview
The goal of this project was to create an interactive version of Conway's game of life. The 
interactions are controlled by a [NFC tag reader](http://www.adafruit.com/products/789) from Adafruit. The last 2 bytes of a FeliCa tag target ID are used to determine which cells to bring to life. The 
reason the FeliCa NFC standard was chosen was because it was the standard NFC 
tag used in our college ID cards which are used with Blackboard card readers for
door access and meal payments. So if you go to a college that uses Blackboard 
there is a good chance that the cards use FeliCa instead of the common MiFare standard. The game is
displayed on a [16x24 Red LED matrix](http://www.adafruit.com/products/555) purchased from Adafruit.

# Hardware Setup
To get the different components to work properly together, we mostly followed 
the guides provided by Adafruit for each of devices. However, instead of connecting the LED
matrix to the pins on the arduino, we soldered the wires to the vias on the NFC 
shield that aren't used by the pin headers to connect to the Arduino Uno. This setup
was used so that the connections would be more secure.

# Hardware Details
As described previously, the NFC shield is connected directly to the Arduino Uno, and the connection to the LED matrix passes through the shield to the Arduino. This whole assembly is powered by the +5 V delivered to the Arduino over USB. While the standard 10 watts supplied by USB may be overdrawn if all 384 LEDs in the matrix are simultaneously driven at full brightness, causing the system to hang, this configuration does not happen throughout the normal course of the game of life.

# Software Setup
This project uses library repos that were forked from Adafruit. There are future 
plans to expand the functions that are within these forked libraries so that 
there would be more ways to use the NFC and LED matrix. Since the libraries are 
included as submodules there are a few extra steps needed to help ensure that the
code will run properly. 

# Software Details
The lifegame library created for this project implements a game of life parameterized by the number of rows and columns, so it can easily be expanded to larger sizes that fit within the memory of the Arduino. It also employs a toroidal structure, meaning patterns that move off one edge of the game wrap around to the opposite edge. The standard rules of the game of life are applied to compute successive generations.

The Adafruit library for the HT1632 driven LED matrix is used as-is to individually set and clear LEDs in the display.

While the Adafruit library for the PN532 based NFC shield was written to interact with the MiFare standard of NFC tags, it provided a starting point for how to send packets to the PN532 controller and detect tags with its `InListPassiveTarget` instruction. Details for modifying packets sent with the `InListPassiveTarget` instruction to detect FeliCa tags were found in the [PN532 User Manual](http://www.adafruit.com/datasheets/pn532um.pdf). The [FeliCa Card User's Manual](http://www.proxmark.org/files/Documents/13.56%20MHz%20-%20Felica/card_usersmanual_2.0.pdf) was consulted to determine the structure of packets to send to FeliCa tags and interpret the poll response from them.

In the main Arduino program, the NFC shield and the LED display are both initialized, and a game of life is instantiated fitting the size of the LED display. In its loop, cells in the game are brought to life based on any NFC UIDs detected. The display is updated, and the next generation of the game is computed before restarting the loop.

## Using GIT
The best way to set up and retrive the library folders 
for the NFC tag reader and LED matrix is to use git to pull the main repo then 
use the command 'git submodule init' then 'git submodule update' to add the sub git
repos into this main one. [This link](http://www.git-scm.com/book/en/Git-Tools-Submodules) offers more info about git submodules. Then place all of the library folders (Adafruit_NFC, HT1632, and lifegame) into the libraries 
folder within the Arduino work path. For more help with Arduino libraries, follow [this link](http://arduino.cc/en/Hacking/Libraries#.UxAniOqPL3Y). The libraries folder may need to be created when 
first using the Arduino IDE.

## Downloading ZIP files
If using git is not an option for you, it is recommended that you download this file as a zip.
Then using the links to the libraries will bring you to the repos that hold the files for each
library. 
