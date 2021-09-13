//#include "PCH.hpp"
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

void Scene::afterLoad(bool isLoaded)
{

}


void Scene::update(float timeDelta)
{

}

void Scene::draw(sf::RenderWindow& window, float timeDelta)
{

}

const Game& Scene::getGame() const
{
	return m_game;
}
