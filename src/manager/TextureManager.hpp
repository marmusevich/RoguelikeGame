#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML\Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager
{
public:
	/**
	 * Default constructor.
	 */
	TextureManager() = delete;

	/**
	 * Adds a texture to the manager and returns its id in the map.
	 * @param The path to the image to load.
	 * @return The id to the texture created, or the id in the map if it already exists.
	 */
	static int AddTexture(std::string filePath);
	//static int AddTexture( std::string filePath ); -->  name = filePath
	//static int AddTexture( std::string filePath, std::string name );


	/**
	 * Gets a texture from the texture manager from an ID.
	 * @param textureId The id of the texture to return.
	 * @return A const reference to the texture.
	*/
	static sf::Texture& GetTexture(int textureId);

	//static sf::Texture& GetTexture( std::string name )


	/**
	 * Removes a texture from the manager from a given id.
	 * @param textureID The id of the texture to be removed.
	 */
	static void RemoveTexture(int textureID);
	//static void RemoveTexture( std::string name );


private:
	/**
	 * A map of each texture name with its ID.
	 */

	//want -> 
	//	_unordered_map_ < key1 = file_name, key2 = id, value = Texture > m_textures

	static std::unordered_map<std::string, int> m_FileToId;
	static std::unordered_map<int, std::unique_ptr<sf::Texture>> m_textures;

// to scene ???
//std::unordered_map<std::string, int> m_NameToId;


	/**
	 * The current key value.
	 */
	static int m_currentId;
};
#endif