#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "othelloboard.h"
#include "player.h"

class GameManager {
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    OthelloBoard board;

public:
    GameManager();
      OthelloBoard& getBoard();
     void startGame();
    void playTurn(Player& player);
    void nextTurn();
    Player& getCurrentPlayer();
    void displayBoard() const;
    bool hasValidMoves(const Player& player) const;
    bool isGameOver() const;
    bool isValidMove(int row, int col) const;
    void switchPlayer();
};

#endif // GAMEMANAGER_H
