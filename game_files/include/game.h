#pragma once
#include "camera.h"
#include "character.h"
#include "score.h"
#include "tape.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

/*template <class T> void delete_characters_from_window(std::vector<T> &a) {
  typename std::vector<T>::iterator start = a.begin();
  typename std::vector<T>::iterator current = a.begin();

  for (; current != a.end(); current++) {
    if ((*current).coord.first > -20) {
      break;
    }
  }
  a.erase(start, current);
}*/

class Game {
  friend class Eric;
  friend class OverView;
  friend class Policeman;

private:
  std::string background_image_file;
  sf::Image background;
  sf::Texture background_texture;
  sf::Sprite background_sprite;
  sf::Clock clock;
  OverView camera;
  Score score;
  struct {
    sf::Image gameover_image;
    sf::Sprite gameover_sprite;
    sf::Texture gameover_texture;
  } gameover;
  int game_status =
      0; // this variable shows what happened 0 - game not started, 1 - now
         // playing, 2- gamer has failed but can restart

public:
  Game(const std::string &filename) : background_image_file(filename) {
    background.loadFromFile("src/background.jpg");
    background_texture.loadFromImage(background);
    background_texture.setRepeated(true);
    gameover.gameover_image.loadFromFile("src/gameover.png");
    gameover.gameover_texture.loadFromFile("src/gameover.png");
    gameover.gameover_sprite.setTexture(gameover.gameover_texture);
    gameover.gameover_sprite.setPosition(300, 190);
    background_sprite.setTexture(background_texture);
    background_sprite.setPosition(0, 0);
  }

  template <class T> void delete_characters_from_window(std::vector<T> &a) {
    typename std::vector<T>::iterator start = a.begin();
    typename std::vector<T>::iterator current = a.begin();

    for (; current != a.end(); current++) {
      if ((*current).coord.first > -20) {
        break;
      }
    }
    a.erase(start, current);
  }

  template <class T> void moving_characters(std::vector<T> &a) {
    for (typename std::vector<T>::iterator itr = a.begin(); itr != a.end();
         itr++) {
      (*itr).move();
    }
  }
  void GameRun(Eric &pers) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flat Eric Adventures",
                            sf::Style::Titlebar | sf::Style::Close);
    camera.overview.reset(sf::FloatRect(0, 0, 1280, 720));
    sf::Shader background_shader;
    background_shader.loadFromFile("include/background.cpp",
                                   sf::Shader::Vertex);
    sf::Music song_for_the_game;
    song_for_the_game.openFromFile("msc/song1.ogg");
    song_for_the_game.setVolume(50.f);
    song_for_the_game.play();
    song_for_the_game.setLoop(true);
    Policeman cope("src/policeman.png");

    sf::Text restart;
    sf::Font font_;
    font_.loadFromFile("font/Karumbi.ttf");
    restart.setFont(font_);
    restart.setFillColor(sf::Color::Red);
    restart.setCharacterSize(80);
    restart.move(300, 400);
    restart.setString("Press Whitespace To Restart");
    float offset = 0.f;
    game_status = 1;
    std::vector<Policeman> police;
    std::vector<Tape> tapes;
    Tape tape("src/tape.png");
    long long counter = 0;
    int r = 0;
    while (window.isOpen()) {
      score.table.score_text.setString(std::to_string(score.current_));
      score.table.high_text.setString("Highest Score: " +
                                      std::to_string(score.high));

      double current_time = clock.getElapsedTime().asMicroseconds();
      clock.restart();

      current_time = current_time / 300;
      sf::Event event;

      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && game_status == 1) {
        pers.directory = "U";
        if (pers.coord.second >= 0) {
          pers.character_sprite.move(0, -0.3);
          pers.coord.second -= 0.3;
        }
        camera.follow_point(pers.coord.first, pers.coord.second);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game_status = 1;
        score.current_ = 0;
      }

      if (game_status == 1 && counter % 10000 == 0) {
        r = rand() % 300 + 50;
        cope.coord = {1000, r + 100};
        cope.character_sprite.setPosition(1000, r + 100);
        police.push_back(cope);
      }

      if (game_status == 1 && counter % 15000 == 0) {
        // r = rand() % 300 + 50;
        tape.coord = {1100, r};
        tape.tape_sprite.setPosition(1000, r);
        tapes.push_back(tape);
      }

      if (counter % 10000 == 0) {
        delete_characters_from_window(police);
      }

      if (counter % 15000 == 0) {
        delete_characters_from_window(tapes);
      }

      if (game_status == 1) {
        moving_characters(police);
        moving_characters(tapes);
      }

      if (pers.coord.second < 425) {
        pers.character_sprite.move(0, 0.1);
        pers.coord.second += 0.1;
      }
      if (game_status == 1) {
        for (size_t i = 0; i < police.size(); ++i) {
          if (police[i].collision(
                  {pers.coord.first + 100, pers.coord.second},
                  {pers.coord.first + 100, pers.coord.second + 200})) {
            game_status = 2;
          }
        }
        size_t c = tapes.size();
        for (size_t i = 0; i < c; ++i) {
          if (tapes[i].collision(
                  {pers.coord.first + 100, pers.coord.second},
                  {pers.coord.first + 100, pers.coord.second + 200})) {
            score.update();
            tapes.pop_back();
          }
        }
      }
      if (game_status == 1) {
        background_shader.setUniform(
            "offset", offset += clock.restart().asSeconds() * 1.005);
      }
      window.setView(camera.overview);
      window.clear();
      window.draw(background_sprite, &background_shader);
      window.draw(pers.character_sprite);
      window.draw(score.table.score_text);
      window.draw(score.table.high_text);
      for (size_t i = 0; i < police.size(); ++i) {
        window.draw(police[i].character_sprite);
      }

      for (size_t i = 0; i < tapes.size(); ++i) {
        window.draw(tapes[i].tape_sprite);
      }

      if (game_status == 2) {
        window.draw(gameover.gameover_sprite);
        score.current_ = 0;
        // if (counter % 2 == 0) {
        window.draw(restart);
        // }
      }
      window.display();
      counter++;
    }
  }
};
