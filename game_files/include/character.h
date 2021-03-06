#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>

class Character {
  friend class Game;
  friend class Eric;
  friend class Policeman;

private:
  std::pair<double, double> coord;
  std::string directory;
  double d_x = 0;
  double d_y = 0;
  double speed = 0;
  std::string image_file;
  sf::Image character_image;
  sf::Texture character_texture;
  sf::Sprite character_sprite;

public:
  Character() = default;
  Character(std::pair<double, double> coord0, std::string directory0,
            double d_x0, double d_y0, double speed0, std::string filename)
      : coord(coord0), directory(directory0), d_x(d_x0), d_y(d_y0),
        speed(speed0), image_file(filename) {
    character_image.loadFromFile(image_file);
    character_texture.loadFromFile(image_file);
    character_sprite.setTexture(character_texture);
    character_sprite.setPosition(20, 450);
    character_sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
  }

  Character(const std::string &filename) : image_file(filename) {
    character_image.loadFromFile(image_file);
    character_texture.loadFromFile(image_file);
    character_sprite.setTexture(character_texture);
    character_sprite.setPosition(coord.first, coord.second);
    character_sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
  }

  // void update(const int &) {}
};

class Eric : public Character {
  friend class Character;
  friend class Game;

private:
  std::pair<double, double> coord = {20, 450};
  std::string image_file;

  friend class Character;

public:
  Eric(const std::string &filename) : image_file(filename) {
    character_image.loadFromFile(image_file);
    character_texture.loadFromFile(image_file);
    character_sprite.setTexture(character_texture);
    character_sprite.setPosition(coord.first, coord.second);
    // character_sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
  }

  void update(const int &time) {
    if (directory == "R") {
      d_x = speed;
      d_y = 0;
    }
    if (directory == "U") {
      d_x = 0;
      d_y = -speed;
    }
    if (directory == "D") {
      d_x = 0;
      d_y = speed;
    }
    if (coord.first + d_x * double(time) >= 10 &&
        coord.first + d_x * double(time) <= 300) {
      coord.first += d_x * double(time);
    }
    if (coord.second + d_y * double(time) >= 10 &&
        coord.second + +d_y * double(time) <= 500) {
      coord.second += d_y * double(time);
    }
    speed = 0;
    character_sprite.setPosition(coord.first, coord.second);
  }
};

class Policeman : Character {
  friend class Game;
  friend class Character;
  friend void delete_characters_from_window(std::vector<Policeman> &);

private:
  std::pair<double, double> coord = {1000, 400};
  std::string image_file;

public:
  Policeman(const std::string &filename) : image_file(filename) {
    character_image.loadFromFile(image_file);
    character_texture.loadFromFile(image_file);
    character_sprite.setTexture(character_texture);
    character_sprite.setPosition(coord.first, coord.second);
    // character_sprite.setTextureRect(sf::IntRect(0, 0, 250, 286));
  }

  void move() {
    coord.first -= 0.3;
    character_sprite.move(-0.3, 0);
  }

  bool collision(std::pair<double, double> coord1,
                 std::pair<double, double> coord2) {
    std::pair<double, double> coord_ = {coord.first, coord.second + 200};
    return (std::abs(coord1.first - coord.first) <= 20 &&
            (((coord.second - coord1.second) <= 0 &&
              (coord1.second - coord_.second) <= 0) ||
             (0 <= (coord2.second - coord.second) &&
              (coord2.second - coord_.second) <= 0)));
  }
};
