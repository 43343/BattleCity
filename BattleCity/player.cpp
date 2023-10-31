#include "player.h"
using namespace sf;
bool Player::handleEvent() {
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
    {
        
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
        sprite.move(-2.f, 0.f);
        sprite.setTextureRect(sf::IntRect(32, 15, 16, 15));
        if (soundWalk.getStatus() == SoundSource::Stopped) soundWalk.play();
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
        sprite.move(2.f, 0.f);
        sprite.setTextureRect(sf::IntRect(95, 15, 16, 15));
        if (soundWalk.getStatus() == SoundSource::Stopped) 
            soundWalk.play();
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
        sprite.move(0.f, -2.f);
        sprite.setTextureRect(sf::IntRect(0, 16, 15, 16));
        if (soundWalk.getStatus() == SoundSource::Stopped) 
            soundWalk.play();
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
        sprite.move(0.f, 2.f);
        sprite.setTextureRect(sf::IntRect(65, 16, 15, 16));
        if (soundWalk.getStatus() == SoundSource::Stopped) 
            soundWalk.play();
    }
    else soundWalk.stop();
    return true;
}

void Player::draw(sf::RenderTarget& target) {
    //target.draw(sprite, RenderStates::Default);
}