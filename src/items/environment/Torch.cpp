//#include "PCH.hpp"
#include "items/environment/Torch.hpp"
#include "utils/MathUtils.hpp"

Torch::Torch() :
m_brightness(1.f)
{

}

// update the brightness of the torch.
void Torch::update(float timeDelta)
{
	// Generate a random number between 80 and 120, divide by 100 and store as float between .8 and 1.2.
	m_brightness = Random(80, 120) / 100.f;

}

// Returns the brightness of the torch.
float Torch::GetBrightness()
{
	return m_brightness;
}