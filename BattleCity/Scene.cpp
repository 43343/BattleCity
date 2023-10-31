#include "Scene.h"
#include "SceneStack.h"


Scene::Context::Context(sf::RenderWindow& window)
	: window(&window)
{
}

Scene::Scene(SceneStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}

Scene::~Scene()
{
}

void Scene::SceneLoad(Scenes::ID sceneID)
{
	mStack->popScene();
	mStack->pushScene(sceneID);
}

Scene::Context Scene::getContext() const
{
	return mContext;
}
void Scene::draw() {
	sf::RenderWindow& m_window = *getContext().window;
}
bool Scene::update(const float deltaTime) {
	return true;
}