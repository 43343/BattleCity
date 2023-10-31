#pragma once

#include "Scene.h"
#include "SceneIdentifier.h"
#include "SceneStack.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
	Application();
	void					run();


private:
	void					processInput();
	void					update(float deltaTime);
	void					render();
	void					registerScenes();


private:
	sf::Clock clock;
	float deltaTime;
	sf::RenderWindow		mWindow;

	SceneStack				mSceneStack;
};