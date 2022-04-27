#pragma once
#include "camera.h"
#include "character.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
  friend class Eric;
  friend class OverView;

private:
  std::string background_image_file;
  sf::Image background;
  sf::Texture background_texture;
  sf::Sprite background_sprite;
  sf::Clock clock;
  OverView camera;

public:
  Game(const std::string &filename) : background_image_file(filename) {
    background.loadFromFile("background.jpg");
    background_texture.loadFromImage(background);
    background_texture.setRepeated(true);

    background_sprite.setTexture(background_texture);
    background_sprite.setPosition(0, 0);
  }

  void GameRun(Eric &pers) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flat Eric Adventures",
                            sf::Style::Titlebar | sf::Style::Close);
    camera.overview.reset(sf::FloatRect(0, 0, 1280, 720));
    sf::Shader background_shader;
    background_shader.loadFromFile("background.cpp", sf::Shader::Vertex);
    sf::Music song_for_the_game;
    song_for_the_game.openFromFile("song1.ogg");
    song_for_the_game.setVolume(50.f);
    song_for_the_game.play();
    song_for_the_game.setLoop(true);

    float offset = 0.f;

    while (window.isOpen()) {

      double current_time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      current_time = current_time / 300;

      sf::Event event;
      while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pers.directory = "R";
        pers.speed = 0.05;
        camera.follow_point(pers.coord.first, pers.coord.second);
        background_shader.setUniform(
            "offset", offset += clock.restart().asSeconds() * 1.005);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pers.directory = "U";
        pers.speed = 1;
        camera.follow_point(pers.coord.first, pers.coord.second);
        // background_shader.setUniform(
        //    "offset", offset += clock.restart().asSeconds() / 10);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pers.directory = "D";
        pers.speed = 1;
        camera.follow_point(pers.coord.first, pers.coord.second);
        // background_shader.setUniform(
        //    "offset", offset += clock.restart().asSeconds() / 10);
      }
      pers.update(current_time);
      window.setView(camera.overview);
      window.clear();
      window.draw(background_sprite, &background_shader);
      window.draw(pers.character_sprite);
      window.display();
      // song_for_the_game.play();
    }
  }
};
