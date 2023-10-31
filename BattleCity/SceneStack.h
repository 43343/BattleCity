#pragma once

#include "Scene.h"
#include "SceneIdentifier.h"
#include "Animation.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf
{
	class Event;
	class RenderWindow;
}

class SceneStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			SceneStack(Scene::Context context);

	template <typename T>
	void				registerScenes(Scenes::ID sceneID);

	void				update(const float deltaTime);
	void				draw();
	void				handleEvent(const sf::Event& event);

	void				pushScene(Scenes::ID sceneID);
	void				popScene();
	void				clearScenes();

	bool				isEmpty() const;

private:
	Scene::Ptr			createScene(Scenes::ID sceneID);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, Scenes::ID stateID = Scenes::None);

		Action				action;
		Scenes::ID			sceneID;
	};


private:
	std::vector<Scene::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	Scene::Context										mContext;
	std::map<Scenes::ID, std::function<Scene::Ptr()>>	mFactories;
	sf::RectangleShape rectangle;
	sf::RectangleShape rectangle2;
	sf::Clock clock;
	float deltaTime;
	Animation rectangleAnim;
	Animation rectangle2Anim;
};


template <typename T>
void SceneStack::registerScenes(Scenes::ID sceneID)
{
	mFactories[sceneID] = [this]()
		{
			return Scene::Ptr(new T(*this, mContext));
		};
}