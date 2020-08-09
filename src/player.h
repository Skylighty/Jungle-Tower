//
// Created by Pablo on 09.08.2020.
//

#ifndef PLATFORMOWKA_AGAIN_PLAYER_H
#define PLATFORMOWKA_AGAIN_PLAYER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

//TODO
struct Physics{
    float g = 9.8;
    float m = 20;
    float fg = m*g;
    float t = 0;
};

class Player {
public:
    //------------------------ STATE -------------------------
    enum class State{
        IDLE,
        JUMP,
        MOVING_R,
        MOVING_L,
        FALLING,
        IN_AIR,
        ON_GRD,
        DEAD,
    };

    Player();                   // Player object constructor
    ~Player();

    void update();              // Updates the player position,state etc.
    void updateMovement();      // Reaction for key-pressing movement of player object
    void updateAnimations();    // Updates the animation of player while in movement
    void render(sf::RenderTarget* target);  // Renders player object in the specified target (window)
    State get_player_state() {return state;}    // Returns state of character

private:

    //--------------------- ATTRIBUTES -----------------------
    sf::Texture textureSheet;   // Texture pattern for the player object
    sf::Sprite sprite;          // Sprite object for player
    sf::Clock animationTimer;   // Animation timer to prevent it from executing too fast
    bool in_movement;           // Flag which specifies if player is moving
    State state;                // Enum variable indicating in which state player's character currently is
    Physics physics;


    //-------------------- ANIMATIONS ------------------------
    sf::IntRect frame;

    //------------------------ METHODS------------------------
    void initTexture();         // Initializes the texture from file for player object
    void initSprite();          // Initializes the sprite from textures for player object
    void initAnimations();      // Initializes the animations
};


#endif //PLATFORMOWKA_AGAIN_PLAYER_H
