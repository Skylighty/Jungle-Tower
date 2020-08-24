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
    mt = std::mt19937();
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
    player = new Player(this);
}
void Game::update() {
    while(window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed || (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape))
            window->close();
        if ((sfEvent.type == sf::Event::KeyPressed) && (sfEvent.key.code == sf::Keyboard::Space))
            player->Jump();
    }
    updateDT();
    updatePlayer();
    updateScore();
    updateCollision();
    updatePlatforms();
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
//    // Bottom
//    if (player->getGlobalBounds().top + player->getGlobalBounds().height > window->getSize().y) {
//        player->resetVelocity();
//        player->setPlayerPosition(player->getGlobalBounds().left,window->getSize().y - player->getGlobalBounds().height);
//    }

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
                player->resetJump();
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


    // Screen segmentation
    int splitter = 0;
    int dt_conv = static_cast<int>(dt);

    std::uniform_real_distribution<float> w_dist(width_start, width_stop);
    std::uniform_real_distribution<float> splitter_dist(100.f, 200.f);

    if (Platforms->size() <= 6 && splitter <= 750.f)
    {
        //while (Platforms->size() <= 7)
        //{
        while (Platforms->size() < 6)
        {
            splitter += splitter_dist(mt);
            generatePlatform(w_dist(mt), static_cast<float>(splitter), 1);
        }
        //}
    }

}
void Game::updatePlatforms() {
    Platform* temp = nullptr;
    for (auto &Platform : *Platforms)
    {
        Platform->movePlatform();
    }
    for (int i = 0; i < Platforms->size(); ++i)
    {
        sf::FloatRect platformBounds = Platforms->at(i)->getGlobalBounds();
        if ((platformBounds.top + platformBounds.height > window->getSize().y - ground->getGlobalBounds().height) &&
        !Platforms->at(i)->ground)
        {
            temp = Platforms->at(i);
            Platforms->erase(Platforms->begin()+(i));
            delete temp;
            temp = nullptr;
            platformRNG();
        }
    }
}
void Game::updateDT() {
    dt = dtClock.getElapsedTime().asSeconds();
}

void Game::updateScore() {
    auto playerBounds = player->getGlobalBounds();
    for (auto &Platform: *Platforms)
    {
        auto platformBounds = Platform->getGlobalBounds();
        if (playerBounds.top + playerBounds.height < platformBounds.top)
            score++;
    }
}

void Game::setEvent(sf::Event::EventType type) {
    sfEvent.type = type;
}






