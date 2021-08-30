#ifndef SCENE_H
#define SCENE_H

#include <SFML\Graphics.hpp>

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
	virtual void Update(float timeDelta);

	/**
	 * Draws all game objects to screen.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void Draw(sf::RenderWindow& window, float timeDelta);



	/** 
	 * callbeck before load
	 * return true if can load resurse
	 */
	virtual bool BeforeLoad();


	/**
	 *  invoke from game
	 * do load resurse from file, -> resurse.xml
	 */
	 // in protected ??? and freands game
	bool LoadResurce();

	// ???
	//bool UnLoadResurce();

	/** 
	 *  callback after
	 * isLoaded resurse loaded
	 */
	virtual void AfterLoad(bool isLoaded);


protected:

	const Game& GetGame() const;

private:



	const Game& m_game;


};

#endif //SCENE_H