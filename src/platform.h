//
// Created by Pablo on 11.08.2020.
//

#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <SFML/Graphics.hpp>
#include <random>


class Platform {
public:
    enum class Pattern{
        GRASS,
        GROUND,
        STONE,
        SNOW,
        ICE
    };
    Platform(const float x, const float y, int patt);
    Platform();
    ~Platform();
    void render(sf::RenderTarget* target);          // Rendering the platforms
    void patternSwitch(int x);                      // Pattern switcher
    const sf::FloatRect getGlobalBounds() const;    // Returns the bounds of platform sprite rectangle

private:

public:


private:
    // Sprite object for the platform
    sf::Sprite sprite;                      // Sprite for platform
    sf::Texture texture;                    // Texture pattern for the platform
    Pattern pattern;                        // Different textures for platforms
    void initTexture();                     // Initialize texture from file
    void initSprite();                      // Initialize sprite from texture
};


#endif //PLATFORM_H_
