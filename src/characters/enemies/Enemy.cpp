#include "characters/enemies/Enemy.hpp"
#include "core/Scene.hpp"
#include "core/manager/ResourceManager.hpp"
#include "utils/MathUtils.hpp"

#include <plog/Log.h>


Enemy::Enemy(const Scene& scene) 
: tBase(scene)
, m_currentTarget({ 0.f, 0.f })
{
	// Set stats.
	m_health = Random(80, 120);
	m_attack = Random(6, 10);
	m_defense = Random(6, 10);
	m_strength = Random(6, 10);
	m_dexterity = Random(6, 10);
	m_stamina = Random(6, 10);
	m_speed = Random(151, 200);


	debugPathColor = RandomColor(150, 255);
	debugPathColor.a = 200;
}

// Overrides the default update function of Entity.
void Enemy::update(float timeDelta)
{
	// Move towards current target location.
	if (!m_targetPositions.empty())
	{
		const sf::Vector2f targetLocation{ m_targetPositions.front() };
		m_velocity = sf::Vector2f(targetLocation.x - m_position.x, targetLocation.y - m_position.y);

		if (abs(m_velocity.x) < 10.f && abs(m_velocity.y) < 10.f)
		{
			m_targetPositions.erase(m_targetPositions.begin());
		}
		else
		{
			const float length{ sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y) };
			m_velocity.x /= length;
			m_velocity.y /= length;

			m_position.x += m_velocity.x * (m_speed * timeDelta);
			m_position.y += m_velocity.y * (m_speed * timeDelta);

			m_sprite.setPosition(m_position);
		}
	}

	// Call Entity update.
	tBase::update(timeDelta);
}

void Enemy::draw(sf::RenderWindow& window, float timeDelta)
{
	tBase::draw(window, timeDelta);

//show path
#ifndef NDEBUG
for (const auto p : m_targetPositions)
{
	sf::CircleShape shape(m_speed / 20);
	shape.setFillColor(debugPathColor);
	shape.setPosition(p);
	window.draw(shape);
}
#endif

}

// Recalculates the enemies path finding.
void Enemy::invokeAI(const Level& level, sf::Vector2f playerPosition)
{
	// [WA] in future each enemy type has self AI logic

	//static sf::Vector2i s_playerPreviousPos { -1, -1 };

	const auto playerCurrentPos = level.locationToMapCord(playerPosition);
	if (s_playerPreviousPos != playerCurrentPos)
	{
		s_playerPreviousPos = playerCurrentPos;

		LOG_DEBUG << "s_playerPosition = { " << s_playerPreviousPos.x << " ; " << s_playerPreviousPos.y << " } ";


#ifdef NDEBUG
		const float distanceToPlayer = 300.f;
#else
		const float distanceToPlayer = 30000.f;
#endif
		if (DistanceBetweenPoints(m_position, playerPosition) < distanceToPlayer)
		{
			m_targetPositions = level.pathfinding(m_position, playerPosition);
		}
	}
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
	m_health -= damage;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (m_health <= 0);
}