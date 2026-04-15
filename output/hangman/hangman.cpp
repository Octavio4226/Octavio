#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Your list of words
    vector<string> words = {
        "computer", "programming", "python", "robot", "tree", "phone"
    };

    // Pick a random word
    srand(time(0));
    string word = words[rand() % words.size()];

    string guessed(word.size(), '_');
    int attempts = 6;
    vector<char> tried;

    cout << "Welcome to Hangman!\n";

    while (attempts > 0 && guessed != word) {
        cout << "\nWord: ";
        for (char c : guessed) cout << c << ' ';

        cout << "\nAttempts left: " << attempts << "\nTried letters: ";
        for (char c : tried) cout << c << ' ';
        cout << "\nChoose a letter: ";

        char letter;
        cin >> letter;

        // Check if already tried
        bool already = false;
        for (char c : tried) {
            if (c == letter) {
                already = true;
                break;
            }
        }
        if (already) {
            cout << "You already tried that letter.\n";
            continue;
        }

        tried.push_back(letter);

        // Check if letter is in the word
        bool found = false;
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }

        if (found) {
            cout << "Nice! The letter is in the word.\n";
        } else {
            cout << "Wrong guess.\n";
            attempts--;
        }
    }

    if (guessed == word) {
        cout << "\nYou won! The word was: " << word << "\n";
    } else {
        cout << "\nYou lost! The word was: " << word << "\n";
    }

    return 0;
}