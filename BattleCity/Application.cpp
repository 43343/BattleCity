#include "Application.h"
#include "menu.h"
#include "level1.h"



Application::Application()
	: mWindow(sf::VideoMode(1920, 1080), "BattleCity", sf::Style::Fullscreen)
	, mSceneStack(Scene::Context(mWindow))
{
	mWindow.setFramerateLimit(60);
	deltaTime = clock.restart().asSeconds();
	registerScenes();
	mSceneStack.pushScene(Scenes::Menu);
}

void Application::run()
{
	while (mWindow.isOpen())
	{

			processInput();
			update(deltaTime);

			// Check inside this loop, because stack might be empty before update() call
			if (mSceneStack.isEmpty())
				mWindow.close();

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mSceneStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(float deltaTime)
{
	mSceneStack.update(deltaTime);
}

void Application::render()
{
	mWindow.clear();

	mSceneStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}



void Application::registerScenes()
{
	mSceneStack.registerScenes<Menu>(Scenes::Menu);
	mSceneStack.registerScenes<Level1>(Scenes::Level1);
}