//----------------------------------------------------------
// Programmer: Joseph R Brady
// Date: 9/23/2022
// Name: hw3
// Description: Wordle.h is the user interface of the Wordle Class
//----------------------------------------------------------
#ifndef HW3_WORDLE_H
#define HW3_WORDLE_H
#include <string>
#include <vector>

using namespace std;

class Wordle{
    public:
        void setFilename(const string newListFilename);    //Initializes the setFileName function
        string getFilename() const;                  //Initializes the getFileName function with plp in mind
        explicit Wordle(string newFilename = "wordlist.txt");    //Initializes the Wordle constructor as explicit
        void loadWordList();                        //Initializes the loadWordList function
        void printWordList() const;                  //Initializes the printWordList function with plp in mind
        string getSecretWord() const;                //Initializes the getSecretWord function with plp in mind
        void setSecretWord(const string newSecret);       //Initializes the setSecretWord function with plp in mind
        void setRandomSecretWord() ;                 //Initializes the setRandomSecretWord
        int getGuessNum() const;                     //Initializes the getGuessNum function with plp in mind
        bool makeGuess(const string newGuess);             //Initializes the makeGuests function
        void print() const;                           //Initializes the print function
        void printAvailableLetters() const;    //Iniitializes the available letter array

    private:
        string wordListFilename;              //Initializes the private wordListFilename to store the Wordle filename
        vector<string> wordList;              //Initializes the private wordList to store the words from the filename
        string secretWord;                    //Initializes the secretWord
        int guessNum = 0;                     // number of guesses
        const int MAX_GUESS_NUM = 6;          // maximum number of guesses
        vector<string> guess;                 // list of previous guesses
        vector<string> feedback;            // list of feedback strings
        bool availableLetter[26];           // boolean array to represent 26 letters

};

#endif //HW3_WORDLE_H
