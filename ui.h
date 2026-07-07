/*
==========================================================
ui.h
World Cup Love Machine

OLED User Interface Function Declarations

==========================================================
*/

#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

//----------------------------------------------------
// Main Drawing Function
//----------------------------------------------------

void drawCurrentScreen(Adafruit_SSD1306 &display);

//----------------------------------------------------
// Individual Screens
//----------------------------------------------------

void drawTitle(Adafruit_SSD1306 &display);

void drawIntro(Adafruit_SSD1306 &display);

void drawQuestion(Adafruit_SSD1306 &display);

void drawLoading(Adafruit_SSD1306 &display);

void drawResult(Adafruit_SSD1306 &display);

void drawProfile(Adafruit_SSD1306 &display);

void drawEnding(Adafruit_SSD1306 &display);

//----------------------------------------------------
// UI Helpers
//----------------------------------------------------

void drawCenteredText(
    Adafruit_SSD1306 &display,
    String text,
    int y,
    int size
);

void drawProgressBar(
    Adafruit_SSD1306 &display,
    int progress
);

void drawHeart(
    Adafruit_SSD1306 &display,
    int x,
    int y,
    bool filled
);

void drawSoccerBall(
    Adafruit_SSD1306 &display,
    int x,
    int y
);

//----------------------------------------------------
// Small Animations
//----------------------------------------------------

void animateTitle();

void animateLoading();

#endif