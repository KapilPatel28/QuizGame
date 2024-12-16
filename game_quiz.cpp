#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct Player {
    string name;
    string email;
};
// Function to register player details
Player registerPlayer() {
    Player player;
    cout << "Enter your name: ";
    getline(cin, player.name);  // Get the player's name
    cout << "Enter your email: ";
    getline(cin, player.email);  // Get the player's email
    cout << "Registration successful!" << endl;
    return player;
}

// Structure to store quiz questions, options, and the correct answer
struct Question {
    string question;
    string options[4];
    char correctAnswer;
};

// Function to load quiz questions from a file
vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream file("questions.txt");  // Open questions.txt for reading
    if (!file) {
        cout << "Error opening questions file!" << endl;
        return questions;  // Return empty vector if file not found
    }

    string line;
    while (getline(file, line)) {
        Question q;
        q.question = line;  // Read the question
        for (int i = 0; i < 4; i++) {
            getline(file, line);
            q.options[i] = line;  // Read the options
        }
        getline(file, line);
        q.correctAnswer = line[line.size() - 1];  // Access last character (correct answer)
        questions.push_back(q);  // Add question to the vector
    }
    file.close();
    return questions;  // Return the vector of questions
}

// Function to play the quiz
void playQuiz(const vector<Question>& questions) {
    int score = 0;
    char answer;

    // Using traditional for loop instead of range-based
    for (int i = 0; i < questions.size(); i++) {
        cout << questions[i].question << endl;  // Display the question
        for (int j = 0; j < 4; j++) {
            cout << (char)('A' + j) << ". " << questions[i].options[j] << endl;  // Display the options
        }
        cout << "Enter your answer (A/B/C/D): ";
        cin >> answer;
        if (toupper(answer) == toupper(questions[i].correctAnswer)) {  // Compare answers (case insensitive)
            score++;
            cout << "Correct!" << endl;
        } else {
            cout << "Incorrect!" << endl;
        }
        cout << endl;
    }
    cout << "Your final score is: " << score << endl;
}

// Function to save the player's score to a file
void saveScore(const Player& player, int score) {
    ofstream file("scores.txt", ios::app);  // Open scores.txt in append mode
    if (!file) {
        cout << "Error opening score file!" << endl;
        return;  // If the file cannot be opened, do not proceed
    }
    file << player.name << " (" << player.email << ") - Score: " << score << endl;  // Save the score
    file.close();
}

// Function to display the leaderboard from the file
void displayLeaderboard() {
    ifstream file("scores.txt");  // Open scores.txt for reading
    if (!file) {
        cout << "Error opening score file!" << endl;
        return;  // If the file is not found, return
    }

    string line;
    cout << "Leaderboard:" << endl;
    while (getline(file, line)) {
        cout << line << endl;  // Display each score entry
    }
    file.close();
}

int main() {
    Player player = registerPlayer();  // Register the player
    vector<Question> questions = loadQuestions();  // Load questions from the file
    if (questions.empty()) {
        cout << "No questions loaded. Exiting..." << endl;
        return 1;  // Exit if no questions were loaded
    }

    playQuiz(questions);  // Play the quiz
    saveScore(player, 10);  // Example: Save score as 10
    displayLeaderboard();  // Display the leaderboard
    return 0;
}

