#pragma once

#include "SceneIdentifier.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class SceneStack;

class Scene
{
public:
	typedef std::unique_ptr<Scene> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window);

		sf::RenderWindow* window;
	};


public:
	Scene(SceneStack& stack, Context context);
	virtual				~Scene();

	virtual void		draw() = 0;
	virtual bool		update(const float deltaTime) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;


protected:
	void				SceneLoad(Scenes::ID sceneID);

	Context				getContext() const;


private:
	SceneStack* mStack;
	Context				mContext;
};