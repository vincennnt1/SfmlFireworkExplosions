#include <SFML/Graphics.hpp>
#include "explosion.hpp"

int main() {

  sf::RenderWindow window(sf::VideoMode(600,600), "Explosions");
  window.setFramerateLimit(60);
  int expCount = 0; // makes it so that I can't constantly make explosions
  bool isExplode = false; 

  std::vector<Explosion> explosions; // vector of explosions


  while (window.isOpen()) { //BEGINNING OF MAIN LOOP
    sf::Event event;

    while (window.pollEvent(event)) { // BEGINNING OF POLL EVENTS
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape){
          window.close();
        }
      }
    } // END OF POLL EVENTS

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && expCount >= 10 && isExplode == false) {
      isExplode = true;
      expCount = 0;
    }

    if (isExplode) {
      Explosion newExplosion(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, window);
      explosions.push_back(newExplosion);

      isExplode = false;
    }

  window.clear();
    
  for (int i = 0; i < explosions.size(); i++) {
    explosions[i].draw(window);
    explosions[i].move();
  } 

  window.display();
  

  expCount++;
  }


}
