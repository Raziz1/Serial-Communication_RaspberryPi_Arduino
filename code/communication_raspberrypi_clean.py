#!/usr/bin/env python3
#====================Import Libraries====================
import serial
import time
import requests
import json
import datetime
import re
from bs4 import BeautifulSoup

#====================Variables====================
#OpenWeatherAPI Variables
apiKey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
temp = 0.00
maxTemp = 0.00
minTemp = 0.00
rain = 0
descriptor = "" 
wind = 0.00
icon = ""

#Snow Day predictor Variables
zip_code = "XXXXXX"
URL = "https://www.snowdaycalculator.com/prediction.php?zipcode="+zip_code+"&snowdays=0&extra=-0.4&"
res = requests.get(URL)
html_page = res.content
soup = BeautifulSoup(html_page, 'html.parser')

# Get tomorrows date
date_tomorrow = datetime.date.today() + datetime.timedelta(days=1)
set_time = datetime.datetime.now()

# Get OSTA
URL1 = "http://www.ottawaschoolbus.ca/"
res1 = requests.get(URL1)
html_page1 = res1.content
soup1 = BeautifulSoup(html_page1, 'html.parser')

# Function that gets the OSTA bus status
def busStatus():
    try:
        #osta_status = soup1.find("h4", attrs={"class": "alert"}).get_text()  # get_text() strips the HTML tags
        osta_status = soup1.find("div", attrs={"class": "light red"})
        if osta_status==None:
            osta_status = soup1.find("div", attrs={"class": "light yellow"})
            if osta_status==None:
                osta_status = soup1.find("div", attrs={"class": "light green"})
                osta_status = "green"
            else:
                osta_status="yellow"
        else:
            osta_status="red"
                
        #print(osta_status)
        return osta_status
    except:
        osta_status = "Failed"
        return osta_status


#====================Forecast Function====================
def forecast(lat, long):
    url = "https://api.openweathermap.org/data/2.5/onecall?lat=" + lat + "&lon=" + long + "&exclude=minutely," \
                                                                                          "hourly,alerts&appid=" + apiKey + "&units=metric"
    # Use parsed long and lat coordinates to request API JSON file
    response = requests.get(url)
    data = json.loads(response.text)
    # Catch exception of entered location is invalid
    try:
        #Set the variables to global
        global temp, maxTemp, minTemp, descriptor, wind, icon
        icon = data["current"]["weather"][0]["icon"]
        temp = data["current"]["temp"]
        maxTemp = data["daily"][0]["temp"]["max"]
        minTemp = data["daily"][0]["temp"]["min"]
        descriptor = data["daily"][0]["weather"][0]["description"]
        wind = data["daily"][0]["wind_speed"]
        try:
            rain = (data["daily"][0]["rain"])  # If rain is null set to 0
        except KeyError:
            rain = 0

        # Print centered forecast
        print(("____________________").center(40))
        print(("|" + "Temp: " + str(temp) + "°C" + "|").center(40))
        print(("|" + "Max Temp: " + str(maxTemp) + "°C" + "|").center(40))
        print(("|" + "Min Temp: " + str(minTemp) + "°C" + "|").center(40))
        print(("|" + "Rain: " + str(rain) + "%" + "|").center(40))
        print(("|" + "Wind: " + str(wind) + "km/h" + "|").center(40))
        print(("|" + "Description: " + descriptor + "|").center(40))
        print(("|" + "Icon: " + icon + "|").center(40))
        print(("____________________\n").center(40))
    except KeyError:
        print("Error! Try Again")

        
# Function that returns the snow day predictor percentage
def getPredictor():
    # Gets tomorrows date and prints it like the following: 20201101
    snowDate = ''.join((str(date_tomorrow.year), str(date_tomorrow.month), str(date_tomorrow.day).zfill(2)))
    try:
        # Get the text under the following html tag
        gdp_table = soup.find("table", attrs={"class": "prediction"})
        gdp_data = gdp_table.getText
        data_str = str(gdp_data)  # Convert the text to string

        # Find the string containg the prediction percentage
        for item in data_str.split("\n"):
            if "theChance[" + snowDate + "]" in item:
                # print(item.strip())
                # Strip the item and remove unnecessary strings
                s = item.strip()
                s = s.replace("theChance[" + snowDate + "] = ", "")
                s = s.replace("//PREDICTION", "")
                s = s.replace(";", "")
                s = s.replace("\t", "")
                # print(s)
                # Convert and round the float
                s = float(s)
                s = round(s)
                # print(s)
                # The predictor can return numbers larger than 100 and smaller 0 so round those so round them
                if s < 0:
                    s = 0
                elif s > 100:
                    s = 100
                return s
    except:
        print("error")
        return s

#====================Main Function====================
if __name__=='__main__':
    #Get the USB Serial port and set it's baud rate
    ser = serial.Serial('/dev/ttyACM0',9600)
    ser.flush()
    time.sleep(2) #Add a delay after flush otherwise it does not recieve
    date_tomorrow = datetime.date.today() + datetime.timedelta(days=1)  # Get the current date
    set_time = datetime.datetime.now()  # Get the current time
    get_time = set_time.strftime("%H:%M")  # Get the only the hours and minutes
    forecast("xx.xx","xx.xx") # You might have to chang the latitude and longitude depending on where you live
    full = str(date_tomorrow) +","+str(get_time)+","+descriptor+","+icon+","+str(round(temp))+","+str(round(maxTemp))+","+str(round(minTemp)) +"," + str(wind) +","+busStatus()+","+str(getPredictor())
    ser.write(full.encode()) # Encode the data and send it through the serial port
    exit() #Exit the program

