//====================Libraries====================
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include <TouchScreen.h> //touch library
#include "font.h"
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset
//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV mylcd(320,480,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset


//====================Variables====================
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//param calibration from kbv
#define TS_MINX 906
#define TS_MAXX 116

#define TS_MINY 92
#define TS_MAXY 952

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Weather Variables
String temp = "15";
String description = "Cloudy";
String temp_max = "16";
String temp_min = "3";
String wind = "5";
String icon = "01d";
//Time Variables
String current_time = "00:00";
String current_date = "1-1-2020";
//Snow day Variables
int percentage = 99;
//News Variables
String osta_color  = "green";
String osta_status = "Running";
boolean switchBottom = false;
boolean checkTouch = true;
int interval = 2000;
// Tracks the time since last event fired
unsigned long previousMillis = 0;



//==================== Function for Drawing Squares ====================
void fill_rectangle_test(void) {
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(YELLOW);
  mylcd.Fill_Round_Rectangle(5, 5, 315, 96, 8);
  mylcd.Set_Draw_color(WHITE);
  mylcd.Fill_Round_Rectangle (5, 101, 315, 261, 8);
  mylcd.Fill_Round_Rectangle (5, 266, 315, 475, 8);

}

//==================== Function for Drawing CLOCK ====================
void text_time(void) {
  //Text (TIME)_____________________________________
  mylcd.Set_Text_Mode(1);
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Size(5);
  mylcd.Print_String(current_time, 80, 20);
  //Text (DATE)____________________________________
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(current_date, 100, 75);

}

//==================== Function for Drawing Weather ====================

void text_weather(void) {
  //Current Temp________________________
  //mylcd.Set_Text_Mode(1);
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_Size(5);
  mylcd.Print_String(temp + "C", 110, 125);
  //Description_________________________
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(description, 110, 175);
  //Max Temp_________________________
  mylcd.Print_String("Max:" + temp_max + "C", 110, 200);
  //Min Temp_________________________
  mylcd.Print_String("Min:" + temp_min  + "C", 200, 200);
  //Percentage of Precipitation_________________________
  mylcd.Print_String("Wind: " + wind + "km/h", 110, 225);
}

//====================Function for drawing SnowDay Predictor====================
void snow_predictor(void) {
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("SnowDay %", 60, 290);

  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_Size(6);
  mylcd.Print_String(String(percentage) + "%", 50, 360);

  if (percentage >= 50 & percentage <= 75) {
    mylcd.Set_Draw_color(YELLOW);
  } else if (percentage >= 76 & percentage <= 100) {
    mylcd.Set_Draw_color(RED);
  } else {
    mylcd.Set_Draw_color(GREEN);
  }
  mylcd.Fill_Round_Rectangle(176, 465 - (percentage * 1.3) , 274, 465, 8);
  //mylcd.Fill_Round_Rectangle(275, 335 , 275, 465, 8);

  mylcd.Set_Draw_color(BLACK);
  //Boundary Empty Rectangle
  mylcd.Draw_Round_Rectangle(175 , 335 , 275, 465, 8);


}

//====================Function for drawing Icons====================
void show_pic(void)
{
  mylcd.Set_Addr_Window(25, 150, 80, 205);
  if (icon == "01d" || icon == "01n") {
    mylcd.Push_Any_Color(oned, 2400, 1, 1);
  } else if (icon == "02d" || icon == "02n") {
    mylcd.Push_Any_Color(twod, 2400, 1, 1);

  } else if (icon == "03d" || icon == "03n") {
    mylcd.Push_Any_Color(threed, 2400, 1, 1);

  } else if (icon == "04d" || icon == "04n") {
    mylcd.Push_Any_Color(fourd, 2400, 1, 1);

  } else if (icon == "09d" || icon == "09n") {
    mylcd.Push_Any_Color(nined, 2400, 1, 1);

  } else if (icon == "10d" || icon == "10n") {
    mylcd.Push_Any_Color(tend, 2400, 1, 1);

  } else if (icon == "11d" || icon == "11n") {
    mylcd.Push_Any_Color(elevend, 2400, 1, 1);

  } else if (icon == "13d" || icon == "13n") {
    mylcd.Push_Any_Color(thirteend, 2400, 1, 1);

  } else if (icon == "50d" || icon == "50n") {
    mylcd.Push_Any_Color(fiftyd, 2400, 1, 1);

  }
}

//====================Function for bus status====================
void bus_status(void) {
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_Size(5);
  mylcd.Print_String("BUS STATUS", 15, 290);

  if (osta_color == "yellow") {
    osta_status = "Delay";
    mylcd.Set_Draw_color(YELLOW);
  } else if (osta_color == "red") {
    mylcd.Set_Draw_color(RED);
    osta_status = "Canceled";
  } else {
    osta_status = "Running";
    mylcd.Set_Draw_color(GREEN);
  }
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Set_Text_Size(3);
  mylcd.Print_String(osta_status, 15, 360);
  mylcd.Fill_Circle(225, 400, 60);
  mylcd.Set_Draw_color(BLACK);
  mylcd.Draw_Circle(225, 400, 62);
}

//====================Draw all the graphics====================
void draw() {
  fill_rectangle_test();
  text_time();
  text_weather();
  show_pic();
  if (switchBottom) {
    bus_status();
  } else {
    snow_predictor();
  }
}

//====================Setup Function====================
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  mylcd.Init_LCD();
  draw();
}

//====================Main Function====================
// the loop function runs over and over again forever
void loop() {

  // Get snapshot of time
  unsigned long currentMillis = millis();
  // How much time has passed, accounting for rollover with subtraction!
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    checkTouch = true;
  }

  //If the screen has been touched and it is within the interval change the snow day predictor to the bus status
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (checkTouch == true && p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    switchBottom = !switchBottom;
    draw();
    checkTouch = false;
  }

  //Receive serial data from Raspberry PI 4 and assign our variables
  if (Serial.available() > 0) {
    // read the incoming byte:
    current_date = Serial.readStringUntil(',');
    current_time = Serial.readStringUntil(',');
    description =  Serial.readStringUntil(',');
    icon =  Serial.readStringUntil(',');
    temp =  Serial.readStringUntil(',');
    temp_max =  Serial.readStringUntil(',');
    temp_min =  Serial.readStringUntil(',');
    wind =  Serial.readStringUntil(',');
    osta_color = Serial.readStringUntil(',');
    String temp_percentage = Serial.readStringUntil('\n');
    percentage = temp_percentage.toInt();

    //When we receive new data update the screen
    draw();
  }
}
