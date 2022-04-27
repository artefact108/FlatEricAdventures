#include "game.h"
#include <iostream>

int main() {
  Game game("background.jpg");
  Character Eric("flat_eric_main.png");
  game.GameRun(Eric);
}
