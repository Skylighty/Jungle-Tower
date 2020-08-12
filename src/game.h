//
// Created by Pablo on 09.08.2020.
//

#ifndef GAME_H_
#define GAME_H_
#include <ctime>
#include <cstdlib>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
#include "player.h"
#include "platform.h"
#include <vector>

class Game {

public:
    //----------------------------- CONSTRUCTION ---------------------------------
    Game();                     // Game constructor - creates the game window in the main.cpp.
    ~Game();                    // Game de-constructor


    //------------------------------BOUND ACCESSORS ------------------------------
    float playerTop;
    float playerLeft;
    float playerH;
    float playerW;
    sf::FloatRect nextPos;
    //-------------------------------- HELPERS -----------------------------------
    const unsigned int win_width = 1680.f;
    const unsigned int win_height = 960.f;

    //------------------------------- METHODS ------------------------------------
    void update();
    void updatePlayer();
    void updateCollision();
    void updateAccessors();
    void renderPlayer();
    void renderBg();
    void renderPlatforms();
    void render();
    void run();

private:
    //-------------------------------ATTRIBUTES-----------------------------------
    sf::RenderWindow* window;   // Main window object of the game class.
    Player* player;
    sf::Texture bg_texture;     // Texture for background
    sf::Sprite bg_sprite;       // Sprite for background
    sf::IntRect bg_rect;         // Rectangle object for background to render it
    sf::Event sfEvent;          // Event object that we overwrite each time
    sf::Clock dtClock;          // Clock object that tracks delta time
    sf::SoundBuffer sbuffer;    // Sound buffer for game window
    sf::Sound sound;            // Sound for game window
    float dt;                   // Current delta time
    void initWindow();          // Method initializing the window.
    void initPlayer();          // Initializes the player object
    void initBg();
    void generatePlatform(float x, float y, int pattern);    // Generates a new platform at specified place
    void patternSwitcher();                     // Function switching patterns
    unsigned int score;                         // Player's score (hopped platforms)
    std::vector<Platform*>* Platforms;          // Vector to contain platforms on the screen

};



#endif //GAME_H_
