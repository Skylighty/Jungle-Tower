//
// Created by Pablo on 11.08.2020.
//

#include "platform.h"

Platform::Platform(const float x, const float y, int patt, float globalVelo) {
    patternSwitch(patt);
    velocity.y = globalVelo;
    velocity.x = 0.f;
    initTexture();
    initSprite();
    sprite.setPosition(x,y);
    visited = false;
    ground = false;
} // Basic constructor
Platform::Platform()
{
    texture.loadFromFile("ground.png");
    sprite.setTexture(texture);
    sf::IntRect frame = sf::IntRect(0,0,1680,61);
    sprite.setTextureRect(frame);
    velocity.y = 2.0f;
    velocity.x = 0.f;
    sprite.setPosition(0.f, 960.f-61.f);
    ground = true;
    visited = false;
}       // Ground constructor
Platform::~Platform() {          // Basic deconstructor

}

void Platform::render(sf::RenderTarget *target) {
    target->draw(sprite);
}           // Renders platforms to the main window
void Platform::initTexture() {
    if (pattern == Pattern::GRASS)
        texture.loadFromFile("grass-platform.png");
    else if (pattern == Pattern::GROUND)
        texture.loadFromFile("ground-platform.png");
    else if (pattern == Pattern::STONE)
        texture.loadFromFile("stone-platform.png");
    else if (pattern == Pattern::SNOW)
        texture.loadFromFile("snow-platform.png");
    else
        texture.loadFromFile("ice-platform.png");
}                              // Initializing the correct textures for platforms
void Platform::initSprite() {
    sprite.setTexture(texture);
    sf::IntRect frame = sf::IntRect(0,0,444,60);
    sprite.setTextureRect(frame);
    sprite.setScale(0.7f, 0.7f);
}                               // Initializing the sprites of platforms
void Platform::patternSwitch(int x) {
    if (x == 1)
        pattern = Pattern::GRASS;
    else if (x == 2)
        pattern = Pattern::GROUND;
    else if (x == 3)
        pattern = Pattern::STONE;
    else if (x == 4)
        pattern = Pattern::SNOW;
    else if (x == 5)
        pattern = Pattern::ICE;
}                       // Switching textures for the correct in dependency of STATE
const sf::FloatRect Platform::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}      // Returns the platform rectangle
void Platform::setVelocity(const float x) {
    velocity.y = x;
}                 // Sets the platform vertical velocity
void Platform::movePlatform() {
    sprite.move(velocity);
}                             // Moves the platforms' sprites







