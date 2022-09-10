#ifndef SLIME_H
#define SLIME_H

#include "characters/enemies/Enemy.hpp"

class Slime : public Enemy
{
	using tBase = Enemy;

public:
	explicit Slime(const Scene& scene);
};
#endif