//
// Created by Pablo on 09.08.2020.
//

#include <iostream>
#include "player.h"

//================ CONSTRUCTORS ====================
Player::Player() {
    initTexture();
    initSprite();
    initAnimations();
    state = State::IDLE;
    position.x = 700.f;
    position.y = 660.f;
    isOnPlatform = false;
    jumpcount = 0;
    dead = false;
}
Player::~Player() {
    //delete this;
}
//==================================================


//============== INITIALIZATIONS ===================
void Player::initTexture() {
    textureSheet.loadFromFile("PlayerTexture.png"); // Load texture sheet from file (whole pattern)
}
void Player::initSprite() {
    sprite.setTexture(textureSheet);                        // Set te texture sprite sheet for character
    frame = sf::IntRect(0,0,50,48);
    sprite.setTextureRect(frame);                           // Place the sprite pattern rect
    sprite.setScale(1.5f,1.5f);              // Rescaling the sprite - bigger
    sprite.setPosition(500,800);
}
void Player::initAnimations() {
    animationTimer.restart();
}
void Player::render(sf::RenderTarget* target) {
    target->draw(sprite);
}
//==================================================


//================= UPDATING =======================
void Player::update() {
    updatePhysics();
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
        move(-5.f, 0.f);
        state = State::MOVING_L;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(5.f, 0.f);
        state = State::MOVING_R;
    }
    //TODO implement fast fall
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move(0.f, 5.f);
        //velocity.y = kDownDragAccel;
    }

    //TODO - We have to implement this triggering on event, because the key is constantly being chekcked
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (jumpcount < 3))
//    {
//            jumpcount++;
//            isOnPlatform = false;
//            velocity.y = kJumpAccel;
//    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move(0.f, -5.f);

    if (!IsAnyKeyPressed())
        state = State::IDLE;
    sprite.move(velocity);
}
void Player::updatePhysics() {

//    // Accelerating the gravity drag force
    if (!isOnPlatform) //TODO remove hardcored positiion
    {
        velocity.y += 1.0 * gravity;
        if (std::abs(static_cast<int>(velocity.y)) > kMaxGravity)
            velocity.y = kMaxGravity * ((velocity.y < 0.f) ? -1.f : 1.f);
    }


//    if (jumping) // TODO Chceck if it works - implement in updateMovement()
//    {
//        if (velocity.y >= kMinGravity) //TODO remove hardcored positiion
//        {
//            jumping = false;
//        }
//    }

    // Slowing down the player's character
    velocity *= kDrag;

    // Limit the slowing process
    if (std::abs(static_cast<int>(velocity.x))  < kVelocityMin)
        velocity.x = 0.f;
    if (std::abs(static_cast<int>(velocity.y)) < kVelocityMin)
        velocity.y = 0.f;

    sprite.move(velocity);
}
//==================================================


//============== CHARACTER EVENTS ==================
void Player::move(const float dir_x, const float dir_y) {

    // Accelerating the player's character
    velocity.x += dir_x * kAccel;
    //velocity.y += dir_y * kAccel;

    // Limiting the player's velocity
    if (std::abs(static_cast<int>(velocity.x)) > kVelocityMax)
    {
        velocity.x = kVelocityMax * ((velocity.x < 0.f) ? -1.f : 1.f);
    }
    //if (std::abs(velocity.y) > kVelocityMax)
    //{
       // velocity.y = kVelocityMax * ((velocity.y < 0.f) ? -1.f : 1.f);
   // }
}
bool Player::IsAnyKeyPressed() {
    for (int i = -1; i < sf::Keyboard::KeyCount; ++i)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
            return true;
    }
    return false;
}
void Player::setPlayerPosition(const float x, const float y) {
    sprite.setPosition(x,y);
}
const sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
sf::Vector2f Player::getVelocity() {
    return velocity;
}
void Player::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}
void Player::setIsOnPlatform(bool x) {
    Player::isOnPlatform = x;
}
void Player::resetJump() {
    jumpcount = 0;
}
void Player::Jump() {

    if (jumpcount < 2)
    {
        jumpcount++;
        isOnPlatform = false;
        velocity.y = kJumpAccel;
        sbuffer.loadFromFile("jump.ogg");
        sound.setBuffer(sbuffer);
        sound.setVolume(2.f);
        sound.play();
    }
}
//==================================================



