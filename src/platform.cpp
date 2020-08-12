//
// Created by Pablo on 11.08.2020.
//

#include "platform.h"

Platform::Platform(const float x, const float y, int patt) {
    pattern = Pattern::GRASS;
    patternSwitch(patt);
    initTexture();
    initSprite();
    sprite.setPosition(x,y);
}

Platform::~Platform() {
    delete this;
}

void Platform::render(sf::RenderTarget *target) {
    target->draw(sprite);
}

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
}


void Platform::initSprite() {
    sprite.setTexture(texture);
    sf::IntRect frame = sf::IntRect(0,0,446,70);
    sprite.setTextureRect(frame);
    //sprite.setScale(0.7f, 0.7f);
}

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

}

const sf::FloatRect Platform::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}



