#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Tape {
  friend class Game;
  friend void delete_characters_from_window(std::vector<Tape> &);

private:
  std::pair<double, double> coord;
  std::string tape_image;
  sf::Texture tape_texture;
  sf::Sprite tape_sprite;

public:
  Tape(const std::string &file_image) : tape_image(file_image) {
    tape_texture.loadFromFile(tape_image);
    tape_sprite.setTexture(tape_texture);
  }

  void move() {
    coord.first -= 0.3;
    tape_sprite.move(-0.3, 0);
  }

  bool collision(std::pair<double, double> coord1,
                 std::pair<double, double> coord2) {
    std::pair<double, double> coord_ = {coord.first, coord.second + 15};
    return (std::abs(coord1.first - coord.first) <= 10 &&
            (((coord.second - coord1.second) >= 0 &&
              (coord2.second - coord.second) >= 0) ||
             (0 <= (coord2.second - coord_.second) &&
              (coord.second - coord1.second) <= 0)));
  }
};
