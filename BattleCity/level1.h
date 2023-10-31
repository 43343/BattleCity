#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "SceneStack.h"
#include "Scene.h"
#include "SceneIdentifier.h"
#include "player.h"
class Level1 : public Scene {
public:
    Level1(SceneStack& stack, Context context);

private:
    sf::RectangleShape rectangleShape_;
    Player player_;
    virtual bool			handleEvent(const sf::Event& event);

    virtual bool update(const float deltaTime);

    virtual void draw();

    sf::SoundBuffer soundWalkBuffer;
    sf::Sound soundWalk;
    sf::Sprite sprite;

};