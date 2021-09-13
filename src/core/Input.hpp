#ifndef INPUT_H
#define INPUT_H

class Input
{
public:

	/**
	 * An enum denoting all possible input keys.
	 */
	enum class KEY
	{
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_ATTACK,
		KEY_ESC
	};

	/**
	 * Checks if a given key is currently pressed.
	 * @param keycode The key to check.
	 * @return True if the given key is currently pressed.
	 */
	static bool IsKeyPressed(KEY keycode);
};
#endif