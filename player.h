#ifndef PLAYER_H
#define PLAYER_H

#include <string>  // Einbindung der Bibliothek <string>

class Player {
public:
    // Aufzählung der Spielerfarben, EMPTY für leere Felder hinzugefügt
    enum class Color {
        EMPTY,  // Repräsentiert ein leeres Feld auf dem Spielfeld
        BLACK = 'B',
        WHITE = 'W'
    };

    // Konstruktor mit der Standardfarbe (BLACK)
    Player(Color color = Color::BLACK);

    // Konstruktor mit dem Namen des Spielers
    Player(const std::string& playerName);

    // Getter und Setter
    Color getColor() const;
    void setColor(Color color);
    std::string getName() const;
    void setName(const std::string& playerName);

    // Zusätzliche Methoden für Spieleraktionen
    void makeMove(int row, int col);  // Platzhalter für die Bewegung

private:
    std::string name;  // Name des Spielers
    Color playerColor;  // Spielerfarbe (BLACK oder WHITE)
};

#endif // PLAYER_H
