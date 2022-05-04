#include "include/game.h"
#include <iostream>

int main() {
  Game game("src/background.jpg");
  Eric Eric("src/flat_eric_main.png");
  game.GameRun(Eric);
}
