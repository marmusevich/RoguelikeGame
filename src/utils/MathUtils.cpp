#include "utils/MathUtils.hpp"

#include <ctime>

float DistanceBetweenPoints(sf::Vector2f poit1, sf::Vector2f poit2)
{
	return Magnitude(poit1 - poit2);
}

float Magnitude(sf::Vector2f vec)
{
	return std::sqrtf(std::powf(vec.x, 2) + std::powf(vec.y, 2));
}

float AngleBetweenVectors(sf::Vector2f vec1, sf::Vector2f vec2)
{
	float ret = std::nanf("0");
	
	const float magnitude = Magnitude(vec1) * Magnitude(vec2);//allways great zero
	if (magnitude > 0.0f)
	{
		const float cosValue = (vec1.x * vec2.x + vec1.y * vec2.y) / magnitude;
		if(-1.0f <= cosValue && cosValue <= 1.0f)
		{
			ret = acosf(cosValue);
		}
	}
	return ret;
}

sf::Vector2f Normalize(sf::Vector2f vec)
{
	sf::Vector2f ret{ std::nanf("0") , std::nanf("0") };

	const float magnitude = Magnitude(vec);
	if (magnitude > 0.0f)
	{
		ret = vec / magnitude;
	}
	return ret;
}

float RadToGrad(float rad)
{
	return rad / PI * 180.0f;
}

float GradToRad(float grad)
{
	return grad / 180.0f * PI;
}

void RandomSeedByTime()
{
	RandomSeed(static_cast<unsigned int>(std::time(nullptr)));
}

