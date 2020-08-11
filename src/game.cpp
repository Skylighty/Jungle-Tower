//
// Created by Pablo on 09.08.2020.
//

#include "game.h"




Game::Game() {
    window = nullptr;
    dt = 0;
    initWindow();
    initPlayer();
}
Game::~Game() {
    delete window;
    delete player;
}
void Game::update() {
    while(window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed || (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape))
            window->close();
    }
    updatePlayer();
}
void Game::render(){
    window->clear();

    //Render the whole game
    renderPlayer();

    window->display();
}
void Game::run() {
    while (window->isOpen())
    {
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
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(win_width, win_height), "Jungle Tower");
    window->setFramerateLimit(60);
}
void Game::renderPlayer() {
    player->render(window);
}
