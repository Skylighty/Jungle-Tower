//
// Created by Pablo on 09.08.2020.
//

#include "game.h"
#include <iostream>



//========= CONST & DECONST ==========
Game::Game() {
    srand(static_cast<unsigned int>(time(nullptr)));
    window = nullptr;
    started = false;
    level = Level::GRASS;
    platformsVelocity = 3.0f;
    dt = 0;
    startime = 0;
    patternNumber = 1;
    score = 0;
    Platforms = new std::vector<Platform*>;
    Features = new std::vector<Feature*>;
    initWindow();
    initBg();
    generateGround();
    platformRNG();
    initPlayer();
    initMusic();
    initScore();
}                 //|
Game::~Game() {
    delete window;
    delete player;
}                //|
//====================================



//================================ ! MAIN FUNCTIONS ! =======================================|
void Game::run() {
    while (window->isOpen())
    {
        //TODO TEST
        update();
        render();
    }
}                                                                     //|
void Game::update() {
    while(window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed || (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape))
            window->close();
            //TODO PAUSE MENU!

        if ((sfEvent.type == sf::Event::KeyPressed) && (sfEvent.key.code == sf::Keyboard::Space))
        {
            player->Jump();
        }

    }
    updateDT();
    updatePlayer();
    updateCollision();
    updatePlatforms();
    updateScore();
    updateBg();
    updateFeatures();
}                                                                  //|
void Game::render(){
    window->clear();

    //Render the whole game
    renderBg();
    renderPlatforms();
    renderPlayer();
    renderScore();
    renderFeatures();

    window->display();
}                                                                   //|
//===========================================================================================|



// ----------------------------------------- INITS -------------------------------------------
void Game::initWindow() {
    window = new sf::RenderWindow(
            sf::VideoMode(win_width, win_height),
            "Jungle Tower",
            sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("vine-leaf.png");
    window->setIcon(256, 256, icon.getPixelsPtr());
    window->setFramerateLimit(60);
}
void Game::initBg() {
    bg_texture.loadFromFile("background.png");
    bg_sprite.setTexture(bg_texture);
    bg_rect = sf::IntRect(0,0,1688,961);
    bg_sprite.setTextureRect(bg_rect);
}
void Game::initMusic() {
    music.openFromFile("music.ogg");
    music.setVolume(5.f);
    music.setLoop(true);
    music.play();
}
void Game::initPlayer() {
    player = new Player();
}
void Game::initScore() {
    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    else
        std::cout << "Font loaded successfully\n";
    Score.setFont(font);
    Score.setCharacterSize(50);
    Score.setFillColor(sf::Color::White);
    Score.setPosition(30.f,30.f);
    Score.setString("0"+std::to_string(score));
}


// --------------------------------------- RENDERS -------------------------------------------
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
void Game::renderScore() {
    window->draw(Score);
}
void Game::renderFeatures(){
    if (!Features->empty()){
        for (auto &Feature : *Features)
        {
            Feature->render(window);
        }
    }
}


// --------------------------------------- UPDATES --------------------------------------------
void Game::updatePlayer() {
    player->update();
    checkDeath();
}
void Game::updateCollision() {

    // Left side of the screen collision
    if (player->getGlobalBounds().left < 0) {
        player->setVelocity(0.f, player->getVelocity().y);
        player->setPlayerPosition(0, player->getGlobalBounds().top);
        player->setVelocity(10.f, player->getVelocity().y);
    }

    // Right side of the screen collision
    if (player->getGlobalBounds().left + player->getGlobalBounds().width > window->getSize().x) {
        player->setVelocity(0.f, player->getVelocity().y);
        player->setPlayerPosition(window->getSize().x - player->getGlobalBounds().width, player->getGlobalBounds().top);
        player->setVelocity(-10.f, player->getVelocity().y);
    }

    // Platforms collision
    if (!Platforms->empty()) {

        // Collision algorithim for all of the platforms!!! Working Well!!!!!!!
        for (auto &Platform : *Platforms) {
            sf::FloatRect platformBounds = Platform->getGlobalBounds();
            sf::FloatRect playerBounds = player->getGlobalBounds();

            // ((playerBounds.left ))

            if ((playerBounds.top + playerBounds.height >= platformBounds.top) &&
                (playerBounds.top + playerBounds.height <= platformBounds.top + (0.5 * platformBounds.height)) &&
                (playerBounds.left + playerBounds.width >= platformBounds.left) &&
                (playerBounds.left <= platformBounds.left + platformBounds.width)) {
                player->resetJump();
                player->setIsOnPlatform(true);
                player->setVelocity(player->getVelocity().x, 0.f);
                player->setPlayerPosition(playerBounds.left, platformBounds.top - playerBounds.height + 10);

            } else
                player->setIsOnPlatform(false);
        }
    }

    // Features collision
    if (!Features->empty())
    {
        for (int i = 0; i < Features->size(); ++i)
        {
            if (player->getGlobalBounds().intersects(Features->at(i)->getGlobalBounds()))
            {
                if (Features->at(i)->type == Feature::Type::STAR)
                {
                    score += 5;
                    Feature *temp = Features->at(i);
                    Features->erase(Features->begin()+(i));
                    delete temp;
                    temp = nullptr;
                }
            }
        }
        // Fixed - another for is needed becuase if it is in the same for as STAR checks
        // the if checks the memory that is alredy dump-deleted
        for (int i = 0; i < Features->size(); ++i)
        {
            if (player->getGlobalBounds().intersects((Features->at(i)->getGlobalBounds())) &&
                Features->at(i)->type == Feature::Type::GHOST)
            {
                player->dead = true;
//                Feature *temp = Features->at(i);
//                Features->erase(Features->begin()+(i));
//                delete temp;
//                temp = nullptr;
            }
        }
    }
}
void Game::updatePlatforms() {
    Platform* temp = nullptr;
    for (auto &Platform : *Platforms)
    {
        if (started)
            Platform->movePlatform();
        if (((player->getGlobalBounds().top+player->getGlobalBounds().height) <
        (Platform->getGlobalBounds().top+ Platform->getGlobalBounds().height)) && !Platform->visited)
        {
            Platform->visited = true;
            ++score;
        }
    }
    for (int i = 0; i < Platforms->size(); ++i)
    {
        sf::FloatRect platformBounds = Platforms->at(i)->getGlobalBounds();
        if ((platformBounds.top + platformBounds.height > window->getSize().y) &&
            !Platforms->at(i)->ground)
        {
            temp = Platforms->at(i);
            Platforms->erase(Platforms->begin()+(i));
            delete temp;
            temp = nullptr;
            //++score;
            platformRNG();
        }
    }
}
void Game::updateDT() {
    dt = dtClock.getElapsedTime().asSeconds();
    startime = starClock.getElapsedTime().asSeconds();
    ghosttime = ghostClock.getElapsedTime().asSeconds();
}
void Game::updateScore() {
    Score.setString("0"+std::to_string(score));
    if (score > 50 && score < 100)
    {
        patternNumber = 2;
        if (level == Level::GRASS)
            platformsVelocity += 0.6f;
        level = Level::GROUND;
    }
    else if (score > 100 && score < 150)
    {
        patternNumber = 3;
        if (level == Level::GROUND)
            platformsVelocity += 0.6f;
        level = Level::STONE;
    }
    else if (score > 150 && score < 200)
    {
        patternNumber = 4;
        if (level == Level::STONE)
            platformsVelocity += 0.6f;
        level = Level::SNOW;
    }
    else if (score > 200)
    {
        patternNumber = 5;
        if (level == Level::SNOW)
            platformsVelocity += 0.6f;
        level = Level::ICE;;
    }
    if (score > 2)
    {
        started = true;
        ground->setVelocity(2.f);
    }
}
void Game::updateFeatures() {
    // Creating the star features
    if (startime > 5.f)
    {
        starClock.restart();
        Feature *star_new = new Feature(Feature::Type::STAR, ((rand() % 950) + 250), ((rand() % 400) + 100));
        Features->push_back(star_new);
    }

    // Creating the ghost features
    if (ghosttime > 12.f)
    {
        ghostClock.restart();
        Feature *ghost_new = new Feature(Feature::Type::GHOST, ((rand() % 950) + 250), ((rand() % 400) + 100));
        Features->push_back(ghost_new);
    }

    // Animating the features
    if (!Features->empty())
    {
        for (auto &Feature : *Features)
        {
            Feature->updateAnimation();
        }
        if (startime > 2.5f && startime < 2.6f)
        {
            for (int i = 0; i < Features->size(); ++i)
            {
                if (Features->at(i)->type == Feature::Type::STAR)
                {
                    Feature *temp = Features->at(i);
                    Features->erase(Features->begin()+(i));
                    delete temp;
                    temp = nullptr;
                }
            }
        }
        if (ghosttime > 4.0f && ghosttime < 4.1f)
        {
            for (int i = 0; i < Features->size(); ++i)
            {
                if (Features->at(i)->type == Feature::Type::GHOST)
                {
                    Feature *temp = Features->at(i);
                    Features->erase(Features->begin()+(i));
                    delete temp;
                    temp = nullptr;
                }
            }
        }
    }
}
void Game::updateBg() {;
}               //TODO
void Game::checkDeath() {
    auto playerBounds = player->getGlobalBounds();
    if (playerBounds.top + playerBounds.height > window->getSize().y)
        player->dead = true;
}


// ------------------------------------- GENERATING -------------------------------------------
void Game::generatePlatform(float x, float y) {
    auto* new_platform = new Platform(x,y, patternNumber, platformsVelocity);
    auto newBounds = new_platform->getGlobalBounds();
    for (auto &PlatformA : *Platforms)
    {
        auto platformBounds = PlatformA->getGlobalBounds();
        int rands = rand() % 1;
        if (newBounds.intersects(platformBounds))
        {
            if (rands)
                new_platform = new Platform(x+((rand() % 100)+100), y-(rand() % 100) - 50, patternNumber, platformsVelocity);
            else
                new_platform = new Platform(x-((rand() % 100)+100), y-(rand() % 100) + 50, patternNumber, platformsVelocity);
        }
    }
    Platforms->push_back(new_platform);
}
void Game::generateGround() {
    ground = new Platform();
    Platforms->push_back(ground);
}
void Game::platformRNG() {
    int splitter = 120;
    if (!started)
    {
        while (Platforms->size() < 7)
        {
            generatePlatform((rand() % 1000 + 300), splitter);
            splitter += ((rand() % 100) + 75);
        }
    }
    if (dt > 0.5)
    {
        generatePlatform(((rand() % 950) + 350), 10);
        dtClock.restart();
    }

}



























