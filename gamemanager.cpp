#include "gamemanager.h"
#include <iostream>
#include "othelloboard.h"
#include "player.h"

GameManager::GameManager() {
    player1.setColor(Player::Color::BLACK);
    player2.setColor(Player::Color::WHITE);
    currentPlayer = &player1;  // Spieler 1 beginnt
}

void GameManager::startGame() {
    std::cout << "Das Spiel beginnt!" << std::endl;
    board.initializeBoard();  // Initialisierung des Spielbretts

    // Beginn der Spielschleife
    while (!isGameOver()) {
        // Aktuellen Zustand des Spielbretts anzeigen
        board.displayBoard();

        // Aktuelle Punktzahlen der beiden Spieler anzeigen
        int blackScore = board.countPieces(Player::Color::BLACK);
        int whiteScore = board.countPieces(Player::Color::WHITE);
        std::cout << "Aktuelle Punktzahl - Black: " << blackScore << ", White: " << whiteScore << std::endl;

        // Der aktuelle Spieler macht seinen Zug
        playTurn(*currentPlayer);

        // Zum nächsten Spieler wechseln
        switchPlayer();
    }

    std::cout << "Das Spiel ist beendet." << std::endl;

    // Endpunktzahl anzeigen
    int blackScore = board.countPieces(Player::Color::BLACK);
    int whiteScore = board.countPieces(Player::Color::WHITE);

    std::cout << "Endpunktzahl: Black: " << blackScore << ", White: " << whiteScore << std::endl;
}

bool GameManager::hasValidMoves(const Player& player) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.isValidMove(row, col, player.getColor())) {
                return true;
            }
        }
    }
    return false;
}

OthelloBoard& GameManager::getBoard() {
    return board;
}

bool GameManager::isGameOver() const {
    bool noValidMovesPlayer1 = !hasValidMoves(player1);
    bool noValidMovesPlayer2 = !hasValidMoves(player2);

    if (noValidMovesPlayer1 && noValidMovesPlayer2) {
        std::cout << "Das Spiel ist beendet. Es gibt keine gueltigen Züge mehr." << std::endl;
        return true;
    }
    return false;
}

void GameManager::nextTurn() {
    if (!hasValidMoves(*currentPlayer)) {
        std::cout << "Der Spieler " << (currentPlayer->getColor() == Player::Color::BLACK ? "Black" : "White")
                  << " hat keine gültigen Züge, der Zug wird übersprungen." << std::endl;
        switchPlayer();  // Wenn der Spieler keine gültigen Züge hat, ist der nächste Spieler an der Reihe
    }
}

void GameManager::playTurn(Player& player) {
    int row, col;
    std::cout << "Es ist der Zug des Spielers " << (player.getColor() == Player::Color::BLACK ? "Black" : "White") << std::endl;
    board.displayBoard();
    std::cout << "Geben Sie die Koordinaten für den Zug ein (Zeile und Spalte): ";
    std::cin >> row >> col;

    if (board.isValidMove(row - 1, col - 1, player.getColor())) {
        board.placePiece(row - 1, col - 1, player.getColor());
        nextTurn();
    } else {
        std::cout << "Ungültiger Zug. Versuchen Sie es noch einmal." << std::endl;
        playTurn(player);  // Wenn der Zug ungültig ist, erneut fragen
    }
}

void GameManager::switchPlayer() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;  // Zum nächsten Spieler wechseln
}

Player& GameManager::getCurrentPlayer() {
    return *currentPlayer;
}

void GameManager::displayBoard() const {
    board.displayBoard();
}

bool GameManager::isValidMove(int row, int col) const {
    // Direkt die Methode isValidMove des Spielbretts aufrufen, um die Gültigkeit des Zuges zu überprüfen
    return board.isValidMove(row, col, currentPlayer->getColor());
}
