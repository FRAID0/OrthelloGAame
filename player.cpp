#include "player.h"

// Konstruktor mit der Spielerfarbe (Standardwert BLACK)
Player::Player(Color color) : playerColor(color) {
    // Initialisierung der Spielerfarbe
}

// Konstruktor mit dem Namen des Spielers
Player::Player(const std::string& playerName) : name(playerName), playerColor(Color::BLACK) {
    // Initialisierung des Spielernamens und der Standardfarbe (BLACK)
}

// Getter für die Spielerfarbe
Player::Color Player::getColor() const {
    return playerColor;
}

// Setter für die Spielerfarbe
void Player::setColor(Color color) {
    playerColor = color;
}

// Getter für den Spielernamen
std::string Player::getName() const {
    return name;
}

// Setter für den Spielernamen
void Player::setName(const std::string& playerName) {
    name = playerName;
}

// Platzhalter für die Bewegung des Spielers
void Player::makeMove(int row, int col) {
    (void)row;  // Zeigt an, dass row nicht verwendet wird
    (void)col;  // Zeigt an, dass col nicht verwendet wird
    // Platzhalter für die Bewegung
}
