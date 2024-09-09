#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    srand(static_cast<unsigned>(time(0)));

    int randomNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    int maxAttempts = 5;  

    cout << "Welcome to the Number Guessing Game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";
    cout << "You have " << maxAttempts << " attempts to guess the number.\n";

   
    while (attempts < maxAttempts) {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess > randomNumber) {
            cout << "Too high! Try again.\n";
        }
        else if (guess < randomNumber) {
            cout << "Too low! Try again.\n";
        }
        else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
            break;
        }

        
        if (attempts == maxAttempts) {
            cout << "Sorry, you've used all your attempts. The correct number was " << randomNumber << ".\n";
        }
    }

    return 0;
}
