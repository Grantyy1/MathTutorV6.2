/**********************************************************************************************
Program: Math Tutor Version 6
Programmers: River Wallerstedt & Grant Peverett
Date: 12/5/2024
GitHub URL: https://github.com/Grantyy1/MathTutorV6
Description: This file contains all the prototypes for the functions that the main function
             calls.
**********************************************************************************************/

#ifndef MATHTUTOR5_H
#define MATHTUTOR5_H

#include <string>
#include <vector>

using namespace std;

//prototype functions that will be called into the main function
void DisplayGameIntro(); //
string GetUserName(string userName);
vector<int> GenerateRandomQuestion(int mathLevel);
int GetNumericValue();
bool GiveThreeAttempts(string userName, vector<int> &question);
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLevel);
string YesNoQuestion(string question);
void DisplaySummaryReport(const vector<vector<int>> &allQuestions);
void SaveCurrentGame(string userName, const vector<vector<int>> &mathQuestions);
int LoadPreviousGame(string userName, vector<vector<int>> &mathQuestions);
/*
1. random1 - Standard C++ variables start with lowercase letter
2. MAX_ATTEMPTS - Constants use all uppercase with underscores
3. iostream - Required for cin/cout functionality
4. every case block after the first case that tested true would execute - Known as "fall-through" behavior
5. required when there are more than one statement in the block
6. 0-9 - Modulo 10 gives remainder 0-9
7. switch statement - Switch can only test equality
8. is located at index 0 - C++ uses zero-based indexing
9. break; - Breaks out of the loop immediately
10. loop - While and for are looping constructs
11. vector - Vectors can dynamically resize
12. index - Used to access specific elements
13. for(int i = 0; i < myVector.size(); i++) - Starts at 0, continues while less than size
14. outside of all functions - Global scope definition
15. string GetUserName() - Return type first, no parameters needed
16. void myFunction(int& myValue) - & indicates pass by reference
17. void - Indicates no return value
18. pass-by-reference - Allows multiple values to be modified and returned
19. fstream - File stream library required for file operations
20. try - Try-catch blocks work together for exception handling
#endif //MATHTUTOR5_H*/
#endif //MATHTUTOR5_H
