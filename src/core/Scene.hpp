#ifndef SCENE_H
#define SCENE_H

#include <SFML\Graphics.hpp>

#include "core/manager/ResourceManager.hpp"

//fwd
class Game;

class Scene
{
public :
	Scene(const Game& game);

	/**
	 * The main update loop. This loop in turns calls the update loops of all game objects.
	 * @param timeDelta The time, in MS, since the last update call.
	 */
	virtual void update(float timeDelta);

	/**
	 * Draws all game objects to screen.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void draw(sf::RenderWindow& window, float timeDelta);



	/** 
	 * callbeck before load
	 * return true if can load resurse
	 */
	virtual bool beforeLoad();


	/**
	 *  invoke from game
	 * do load resurse from file, -> resurse.xml
	 */
	 // in protected ??? and freands game
	bool loadResurce();

	// ???
	//bool UnLoadResurce();

	/** 
	 *  callback after
	 * isLoaded resurse loaded
	 */
	virtual void afterLoad(bool isLoaded);


protected:

	const Game& getGame() const;

private:



	const Game& m_game;


};

#endif //SCENE_H