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
    void render(sf::RenderTarget* target);                  // Rendering the platforms
    void patternSwitch(int x);                              // Pattern switcher
    void movePlatform();                                    // Move accesor for platforms
    sf::Vector2f getVelocity();                             // Getter for platform velocity
    void setVelocity(const int x, const int y);             // Setter for platform velocity
    const sf::FloatRect getGlobalBounds() const;            // Returns the bounds of platform sprite rectangle
    bool ground;                                            // Checks if the platform is the floor

private:

public:


private:
    // Sprite object for the platform
    sf::Sprite sprite;                      // Sprite for platform
    sf::Texture texture;                    // Texture pattern for the platform
    sf::Vector2f velocity;                  // Platform velocity
    Pattern pattern;                        // Different textures for platforms
    void initTexture();                     // Initialize texture from file
    void initSprite();                      // Initialize sprite from texture
};


#endif //PLATFORM_H_
