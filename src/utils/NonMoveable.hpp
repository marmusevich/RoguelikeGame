#ifndef UTILS_NONMOVEABLE_H
#define UTILS_NONMOVEABLE_H

/**
 * Disable move operation to derived class.
 */
class NonMoveable
{
protected:
	NonMoveable() = default;
	~NonMoveable() = default;

	NonMoveable(NonMoveable&&) = delete;
	NonMoveable& operator=(NonMoveable&&) = delete;
};

#endif //UTILS_NONMOVEABLE_H