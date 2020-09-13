//
// Created by Pablo on 24.08.2020.
//

#include "feature.h"

Feature::Feature(Type feature_type, float x, float y) {
    if (feature_type == Type::STAR)
    {
        type = Type::STAR;
    }
    else if (feature_type == Type::BOOSTER)
    {
        type = Type::BOOSTER;
    }
    else if (feature_type == Type::GHOST)
    {
        type = Type::GHOST;
    }
    initTexture();
    initSprite();
    initAnimation();

    sprite.setPosition(x,y);
}

Feature::~Feature() = default;

void Feature::initTexture() {
    if (type == Type::STAR)
    {
        texture.loadFromFile("star-coin.png");
    }
    if (type == Type::GHOST)
    {
        texture.loadFromFile("ghost-idle.png");
    }
}

void Feature::initSprite() {
    sprite.setTexture(texture);
    if (type == Type::STAR)
    {
        frame = sf::IntRect (0,0,89,87);
        sprite.setTextureRect(frame);
        sprite.setScale(0.7f,0.7f);
    }
    else if (type == Type::GHOST)
    {
        frame = sf::IntRect(0,0,76,74);
        sprite.setTextureRect(frame);
        sprite.setScale(1.4f, 1.4f);
    }
}

void Feature::initAnimation() {
    animationTimer.restart();
}

void Feature::updateAnimation() {
    if (type == Type::STAR && animationTimer.getElapsedTime().asSeconds() >= 0.1f)
    {
        frame.top = 0.f;
        frame.left += 89.f;
        if (frame.left > 600)
            frame.left = 0.f;
        initAnimation();
        sprite.setTextureRect(frame);
    }
    if (type == Type::GHOST && animationTimer.getElapsedTime().asSeconds() >= 0.1f)
    {
        frame.top = 0.f;
        frame.left += 76.f;
        if (frame.left > 450)
            frame.left = 0.f;
        initAnimation();
        sprite.setTextureRect(frame);
    }
}

void Feature::render(sf::RenderTarget *target) {
    target->draw(sprite);
}

sf::FloatRect Feature::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Feature::setSpriteColor(sf::Color color) {
    sprite.setColor(color);
}
