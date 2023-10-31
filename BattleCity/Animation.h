#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <queue>

class Animation {
public:
    Animation();
    void startNextAnimation();
    void startAnimation();
    void addFlag(const std::function<void()>& onAnimation, float animationDuration);
    void addFlag(const sf::Vector2f& targetPosition, float animationDuration);
    void animSet(sf::Transformable& object);
    void update(float deltaTime);
    bool isAnimating();
    bool repeat;

private:
    struct AnimationFlag {
        std::function<void()> animationFunction;
        sf::Vector2f targetPosition;
        float animationDuration;
    };

    sf::Transformable* animatedObject;
    sf::Vector2f startPosition;
    sf::Vector2f currentPosition;
    float animationDuration;
    float elapsedTime;
    bool isAnimating_;
    bool isAnimationStarted;
    std::queue<AnimationFlag> animationQueue;
};