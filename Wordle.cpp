//----------------------------------------------------------
// Programmer: Joseph R Brady
// Date: 9/23/2022
// Name: hw3
// Description: The Wordle.cpp file stores what the functions
//              of the Wordle Class do
//----------------------------------------------------------
#include "Wordle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void Wordle::setFilename(const string newListFilename){ //Changes wordListFilename to the new name
    wordListFilename=newListFilename;
}

string Wordle::getFilename() const{                //Returns the wordListFilename
    return wordListFilename;
}

Wordle::Wordle(string newFilename){               //Wordle constructor using the setFilename Function
    setFilename(newFilename);
    srand (time(nullptr));             //Initializes srand for random numbers elsewhere in the class
    for(int x=0; x<sizeof(availableLetter); x++){        //Sets all the variables in the availableLetter array to true
        availableLetter[x]=true;
    }
}

/////////////////////////////////////////////////////////////
//
// Description: << Stores all the words/strings from a file into vector<string> wordList >>
// Inputs: << No Inputs >>
// Output: << Void function returns nothing >>
//
/////////////////////////////////////////////////////////////
void Wordle::loadWordList() {                     //Takes the words from the file to store in vector wordList
    ifstream fin(wordListFilename);            // Attempt to open file
    if (fin.fail()) {                            //If file doesnt open reports a failure
        cout<<"Error Word List Filename has not been specified"<<endl;
    }
    else {                                    //If file does open proceeds to transfer words from the file
        int fileLength = 0;                   //Tracks the files length
        int traverseCount = 0;                //Holds the position for vector index
        string hold;                          //Holds the strings coming in from the file

        while (!fin.eof()) {                 //While loop only ends once it's traversed the whole file
            fin >> hold;                     //Holds the strings to traverse through the file
            fileLength++;                    //Counts every word that it's in the file
        }
        wordList.resize(fileLength);  //Changes the vector size to accomadate the data from the file
        fin.clear();                          //Clears the end flag
        fin.seekg(0, fin.beg);                //Starts the file back at the beginning of the data

        while (traverseCount < fileLength) {  //Goes through the file again this time
            fin >> hold;                      //putting the words from the file into the vector wordList
            wordList.at(traverseCount) = hold;
            traverseCount++;                  //Updates loop counter
            }
        }
}

/////////////////////////////////////////////////////////////
//
// Description: <<Prints out each word from the word list>
// Inputs: << No Inputs >>
// Output: << Returns nothing but prints all the strings(unnamed called as wordList.at(printCount))
//             stored in vector<string> wordList>
//
/////////////////////////////////////////////////////////////
void Wordle::printWordList() const{              //Prints the words from the vector Word List
    int printCount=0;
    if(wordList.size()<=0){                      //Checks to make sure the wordlist is not empty
        cout<<"Warning: Word List is empty"<<endl; //Produces error message if it does
    }
    else {                                       //If file is not empty...
        while (printCount < wordList.size()) {
            cout << wordList.at(printCount) << endl; //Traverse the vector printing each word stored
            printCount++;
        }
    }
}

string Wordle::getSecretWord() const {    //Returns the secretWord
    return secretWord;
}

void Wordle::setSecretWord(const string newSecret) {      //Changes the secret word to the new secret word
    //Checks to see if the newSecret word is in the vector wordList
    if ( find(wordList.begin(), wordList.end(), newSecret) == wordList.end()) {
        cout<<"Warning: "<< newSecret <<" is not found in Word List" << endl;
    } else {
        secretWord=newSecret;                     //If word is in the list changes the secretWord to the new word
        }
    }

void Wordle::setRandomSecretWord() {             //Changes the secret word to a random word from the list
    int randomNumber = rand()%(wordList.size()); //Creates a random number with the size of the vector being the max
    secretWord=wordList.at(randomNumber);     //Changes the secret word to a random word from the list.
}

int Wordle::getGuessNum() const{                //Returns the guessNum
    return guessNum;
}

/////////////////////////////////////////////////////////////
//
// Description: << The main function of the project, takes in a newGuess, determines if the guess is a valid one,
//                  then checks if the user has not reached their maximum number of guesses, adds the guess to the
//                   guess vector, adds the appropriate feedback to the feedback vector, updates the availableLetter
//                   array to change letters not into the secret word to false then
//                   checks if the user has guess the right number, if yes prints a victory message if not checks
//                   to see if a game over message needs to be printed if not, prints a wrong guess message>>
// Inputs: << Takes in a string labeled as guess>>
// Output: << Returns either true or false while printing a victory message if its returning true and returns
//            either a wrong guess message or a game over message >>
//
/////////////////////////////////////////////////////////////
bool Wordle::makeGuess(const string newGuess){
    if ( find(wordList.begin(), wordList.end(), newGuess) == wordList.end()) {      //Checks to see if the
        cout<<"Warning: "<< newGuess <<" is not found in Word List" << endl;                //guess is in the word list
        return false;                                                         //returns false if the guess is not valid
    }
    else {
        if(guessNum < MAX_GUESS_NUM) {           //Checks to ensure the maximum number of guesses has not been reached
            guess.push_back(newGuess);                    //Adds guess to the guess vector
            vector<char> secretCopy(secretWord.begin(),secretWord.end());    //Splits the string of secret word into a vector <char>
            vector<char> guessCopy(newGuess.begin(),newGuess.end());           //Splits the string of newGuess into a vector<char>
            vector<char> feedbackInput(5,'.');                                               //Creates a vector<char> that mimic what the vector<string> feedback should be
            for(int x =0; x<guessCopy.size(); x++) {                       //This loop is the inital loop that traverses through the guessCopy vector<char>
                if (guessCopy.at(x) == secretCopy.at(x)) {    //Checks to see if the guess letter is in the same spot as in the secretWord
                    secretCopy.at(x) = '-';                               //Changes the secretCopy letter to - to show that letter has been matched
                    feedbackInput.at(x) = '!';                         //Changes the feedbackInput element of the same spot to show a matching letter
                    for (int b = 0; b < guessCopy.size(); b++) {         //A loop that will travers guessCopy for each letter traversed in the main loop
                        if (guessCopy.at(x) == guessCopy.at(b) && x != b) { //Checks to see if there is two of the same letters in the newGuess
                            guessCopy.at(b) = '~';                                          //If so it gets changed to make sure it does not get removed from availableLetter[]
                        }
                    }
                    guessCopy.at(x) = '~';                         //Changes the letter that was matched so it doesn't get removed from availableLetter[]
                }
                else {                                                    //If the letters are not a direct match
                    for (int y = 0; y < secretCopy.size(); y++) {             //A loop that will now traverse the vector<char> secretCopy
                        if (guessCopy.at(x) == secretCopy.at(y)) {    //Checks to see if the letter from the guess is in the secretWord
                            feedbackInput.at(x) = '+';                           //Changes the feedbackInput of the same spot to show that the letter is in the word
                            secretCopy.at(y) = '-';                              //Changes the secretCopy to show that the letter has been matched
                            for(int a =0; a<guessCopy.size(); a++){             //A loop that will travers guessCopy for each letter traversed in the main loop
                                if(guessCopy.at(x)==guessCopy.at(a)&& x!=a){      //Checks to see if there is two of the same letters in the newGuess
                                    guessCopy.at(a)= '~';                                        //If so it gets changed to make sure it does not get removed from availableLetter[]
                                }
                            }
                            guessCopy.at(x)='~';                         //Changes the letter that was matched so it doesn't get removed from availableLetter[]
                        }
                    }
                }
            }
            for (int z = 0; z < guessCopy.size(); z++) {         //Traverses the guessCopy vector<char>
                int index = 0;                                            //Initializes an index variable
                if ((int) guessCopy.at(z) != 126) {                //Checks to see that the element is not a ~
                    index = (int) guessCopy.at(z) - 97;        //Converts the int version of the letter into an index for the availableLetters array
                    availableLetter[index] = false;                 //Changes that letter spot to false
                }
            }

            string feedbackOutput(feedbackInput.begin(),feedbackInput.end()); //Converts vector<char> feedbackInput into a string feedbackOutput
            feedback.push_back(feedbackOutput);               //Adds the feedbackOutput to the feedback private vector

            guessNum++;                           //Adds up the guessNum to account for the new guess

            if (newGuess == secretWord) {         //Checks to see if the guess is correct
                cout << "You're a Winner!" << endl;   //Prints and returns a victory message
                return true;
            }
        }
        if (guessNum >= MAX_GUESS_NUM) {                 //Checks to see if this was the last guess or not
            cout << "Haha! Better Luck Next Time" << endl;  //Prints a gameover message if maximum number of
            return false;                                   //guess has been reached and returns false
        }
        else{                                      //If it's not the last guess and nothing else has been returned
            cout << "Close! Try Again" << endl;     //prints the wrong guess message and returns false
                return false;
            }
    }
}

/////////////////////////////////////////////////////////////
//
// Description: << Prints the guess and feedback vectors in a readable fashion >>
// Inputs: << No Inputs >>
// Output: << Does not return anything just prints the string elements from vector<string> guess
//            and vector<string> feedback >>
//
/////////////////////////////////////////////////////////////
void Wordle::print() const{                          //Traverses through the guess and feedback vectors to print
    for(int x = 0; x<guess.size();x++){              //the elements of the vectors in a nice readable fashion
        cout<<x+1<<": "<<guess.at(x)<<" "<<feedback.at(x)<<endl;
    }
}

/////////////////////////////////////////////////////////////
//
// Description: << Prints the letters associated with the variable of  bool availableLetters array  >>
// Inputs: << No Inputs >>
// Output: << Does not return anything just prints the letters marked as true in the bool availableLetters array>>
//
/////////////////////////////////////////////////////////////
void Wordle::printAvailableLetters() const{
    for(int x = 0;x < sizeof(availableLetter); x++ ){         //Loop that traverses the availableLetter array
        if(availableLetter[x]){                                     //Checks to if that index is true or false
            cout<< (char)(x+97)<<" ";                          //Prints out the letters associated with that index
        }
    }
    cout<<endl;                                                 //Adds a spacer for readability
}