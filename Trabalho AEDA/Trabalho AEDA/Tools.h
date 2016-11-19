#pragma once

/** @defgroup Tools Tools
* @{
*
* Useful tools used
*/
#include <string>
#include <algorithm>
#include "Utilities.h"

using namespace std;

/**
* @brief Checks if the given parameter is a string or an integer
*
* @param output string to evaluate
*
* @return true if output is a string, false otherwise
*/
bool outputName(string output); 

/**
* @brief Reads user input for a password, printing '*' to the screen for each valid input received 
*
* @return string containing the password entered
*/
string insertPassword(); 

/**
* @brief Compares two strings and checks if their are equal
*
* @param a first string
* @param b second string
*
* @return true if the parameters are equal, false otherwise
*/
bool sameString(string a, string b);

/**
* @brief Converts a given string elements to uppercase
*
* @param code string to convert
*
* @return string with all elements uppercased
*/
string convertUpper(string code);
