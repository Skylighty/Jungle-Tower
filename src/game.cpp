//
// Created by Pablo on 09.08.2020.
//

#include "game.h"
#include <iostream>




Game::Game() {
    window = nullptr;
    dt = 0;
    Platforms = new std::vector<Platform*>;
    generateGround();
    platformRNG();
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
    updateCollision();
    platformRNG();
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

    if (player->getGlobalBounds().left < 0)
    {
        player->setVelocity(0.f, player->getVelocity().y);
        player->setPlayerPosition(0, player->getGlobalBounds().top);
    }

    if (player->getGlobalBounds().left + player->getGlobalBounds().width > window->getSize().x)
    {
        player->setVelocity(0.f, player->getVelocity().y);
        player->setPlayerPosition(window->getSize().x - player->getGlobalBounds().width, player->getGlobalBounds().top);
    }
    if (!Platforms->empty()) {


        // Collision algorithim for all of the platforms!!! Working Well!!!!!!!
        for (auto &Platform : *Platforms) {
            sf::FloatRect platformBounds = Platform->getGlobalBounds();
            sf::FloatRect playerBounds = player->getGlobalBounds();

            // ((playerBounds.left ))

            if ((playerBounds.top+playerBounds.height >= platformBounds.top) &&
                    (playerBounds.top+playerBounds.height <= platformBounds.top+(0.5*platformBounds.height)) &&
                    (playerBounds.left + playerBounds.width >= platformBounds.left) &&
                    (playerBounds.left <= platformBounds.left+platformBounds.width))
            {
                player->setIsOnPlatform(true);
                player->setVelocity(player->getVelocity().x, 0.f);
                player->setPlayerPosition(playerBounds.left, platformBounds.top - playerBounds.height+10);

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


void Game::generateGround() {
    ground = new Platform();
    Platforms->push_back(ground);
}

void Game::platformRNG() {

    // Definition of boundaries within which i want to generate platforms
    float width_start = 0.f;
    float width_stop = 1300.f;
    float height_start = 150.f;
    float height_stop = 750.f;

    // Initialization of random device
    std::random_device rd;
    std::mt19937  mt(rd());
    std::uniform_real_distribution<float> w_dist(width_start, width_stop);
    //std::uniform_real_distribution<float> h_dist(height_start, height_stop);
    std::uniform_real_distribution<float> splitter_dist(80.f, 150.f);

    // Screen segmentation
    int splitter = 0;

    if (Platforms->size() <= 7 && splitter <= height_stop)
    {
        while (Platforms->size() <= 7)
        {
            splitter += splitter_dist(mt);
            generatePlatform(w_dist(mt), static_cast<float>(splitter), 1);
        }
    }

}

void Game::updatePlatforms() {
    Platform* temp = nullptr;
    for (int i = 0; i < Platforms->size(); ++i)
    {
        sf::FloatRect platformBounds = Platforms->at(i)->getGlobalBounds();
        if (platformBounds.top > window->getSize().y)
        {
            temp = Platforms->at(i);
            Platforms->erase(Platforms->begin()+(i-1));
            delete temp;
            temp = nullptr;
        }
    }

}


