#ifndef UTILS_NONCOPYABLE_H
#define UTILS_NONCOPYABLE_H

/**
 * Disable copy operation to derived class.
 */
class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator =(const NonCopyable&) = delete;
};

#endif //UTILS_NONCOPYABLE_H