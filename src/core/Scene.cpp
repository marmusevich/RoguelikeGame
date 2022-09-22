#include "core/Scene.hpp"

Scene::Scene(const Game& game)
	:m_game(game)
{

}


bool Scene::beforeLoad()
{
	return true;
}

bool Scene::loadResurce()
{
	return true;
}

void Scene::afterLoad(const bool isLoaded)
{

}


void Scene::update(const float timeDelta)
{

}

void Scene::draw(sf::RenderWindow& window, const float timeDelta)
{

}

const Game& Scene::getGame() const
{
	return m_game;
}


const NResurceManagement::ResourceManager& Scene::getResourceManager() const
{
	return mResourceManager;
}

NResurceManagement::ResourceManager& Scene::getResourceManager()
{
	return mResourceManager;
}

