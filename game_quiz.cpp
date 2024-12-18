#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct Player {
    string name;
    string email;
};

Player registerPlayer() {
    Player player;
    cout << "Enter your name: ";
    getline(cin, player.name);  
    cout << "Enter your email: ";
    getline(cin, player.email);  
    cout << "Registration successful!" << endl;
    return player;
}


struct Question {
    string question;
    string options[4];
    char correctAnswer;
};


vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream file("questions.txt");  
    if (!file) {
        cout << "Error opening questions file!" << endl;
        return questions;  
    }

    string line;
    while (getline(file, line)) {
        Question q;
        q.question = line;  
        for (int i = 0; i < 4; i++) {
            getline(file, line);
            q.options[i] = line;  
        }
        getline(file, line);
        q.correctAnswer = line[line.size() - 1]; 
        questions.push_back(q); 
    }
    file.close();
    return questions;  
}


void playQuiz(const vector<Question>& questions) {
    int score = 0;
    char answer;


    for (int i = 0; i < questions.size(); i++) {
        cout << questions[i].question << endl;  
        for (int j = 0; j < 4; j++) {
            cout << (char)('A' + j) << ". " << questions[i].options[j] << endl;  
        }
        cout << "Enter your answer (A/B/C/D): ";
        cin >> answer;
        if (toupper(answer) == toupper(questions[i].correctAnswer)) {  
            score++;
            cout << "Correct!" << endl;
        } else {
            cout << "Incorrect!" << endl;
        }
        cout << endl;
    }
    cout << "Your final score is: " << score << endl;
}


void saveScore(const Player& player, int score) {
    ofstream file("scores.txt", ios::app);  
    if (!file) {
        cout << "Error opening score file!" << endl;
        return;  
    }
    file << player.name << " (" << player.email << ") - Score: " << score << endl; 
    file.close();
}


void displayLeaderboard() {
    ifstream file("scores.txt");  
    if (!file) {
        cout << "Error opening score file!" << endl;
        return; 
    }

    string line;
    cout << "Leaderboard:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    Player player = registerPlayer();  
    vector<Question> questions = loadQuestions();  
    if (questions.empty()) {
        cout << "No questions loaded. Exiting..." << endl;
        return 1; 
    }

    playQuiz(questions);  
    saveScore(player, 10);  
    displayLeaderboard();  
    return 0;
}

