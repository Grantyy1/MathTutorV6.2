/**********************************************************************************************
Program: Math Tutor Version 6
Programmers: River Wallerstedt & Grant Peverett
Date: 12/5/2024
GitHub URL: https://github.com/Grantyy1/MathTutorV6
Description: This file contains all the functions that the main function calls
**********************************************************************************************/

#include <cstdlib>  // allows for randomizer
#include <cctype>   // used for character handling function
#include <iostream> // required for couts & cins + left and right alignment
#include <iomanip>  // used for formatting
#include <limits>   // required for numeric limits
#include <string>   // allows for strings to be used
#include <vector>   // used for vectors
#include <fstream>
#include <stdexcept>

using namespace std;

//Max number of attempts before displaying the answer
const int MAX_ATTEMPTS = 3;
//How much to increase and decrease the random number range per level
const int LEVEL_RANGE_CHANGE = 10;

const string FILE_NAME = "mathtutor.txt";

/*****************************************************************************
Displays the games intro
*****************************************************************************/
void DisplayGameIntro() {
    string userYN = "?";
    // Set of cout statements to display the Silly Math ASCII art and welcome banner
    cout << "*******************************************" << endl;
    cout << " _____ _ _ _      ___  ___      _   _    " << endl;
    cout << "/  ___(_| | |     |  /// |     | | | |   " << endl;
    cout << "| `--. _| | |_   _| .  . | __ _| |_| |__ " << endl;
    cout << " `--. | | | | | | | |//| |/ _` | __| '_ | " << endl;
    cout << " ___/ | | | | |_| | |  | | (_| | |_| | | |" << endl;
    cout << "/____/|_|_|_|__, /|_|  |_/,__,_|,__|_| |_|" << endl;
    cout << "            __/ /                       " << endl;
    cout << "           |___/                       " << endl;
    cout << "*******************************************" << endl;
    cout << "*    Welcome to Silly Math Tutor V5 by    *" << endl;
    cout << "*          GrantPev and RivJams           *" << endl;
    cout << "*******************************************" << endl;
    cout << endl;

    // Asks prompt whether to display the jokes or not
    cout << "Do you wanna hear some math puns? (yes/no): ";
    cin >> userYN;

    // changes user input so it's all lowercase
    getline(cin, userYN);
    for (int i = 0; i < userYN.size(); i++) {
        userYN.at(i) = tolower(userYN.at(i));
    }

    if (userYN == "y" || userYN == "yes") {
        cout << "Great! Here they are:" << endl;
    } else {
        cout << "That's too bad." << endl;
        cout << "You're gonna hear them anyway!" << endl;
    }

    cout << endl;

    // Displays math jokes
    cout << "*******************************************" << endl;
    cout << endl;
    cout << "Question: Do you think monsters are good at math?" << endl;
    cout << "Answer: No, unless you Count Dracula." << endl;
    cout << endl;
    cout << "Question: Which knight created the round table?" << endl;
    cout << "Answer: Sir Cumference." << endl;
    cout << endl;
    cout << "Question: What do you call a number who can't stay in place?" << endl;
    cout << "Answer: A roamin' numeral." << endl;
    cout << endl;
    cout << "*******************************************" << endl;
    cout << endl;

    return;

}// end of DisplayIntro function

/*****************************************************************************
Gets the user’s name and welcomes the user
Returns the user’s name
*****************************************************************************/
string GetUserName(string userName) {
    cout << "Please enter your name to begin: ";
    //getline(cin, userName); // Clears out leftover carriage return
    getline(cin, userName); // Get user input for name
    cout << endl;

    // Welcome message
    cout << "Welcome " << userName << ", to the Silly Math Tutor!" << endl;
    cout << endl;

    return userName;

}// end of GetUserName function

/*****************************************************************************
Generate each random question
Parameters: mathLevel used to set the left and right number ranges
Returns the current question’s data as an integer vector
Example: return {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer};
*****************************************************************************/
vector<int> GenerateRandomQuestion(int mathLevel) {
    enum MathType { MT_ADD = 1, MT_SUB = 2, MT_MUL = 3, MT_DIV = 4 };
    MathType mathType = MT_ADD;

    int temp = 0;           // used to swap two values
    int leftNum = 0;        // the 1st random number btw 1 & 10
    int rightNum = 0;       // the 2nd random number btw 1 & 10
    char mathSymbol = '?';  // [+, -, *, /]
    int correctAnswer = 0;  // the correct answer

    // generates 1st random number between 1 and 10
    leftNum = (rand() % (mathLevel * LEVEL_RANGE_CHANGE)) + 1;
    // generates 2nd randm number between 1 and 10
    rightNum = (rand() % (mathLevel * LEVEL_RANGE_CHANGE)) + 1;
    // generates the 3rd number, which determines math function type
    mathType = static_cast<MathType>(rand() % 4 + 1);

    //Assigns a math symbol for the equation
    switch (mathType) {
        case MT_ADD:
            mathSymbol = '+';
            correctAnswer = leftNum + rightNum;
            break;

        case MT_SUB:
            mathSymbol = '-';
            if (leftNum < rightNum) { // Prevent negative numbers
                temp = leftNum;
                leftNum = rightNum;
                rightNum = temp;
            }
            correctAnswer = leftNum - rightNum;
            break;

        case MT_MUL:
            mathSymbol = '*';
            correctAnswer = leftNum * rightNum;
            break;

        case MT_DIV:
            mathSymbol = '/';
            correctAnswer = leftNum; //Do this to avoid fractions or negatives
            leftNum *= rightNum;
            break;

        default:
            cout << "Invalid question type: " << mathType << endl;
            cout << "Contact RivJams or Grantyy1 about the error" << endl;
            cout << "Program ended with a -1 error" << endl;
            throw runtime_error("Invalid question type" + mathType); //error handling
    }

    return {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer};

}// end of GenerateRandomQuestion function

/*****************************************************************************
Prompt the user to give an answer to the question
Gets the users inputted answer
*****************************************************************************/
int GetNumericValue() {

    int userAnswer = 0; // user's numeric input

    // ensures the user inputs something numeric
    while (!(cin >> userAnswer)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input!" << endl;
        cout << "\tPlease enter a number: ";
    }

    return userAnswer;

} // end of GetNumericValue function

/****************************************************************************
Gives the user 3 attempts to answer the question correctly
Params: username to address the user and the current question data as a vector
Returns true if they answered it correctly otherwise it answers false
*****************************************************************************/
bool GiveThreeAttempts(string userName, vector<int> &question) {
    int userAnswer = 0;
    bool isCorrect = false;

    int mathLevel = question.at(0);
    int leftNum = question.at(1);
    char mathSymbol = static_cast<char>(question.at(2));
    int rightNum = question.at(3);
    int correctAnswer = question.at(4);

    for (int i = 1; i <= MAX_ATTEMPTS; i++) {
        cout << endl;
        cout << "[Level #" << mathLevel << "] " << userName << ", what does "
                << leftNum << " " << mathSymbol << " " << rightNum << " = ";
        userAnswer = GetNumericValue();
        if (userAnswer == correctAnswer) {
            cout << "\tCorrect!" << endl;
            cout << "\tYou're a real Math Whizz!" << endl;
            cout << endl;
            question.push_back(i); //i tracks attempts
            return true;
        }
        if (i == MAX_ATTEMPTS) {
            cout << "\tI'm sorry, you're out of attempts." << endl;
            cout << "\tThe correct answer was: " << correctAnswer << endl;
            cout << endl;
            question.push_back(0);
            return false;
        }
            cout << "\tSorry, that was incorrect. You have " << (MAX_ATTEMPTS - i)
                    << " attempt(s) left." << endl;
        }
    }
//end of GiveThreeAttempts function

/****************************************************************************
After the user has gotten 3 correct answers they will move to the next level
If the user gets 3 questions wrong in a row they move down a level
The difficulty range changes as they move up the levels
*****************************************************************************/
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLevel) {
    if (totalCorrect == 3) {
        mathLevel++;
        totalCorrect = 0;
        totalIncorrect = 0;
        cout << "You are now on Level " << mathLevel << "!" << endl;
        cout << "New range is 1 to " << mathLevel * LEVEL_RANGE_CHANGE << endl;
        cout << endl;
    } else if (totalIncorrect >= 3 && mathLevel > 1) {
        mathLevel--;
        totalCorrect = 0;
        totalIncorrect = 0;
        cout << "You are now on Level " << mathLevel << "!" << endl;
        cout << "New range is 1 to " << mathLevel * LEVEL_RANGE_CHANGE << endl;
        cout << endl;
    }

    return;

} // end of CheckForLevelChange

/****************************************************************************
After getting a question wrong or write the code asked the user if they would
like to carry on playing.
If yes, a new question will be asked
If no, the code will end and the summary report will be displayed
*****************************************************************************/
string YesNoQuestion(string question){
    string questionYN = "?";
    while (true) {
        cout << question;
        getline(cin, questionYN);

        // Convert input to lowercase
        for (int i = 0; i < questionYN.size(); i++) {
            questionYN.at(i) = tolower(questionYN.at(i));
        }
        //If the user answers with yes it will break out, and ask a new question
        if (questionYN == "y" || questionYN == "yes" || questionYN == "no" || questionYN == "n") {
            break;
        }

        cout << "Invalid input, please try again..." << endl;

        cout << endl;
    }//End of While(true)

    return questionYN;

}// end of AskToPlayAgain function

/****************************************************************************
Report that displays how manny questions the user got correct, incorrect, the
number of attempts it too as well as the question itself
Displays the users average, total incorrect, total correct, how many
questions were asked score at the end of the report
*****************************************************************************/
void DisplaySummaryReport(const vector<vector<int>> &allQuestions) {

    //Output for the final mathTutor report
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int mathLevel = 0;
    int leftNum = 0;
    char mathSymbol = '?';
    int rightNum = 0;
    int correctAnswer = 0;
    string userAnswer = "";
    int totalQuestions = 0;

    cout << endl;
    cout << "=====================================" << endl;
    cout << "           Summary Report            " << endl;
    cout << "=====================================" << endl;
    cout << "Level        Question       Attempts " << endl;
    cout << "------  -----------------  ----------" << endl;

    //Resets variable back to 0 after previous use above
    totalCorrect = 0;
    totalIncorrect = 0;

    //For loop used to display the report
    for (int i = 0; i < allQuestions.size(); i++) {
        mathLevel = allQuestions.at(i).at(0);
        leftNum = allQuestions.at(i).at(1);
        mathSymbol = static_cast<char>(allQuestions.at(i).at(2));
        rightNum = allQuestions.at(i).at(3);
        correctAnswer = allQuestions.at(i).at(4);
        userAnswer = allQuestions.at(i).at(5);

        //Spacing and output for the equation
        cout << "  " << setw(1) << right << mathLevel << "   "
                << setw(5) << right << leftNum << "  "
                << mathSymbol << setw(3) << right << rightNum << setw(3) << " ="
                << setw(4) << correctAnswer;

        totalQuestions++;

        //If statement for counting amount of correct and incorrect answers
        if (allQuestions.at(i).back() != 0) {
            cout << "  " << setw(7) << allQuestions.at(i).back() << endl;
            totalCorrect++;
        } else {
            cout << "  " << setw(11) << right << "Incorrect" << endl;
            totalIncorrect++;
        }
    } //End outputs of the for loop

    //Displays question stats
    cout << endl;
    cout << "Total Questions: " << setw(3) << right << totalQuestions << endl;
    cout << "Total Correct  : " << setw(3) << right << totalCorrect << endl;
    cout << "Total Incorrect: " << setw(3) << right << totalIncorrect << endl;
    cout << "Average Correct: " << setw(3) << right << totalCorrect * 100 / totalQuestions << "%" << endl;
    cout << "-------------------------------------" << endl;

    return;

} // end of DisplaySummaryReport function

/****************************************************************************
Saves the summary report to a .txt file
Saves how many questions the user answered, whether they were incorrect
or correct. Code outputs a message if the game was saved successfully or not.
*****************************************************************************/
void SaveCurrentGame(string userName, const vector<vector<int>> &mathQuestions) {
    string userInput = "?";
    ofstream outFS;

    string questionYN = YesNoQuestion( userName + ", would you like to save your game (y = yes | n = no)? ");
    if (questionYN == "n" || questionYN == "no") { //If statement only runs when user says no
        cout << "Game save cancelled" << endl;
        return;
    }

    outFS.open(FILE_NAME); //Opens / creates the .txt file

    if (!outFS.is_open()) {
        throw runtime_error("Could not open file" + FILE_NAME + " for writing."); //Error gets thrown if file can't be opened
    }

    cout << "Saving the current game...please wait." << endl;
    cout << mathQuestions.size() <<" saved correctly!" << endl;
    cout << "Game saved successfully" << endl;

    for(int i =0; i < mathQuestions.size(); i++) { //Loop saves all the questions to the .txt file
        outFS << mathQuestions.at(i).at(0) << " "
              << mathQuestions.at(i).at(1) << " "
              << mathQuestions.at(i).at(2) << " "
              << mathQuestions.at(i).at(3) << " "
              << mathQuestions.at(i).at(4) << " "
              << mathQuestions.at(i).at(5) << endl;
    }
}


/****************************************************************************
Reads the information stored on the .txt file
Outputs a message if the game was loaded properly or not.
*****************************************************************************/
int LoadPreviousGame(string userName, vector<vector<int>> &mathQuestions) {

    string userInput = "?";

    int mathLevel = 1;
    int leftNum = 0;
    int mathSymbol = 0;
    int rightNum = 0;
    int correctAnswer = 0;
    int attempts = 0;

    ifstream inFS;
    inFS.open(FILE_NAME);

    if (inFS.is_open()) { //Detects if the game has been saved before, and if so it'll ask the user if they want to continue their progress
        cout << userName << ", it's great to see you again! It looks like you have played this game before!" << endl;
        userInput = YesNoQuestion("Would you like to load your game (y = yes | n = no)? "); //Calls function YesNoQuestion with string

        if (userInput == "y" || userInput == "yes") {
            cout << "Loading previous game. Please wait..." << endl;
            cout << "Previous game loaded successfully!" << endl;

            while(inFS >> mathLevel >> leftNum >> mathSymbol >> rightNum >> correctAnswer >> attempts) {
                mathQuestions.push_back( {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer, attempts}); //Saves the question into a vector
            }

            if (!inFS.eof()) { //Throws error only if file isn't able to open
                throw runtime_error("Oops, something went wrong reading the " + FILE_NAME + " file.");
            }

            mathLevel = mathQuestions.back().at(0); //Sets math question to the last recorded value in the vector

            inFS.close(); //Closes the file after

        } //End of if statement

    }

    return mathLevel;//Sends value of math level back up

}
