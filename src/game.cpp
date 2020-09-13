//
// Created by Pablo on 09.08.2020.
//

#include "game.h"
#include <iostream>



//========= CONST & DECONST ==========
Game::Game() {
    srand(static_cast<unsigned int>(time(nullptr)));
    window = nullptr;
    starClock.restart();
    ghostClock.restart();
    started = false;
    level = Level::GRASS;
    platformsVelocity = 3.0f;
    dt = 0;
    patternNumber = 1;
    score = 0;
    Platforms = new std::vector<Platform*>;
    Features = new std::vector<Feature*>;
    play_again = false;
    initWindow();
    initBg();
    generateGround();
    platformRNG();
    initPlayer();
    initMusic();
    initScore();
}                 //|
Game::Game(bool decision){         //|
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
    play_again = true;
    initWindow();
    initBg();
    generateGround();
    platformRNG();
    initPlayer();
    initMusic();
    initScore();
}
Game::~Game() {
    delete window;
    delete player;
}                //|
//====================================



//================================ ! MAIN FUNCTIONS ! =======================================|
void Game::run() {
    if (!player->dead && !play_again)
    {
        renderStart();
        while (start)
        {
            initStart();
            startMenu();
        }
    }
    while (window->isOpen()) {
        if (!pause && !player->dead) {
            update();
            render();
        }
        else if(player->dead)
        {
            initDeath();
            renderDeath();
            while (player->dead)
                updateDeath();
        }
        else if (pause){
            if (!menu_render) {
                menu();
                buttons();
                renderMenu();
                menu_render = true;
                while (menu_render)
                    updateMenu();
            }
        }
    }
}                                                                     //|
void Game::update() {
    while(window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed || (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape))
            pause = true;


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
    updateFeatures();
    checkDeath();
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
void Game::Restart() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow* temp = window;
    window = nullptr;
    delete temp;
    initWindow();
    started = false;
    level = Level::GRASS;
    platformsVelocity = 3.0f;
    dt = 0;
    startime = 0;
    ghosttime = 0;
    patternNumber = 1;
    score = 0;
    initBg();
    generateGround();
    platformRNG();
    initPlayer();
    initMusic();
    initScore();

}                                                                 //|
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
    music.setVolume(30.f);
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
void Game::initDeath(){
    Features->clear();
    Platforms->clear();
    bg_texture.loadFromFile("death_bg.png");
    bg_sprite.setTexture(bg_texture);
    bg_rect = sf::IntRect(0,0,1688,961);
    bg_sprite.setTextureRect(bg_rect);

    player->changeSpriteColor(sf::Color(200,0,0,90));
    for (auto &Feature : *Features){
        Feature->setSpriteColor(sf::Color(200,0,0,90));
    }

    sf::Color gray = sf::Color(128,128,128);
    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    You_Died.setFont(font);
    You_Died.setCharacterSize(110);
    You_Died.setFillColor(sf::Color::Red);
    You_Died.setString("You Died!");
    You_Died.setOutlineColor(sf::Color::Black);
    You_Died.setOutlineThickness(5.f);
    You_Died.setScale(1.3f, 1.3f);
    You_Died.setPosition(400.f,150.f);

    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Play_Again.setFont(font);
    Play_Again.setCharacterSize(60);
    Play_Again.setFillColor(gray);
    Play_Again.setString("Play Again");
    Play_Again.setOutlineColor(sf::Color::Black);
    Play_Again.setOutlineThickness(5.f);
    Play_Again.setScale(1.3f, 1.3f);
    Play_Again.setPosition(550.f,450.f);


    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Close.setFont(font);
    Close.setCharacterSize(60);
    Close.setFillColor(gray);
    Close.setString("Close");
    Close.setOutlineColor(sf::Color::Black);
    Close.setOutlineThickness(5.f);
    Close.setScale(1.3f, 1.3f);
    Close.setPosition(660.f, 650.f);

    started = false;
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
void Game::renderDeath() {
    window->draw(bg_sprite);
    player->render(window);
    window->draw(Play_Again);
    window->draw(You_Died);
    window->draw(Close);
    window->display();
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
    if (!Features->empty()) {
        for (int i = 0; i < Features->size(); ++i) {
            if (player->getGlobalBounds().intersects(Features->at(i)->getGlobalBounds())) {
                if (Features->at(i)->type == Feature::Type::STAR) {
                    score += 5;
                    Feature *temp = Features->at(i);
                    Features->erase(Features->begin() + i);
                    //delete temp;
                }
            }
//        for (auto &Feature : *Features) {
//            if (Feature->getGlobalBounds().intersects(player->getGlobalBounds()))
//            {
//                Features->erase(Feature)
//            }
//        }
            for (int i = 0; i < Features->size(); ++i) {
                if (player->getGlobalBounds().intersects(Features->at(i)->getGlobalBounds())) {
                    if (Features->at(i)->type == Feature::Type::GHOST) {
                        Features->clear();
                        player->dead = true;
                    }
                }
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
    feature_count = Features->size();
    if (started)
   {
      sf::FloatRect player_bounds = player->getGlobalBounds();
      sf::FloatRect col_bounds = sf::FloatRect(player_bounds.left + 20, player_bounds.top + 20,
        player_bounds.width + 20, player_bounds.height + 20);
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
           if(ghost_new->getGlobalBounds().intersects(col_bounds))
           {
             ghost_new = new Feature(Feature::Type::GHOST, ((rand() % 950) + 50), ((rand() % 400) + 250));
           }
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
}
void Game::checkDeath() {
    auto playerBounds = player->getGlobalBounds();
    if (playerBounds.top + playerBounds.height > window->getSize().y)
        player->dead = true;
}
void Game::updateDeath() {
    while (window->pollEvent(sfEvent)) {
        sf::Color gray = sf::Color(128, 128, 128);
        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        sf::Vector2f mpos = window->mapPixelToCoords(mouse);
        float val_x = mpos.x;
        float val_y = mpos.y;


        if (Play_Again.getGlobalBounds().contains(val_x, val_y)) {
            Play_Again.setFillColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window->close();
                Restart();
            }
        }
        else {
            Play_Again.setFillColor(gray);
        }
        if (Close.getGlobalBounds().contains(val_x, val_y)) {
            Close.setFillColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window->close();
            }
            } else {
                Close.setFillColor(gray);
            }
        }
        renderDeath();
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

// ---------------------------------------- MENU ----------------------------------------------
void Game::menu(){

    bg_menu.loadFromFile("menu.png");
    bg_sprite_menu.setTexture(bg_menu);
    bg_rect_menu = sf::IntRect(0,0,1688,961);
    bg_sprite_menu.setTextureRect(bg_rect_menu);

}
void Game::buttons(){
    sf::Color gray = sf::Color(128,128,128);
    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Resume.setFont(font);
    Resume.setCharacterSize(60);
    Resume.setFillColor(sf::Color::White);
    Resume.setPosition(670.f,300.f);
    Resume.setString("Resume");
    Resume.setOutlineColor(sf::Color::Black);
    Resume.setOutlineThickness(5.f);
    Resume.setScale(1.3f, 1.3f);

    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Close.setFont(font);
    Close.setCharacterSize(60);
    Close.setFillColor(sf::Color::White);
    Close.setPosition(665.f,500.f);
    Close.setOutlineColor(sf::Color::Black);
    Close.setOutlineThickness(5.f);
    Close.setString("  Close");
    Close.setScale(1.3f, 1.3f);

}
void Game::renderMenu()
{
    window->draw(bg_sprite_menu);
    window->draw(Resume);
    window->draw(Close);
    window->display();
}
void Game::updateMenu(){
    while(window->pollEvent(sfEvent))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        pause = false;
            
            sf::Color gray = sf::Color(128,128,128);
            sf::Vector2i mouse = sf::Mouse::getPosition(*window);
            sf::Vector2f mpos = window->mapPixelToCoords(mouse);
            float val_x = mpos.x;
            float val_y = mpos.y;

            if (Close.getGlobalBounds().contains(val_x, val_y))
            {
                Close.setFillColor(sf::Color::White);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    menu_render = false;
                    window->close();
                }
            }
            else{
                Close.setFillColor(gray);
            }

            if (Resume.getGlobalBounds().contains(val_x, val_y))
            {
                Resume.setFillColor(sf::Color::White);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    menu_render = false;
                    pause=false;
                }
            }
            else
                {
                Resume.setFillColor(gray);
            }
            window->draw(bg_sprite_menu);
            window->draw(Resume);
            window->draw(Close);
            window->display();

    }
}
void Game::renderStart(){

    bg_menu.loadFromFile("start_menu.png");
    bg_sprite_menu.setTexture(bg_menu);
    bg_rect_menu = sf::IntRect(0,0,1688,961);
    bg_sprite_menu.setTextureRect(bg_rect_menu);
    sf::Color color = sf::Color(128,128,128);

    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Play.setFont(font);
    Play.setString("Play");
    Play.setCharacterSize(60);
    Play.setFillColor(color);
    Play.setOutlineColor(sf::Color::Black);
    Play.setOutlineThickness(5.f);
    Play.setScale(1.3f,1.3f);
    Play.setPosition(730.f,400.f);

    if(!font.loadFromFile("ka1.ttf"))
        std::cout << "ERROR: FONT LOADING ERROR!\n";
    Exit.setFont(font);
    Exit.setString("Exit");
    Exit.setCharacterSize(60);
    Exit.setFillColor(color);
    Exit.setOutlineColor(sf::Color::Black);
    Exit.setOutlineThickness(5.f);
    Exit.setScale(1.3f,1.3f);
    Exit.setPosition(740.f,600.f);
}
void Game::initStart(){
    window->draw(bg_sprite_menu);
    window->draw(Play);
    window->draw(Exit);
    window->display();
}
void Game::startMenu() {
    while(window->pollEvent(sfEvent))
    {
        sf::Color gray = sf::Color(128,128,128);
        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        sf::Vector2f mpos = window->mapPixelToCoords(mouse);
        float val_x = mpos.x;
        float val_y = mpos.y;


           if (Exit.getGlobalBounds().contains(val_x, val_y))
           {
               Exit.setFillColor(sf::Color::White);
               if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                   start = false;
                   window->close();
               }
            }
           else {
               Exit.setFillColor(gray);
           }

           if (Play.getGlobalBounds().contains(val_x, val_y))
           {
               Play.setFillColor(sf::Color::White);
               if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                   start = false;
               }
            }
           else {
               Play.setFillColor(gray);
           }
        }
}




























