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

#endif //MATHTUTOR5_H
