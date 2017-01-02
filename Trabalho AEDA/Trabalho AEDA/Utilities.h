#pragma once

/** @defgroup Utilities Utilities
* @{
*
* Utilities class declaration
*/
#include <Windows.h>
#include <iostream>
#include <limits>
#include <conio.h>
#include <ctime>

#undef max

using namespace std;

/**
* @brief Main display
*
* Display that will be used between all menus
*/
void menuHeader();

/**
* @brief Changes characters color on screen
*
* @param ForgC color code to change to
*/
void setcolor(int ForgC);

/**
* @brief Basic clearscreen function use to erase the entire screen
*/
void clearScreen();

/**
* @brief Reads an integer between two other disctinct ones
*
* @param min minimum value permitted by user input
* @param max maximum value permitted by user input
*
* @return valid input read
*/
int readInt(int min, int max);

/**
* @brief Waits for user input of the ENTER key
*/
void getEnter();

/** @name Color Changing Functions*/
/**@{
*
* Functions that change the characters color on screen to the color 
* especified by the functions name using @setcolor function
*/
void white();
void blue();
void grey();
void red();
void green();
void yellow();
/** @} end of Color Changing Functions */


