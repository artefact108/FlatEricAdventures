#pragma once
#include <SFML/Graphics.hpp>

class Score {
  friend class Game;

private:
  long long high = 0;
  long long current_ = 0;

  struct {
    sf::Text score_text;
    sf::Text high_text;
    sf::Font font;
  } table;

public:
  Score() {
    table.font.loadFromFile("font/Karumbi.ttf");
    table.score_text.setFont(table.font);
    table.score_text.setFillColor(sf::Color::Yellow);
    table.score_text.setCharacterSize(80);
    table.score_text.move(800, -40);
    table.high_text.setFont(table.font);
    table.high_text.setFillColor(sf::Color::Yellow);
    table.high_text.setCharacterSize(80);
    table.high_text.move(800, 0);
  }

  void update() {
    current_ += 1;
    if (current_ >= high) {
      high = current_;
    }
  }
};
