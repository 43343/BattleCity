#include "Animation.h"
#include <iostream>

Animation::Animation() : animatedObject(nullptr), animationDuration(0), elapsedTime(0), isAnimating_(false), isAnimationStarted(false) {
} 

void Animation::animSet(sf::Transformable& object) {
    animatedObject = &object;
    elapsedTime = 0;
    isAnimating_ = false;
    isAnimationStarted = false;
}

void Animation::startAnimation() {
    if (!isAnimationStarted) {
        isAnimationStarted = true;
        startNextAnimation();
    }
}

void Animation::update(float deltaTime) {
    if (animatedObject && isAnimating_) {
        animationDuration = animationQueue.front().animationDuration;

        if (elapsedTime >= animationDuration) {
            isAnimating_ = false;
            elapsedTime = animationDuration;
            animationQueue.pop();
        }

        else {
            elapsedTime += deltaTime;
            float progress = elapsedTime / animationDuration;
            if (progress > 1) progress = 1;
            animatedObject->setPosition(currentPosition + (animationQueue.front().targetPosition - currentPosition) * progress);
           std::cout << " CurrentPosition : " << progress;
        }
    }
    else {
            startNextAnimation();
    }
}

void Animation::startNextAnimation() {
    try {
        if (!animationQueue.empty()) {
            currentPosition = animatedObject->getPosition();
            const AnimationFlag& nextFlag = animationQueue.front();
            nextFlag.animationFunction();
            if (repeat) {
                animationQueue.push(nextFlag);
            }
        }
    }
    catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
void Animation::addFlag(const std::function<void()>& onAnimation, float animationDuration) {
    animationQueue.push({ onAnimation, sf::Vector2f(),animationDuration });
}

void Animation::addFlag(const sf::Vector2f& targetPosition, float animationDuration) {
    try {
        auto moveAnimation = [this,targetPosition]() {
            startPosition = animatedObject->getPosition();
            elapsedTime = 0;
            isAnimating_ = true;
            std::cout << "Меня вызвали";
            };

        animationQueue.push({ moveAnimation, targetPosition,animationDuration });
        std::cout << "push flag " <<isAnimating_ << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Don't push flag" << std::endl;
    }
}

bool Animation::isAnimating() {
    return isAnimating_;
}