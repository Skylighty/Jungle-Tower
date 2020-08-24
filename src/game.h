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

    // Enum class for changing textures of platforms
    enum class Level{
        GRASS,
        GROUND,
        STONE,
        SNOW,
        ICE
    };


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
    Level level;                    // Platform level that player currently is on
    Player* player;                 // Player object in the game
    Platform* ground;               // Ground platform object for start of the game
    sf::Texture bg_texture;         // Texture for background
    sf::Sprite bg_sprite;           // Sprite for background
    sf::Font font;                  // Font for the whole game
    sf::Text Score;                 // Score for the game in text SFML format
    sf::IntRect bg_rect;            // Rectangle object for background to render it
    sf::Event sfEvent;              // Event object that we overwrite each time
    sf::Clock dtClock;              // Delta time clock
    bool started;                   // Flag determining whether the game has begun
    int score;                      // Player's current score
    int patternNumber;              // Pattern number for different platforms
    float dt;                       // Current delta time
    float platformsVelocity;        // Global velocity for all platforms
    //sf::SoundBuffer sbuffer;      // Sound buffer for game window
    //sf::Sound sound;              // Sound for game window
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
    void renderScore();             // Renders the player's score
    void initScore();               // Initializes the palyer's score
    void renderPlatforms();         // Responsible for rendering platform objects
    void render();                  // Renders the game as whole - !GENERAL METHOD
    void checkDeath();              // Checks if player is dead
    void updateBg();                // Moves the background slowly
    void initWindow();              // Method initializing the window.
    void initPlayer();              // Initializes the player object
    void initBg();                  // Initializes game background image/images
    void generatePlatform(float x, float y);                    // Generates a new platform at specified place
    void generateGround();                                      // Generates basic ground for start of the game
    void platformRNG();                                         // Random generating of platforms


};



#endif //GAME_H_
