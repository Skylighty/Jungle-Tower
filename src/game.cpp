//
// Created by Pablo on 09.08.2020.
//

#include "game.h"
#include <iostream>




Game::Game() {
    window = nullptr;
    dt = 0;
    Platforms = new std::vector<Platform*>;
    generatePlatform(200, 800, 1);
    generatePlatform(1300, 200,4);
    generatePlatform(700,600, 5);
    initWindow();
    initBg();
    initPlayer();
}
Game::~Game() {
    delete window;
    delete player;
}

void Game::run() {
    while (window->isOpen())
    {
        //TODO TEST
        update();
        render();
    }
}
void Game::updatePlayer() {
    player->update();
}
void Game::initPlayer() {
    player = new Player();
}
void Game::update() {
    while(window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed || (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape))
            window->close();
    }
    updatePlayer();
    updateAccessors();
    updateCollision();
}
void Game::render(){
    window->clear();
    //Platforms->clear();

    //Render the whole game
    renderBg();
    renderPlatforms();
    renderPlayer();
    //renderPlatforms();

    window->display();
}
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(win_width, win_height), "Jungle Tower", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
}
void Game::initBg() {
    bg_texture.loadFromFile("background.png");
    bg_sprite.setTexture(bg_texture);
    bg_rect = sf::IntRect(0,0,1688,961);
    bg_sprite.setTextureRect(bg_rect);
}
void Game::renderPlayer() {
    player->render(window);
}
void Game::renderPlatforms() {
    // Iterating through all of the platforms, NOTE: auto for balancing mistakes
    if (!Platforms->empty()) {
        for (auto &Platform : *Platforms) {
            Platform->render(window);
        }
    }
}
void Game::renderBg() {
    window->draw(bg_sprite);
}
void Game::updateCollision() {
    if (player->getGlobalBounds().top + player->getGlobalBounds().height > window->getSize().y) {
        player->resetVelocity();
        player->setPlayerPosition(player->getGlobalBounds().left,
                                  window->getSize().y - player->getGlobalBounds().height);
    }
    if (!Platforms->empty()) {


        // Collision algorithim for all of the platforms!!! Working Well!!!!!!!
        for (auto &Platform : *Platforms) {
            sf::FloatRect platformBounds = Platform->getGlobalBounds();
            sf::FloatRect playerBounds = player->getGlobalBounds();

            if ((playerBounds.top+playerBounds.height > platformBounds.top) &&
                    (playerBounds.top+playerBounds.height < platformBounds.top+platformBounds.height) &&
                    (playerBounds.left + playerBounds.width > platformBounds.left) &&
                    (playerBounds.left < platformBounds.left+platformBounds.width))
            {
                std::cout << "COLLISION from UP\n";
                player->setIsOnPlatform(true);
                player->setVelocity(player->getVelocity().x, 0.f);
                player->setPlayerPosition(playerBounds.left, platformBounds.top - playerBounds.height );

            }
            else
                player->setIsOnPlatform(false);
        }
    }
}


void Game::generatePlatform(float x, float y, int patt) {
    auto* new_platform = new Platform(x,y, patt);
    Platforms->push_back(new_platform);
}

void Game::updateAccessors() {
    playerTop = player->getGlobalBounds().top;
    playerLeft = player->getGlobalBounds().left;
    playerH = player->getGlobalBounds().height;
    playerW = player->getGlobalBounds().width;
}


