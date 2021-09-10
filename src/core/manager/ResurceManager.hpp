#ifndef SCR_CORE_MANAGER_RESURCEMANAGER_HPP
#define SCR_CORE_MANAGER_RESURCEMANAGER_HPP

#include "core/manager/ResurceType.hpp"

#include <memory>


#include "core/manager/TResourceHolder.hpp"

namespace NResursesManagement
{


/*
�����
- �������� ������� ��������� ������� ���� add*, load*, get*, isPresent* - ��� ������� ���� ������� = getFont(...)
		��� ����� get<Font>(...) --> ����� ������
�������� ������ ����� ��� �������� ����� ����� ����, �� ���� ����� ��� ����� ��������� (�������� ����� ������� ��������),
  ��� ������� ���� ������������(�����)
*/

/**
 * Pimp idiom for resurses.
 * TODO disable copy and move,
 *  see note by ~ResurceManager()  
 */
class ResurceManager
{
public:
	ResurceManager();

	//loadResuse(xml or jml file)

	std::unique_ptr<TResourceHolder<EResurceType::Texture>> mTexture;
	std::unique_ptr<TResourceHolder<EResurceType::Font>> mFonts;
	std::unique_ptr<TResourceHolder<EResurceType::Image>> mImage;
	std::unique_ptr<TResourceHolder<EResurceType::Shader>> mShader;
	std::unique_ptr<TResourceHolder<EResurceType::Sound>> mSound;

	/**
	 * prevent 'uncomplete type error' in unique_ptr
	 * see:
	 * https://stackoverflow.com/questions/28786387/c-pimpl-idiom-incomplete-type-using-stdunique-ptr
	 * https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
	 */
	~ResurceManager();

};

} // namespace NResursesManagement
#endif // SCR_CORE_MANAGER_RESURCEMANAGER_HPP
