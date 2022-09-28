#include "core/Object.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"


Object::Object(const Scene& scene)
: m_position{ 0.f, 0.f }
, m_animationSpeed(0)
, m_isAnimated(false)
, m_frameCount(0)
, m_currentFrame(0)
, m_frameWidth(0)
, m_frameHeight(0)
, m_timeDelta(0)
, m_scene(scene)
{
}

// Gives the object the given sprite.
bool Object::setSprite(const sf::Texture& texture, const int frames, const int frameSpeed)
{
	// Create a sprite from the loaded texture.
	m_sprite.setTexture(texture);

	// Set animation speed.
	m_animationSpeed = frameSpeed;

	// Store the number of frames.
	m_frameCount = frames;

	// Calculate frame dimensions.
	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	// Check if animated or static.
	if (frames > 1)
	{
		// Set sprite as animated.
		m_isAnimated = true;

		// Set the texture rect of the first frame.
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
	else
	{
		// Set sprite as non animated.
		m_isAnimated = false;
	}

	// Set the origin of the sprite.
	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

bool Object::setSprite(const std::string& textureId, const int frames, const int frameSpeed)
{
	return setSprite(getTexture(textureId), frames, frameSpeed);
}

// Returns the object's sprite.
sf::Sprite& Object::getSprite()
{
	return m_sprite;
}

// Sets the position of the object.
void Object::setPosition(const sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(position);
}

// Returns the position of the object.
sf::Vector2f Object::getPosition() const
{
	return m_position;
}

// Gets the current animation state of the object.
bool Object::isAnimated() const
{
	return m_isAnimated;
}

// Sets the animation state of the object.
void Object::setAnimated(const bool isAnimated)
{
	m_isAnimated = isAnimated;

	if (isAnimated)
	{
		m_currentFrame = 0;
	}
	else
	{
		// set the texture rect of the first frame
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
}

// Draws the object to the given render window.
void Object::draw(sf::RenderWindow &window, const float timeDelta)
{
	// check if the sprite is animated
	if (m_isAnimated)
	{
		// add the elapsed time since the last draw call to the aggregate
		m_timeDelta += timeDelta;

		// check if the frame should be updated
		if (m_timeDelta >= (1.f / m_animationSpeed))
		{
			NextFrame();
			m_timeDelta = 0;
		}
	}

	window.draw(m_sprite);
}

// Advances the sprite forward a frame.
void Object::NextFrame()
{
	// check if we reached the last frame
	if (m_currentFrame == (m_frameCount - 1))
		m_currentFrame = 0;
	else
		m_currentFrame++;

	// update the texture rect
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

// Gets the frame count of the object.
int Object::getFrameCount() const
{
	return m_frameCount;
}

const Scene& Object::getScene() const
{
	return m_scene;
}

const NResurceManagement::ResourceManager& Object::getResourceManager() const
{
	return m_scene.getResourceManager();
}

const sf::Texture& Object::getTexture(const std::string& textureId) const
{
	return	m_scene.getResourceManager().get<NResurceManagement::EResourceType::Texture>(textureId);
}
