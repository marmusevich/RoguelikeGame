#ifndef TORCH_H
#define TORCH_H

#include "core/Item.hpp"

class Torch : public Object
{
	using tBase = Object;

public:

	/**
	 * Default Constructor.
	 */
	explicit Torch(const Scene& scene);

	/**
	 * Updates the brightness of the torch.
	 * @param timeDelta The time that has passed since the last update.
	 */
	void update(const float timeDelta) override;

	/**
	 * Gets the brightness modifier of the torch. This is used to create flicker.
	 * @return The brightness of the torch.
	 */
	float GetBrightness() const;

private:

	/**
	 * The brightness modifier of the torch. This is used to denote flicker.
	 */
	float m_brightness;
};
#endif