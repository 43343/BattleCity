#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Actor.h"
class Player : Actor {
public:
    sf::Sprite sprite;
	Player() {
        sf::Texture texture;
        if(texture.loadFromFile("textures\\texture.png")) std::cout << "Texture load";
        sprite.setTexture(texture);
        if(sprite.getTexture()) std::cout << "Texture load 1"; 
        sprite.setTextureRect(sf::IntRect(32, 15, 16, 15));
        sprite.setScale(6.f, 6.f);
        sprite.setColor(sf::Color(255, 255, 255, 200));
        sprite.setPosition(100, 25);
        soundWalkBuffer.loadFromFile("audio\\walk.mp3");
        soundWalk.setBuffer(soundWalkBuffer);
	};
    sf::Sprite getSprite() {
        return sprite;
    }
    sf::SoundBuffer soundWalkBuffer;
    sf::Sound soundWalk;
public:
    virtual bool handleEvent();
    void draw(sf::RenderTarget& target);
private:
    std::map<sf::Keyboard::Key, Action>		mKeyBinding;
};