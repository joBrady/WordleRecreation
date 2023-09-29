//----------------------------------------------------------
// Programmer: Joseph R Brady
// Date: 9/23/2022
// Name: hw3
// Description: Currently main.cpp test the functions of the Wordle Class
//----------------------------------------------------------
#include <iostream>
#include <string>
#include "Wordle.h"

int main() {
    Wordle test;               //Constructs the Wordle class with no parameters
    cout<<test.getFilename()<<endl;  //Testing the getFilename function with no fileName
    test.loadWordList();        //Testinng the loadWordList function with no fileName
    //test.printWordList();      //Tested the printWordList function with the wordList vector empty
    cout<<endl;

    Wordle testTwo("RandomWrongName");  //Constructs the Wordle class with a missing file
    cout<<testTwo.getFilename()<<endl;             //Testing the getFilename function with a missing file
    testTwo.loadWordList();                       //Testing loadWordList function with a missing file
    testTwo.printWordList();                      //Testing printWordList function with a missing file
    cout<<endl;

    testTwo.setFilename("wordList.txt"); //Testing the setFilename function with the proper file
    cout<<testTwo.getFilename()<<endl;                //Testing the getFilename function with a modified file name
    testTwo.loadWordList();                          //Testing loadWordList function with a modified file name
    //testTwo.printWordList();                         //Tested printWordList function with a modified file name
    cout<<endl;

    testTwo.setFilename("DifferentWrongName"); //Testing setFileName with a missing file
    cout<<testTwo.getFilename()<<endl;                   //Testing getFileName with a modified missing file
    cout<<endl;

    Wordle wordle("wordList.txt");     //Constructs the Wordle Class with the proper file
    wordle.loadWordList();                        //Testing the loadWordList function with the proper file
    cout<<wordle.getFilename()<<endl;             //Testing the getFilename function with the proper file
    //wordle.printWordList();                     //Tested the printWordList function with the proper file
    cout<<endl;

    wordle.setSecretWord("quiet");      //Testing setSecretWord with a proper word

    cout<<wordle.getSecretWord()<<endl;          //Testing getSecretWord with a proper word
    cout<<endl;

    wordle.setSecretWord("fireman");    //Testing setSecretWord with an improper word
    cout<<wordle.getSecretWord()<<endl;          //Testing getSecretWord with an improper word
    cout<<endl;

    wordle.setSecretWord("wimpy");      //Testing setSecretWord with a 5 letter word not in the list
    cout<<wordle.getSecretWord()<<endl;          //Testing getSecretWord with a 5 letter word not in the list
    cout<<endl;

    wordle.setRandomSecretWord();                //Testing setRandomSecret Word 3 times to ensure its a different
    cout<<wordle.getSecretWord()<<endl;          //random output everytime
    wordle.setRandomSecretWord();
    cout<<wordle.getSecretWord()<<endl;
    wordle.setRandomSecretWord();
    cout<<wordle.getSecretWord()<<endl;

    wordle.setSecretWord("quiet"); //Locking in the secret to test the makeGuess function and print function
   wordle.makeGuess("egoth");       //Testing with a word on the lost
   wordle.makeGuess("river");       //Testing make Guess with wrong word from the list 5 times
   wordle.makeGuess("river");
   wordle.makeGuess("river");
   wordle.makeGuess("river");
   wordle.makeGuess("river");
   wordle.makeGuess("quiet");      //Testing the right guess

   wordle.makeGuess("quiet");       //Testing a right guess after the Num Limit is hit
   wordle.print();                  //Testing print function with a wrong word guess and an extra guess

  //Instructions for Game:
  cout<<"Welcome to Wordle"<<endl;
  cout<<"There's a Five Letter Word you Need to Guess, Goodluck!"<<endl;
  cout<<"Rules: ";
  cout<<"1:You have 6 guesses to get the right answer"<<endl;
  cout<<"       2:If your guess doesn't mean the parameters, the guess won't count against you"<<endl;
  cout<<"       3:Type your guess at the prompt and Enjoy!"<<endl;
  cout<<"4: After each guess, you will get feedback to how close your guess was to the word"<<endl;
  cout<<"! is the correct letter in the correct spot"<<endl;
 cout<<"+ is the correct letter in the wrong spot"<<endl;
 cout<<". is a letter that does not appear in the word"<<endl;

  Wordle gameTime("wordList.txt");         //Initializes an object of the Wordle class
  gameTime.loadWordList();                            //Loads the strings stored in the file
  gameTime.setSecretWord("major");           //Initializes the set secret word
  int guessCount = 0;                                 //Initializes counter for the while loop
  int gameOver = 0;                                   //Initializes
  string userGuess;                                   //Initializes the variable that will the store the user guesses

  while(guessCount < 6){                             //Loop that limits the player to only 6 guesses
      cout<<"Make a Guess: ";                        //Prints User Prompt
      cin>>userGuess;                                //Takes in the user's guest

      if(gameTime.makeGuess(userGuess)){    //Put the users guess into the makeGuess function while also
          gameOver = 5;                              //checking if the guess is right, which if it is, it updates
      }                                              //an int that always gets added at the end of the loop

      cout << "Valid Guesses Made: " << gameTime.getGuessNum() << endl;   //Outputs the guessNum from the private class
      gameTime.print();                                           //Uses the print function to print out the guess data
      gameTime.printAvailableLetters();
      guessCount = gameTime.getGuessNum() + gameOver;             //Changes the counter to match the private guessNum
  }                                                                                           //and ends game if gameOver was changed from 0
}

