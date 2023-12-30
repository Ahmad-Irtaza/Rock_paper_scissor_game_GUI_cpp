#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace std;

enum Choice { ROCK, PAPER, SCISSORS };

class RockPaperScissorsGame {
public:
    RockPaperScissorsGame() : window(sf::VideoMode(400, 300), "Rock Paper Scissors Game") {
        setupUI();
    }
    
    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    handleMouseClick(event.mouseButton.x);
                }
            }

            window.clear();
            window.draw(title);
            window.draw(choicesText);
            window.draw(resultText);
            window.display();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    sf::Text choicesText;
    sf::Text resultText;
    Choice playerChoice;
    Choice computerChoice;

    void setupUI() {
        if (!font.loadFromFile("Poppins.ttf")) { 
            cerr << "Failed to load font" << endl;
            return;
        }

        title.setFont(font);
        title.setString("Rock Paper Scissors Game");
        title.setCharacterSize(26);
        title.setPosition(30, 20);

        choicesText.setFont(font);
        choicesText.setCharacterSize(25);
        choicesText.setPosition(45, 155);  
        choicesText.setString("Rock             Paper         Scissors");

        resultText.setFont(font);
        resultText.setCharacterSize(20);
        resultText.setPosition(30, 200);  

        updateChoicesText();
    }

    void handleMouseClick(int mouseX) {
        if (mouseX < 150) {
            playerChoice = ROCK;
        } else if (mouseX < 250) {
            playerChoice = PAPER;
        } else {
            playerChoice = SCISSORS;
        }

        determineWinner();
    }

    void determineWinner() {
        computerChoice = static_cast<Choice>(rand() % 3);

        string result = "It's a tie!";
        if ((playerChoice == ROCK && computerChoice == SCISSORS) ||
            (playerChoice == PAPER && computerChoice == ROCK) ||
            (playerChoice == SCISSORS && computerChoice == PAPER)) {
            result = "You win!";
        } else if ((computerChoice == ROCK && playerChoice == SCISSORS) ||
                   (computerChoice == PAPER && playerChoice == ROCK) ||
                   (computerChoice == SCISSORS && playerChoice == PAPER)) {
            result = "Computer wins!";
        }

        resultText.setString("Result: " + result + "\nYou chose: " + choiceToString(playerChoice) +
                             "\nComputer chose: " + choiceToString(computerChoice));

        cout << "You chose " << choiceToString(playerChoice) << "\nComputer chose " << choiceToString(computerChoice) << "\n\n" << result << endl;

        updateChoicesText();
    }

    string choiceToString(Choice choice) {
        switch (choice) {
        case ROCK:
            return "Rock";
        case PAPER:
            return "Paper";
        case SCISSORS:
            return "Scissors";
        }
        return "";
    }

    void updateChoicesText() {
        // Update the text based on the selected choices if needed
    }
};


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    RockPaperScissorsGame game;
    game.run();

    return 0;
}
