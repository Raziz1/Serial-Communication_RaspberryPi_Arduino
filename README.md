# Serial-Communication_RaspberryPi_Arduino 💻📶💻
One way serial communication from Raspberry Pi to Arduino Mega/Uno

<p> 
  <img width=384 height=384 align='Right' src="https://github.com/Raziz1/Serial-Communication_RaspberryPi_Arduino/blob/main/images/Rasp-Arduino.png? raw=true">
</p>

## Parts 🛠
* [Raspberry Pi 4 Model B](https://www.amazon.ca/Raspberry-Pi-Computer-Model-4GB/dp/B07W4JM192/ref=sr_1_7?dchild=1&keywords=raspberry+pi+4&qid=1607186145&sr=8-7)
* [Arduino Mega/Uno](https://www.amazon.ca/Elegoo-Board-ATmega2560-ATMEGA16U2-Arduino/dp/B01H4ZLZLQ/ref=sr_1_12?dchild=1&keywords=arduino+mega&qid=1607186201&sr=8-12)
* [USB Type A to USB Type B](https://www.amazon.ca/JSAUX-Printer-Scanner-Compatible-Lexmark/dp/B07RW66XRW/ref=sr_1_7?dchild=1&keywords=usb+a+to+usb+b&qid=1607186219&sr=8-7)
* [Kuman TFT display](https://www.amazon.ca/480x320-Screen-Module-Arduino-Without/dp/B07NWH47PV/ref=sr_1_24?dchild=1&keywords=tft+display+kuman&qid=1607187338&sr=8-24)

## Overview
* The following demonstrates how to communicate between the Raspberry Pi and the Arduino Mega. In this project it is done only one way, from the Raspberry Pi to the Arduino Mega. If you would like to perform two way communcation check out this link on [Serial Communcation Between Raspberry Pi and Arduino](https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/)
* The python (.py) file is to be run on the Raspberry Pi while the arduino (.ino) file is to be uploaded to the arduino board
* This project is a general display that shows the weather, time, date, and snow day prediction using the Raspberry Pi's WIFI capabilities
* The tft display I used has a touchscreen and so the code is written so that when you touch the screen it changes the snow day prediction to the bus status checker
* You will have to input your OpenWeatherMap API key as well as your zip code for the snowday predictor

## Libraries 📚

<p> 
  <img width=256 height=384 align='Right' src="https://github.com/Raziz1/Serial-Communication_RaspberryPi_Arduino/blob/main/images/SnowdayPredictor.png? raw=true">
</p>

### Arduino
* Kuman TFT Display Shield Libraries
  - [LCDWIKI_gui](https://github.com/lcdwiki/LCDWIKI_gui)
  - [LCDWIKI_kbv](https://github.com/lcdwiki/LCDWIKI_kbv)
  - [LCDWIKI_touch](https://github.com/lcdwiki/LCDWIKI_touch)
* [Arduino JSON](https://github.com/bblanchon/ArduinoJson)
  - Arduino JSON version 5.13.5 worked for me
 ### Raspberry Pi 4
 *  [pyserial](https://pypi.org/project/pyserial/)
 *  [requests](https://pypi.org/project/requests/)
 *  [json](https://docs.python.org/3/library/json.html)
 *  [datetime](https://docs.python.org/3/library/datetime.html)
 *  [re](https://docs.python.org/3/library/re.html)
 *  [beautifulsoup4](https://pypi.org/project/beautifulsoup4/)

## API/Websites 📶
* [OpenWeather](https://openweathermap.org/)
* [OSTA](http://www.ottawaschoolbus.ca/)
* [SnowdayPredictor](https://www.snowdaycalculator.com/)

## Raspberry Pi 4 setup
* In the code you will have to check which USB port to write serial data to.
  1. Press CTRL + ALT + T to open the terminal
  2. Type in 'ls /dev/tty'. A list of terminals should show up
  3. Plug in your Arduino board into the usb port and run the same command as in the previous step. Check to see if there are any new list items. It is usually (AMC0 or AMC1)
  4. Find the new list item and input it into the python code where it says 'ser = serial.Serial('/dev/ttyACM1',9600)'
 
