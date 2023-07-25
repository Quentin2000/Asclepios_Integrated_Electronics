# Master Project

## Integration of a miniaturized O2 sensor into a space suit helmet.

#### Author: Quentin Delfosse
#### Academic Supervisor: Pr. Guillermo Villanueva
#### Technical Supervisor: Arnault Monoyer

## Repository files


This repository includes the following design files:
- **HW**: Kicad hardware files for the interface board and air quality sensor board.
- **SW**: Arduino files used to flash the ESP32 S2 Mini 1 computer.
- **SD**: Setup files for the SD card.

To access CAD design files, please refer to the Google Drive: https://drive.google.com/drive/folders/1vZVMf6BT2zpStATiHxgfttCtssU6DIhK?usp=drive_link.

## Introduction

Asclepios is a student-led project from Switzerland aiming at organizing simulations of manned space missions. For this purpose, the association rents existing infrastructure and builds its base inside. Therefore, by design, the mission will take place on Earth, where many parameters are different than on other celestial bodies. However, the analog astronauts will live together in close contact during the two weeks of the mission to experience the constraints of extraterrestrial environments during the Earth-based simulation. The project aims at optimizing their environment to make their mission as realistic as possible.

<br />

This project aims at integrating a miniaturized O2 sensor into a space suit helmet to monitor the user's breathable atmosphere. Both mechanical and electrical sensor integration will be required. Additionally, the sensor data will need to be processed. Thus, a graphical interface for the visualization of the O2 data in real time will need to be created.

<p align="center">
<img src="ReadMe Images/Final_product.png" width="400"></img>
</p>

## Setup

### Hardware

The system is made of 3 stacked layers:
- **Upper stage**: Sensor stage (O2 + Air quality sensors)
- **Middle stage**: Interface stage 
- **Lower stage**: Main computer stage (ESP32 S2 Mini 1)

**CAREFUL: Before connecting two boards together, please make sure that the signals on both end match! This can be checked on the surface of the boards! Otherwise you may fry the sensors and the computer!**

To assemble the system, simply stack the layers on top of each other:
- Connect the main computer board (black one) to the interface board (long green one).
- **Make sure to check that the signals match: 3V3, Ground, 5V!**
- Insert the SD card into the interface board (bottom face).
- Connect the screen to the interface board (long white connector).
- Connect the Air quality sensor board (small green one) on top of the rooting board (long green one).
- **Again, check that the signals match: 3V3, Ground, 5V!**
- Place the stacked-up module on the 4 rails of the bottom cover. Only one orientation should fit.
- Connect the O2 sensor cable to the O2 sensor board.
- Insert the O2 sensor into the top cover hole, following the 2 rails and making sure that its cable comes out through the dedicated hole on the side.
- Place a foam on top of the interface board where the O2 sensor will be positioned (next to the air quality sensor).
- Close both end on the case together.
- Plug a USB cable to the micro usb port of the main computer and connect it to the portable battery.
- Power up the battery.


The screen should initialize after a couple of seconds and show a similar screen as the following one:
<p align="center">
<img src="ReadMe Images/Display.png" width="400"></img>
</p>


The following figure shows a guidethrough of the procedure.
<p align="center">
<img src="ReadMe Images/Mounting_strategy.png" width="400"></img>
</p>

### Software

To display the sensors data, you will need the following package:
```ruby
pip install pandas 
```

To retrieve the data from the SD card, the following procedure must be applied:
- Plug it into your computer
- Open the SD card folder and check the mission log which you want to display
- Open a terminal window
- Go to the SD card directory, something like the following for MAC OS users.
```ruby
 cd /Volumes/NO\ NAME 
```
- Type the following command, where **x** is the number of the mission log to display. You may also need to change to **python** instead of **python3** depending on your computer
```ruby
python3 display.py mission_log_x 
```

This will create a png file with the sensor graphs over the mission duration and an excel file with these values.
<p align="center">
<img src="ReadMe Images/Sensor_readings.png" width="400"></img>
</p>


