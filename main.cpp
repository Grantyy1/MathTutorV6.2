/**********************************************************************************************
Program: Math Tutor Version 6
Programmers: River Wallerstedt & Grant Peverett
Date: 12/5/2024
GitHub URL: https://github.com/Grantyy1/MathTutorV6
Description: An easy math tutor for young children.

- It will generate two random numbers between 1-10 before randomly selecting between
addition, subtraction, multiplication, and division via a third number.

- Uses an outer while loop until the user wishes to quit.

- Uses an inner while loop to validate the user's input for "Do you want to continue?"
accepting yes, y, no, or n as valid input.

- Uses a for loop to give the user 3 attempts to answer the question correctly. After the third
failed attempt, the correct answer will be displayed.

- After three correct answers in a row, leveling up increases the number range by 10.
- After three incorrect answers in a row, leveling up decreases the number range by 10.

- Uses a while loop to validate numeric input.

- Uses a 2D vector to store all questions which is used to later display a summary report at
the end of the program.
**********************************************************************************************/

#include <cstdlib>  // allows for randomizer
#include <ctime>    // enables use of time function
#include <iostream> // required for couts & cins + left and right alignment
#include <string>   // allows for strings to be used
#include <vector>   // used for vectors

#include "mathTutor5.h"

using namespace std; // sets standard namespace

int main() {
    // used to store all the questions for a summary report
    vector<vector<int> > allQuestions;
    string userYN = "?"; // the user’s name
    string userName = "unknown"; // used for yes/no prompt
    string questionYN = "?";

    int totalCorrect = 0; // used to level up
    int totalIncorrect = 0; // used to level down
    int mathLevel = 1; // current level the user is on

    bool isCorrect = false; // did the user answer the current question correctly

    srand(time(0)); // seed the random method with the current time

    DisplayGameIntro();
    userName = GetUserName(userName);//calls GetUserName fuction

    try {//loads the previous game
        mathLevel = LoadPreviousGame(userName, allQuestions);
    } catch (runtime_error &e) { //catches error if previous game does not load properly
        cout << endl;
        cout << e.what() << endl;
    }

    do {// keep asking math questions until the user wants to quit

        vector<int> question = GenerateRandomQuestion(mathLevel);

        try { //generates random question
            vector<int> question = GenerateRandomQuestion(mathLevel);
        }catch (runtime_error &e) { //catches error if question is not gernerated
            cout << endl;
            cout << e.what() << endl;
            cout << "Program ended with an error -1" << endl;
        }

        isCorrect = GiveThreeAttempts(userName, question);

        // used for leveling up & down
        if (isCorrect) {
            totalCorrect++;
        } else {
            totalIncorrect++;
        }

        CheckForLevelChange(totalCorrect, totalIncorrect, mathLevel);

        //put the current question to the 2D vector
        allQuestions.push_back(question);
        getline(cin, questionYN);
        questionYN = YesNoQuestion( "Do you want to continue (y = yes | n = no)? ");
    } while (questionYN == "y" || questionYN == "yes");

    DisplaySummaryReport(allQuestions);

    try { //saves the users current game to the text file
        SaveCurrentGame(userName, allQuestions);
    } catch (runtime_error &e) { //message output if game could not be saved
        cout << endl;
        cout << e.what() << endl;
        cout << "Well that stinks. Unable to save your game :(" << endl;
    }

    // tell the user goodbye
    cout << endl;
    cout << "Thank you, " << userName << ", for playing Silly Math Tutor!" << endl;
    cout << "Be sure to come back for more updates, and most importantly," << endl;
    cout << "MORE FUN!" << endl;

    return 0;
} // end of main function
