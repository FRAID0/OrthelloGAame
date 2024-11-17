#include "othelloboard.h"
#include <iostream>

OthelloBoard::OthelloBoard() {
    initializeBoard();  // Brett initialisieren
}

void OthelloBoard::initializeBoard() {
    // Initialisiere das Brett mit leeren Steinen
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = Player::Color::EMPTY;  // Leere Felder mit Player::Color füllen
        }
    }

    // Setze die Startsteine
    board[3][3] = Player::Color::WHITE;
    board[3][4] = Player::Color::BLACK;
    board[4][3] = Player::Color::BLACK;
    board[4][4] = Player::Color::WHITE;
}

// OthelloBoard.cpp
#include "othelloboard.h"
#include "player.h"

int OthelloBoard::countPieces(Player::Color color) const {
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == color) {
                count++;
            }
        }
    }
    return count;
}

Player::Color OthelloBoard::getPiece(int row, int col) const {
    return board[row][col];  // Gibt die Farbe des Steins an der angegebenen Position zurück
}

void OthelloBoard::displayBoard() const {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << i + 1 << " ";  // Zeilen nummerieren
        for (int j = 0; j < BOARD_SIZE; ++j) {
            char displayChar = '.';
            if (board[i][j] == Player::Color::BLACK) {
                displayChar = 'B';
            } else if (board[i][j] == Player::Color::WHITE) {
                displayChar = 'W';
            }
            std::cout << displayChar << " ";
        }
        std::cout << std::endl;
    }
}

bool OthelloBoard::placePiece(int row, int col, Player::Color color) {
    if (board[row][col] != Player::Color::EMPTY) {
        return false;  // Feld bereits besetzt
    }

    board[row][col] = color;  // Stein setzen
    capturePieces(row, col, color);  // Gegnerische Steine fangen
    return true;
}

bool OthelloBoard::isValidMove(int row, int col, Player::Color color) const {
    if (board[row][col] != Player::Color::EMPTY) {
        return false;  // Das Feld ist bereits besetzt
    }

    // Überprüft alle Richtungen, ob der Zug gültig ist
    for (int dirX = -1; dirX <= 1; ++dirX) {
        for (int dirY = -1; dirY <= 1; ++dirY) {
            // Ignoriere die Richtung (0, 0), da dies das aktuelle Feld ist
            if (dirX == 0 && dirY == 0) continue;

            int r = row + dirX;
            int c = col + dirY;
            bool opponentFound = false;

            // Durchlaufe die Felder in dieser Richtung
            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c] == Player::Color::EMPTY) {
                    break;  // Wenn ein leeres Feld gefunden wird, stoppe die Suche
                }

                if (board[r][c] != color) {
                    opponentFound = true;  // Ein gegnerischer Stein wurde gefunden
                } else if (opponentFound) {
                    return true;  // Wenn nach einem gegnerischen Stein ein Stein der eigenen Farbe gefunden wird, ist der Zug gültig
                } else {
                    break;  // Ein Stein der gleichen Farbe direkt nach einem anderen Stein der gleichen Farbe => ungültiger Zug
                }

                // Weiter in dieser Richtung
                r += dirX;
                c += dirY;
            }
        }
    }

    return false;  // Kein gültiger Zug in den Richtungen gefunden
}

void OthelloBoard::capturePieces(int row, int col, Player::Color color) {
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (auto &dir : directions) {
        int r = row + dir[0], c = col + dir[1];
        std::vector<std::pair<int, int>> piecesToFlip;

        // Durchlaufe die Richtung, bis ein gültiger Stein zum Fangen gefunden wird
        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] != Player::Color::EMPTY && board[r][c] != color) {
            piecesToFlip.emplace_back(r, c);
            r += dir[0];
            c += dir[1];
        }

        // Wenn ein Stein des Spielers am Ende gefunden wird, fange alle Steine dazwischen
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == color) {
            for (auto &p : piecesToFlip) {
                board[p.first][p.second] = color;
            }
        }
    }
}

bool OthelloBoard::checkAllDirections(int row, int col, Player::Color color) const {
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (auto &dir : directions) {
        int r = row + dir[0], c = col + dir[1];
        bool foundOpponent = false;

        // Überprüft in dieser Richtung, ob der Zug gültig ist
        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
            if (board[r][c] == Player::Color::EMPTY) break;
            if (board[r][c] == color) {
                if (foundOpponent) return true;  // Es gibt Steine zu fangen in dieser Richtung
                break;
            }
            foundOpponent = true;
            r += dir[0];
            c += dir[1];
        }
    }
    return false;  // Kein gültiger Zug gefunden
}

bool OthelloBoard::hasValidMoves(const Player::Color& color) const {
    // Durchlaufe alle Felder des Spielbretts
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Wenn ein Feld leer ist und der Zug gültig ist, gebe true zurück
            if (board[row][col] == Player::Color::EMPTY && isValidMove(row, col, color)) {
                return true;
            }
        }
    }
    // Kein gültiger Zug gefunden
    return false;
}
