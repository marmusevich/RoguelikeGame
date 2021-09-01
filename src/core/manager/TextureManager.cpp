//#include "PCH.hpp"
#include "manager\TextureManager.hpp"

std::unordered_map<std::string, int> TextureManager::m_FileToId;
std::unordered_map<int, std::unique_ptr<sf::Texture>> TextureManager::m_textures;
int TextureManager::m_currentId = 0;

// Adds a texture to the manager, and returns its id in the map.
int TextureManager::AddTexture(std::string filePath)
{
	auto it = m_FileToId.find(filePath);
	if (it != m_FileToId.end())
	{
		return it->second;
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filePath))
	{
		// also throw exception, or always check return

		return -1;
	}

	m_currentId++;

	m_FileToId[filePath] =  m_currentId;
	m_textures[m_currentId] = std::move(texture);


	// Return the texture ID.
	return m_currentId;
}

// Removes a texture from the manager from a given id.
void TextureManager::RemoveTexture(int textureID)
{
	auto it = m_textures.find(textureID);
	if (it != m_textures.end())
	{
		m_textures.erase(it);

		//m_FileToId.erase ???
	}
}

// Gets a texture from the texture manager from an ID.
sf::Texture& TextureManager::GetTexture(int textureID)
{
	auto it = m_textures.find(textureID);
	if (it != m_textures.end())
	{
		return *it->second;
	}
	throw std::invalid_argument{ "No such resource id." };
}