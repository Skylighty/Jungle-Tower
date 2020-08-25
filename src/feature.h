//
// Created by Pablo on 24.08.2020.
//

#ifndef FEATURE_H
#define FEATURE_H
#include <SFML/Graphics.hpp>
#include <string>

class Feature {
public:

    enum class Type{
        STAR,
        BOOSTER,
        GHOST
    };


    explicit Feature(Type feature_type, float x, float y);
    virtual ~Feature();

    Type type;
    void initTexture();
    void initSprite();
    void initAnimation();
    void render(sf::RenderTarget *target);
    void updateAnimation();
    sf::FloatRect getGlobalBounds();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock animationTimer;
    sf::IntRect frame;
};


#endif //FEATURE_H
