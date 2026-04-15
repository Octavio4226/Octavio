#include <iostream>

#include <cstdlib>

using namespace std;

int main() {
srand(time(0));    

    //generate a random number
    
    int randomNumber = rand() % 100 + 1; // Number between 1 and 100;

    int userGuess;

    int attempts = 0;

    cout << "Game: Guess the Number(1 - 100)" << endl;

    do {
        cout << "Enter your guess: ";

        cin >> userGuess;

        attempts++;

        int difference = abs(randomNumber - userGuess);

        if (userGuess < randomNumber) {

            cout << "Too low! ";
        } else if (userGuess > randomNumber) {

            cout << "Too high!";

        } else {
            cout << "\nCongratulations! You guessed the number in " << attempts << " attempts." << endl;

            break;
        }

    } while (userGuess != randomNumber);
    return 0;
}