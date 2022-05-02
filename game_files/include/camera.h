#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class OverView {
  friend class Game;

private:
  sf::View overview;

public:
  OverView() = default;

  void follow_point(double x_, double y_) {
    if (x_ < 250) {
      x_ = 250;
    }

    if (x_ > 600) {
      x_ = 600;
    }
    if (y_ < 360) {
      y_ = 360;
    }
    if (y_ > 360) {
      y_ = 360;
    }
    overview.setCenter(x_ + 400, y_);
  }
};
