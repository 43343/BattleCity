#include "level1.h"
using namespace sf;

Level1::Level1(SceneStack& scene, Context context)
    : Scene(scene, context)
{
    rectangleShape_.setPosition(0.f, 0.f);
    rectangleShape_.setSize(sf::Vector2f(1920, 540));
    rectangleShape_.setFillColor(sf::Color::White);
    sf::Texture texture;
    texture.loadFromFile("textures\\texture.png");
    sprite.setTexture(texture);
    //sprite.setTextureRect(sf::IntRect(32, 15, 16, 15));
    sprite.setScale(6.f, 6.f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(100, 25);
    soundWalkBuffer.loadFromFile("audio\\walk.mp3");
    soundWalk.setBuffer(soundWalkBuffer);
}
bool Level1::handleEvent(const sf::Event& event) {
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

bool Level1::update(const float deltaTime) {
    
    return true;
}
void Level1::draw() {
    sf::RenderWindow& m_window = *getContext().window;
    m_window.setView(m_window.getDefaultView());
    //m_window.draw(rectangleShape_);
    m_window.draw(sprite);
}