/*
==========================================================
ui.cpp
World Cup Love Machine

OLED User Interface

Part 1
==========================================================
*/

#include "ui.h"
#include "game.h"
#include "questions.h"
#include "players.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//----------------------------------------------------------
// Draw Centered Text
//----------------------------------------------------------

void drawCenteredText(
    Adafruit_SSD1306 &display,
    String text,
    int y,
    int size)
{

    display.setTextSize(size);

    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    display.getTextBounds(
        text,
        0,
        0,
        &x1,
        &y1,
        &w,
        &h
    );

    int x = (128 - w) / 2;

    display.setCursor(x, y);

    display.print(text);

}

//----------------------------------------------------------
// Progress Bar
//----------------------------------------------------------

void drawProgressBar(
    Adafruit_SSD1306 &display,
    int progress)
{

    if(progress < 0)
        progress = 0;

    if(progress > 100)
        progress = 100;

    display.drawRect(
        14,
        50,
        100,
        8,
        WHITE
    );

    int width = map(
        progress,
        0,
        100,
        0,
        98
    );

    display.fillRect(
        15,
        51,
        width,
        6,
        WHITE
    );

}

//----------------------------------------------------------
// Pixel Heart
//----------------------------------------------------------

void drawHeart(
    Adafruit_SSD1306 &display,
    int x,
    int y,
    bool filled)
{

    if(filled)
    {

        display.fillCircle(x+2,y+2,2,WHITE);
        display.fillCircle(x+6,y+2,2,WHITE);

        display.fillTriangle(
            x,
            y+3,
            x+8,
            y+3,
            x+4,
            y+9,
            WHITE
        );

    }

    else
    {

        display.drawCircle(x+2,y+2,2,WHITE);
        display.drawCircle(x+6,y+2,2,WHITE);

        display.drawLine(
            x,
            y+3,
            x+4,
            y+9,
            WHITE
        );

        display.drawLine(
            x+8,
            y+3,
            x+4,
            y+9,
            WHITE
        );

    }

}

//----------------------------------------------------------
// Tiny Soccer Ball
//----------------------------------------------------------

void drawSoccerBall(
    Adafruit_SSD1306 &display,
    int x,
    int y)
{

    display.drawCircle(
        x,
        y,
        6,
        WHITE
    );

    display.fillCircle(
        x,
        y,
        2,
        WHITE
    );

    display.drawPixel(x,y-6,WHITE);
    display.drawPixel(x+4,y-4,WHITE);
    display.drawPixel(x-4,y-4,WHITE);

    display.drawPixel(x+5,y+2,WHITE);
    display.drawPixel(x-5,y+2,WHITE);

    display.drawPixel(x,y+6,WHITE);

}

//----------------------------------------------------------
// Title Animation
//----------------------------------------------------------

void animateTitle()
{

    if(millis() - heartTimer > 450)
    {

        heartVisible = !heartVisible;

        heartTimer = millis();

    }

}

//----------------------------------------------------------
// Loading Animation
//----------------------------------------------------------

void animateLoading()
{

    if(millis() - loadingTimer > 35)
    {

        loadingProgress++;

        if(loadingProgress > 100)
        {

            loadingProgress = 100;

        }

        loadingTimer = millis();

    }

}

//----------------------------------------------------------
// TITLE SCREEN
//----------------------------------------------------------

void drawTitle(Adafruit_SSD1306 &display)
{
    animateTitle();

    display.clearDisplay();

    // Top border
    display.drawLine(0, 0, 127, 0, WHITE);
    display.drawLine(0, 63, 127, 63, WHITE);

    // Soccer balls
    drawSoccerBall(display, 12, 10);
    drawSoccerBall(display, 116, 10);

    drawCenteredText(display, "WORLD CUP", 8, 2);
    drawCenteredText(display, "LOVE MACHINE", 28, 1);

    if (heartVisible)
    {
        drawHeart(display, 58, 44, true);
    }
    else
    {
        drawHeart(display, 58, 44, false);
    }

    drawCenteredText(display, "PRESS OK", 55, 1);

    display.display();
}

//----------------------------------------------------------
// INTRO SCREEN
//----------------------------------------------------------

void drawIntro(Adafruit_SSD1306 &display)
{

    display.clearDisplay();

    drawCenteredText(display, "WELCOME!", 4, 2);

    display.setTextSize(1);

    display.setCursor(5, 22);
    display.println("Answer honestly.");

    display.setCursor(5, 33);
    display.println("We'll compare");

    display.setCursor(5, 43);
    display.println("your personality");

    display.setCursor(5, 53);
    display.println("with football legends!");

    display.display();

}

//----------------------------------------------------------
// QUESTION SCREEN
//----------------------------------------------------------

void drawQuestion(Adafruit_SSD1306 &display)
{

    display.clearDisplay();

    // Question number

    display.setTextSize(1);

    display.setCursor(0, 0);

    display.print("Question ");

    display.print(currentQuestion + 1);

    display.print("/");

    display.print(QUESTION_COUNT);

    // Divider

    display.drawLine(0, 10, 127, 10, WHITE);

    // Question

    display.setCursor(0, 16);

    display.println(
        questions[currentQuestion].question
    );

    // Current Choice

    display.drawRoundRect(
        8,
        40,
        112,
        18,
        3,
        WHITE
    );

    display.setCursor(18, 46);

    display.print("< ");

    display.print(
        questions[currentQuestion]
            .choices[currentChoice]
    );

    display.print(" >");

    display.display();

}

//----------------------------------------------------------
// LOADING SCREEN
//----------------------------------------------------------

void drawLoading(Adafruit_SSD1306 &display)
{
    animateLoading();

    display.clearDisplay();

    drawCenteredText(display, "ANALYZING...", 4, 2);

    drawSoccerBall(display, 18, 28);

    display.setTextSize(1);

    if (loadingProgress < 25)
    {
        display.setCursor(35, 25);
        display.print("Reading");
        display.setCursor(35, 35);
        display.print("personality...");
    }
    else if (loadingProgress < 50)
    {
        display.setCursor(35, 25);
        display.print("Comparing");
        display.setCursor(35, 35);
        display.print("chemistry...");
    }
    else if (loadingProgress < 75)
    {
        display.setCursor(35, 25);
        display.print("Searching");
        display.setCursor(35, 35);
        display.print("FIFA database...");
    }
    else
    {
        display.setCursor(35, 25);
        display.print("Finding your");
        display.setCursor(35, 35);
        display.print("soulmate...");
    }

    drawProgressBar(display, loadingProgress);

    display.display();
}

//----------------------------------------------------------
// RESULT SCREEN
//----------------------------------------------------------

void drawResult(Adafruit_SSD1306 &display)
{
    display.clearDisplay();

    drawCenteredText(display, "YOUR MATCH!", 2, 2);

    display.drawLine(0,18,127,18,WHITE);

    display.setTextSize(2);
    drawCenteredText(
        display,
        players[matchedPlayer].name,
        24,
        1
    );

    display.setTextSize(2);

    String scoreText = String(compatibilityScore) + "%";

    drawCenteredText(
        display,
        scoreText,
        44,
        2
    );

    display.display();
}

//----------------------------------------------------------
// PLAYER PROFILE
//----------------------------------------------------------

void drawProfile(Adafruit_SSD1306 &display)
{

    display.clearDisplay();

    display.setTextSize(1);

    drawCenteredText(
        display,
        players[matchedPlayer].title,
        0,
        1
    );

    display.drawLine(0,10,127,10,WHITE);

    display.setCursor(0,16);

    display.println(
        players[matchedPlayer].description
    );

    display.setCursor(0,48);

    display.print("Warning:");

    display.setCursor(0,57);

    display.print(
        players[matchedPlayer].warning
    );

    display.display();

}

//----------------------------------------------------------
// ENDING SCREEN
//----------------------------------------------------------

void drawEnding(Adafruit_SSD1306 &display)
{

    display.clearDisplay();

    drawCenteredText(
        display,
        "THANK YOU!",
        2,
        2
    );

    display.setTextSize(1);

    drawCenteredText(
        display,
        "World Cup",
        24,
        1
    );

    drawCenteredText(
        display,
        "Love Machine",
        34,
        1
    );

    drawCenteredText(
        display,
        "Football never lies.",
        48,
        1
    );

    drawCenteredText(
        display,
        "Press RESET",
        58,
        1
    );

    display.display();

}

//----------------------------------------------------------
// Draw Current Screen
//----------------------------------------------------------

void drawCurrentScreen(Adafruit_SSD1306 &display)
{

    switch(gameState)
    {

        case TITLE:
            drawTitle(display);
            break;

        case INTRO:
            drawIntro(display);
            break;

        case QUESTION:
            drawQuestion(display);
            break;

        case LOADING:
            drawLoading(display);
            break;

        case RESULT:
            drawResult(display);
            break;

        case PROFILE:
            drawProfile(display);
            break;

        case ENDING:
            drawEnding(display);
            break;

    }

}