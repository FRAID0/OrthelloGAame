#ifndef OTHELLOBOARD_H
#define OTHELLOBOARD_H

#include <vector>
#include "player.h"

class OthelloBoard {
private:
    static const int BOARD_SIZE = 8;  // Größe des Spielbretts (8x8)
    Player::Color board[8][8];  // Spielbrett mit Spielsteinen vom Typ Player::Color

public:
    OthelloBoard();  // Konstruktor
    void initializeBoard();  // Initialisierungsmethode
    void displayBoard() const;  // Methode zur Anzeige des Spielbretts
    Player::Color getPiece(int row, int col) const;  // Erhalte das Spielstein an einer bestimmten Position
    bool placePiece(int row, int col, Player::Color color);  // Setze einen Spielstein
    bool isValidMove(int row, int col, Player::Color color) const;  // Überprüfen der Gültigkeit des Zuges
    void capturePieces(int row, int col, Player::Color color);  // Fangen der Spielsteine
    bool hasValidMoves(const Player::Color& color) const;  // Überprüfen der gültigen Züge für einen Spieler
    int countPieces(Player::Color color) const;

private:
    bool checkAllDirections(int row, int col, Player::Color color) const;  // Überprüfen in alle Richtungen
};

#endif // OTHELLOBOARD_H
