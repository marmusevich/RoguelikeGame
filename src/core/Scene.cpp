//#include "PCH.hpp"
#include "core/Scene.hpp"

Scene::Scene(const Game& game)
	:m_game(game)
{

}


bool Scene::BeforeLoad()
{
	return true;
}

bool Scene::LoadResurce()
{
	return true;
}

void Scene::AfterLoad(bool isLoaded)
{

}


void Scene::Update(float timeDelta)
{

}

void Scene::Draw(sf::RenderWindow& window, float timeDelta)
{

}

const Game& Scene::GetGame() const
{
	return m_game;
}
