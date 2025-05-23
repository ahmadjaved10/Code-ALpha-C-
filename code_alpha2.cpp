#include <iostream>
using namespace std;

class User {
public:
    static const int MAX_LENGTH = 256;
private:
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int score;
public:
    User() : score(0) {
        username[0] = '\0';
        password[0] = '\0';
    }
    void setUsername(const char* uname) {
        int i = 0;
        while (uname[i] != '\0' && i < MAX_LENGTH - 1) {
            username[i] = uname[i];
            ++i;
        }
        username[i] = '\0';
    }
    void setPassword(const char* pwd) {
        int i = 0;
        while (pwd[i] != '\0' && i < MAX_LENGTH - 1) {
            password[i] = pwd[i];
            ++i;
        }
        password[i] = '\0';
    }
    const char* getUsername() const { return username; }
    const char* getPassword() const { return password; }
    int getScore() const { return score; }
    void setScore(int s) { score = s; }
};

class Question {
public:
    static const int MAX_LENGTH = 256;
    static const int MAX_OPTIONS = 4;
private:
    char questionText[MAX_LENGTH];
    char options[MAX_OPTIONS][MAX_LENGTH];
    int correctAnswerIndex;
public:
    Question() : correctAnswerIndex(-1) {
        questionText[0] = '\0';
        for (int i = 0; i < MAX_OPTIONS; ++i) {
            options[i][0] = '\0';
        }
    }
    void setQuestionText(const char* qText) {
        int i = 0;
        while (qText[i] != '\0' && i < MAX_LENGTH - 1) {
            questionText[i] = qText[i];
            ++i;
        }
        questionText[i] = '\0';
    }
    void setOptions(const char opts[MAX_OPTIONS][MAX_LENGTH]) {
        for (int i = 0; i < MAX_OPTIONS; ++i) {
            int j = 0;
            while (opts[i][j] != '\0' && j < MAX_LENGTH - 1) {
                options[i][j] = opts[i][j];
                ++j;
            }
            options[i][j] = '\0';
        }
    }
    void setCorrectAnswerIndex(int index) {
        correctAnswerIndex = index;
    }
    const char* getQuestionText() const { return questionText; }
    const char* getOption(int index) const { return options[index]; }
    int getCorrectAnswerIndex() const { return correctAnswerIndex; }
};

class QuizGame {
    static const int MAX_USERS = 100;
    static const int MAX_QUESTIONS = 10;
    User users[MAX_USERS];
    Question questions[MAX_QUESTIONS];
    int userCount;
    int questionCount;
public:
    QuizGame() : userCount(0), questionCount(0) {}

    bool registerUser(const char* username, const char* password) {
        for (int i = 0; i < userCount; ++i) {
            int j = 0;
            bool match = true;
            while (username[j] != '\0' || users[i].getUsername()[j] != '\0') {
                if (username[j] != users[i].getUsername()[j]) {
                    match = false;
                    break;
                }
                ++j;
            }
            if (match) {
                cout << "Username already exists.\n";
                return false;
            }
        }
        users[userCount].setUsername(username);
        users[userCount].setPassword(password);
        ++userCount;
        cout << "User registered successfully.\n";
        return true;
    }

    bool loginUser(const char* username, const char* password) {
        for (int i = 0; i < userCount; ++i) {
            int j = 0;
            bool matchUser = true, matchPass = true;
            while (username[j] != '\0' || users[i].getUsername()[j] != '\0') {
                if (username[j] != users[i].getUsername()[j]) {
                    matchUser = false;
                    break;
                }
                ++j;
            }
            j = 0;
            while (password[j] != '\0' || users[i].getPassword()[j] != '\0') {
                if (password[j] != users[i].getPassword()[j]) {
                    matchPass = false;
                    break;
                }
                ++j;
            }
            if (matchUser && matchPass) {
                cout << "User logged in successfully.\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n";
        return false;
    }

    void addQuestion(const char* questionText, const char options[Question::MAX_OPTIONS][Question::MAX_LENGTH], int correctAnswerIndex) {
        questions[questionCount].setQuestionText(questionText);
        questions[questionCount].setOptions(options);
        questions[questionCount].setCorrectAnswerIndex(correctAnswerIndex);
        ++questionCount;
    }

    void takeQuiz(User& user) {
        int score = 0;
        for (int i = 0; i < questionCount; ++i) {
            cout << "Q" << (i + 1) << ": " << questions[i].getQuestionText() << "\n";
            for (int j = 0; j < Question::MAX_OPTIONS; ++j) {
                cout << (j + 1) << ". " << questions[i].getOption(j) << "\n";
            }
            int answer;
            cout << "Your answer: ";
            cin >> answer;
            if (answer - 1 == questions[i].getCorrectAnswerIndex()) {
                ++score;
            }
        }
        user.setScore(score);
        cout << "You scored " << score << " out of " << questionCount << ".\n";
    }

    void mainLoop() {
        while (true) {
            int choice;
            cout << "1. Register\n2. Login\n3. Exit\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                char username[User::MAX_LENGTH], password[User::MAX_LENGTH];
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                registerUser(username, password);
            }
            else if (choice == 2) {
                char username[User::MAX_LENGTH], password[User::MAX_LENGTH];
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (loginUser(username, password)) {
                    User* user = nullptr;
                    for (int i = 0; i < userCount; ++i) {
                        int j = 0;
                        bool match = true;
                        while (username[j] != '\0' || users[i].getUsername()[j] != '\0') {
                            if (username[j] != users[i].getUsername()[j]) {
                                match = false;
                                break;
                            }
                            ++j;
                        }
                        if (match) {
                            user = &users[i];
                            break;
                        }
                    }
                    if (user != nullptr) {
                        takeQuiz(*user);
                    }
                }
            }
            else if (choice == 3) {
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    QuizGame quizGame;

    // Example questions
    const char options1[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "Option 1", "Option 2", "Option 3", "Option 4" };
    quizGame.addQuestion("What is 2 + 2?", options1, 1); // correct answer: Option 2

    const char options2[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "Red", "Green", "Blue", "Yellow" };
    quizGame.addQuestion("What is the color of the sky?", options2, 2); // correct answer: Blue

    const char options3[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "Earth", "Mars", "Jupiter", "Saturn" };
    quizGame.addQuestion("Which planet is known as the Red Planet?", options3, 1); // correct answer: Mars

    const char options4[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "Albert Einstein", "Isaac Newton", "Galileo Galilei", "Stephen Hawking" };
    quizGame.addQuestion("Who developed the theory of relativity?", options4, 0); // correct answer: Albert Einstein

    const char options5[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "1.618", "3.141", "2.718", "1.414" };
    quizGame.addQuestion("What is the value of the golden ratio?", options5, 0); // correct answer: 1.618

    const char options6[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "Leonardo da Vinci", "Vincent van Gogh", "Pablo Picasso", "Claude Monet" };
    quizGame.addQuestion("Who painted the Mona Lisa?", options6, 0); // correct answer: Leonardo da Vinci

    const char options7[Question::MAX_OPTIONS][Question::MAX_LENGTH] = { "A", "B", "C", "D" };
    quizGame.addQuestion("Which letter comes after B in the alphabet?", options7, 2); // correct answer: C



    cout<<"hello it is me ahmad"<<endl;
    // Run the main loop
    quizGame.mainLoop();

    return 0;
}
