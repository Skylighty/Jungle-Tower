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
#include "feature.h"
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
    Game(bool decision);        // Game constructor for play again
    ~Game();                    // Game de-constructor

    void run();                 // Responsible for running the whole game

    //-------------------------------- HELPERS -----------------------------------
    const unsigned int win_width = 1680.f;
    const unsigned int win_height = 960.f;
    bool play_again;
    int feature_count = 0;

private:
    //-------------------------------ATTRIBUTES----------------------------------
    sf::RenderWindow* window;               // Main window object of the game class.
    sf::Window window_object;               // Window object for mouse operations
    Level level;                            // Platform level that player currently is on
    Player* player;                         // Player object in the game
    Platform* ground;                       // Ground platform object for start of the game
    sf::Texture bg_texture;                 // Texture for background
    sf::Sprite bg_sprite;                   // Sprite for background
    sf::Font font;                          // Font for the whole game
    sf::Text Score;                         // Score for the game in text SFML format
    sf::Text pauseCounter;                  // Text to indicate back from save
    sf::IntRect bg_rect;                    // Rectangle object for background to render it
    sf::Event sfEvent;                      // Event object that we overwrite each time
    sf::Clock dtClock;                      // Delta time clock
    sf::Clock starClock;                    // Star feature appearance clock
    sf::Clock ghostClock;                   // Ghost feature appearance clock
    sf::Music music;                        // Music object for background music
    bool started;                           // Flag determining whether the game has begun
    int score;                              // Player's current score
    int patternNumber;                      // Pattern number for different platforms
    float dt;                               // Current delta time
    float startime;                         // Current star feature time
    float ghosttime;                        // Current ghost feature time
    float platformsVelocity;                // Global velocity for all platforms
    std::vector<Platform*>* Platforms;      // Vector to contain platforms on the screen
    std::vector<Feature*>* Features;        // Vector to contain features on the screen

    //------------------------------- METHODS ------------------------------------
    void update();                  // Constantly updates the game functionality - !GENERAL METHOD
    void updatePlayer();            // Constantly updates all of the player-connected features
    void updateCollision();         // Constantly updates the collision occurance check in update()
    void updatePlatforms();         // Constantly checks if the platforms work properly and updates them
    void updateScore();             // Constantly updates player's score
    void updateFeatures();          // Updates all features
    void updateDT();                // Updates the delta time
    void renderPlayer();            // Renders the player's character during initialization phase
    void renderBg();                // Renders the background during initialization phase
    void renderFeatures();          // Renders all of the features on the screen
    void renderScore();             // Renders the player's score
    void renderDeath();             // Renders the death screen
    void initDeath();               // Inits the dead screen
    void updateDeath();             // Constantly updates the death screen
    void initScore();               // Initializes the palyer's score
    void initMusic();               // Initiialzies the background music with it's properities
    void renderPlatforms();         // Responsible for rendering platform objects
    void render();                  // Renders the game as whole - !GENERAL METHOD
    void checkDeath();              // Checks if player is dead
    void initWindow();              // Method initializing the window.
    void initPlayer();              // Initializes the player object
    void initBg();                  // Initializes game background image/images
    void generatePlatform(float x, float y);                    // Generates a new platform at specified place
    void generateGround();                                      // Generates basic ground for start of the game
    void platformRNG();                                         // Random generating of platforms
    void Restart();                 // Restarts the whole game


    //----------------------------- MENU --------------------------------------------
    bool pause;                     // Flag determining whether the game has paused
    bool start=true;                // Start determining flag
    bool menu_render=false;         // Flag determining whether menu should be rendered
    sf::Texture bg_menu;            // Menu texture
    sf::Sprite bg_sprite_menu;      // Menu sprite object
    sf::IntRect bg_rect_menu;       // Menu boundaries rectangle object
    sf::Text Resume;                // Text for "Resume" option
    sf::Text Close;                 // Text for "Close" option
    sf::Text Play;                  // Text for "Play" option
    sf::Text Exit;                  // Text for "Exit" option
    sf::Text You_Died;              // Text for "You Died" option
    sf::Text Play_Again;            // Text for "Play again" option
    void menu();                    // In Game Menu
    void updateMenu();              // Updates menu closing options
    void renderMenu();              // Renders the menu
    void buttons();                 // Buttons initialization
    void startMenu();               // Start menu maintaining method
    void renderStart();             // Rendering the game-start menu
    void initStart();               // Initializes the starting sequence
    bool textActive();              // Returns if option is active


};



#endif //GAME_H_
