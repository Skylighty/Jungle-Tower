//
// Created by Pablo on 09.08.2020.
//

#ifndef PLATFORMOWKA_AGAIN_GAME_H
#define PLATFORMOWKA_AGAIN_GAME_H
#include <ctime>
#include <cstdlib>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
#include "player.h"

class Game {
private:

    //-------------------------------ATTRIBUTES-----------------------------------
    sf::RenderWindow* window;   // Main window object of the game class.
    Player* player;
    sf::Event sfEvent;          // Event object that we overwrite each time
    sf::Clock dtClock;          // Clock object that tracks delta time
    sf::SoundBuffer sbuffer;    // Sound buffer for game window
    sf::Sound sound;            // Sound for game window
    float dt;                   // Current delta time
    void initWindow();          // Method initializing the window.
    void initPlayer();          // Initializes the player object

public:

    //-------------------------------- HELPERS -----------------------------------
    const unsigned int win_width = 1680.f;
    const unsigned int win_height = 960.f;

    //----------------------------- CONSTRUCTION ---------------------------------
    Game();                     // Game constructor - creates the game window in the main.cpp.
    ~Game();                    // Game de-constructor

    //------------------------------- METHODS ------------------------------------
    void update();
    void updatePlayer();
    void renderPlayer();
    void render();
    void run();
};



#endif //PLATFORMOWKA_AGAIN_GAME_H
