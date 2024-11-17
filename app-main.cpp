//============================================================================
/// \file
/// \ingroup    g_main
/// \brief      Contains the application's main function.
/// \details    No details necessary on this complex functionality :-)
///
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2012-2024 Herbert Thielen
//
// This file is part of the program 'othello',
// see https://gitlab.ai.it.hs-worms.de/swq/24w/othello
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//============================================================================

//#include "app-lib/app-lib.h"
#include <iostream>
using namespace std;

#include <iostream>
#include "othelloboard.h"
#include "gamemanager.h"
#include "player.h"


int main() {
    // Erstellung des Spielmanagers
    GameManager game;

    // Spiel starten
    game.startGame();

    // Hauptspielschleife
    while (!game.isGameOver()) {
        // Aktuellen Zustand des Spielbretts anzeigen
        game.displayBoard();

        // Punktzahlen für beide Spieler anzeigen
        int blackScore = game.getBoard().countPieces(Player::Color::BLACK);
        int whiteScore = game.getBoard().countPieces(Player::Color::WHITE);
        std::cout << "Punktzahl - Schwarz: " << blackScore << ", Weiß: " << whiteScore << std::endl;

        // Überprüfen, ob der aktuelle Spieler einen Zug machen kann, andernfalls Zug überspringen
        game.nextTurn();

        // Zug des aktuellen Spielers durchführen
        game.playTurn(game.getCurrentPlayer());

        // Zum nächsten Zug wechseln
        game.switchPlayer();
    }

    return 0;
}
