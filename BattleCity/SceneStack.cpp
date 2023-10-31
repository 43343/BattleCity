#include "SceneStack.h"
#include <iostream>
#include <cassert>


SceneStack::SceneStack(Scene::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
	deltaTime = clock.restart().asSeconds();
	rectangle.setPosition(sf::Vector2f(0, 0));
	rectangle.setSize(sf::Vector2f(1920, 540));
	rectangle.setFillColor(sf::Color(211, 211, 211));
	rectangle2.setPosition(sf::Vector2f(0, 1080));
	rectangle2.setSize(sf::Vector2f(1920, 540));
	rectangle2.setFillColor(sf::Color(211, 211, 211));
	//rectangleAnim.animSet(rectangle);
	//rectangleAnim.addFlag(sf::Vector2f(0, 530), 1.f);
	//rectangle2Anim.animSet(rectangle2);
	//rectangle2Anim.addFlag(sf::Vector2f(0, 530), 0.001f);
	std::cout << "CreateScene";
}

void SceneStack::update(const float deltaTime)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		(*itr)->update(deltaTime);
	}
	//rectangleAnim.update(deltaTime);
	//rectangle2Anim.update(deltaTime);

	applyPendingChanges();
}

void SceneStack::draw()
{
	// Draw all active states from bottom to top
	sf::RenderWindow& m_window = *mContext.window;
	for (Scene::Ptr& scene : mStack) {
		scene->draw();
	}
	//m_window.draw(rectangle);
	m_window.draw(rectangle2);
}

void SceneStack::handleEvent(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		(*itr)->handleEvent(event);
	}
	applyPendingChanges();
}

void SceneStack::pushScene(Scenes::ID sceneID)
{
	//rectangleAnim.startAnimation();
	//startAnimation();
	mPendingList.push_back(PendingChange(Push, sceneID));
}

void SceneStack::popScene()
{
	mPendingList.push_back(PendingChange(Pop));
}

void SceneStack::clearScenes()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool SceneStack::isEmpty() const
{
	return mStack.empty();
}

Scene::Ptr SceneStack::createScene(Scenes::ID sceneID)
{
	auto found = mFactories.find(sceneID);
	assert(found != mFactories.end());

	return found->second();
}

void SceneStack::applyPendingChanges()
{
	for(PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createScene(change.sceneID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

SceneStack::PendingChange::PendingChange(Action action, Scenes::ID sceneID)
	: action(action)
	, sceneID(sceneID)
{
}