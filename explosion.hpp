#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

class Circle { // circle class so that it is easier to keep track of circles in explosions and their directions
  public:

    Circle(int x, int y, sf::RenderWindow &window) { // constructor
      circle.setPosition(sf::Vector2f(x, y)); // setting position
      posX = x;
      posY = y;
      circle.setRadius(size); // setting radius / size
      circle.setFillColor(sf::Color::Blue); // setting default color to blue

      mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

      distY = circle.getPosition().y - mousePos.y; // distance from mouse to circle Y
      distX = circle.getPosition().x - mousePos.x; // distance from mouse to circle X

      dirAngle = atan2(distY, distX); // finding how much to move each frame so it looks natural

      dirX = cos(dirAngle) * 7.0f;      
      dirY = sin(dirAngle) * 7.0f;
    }

    void draw(sf::RenderWindow &window) {
      window.draw(circle);
    }

    void move(sf::Vector2f dir) { 
      circle.move(dir);
    }

    float getDirX() {
      return dirX;
    }

    float getDirY() {
      return dirY;
    }

    float getDirAngle() {
      return dirAngle;
    }

    float getDistX() {
      return distX;
    }

    float getDistY () {
      return distY;
    }

    bool isOut() { // checking if circle is out of the window
      if (circle.getPosition().x > 600 || circle.getPosition().x < 0 || circle.getPosition().y > 600 || circle.getPosition().y < 0) {
        return true;
      }else{
        return false;
      }
    }

    void setColor(sf::Color color) {
      circle.setFillColor(color);
    }

  private:
    sf::CircleShape circle;
    float dirAngle, dirX, dirY, posX, posY;
    float size = 3.0;
    sf::Vector2f mousePos;

    float distX, distY;
};



class Explosion {
  public:

    Explosion(int x, int y, sf::RenderWindow &window) { // constructor

      posX = x; // MOUSE POSITION
      posY = y; // MOUSE POSITION

      std::random_device rd; // using random numbers for circle locations
      std::mt19937 mt(rd());
      std::uniform_real_distribution<double> dist(-80.0f, 80.0f);
      


      amount = 1000; // setting amount of circles per explosion
      
      for (int count = 0; count < amount; count++){ // adding count amount of circles to vector
        locX = posX + dist(mt);
        locY = posY + dist(mt);
  
        Circle circ(locX, locY, window);
        circles.push_back(circ);
      }

    }



    void draw(sf::RenderWindow &window) {
      for (int n = 0; n < amount; n++) {

        if (!circles[n].isOut()) { // checking if circle is on the window so I don't render circles I don't need to

          if (n % 2 == 0) { // making it multicolored
            circles[n].setColor(sf::Color::Magenta);
            circles[n].draw(window);
          }else {
            circles[n].setColor(sf::Color::Cyan);
            circles[n].draw(window);
          }
        
        }else {
          continue;
         }
      }

    }

    void move() { // move all circles by their dirX and DirY
      for (int i = 0; i < amount; i++) {
        circles[i].move(sf::Vector2f(circles[i].getDirX(), circles[i].getDirY()));
      }
    }


  private:
    float locX, locY;
    int posX, posY;
    int amount;
    std::vector<Circle> circles;
};
