#include <iostream>  // Acest header ne permite să afișăm text și să citim input de la utilizator, ca un dialog cu jucătorul.
#include <vector>    // Acest header ne ajută să stocăm liste de lucruri, cum ar fi literele ghicite sau cuvintele din categorii.
#include <string>    // Acest header ne permite să lucrăm cu cuvinte și texte, ca să manipulăm cuvântul de ghicit.
#include <ctime>     // Acest header ne dă timpul curent, pe care îl folosim pentru a face jocul aleatoriu.
#include <cstdlib>   // Acest header ne permite să generăm numere aleatorii, pentru a alege cuvinte la întâmplare.
#include <algorithm> // Acest header are funcții utile, cum ar fi căutarea într-o listă.

using namespace std;  // Acest lucru face ca toate instrumentele standard să fie ușor de folosit, fără să scriem "std::" mereu.

void clearScreen() {  // Această funcție șterge ecranul pentru a face jocul să arate curat și nou.
#ifdef _WIN32         // Dacă suntem pe Windows...
    system("cls");   // ...folosim comanda "cls" pentru a șterge ecranul.
#else                // Altfel, pe alte sisteme ca Linux...
    system("clear"); // ...folosim "clear".
#endif
}

void drawHangman(int wrong, int maxWrong) {  // Această funcție desenează omulețul spânzurat, în funcție de câte greșeli a făcut jucătorul.
    int stage = wrong;  // Stadiul este același cu numărul de greșeli.

    if (stage > 6) stage = 6;  // Dacă sunt mai mult de 6 greșeli, rămânem la stadiul 6, pentru că nu avem mai multe desene.

    switch (stage) {  // În funcție de stadiu, desenăm o parte diferită a spânzurătorii.
        case 0:  // Dacă nu sunt greșeli, desenăm doar spânzurătoarea goală.
            cout << "  _______\n"
                    " |/      |\n"
                    " |\n"
                    " |\n"
                    " |\n"
                    " |\n"
                    "_|___\n";
            break;
        case 1:  // Adăugăm capul.
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |\n"
                    " |\n"
                    " |\n"
                    "_|___\n";
            break;
        case 2:  // Adăugăm corpul.
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |       |\n"
                    " |       |\n"
                    " |\n"
                    "_|___\n";
            break;
        case 3:  // Adăugăm un braț.
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |      /|\n"
                    " |       |\n"
                    " |\n"
                    "_|___\n";
            break;
        case 4:  // Adăugăm celălalt braț.
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |      /|\\\n"
                    " |       |\n"
                    " |\n"
                    "_|___\n";
            break;
        case 5:  // Adăugăm un picior.
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |      /|\\\n"
                    " |       |\n"
                    " |      /\n"
                    "_|___\n";
            break;
        case 6:  // Adăugăm celălalt picior - sfârșit!
            cout << "  _______\n"
                    " |/      |\n"
                    " |      ( )\n"
                    " |      /|\\\n"
                    " |       |\n"
                    " |      / \\\n"
                    "_|___\n";
            break;
    }
}

int chooseDifficulty() {  // Această funcție lasă jucătorul să aleagă cât de greu să fie jocul.
    cout << "Choose difficulty:\n";  // Afișăm opțiunile.
    cout << "1. Easy   (10 wrong guesses allowed)\n";
    cout << "2. Medium (6 wrong guesses allowed)\n";
    cout << "3. Hard   (4 wrong guesses allowed)\n";
    cout << "Selection: ";

    int choice;  // Variabilă pentru alegerea jucătorului.
    cin >> choice;  // Citim alegerea.

    if (!cin) {  // Dacă input-ul nu este valid (nu e număr)...
        cin.clear();
        cin.ignore(10000, '\n');
        return 6;  // Returnăm dificultatea medie implicit.
    }

    if (choice == 1) return 10;  // Dacă a ales 1, ușor: 10 greșeli permise.
    if (choice == 3) return 4;   // Dacă a ales 3, greu: 4 greșeli.
    return 6;  // Altfel, mediu: 6 greșeli.
}

string chooseCategory(const vector<vector<string>>& categories,  // Această funcție alege o categorie și apoi un cuvânt din ea.
                      const vector<string>& names) {
    cout << "\nChoose a category:\n";  // Afișăm categoriile disponibile.
    for (int i = 0; i < names.size(); i++) {  // Pentru fiecare categorie...
        cout << i + 1 << ". " << names[i] << "\n";  // Afișăm numărul și numele.
    }
    cout << "Selection: ";

    int choice;  // Alegerea categoriei.
    cin >> choice;

    if (!cin) {  // Dacă input invalid...
        cin.clear();
        cin.ignore(10000, '\n');
        choice = 1;  // Alegem prima categorie implicit.
    }

    if (choice < 1 || choice > names.size()) {  // Dacă alegerea e în afara limitelor...
        choice = 1;  // Alegem prima.
    }

    const vector<string>& list = categories[choice - 1];  // Luăm lista de cuvinte din categoria aleasă.
    return list[rand() % list.size()];  // Alegem un cuvânt la întâmplare din listă.
}

int main() {  // Aceasta este funcția principală unde începe jocul.
    srand((unsigned int)time(nullptr));  // Inițializăm generatorul de numere aleatorii cu timpul curent.

    vector<vector<string>> categories = {  // Lista de categorii, fiecare cu cuvintele ei.
        {"cat", "dog", "tiger", "lion", "eagle", "shark", "bear", "wolf"},  // Animale.
        {"computer", "keyboard", "internet", "software", "hardware", "algorithm", "monitor", "program"},  // Tehnologie.
        {"spain", "france", "germany", "brazil", "japan", "canada", "mexico", "italy"},  // Țări.
        {"hangman", "programming", "template", "variable", "pointer", "library", "function", "compile"}  // Programare.
    };

    vector<string> categoryNames = {  // Numele categoriilor.
        "Animals", "Technology", "Countries", "Programming"
    };

    clearScreen();  // Ștergem ecranul.
    cout << "=============================\n";  // Afișăm titlul jocului.
    cout << "         HANGMAN GAME        \n";
    cout << "=============================\n\n";

    int maxWrong = chooseDifficulty();  // Alegem dificultatea.
    clearScreen();  // Ștergem ecranul din nou.

    string word = chooseCategory(categories, categoryNames);  // Alegem cuvântul de ghicit.
    string hidden(word.size(), '_');  // Creăm un șir ascuns cu '_' pentru fiecare literă.

    vector<char> guessed;  // Lista literelor ghicite.
    int wrong = 0;  // Numărul de greșeli.

    while (wrong < maxWrong && hidden != word) {  // Cât timp nu am pierdut și nu am ghicit cuvântul...
        clearScreen();  // Ștergem ecranul.
        cout << "===== HANGMAN =====\n\n";  // Afișăm titlul rundei.
        drawHangman(wrong, maxWrong);  // Desenăm spânzurătoarea.

        cout << "\nWord: " << hidden << "\n";  // Afișăm cuvântul ascuns.
        cout << "Wrong guesses: " << wrong << " / " << maxWrong << "\n";  // Numărul de greșeli.

        cout << "Guessed letters: ";  // Literele încercate.
        for (char c : guessed) cout << c << ' ';  // Le afișăm.
        cout << "\n\nEnter a letter: ";  // Cerem o literă nouă.

        char guess;  // Litera ghicită.
        cin >> guess;

        if (!cin) {  // Dacă input invalid...
            cin.clear();
            cin.ignore(10000, '\n');
            continue;  // Trecem la următoarea rundă.
        }

        guess = tolower(guess);  // Facem litera mică.

        if (find(guessed.begin(), guessed.end(), guess) != guessed.end()) {  // Dacă am încercat deja această literă...
            cout << "You already tried that letter. Press Enter...";  // Spunem jucătorului.
            cin.ignore(10000, '\n');
            cin.get();  // Așteptăm Enter.
            continue;  // Trecem mai departe.
        }

        guessed.push_back(guess);  // Adăugăm litera la lista ghicită.

        bool correct = false;  // Presupunem că e greșită.
        for (int i = 0; i < word.size(); i++) {  // Pentru fiecare literă din cuvânt...
            if (word[i] == guess) {  // Dacă se potrivește...
                hidden[i] = guess;  // Dezvăluim litera în cuvântul ascuns.
                correct = true;  // Marcăm că e corectă.
            }
        }

        if (!correct) wrong++;  // Dacă nu e corectă, creștem greșelile.
    }

    clearScreen();  // Ștergem ecranul pentru sfârșit.
    drawHangman(wrong, maxWrong);  // Desenăm spânzurătoarea finală.

    if (hidden == word) {  // Dacă am ghicit cuvântul...
        cout << "\nCongratulations! You guessed the word: " << word << "\n";  // Felicitări!
    } else {  // Altfel...
        cout << "\nGame Over! The word was: " << word << "\n";  // Joc terminat.
    }

    cout << "\nPress Enter to exit...";  // Așteptăm să ieșim.
    cin.ignore(10000, '\n');
    cin.get();

    return 0;  // Sfârșitul programului.
}