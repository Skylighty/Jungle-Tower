//
// Created by Pablo on 09.08.2020.
//

#include "player.h"


Player::Player() {
    initTexture();
    initSprite();
    in_movement = false;
    state = State::IDLE;
}

Player::~Player() {

}

void Player::initTexture() {
    textureSheet.loadFromFile("PlayerTexture.png");
}

void Player::initSprite() {
    sprite.setTexture(textureSheet);
    frame = sf::IntRect(0,0,50,48);
    sprite.setTextureRect(frame);
    sprite.setScale(2.f,2.f);
}

void Player::update() {
    updateMovement();
    updateAnimations();
}

void Player::updateAnimations()
{
    if (animationTimer.getElapsedTime().asSeconds() >= 0.13f)
    {
        if (state == State::IDLE)
        {
            frame.top = 0;
            frame.left += 50.f;
            if (frame.left >= 150.f)
                frame.left = 0;

        }
        if (state == State::MOVING_L)
        {
            frame.top = 50.f;
            frame.left += 50.f;
            if (frame.left >= 150.f)
                frame.left = 0;
        }
        if (state == State::MOVING_R)
        {

            frame.top = 100.f;
            frame.left += 50.f;
            if (frame.left >= 150.f)
                frame.left = 0;
        }
        animationTimer.restart();
        sprite.setTextureRect(frame);
    }
}

void Player::updateMovement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        sprite.move(-5.f,0.f);
        state = State::MOVING_L;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.move(5.f, 0.f);
        state = State::MOVING_R;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {

        if (state == State::IN_AIR)
        {
            state = State::FALLING;
            sprite.move(0.f, 5.f);
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        state = State::JUMP;
    }
    else
        state = State::IDLE;
}

void Player::render(sf::RenderTarget* target) {
    target->draw(sprite);
}

void Player::initAnimations() {
    animationTimer.restart();
}
