/*
==========================================================
game.cpp
World Cup Love Machine

PART 1
==========================================================
*/

#include "game.h"
#include "questions.h"
#include "players.h"
#include "ui.h"

//----------------------------------------------------------
// Global Variables
//----------------------------------------------------------

GameState gameState = TITLE;

int currentQuestion = 0;
int currentChoice = 0;

int answers[TOTAL_QUESTIONS];

int compatibilityScore = 0;
int matchedPlayer = 0;

int loadingProgress = 0;

unsigned long loadingTimer = 0;
unsigned long heartTimer = 0;

bool heartVisible = true;

//----------------------------------------------------------
// Personality Scores
//----------------------------------------------------------

int kindness = 0;
int humor = 0;
int confidence = 0;
int creativity = 0;
int loyalty = 0;
int ambition = 0;

//----------------------------------------------------------
// Initialize Game
//----------------------------------------------------------

void initGame()
{

    gameState = TITLE;

    currentQuestion = 0;
    currentChoice = 0;

    compatibilityScore = 0;
    matchedPlayer = 0;

    loadingProgress = 0;

    kindness = 0;
    humor = 0;
    confidence = 0;
    creativity = 0;
    loyalty = 0;
    ambition = 0;

    for(int i=0;i<TOTAL_QUESTIONS;i++)
    {
        answers[i]=0;
    }

    heartVisible = true;

    loadingTimer = millis();
    heartTimer = millis();

}

//----------------------------------------------------------
// Reset
//----------------------------------------------------------

void resetGame()
{

    initGame();

}

//----------------------------------------------------------
// Next Question
//----------------------------------------------------------

void nextQuestion()
{

    currentQuestion++;

    currentChoice=0;

    if(currentQuestion>=TOTAL_QUESTIONS)
    {

        calculateCompatibility();

        loadingProgress=0;

        gameState=LOADING;

    }

}
//----------------------------------------------------------
// LEFT BUTTON
//----------------------------------------------------------

void pressLeft()
{

    switch(gameState)
    {

        case TITLE:
            break;

        case INTRO:
            break;

        case QUESTION:

            currentChoice--;

            if(currentChoice < 0)
            {
                currentChoice = CHOICES_PER_QUESTION - 1;
            }

            break;

        case PROFILE:
            gameState = RESULT;
            break;

        case RESULT:
            break;

        case ENDING:
            break;

        default:
            break;

    }

}

//----------------------------------------------------------
// RIGHT BUTTON
//----------------------------------------------------------

void pressRight()
{

    switch(gameState)
    {

        case TITLE:
            break;

        case INTRO:
            break;

        case QUESTION:

            currentChoice++;

            if(currentChoice >= CHOICES_PER_QUESTION)
            {
                currentChoice = 0;
            }

            break;

        case RESULT:
            gameState = PROFILE;
            break;

        case PROFILE:
            break;

        case ENDING:
            break;

        default:
            break;

    }

}

//----------------------------------------------------------
// OK BUTTON
//----------------------------------------------------------

void pressOK()
{

    switch(gameState)
    {

        //--------------------------------------------------
        // Title
        //--------------------------------------------------

        case TITLE:

            gameState = INTRO;

            break;

        //--------------------------------------------------
        // Intro
        //--------------------------------------------------

        case INTRO:

            gameState = QUESTION;

            break;

        //--------------------------------------------------
        // Quiz
        //--------------------------------------------------

        case QUESTION:

            answers[currentQuestion] = currentChoice;

            //--------------------------------------------------
            // Build Personality Stats
            //--------------------------------------------------

            switch(currentChoice)
            {

                case 0:
                    kindness++;
                    break;

                case 1:
                    humor++;
                    break;

                case 2:
                    confidence++;
                    break;

                case 3:
                    creativity++;
                    break;

                case 4:
                    loyalty++;
                    break;

                case 5:
                    ambition++;
                    break;

            }

            nextQuestion();

            break;

        //--------------------------------------------------
        // Result
        //--------------------------------------------------

        case RESULT:

            gameState = PROFILE;

            break;

        //--------------------------------------------------
        // Profile
        //--------------------------------------------------

        case PROFILE:

            gameState = ENDING;

            break;

        //--------------------------------------------------
        // Ending
        //--------------------------------------------------

        case ENDING:

            resetGame();

            break;

        default:

            break;

    }

}
//----------------------------------------------------------
// Calculate Compatibility
//----------------------------------------------------------

void calculateCompatibility()
{

    int bestScore = 100000;
    matchedPlayer = 0;

    //------------------------------------------------------
    // Compare against every football player
    //------------------------------------------------------

    for(int i = 0; i < PLAYER_COUNT; i++)
    {

        int difference = 0;

        difference += abs(kindness    - players[i].kindness);
        difference += abs(humor       - players[i].humor);
        difference += abs(confidence  - players[i].confidence);
        difference += abs(creativity  - players[i].creativity);
        difference += abs(loyalty     - players[i].loyalty);
        difference += abs(ambition    - players[i].ambition);

        if(difference < bestScore)
        {
            bestScore = difference;
            matchedPlayer = i;
        }

    }

    //------------------------------------------------------
    // Convert difference into percentage
    //------------------------------------------------------

    // Maximum possible difference:
    // 6 personality traits
    // each can differ by about 12
    // ≈72

    compatibilityScore = map(
        bestScore,
        0,
        30,
        99,
        60
    );

    //------------------------------------------------------
    // Flash Game Randomness
    //------------------------------------------------------

    compatibilityScore += random(-4,5);

    //------------------------------------------------------
    // Clamp
    //------------------------------------------------------

    if(compatibilityScore > 99)
        compatibilityScore = 99;

    if(compatibilityScore < 60)
        compatibilityScore = 60;

}

//----------------------------------------------------------
// Loading Screen Logic
//----------------------------------------------------------

void updateLoading()
{

    if(gameState != LOADING)
        return;

    if(millis() - loadingTimer > 40)
    {

        loadingProgress++;

        loadingTimer = millis();

    }

    if(loadingProgress >= 100)
    {

        loadingProgress = 100;

        gameState = RESULT;

    }

}

