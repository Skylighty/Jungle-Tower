//
// Created by Pablo on 09.08.2020.
//

#ifndef GAME_H_
#define GAME_H_
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include "player.h"
#include "platform.h"
#include <vector>

class Game {

public:
    //----------------------------- CONSTRUCTION ---------------------------------
    Game();                     // Game constructor - creates the game window in the main.cpp.
    ~Game();                    // Game de-constructor

    void run();                 // Responsible for running the whole game

    //-------------------------------- HELPERS -----------------------------------
    const unsigned int win_width = 1680.f;
    const unsigned int win_height = 960.f;

private:
    //-------------------------------ATTRIBUTES----------------------------------
    sf::RenderWindow* window;       // Main window object of the game class.
    Player* player;                 // Player object in the game
    Platform* ground;               // Ground platform object for start of the game
    sf::Texture bg_texture;         // Texture for background
    sf::Sprite bg_sprite;           // Sprite for background
    sf::IntRect bg_rect;            // Rectangle object for background to render it
    sf::Event sfEvent;              // Event object that we overwrite each time
    sf::Clock dtClock;              // Delta time clock
    int score;                      // Player's current score
    float dt;                       // Current delta time
    //sf::SoundBuffer sbuffer;      // Sound buffer for game window
    //sf::Sound sound;              // Sound for game window
    void initWindow();              // Method initializing the window.
    void initPlayer();              // Initializes the player object
    void initBg();                  // Initializes game background image/images
    void generatePlatform(float x, float y, int pattern);       // Generates a new platform at specified place
    void generateGround();                                      // Generates basic ground for start of the game
    void platformRNG();                                         // Random generating of platforms
    void setEvent(sf::Event::EventType type);                   //  Sets the event type
    //TODO unsigned int score;                                  // Player's score (hopped platforms)
    std::vector<Platform*>* Platforms;                          // Vector to contain platforms on the screen

    //------------------------------- METHODS ------------------------------------
    void update();                  // Constantly updates the game functionality - !GENERAL METHOD
    void updatePlayer();            // Constantly updates all of the player-connected features
    void updateCollision();         // Constantly updates the collision occurance check in update()
    void updatePlatforms();         // Constantly checks if the platforms work properly and updates them
    void updateScore();             // Constantly updates player's score
    void updateDT();                // Updates the delta time
    void renderPlayer();            // Renders the player's character during initialization phase
    void renderBg();                // Renders the background during initialization phase
    void renderPlatforms();         // Responsible for rendering platform objects
    void render();                  // Renders the game as whole - !GENERAL METHOD

    //-------------------------------- RNG ----------------------------------------
    std::random_device rd;
    std::mt19937 mt;
    float width_start = 100.f;
    float width_stop = 1200.f;

};



#endif //GAME_H_
