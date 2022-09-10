#ifndef KEY_H
#define KEY_H

#include "core/Item.hpp"

class Key : public Item
{
	using tBase = Item;

public:
	explicit Key(const Scene& scene);
};
#endif