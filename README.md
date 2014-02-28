NFC-Life-LED
============

Game of life displayed on a LED matrix controlled by an Arduino with starting cells 
determined by UID numbers FeliCa NFC cards 

# Overview
The goal of this project was to create an interactive game of life by Conway's. The 
interactions are controlled by a [NFC tag reader](http://www.adafruit.com/products/789) from Adafruit. The last 2 bytes of 
a Felica tag target ID are used to determine which cells to bring to life. The 
reason the Felica NFC standard was choosen was because it was the standard NFC 
tag used in our college id cards which are used with Blackboard card readers for
door access and meal payments. So if you go to a college that uses Blackboard 
there is a good chance that the cards use Felica instead of MiFare. The game is
displayed on a [16x24 Red LED matrix](http://www.adafruit.com/products/555) purchased from Adafruit. 

# Hardware Setup
To get the different components to work properly together, we mostly followed 
the guide provided by Adafruit for each of devices. However, instead of connecting the LED
matrix to the pins on the arduino, we soldered the wires to the vias on the NFC 
shield that aren't used by the pin headers to connect to the Arduino Uno. This setup
was used so that the connections would be more secure. More details are below:

# Software Setup
This project uses library repos that were forked from Adafruit. There are future 
plans to expand the functions that are within these forked libraries so that 
there would be more ways to use the NFC and LED matrix. Since the libraries are 
included as submodules there are a few extra steps needed to help ensure that the
code will run properly. 

## Using GIT
The best way to set up the retrive the library folders 
for the NFC tag reader and LED matrix is to use git to pull the main repo then 
use the command 'git submodule init' then 'git submodule update' to add the sub git
repos into this main one. For more info about submodules, 
[this link](http://www.git-scm.com/book/en/Git-Tools-Submodules) offers more info.
Then place all of the library folders (Adafruit_NFC, HT1632, and lifegame) into the libraries 
folder within the Arduino work path. For help with this task, [this link](http://arduino.cc/en/Hacking/Libraries#.UxAniOqPL3Y) will
provide some more help with Arduino libraries. This folder may need to be created when 
first using Arduino.

## Downloading ZIP files
If using git is not an option for you, it is recommended that you download this file as a zip.
Then using the links to the libraries will bring you to the repos that hold the files for each
library. 