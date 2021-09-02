#ifndef SCR_CORE_MANAGER_RESURCEMANAGER_HPP
#define SCR_CORE_MANAGER_RESURCEMANAGER_HPP

#include "core/manager/ResurceType.hpp"

#include <memory>


namespace NResursesManagement
{

//fwd
template <EResurceType TYPE>
class ResourceHolder_NumberAutoIncKey;


/*
provide holder with key = string, it is more usefull
the key must asighed from out of holder

TODO
-������ - ��� ������� � ��������� �����


��� �������
-���� ������� =  ������, ������ � ������� ����� ��� �������, � ������ ������ ��������� �������,
	� ��� ���� ��������� ������
	��������� ����� ������ ��� ������������ ����� ���� ����� - ������������������ �� ����������
- ������������ ������� ��� ������ �������� ��������� 2 �������� ���� / ���, �� ������ �������� = delete
- ������� ������� ���� bool addRes(tResurceID id, tResource&& res); - ��� ���������, �������� ������ �� ������
- ��������� � ���� ����� ������ �� ����� bool IsPresent(tResurceID id)
- �������� ���������� �������� getCount

�����
- �������� ������� ��������� ������� ���� add*, load*, get*, isPresent* - ��� ������� ���� ������� = getFont(...)
		��� ����� get<Font>(...) --> ����� ������
�������� ������ ����� ��� �������� ����� ����� ����, �� ���� ����� ��� ����� ��������� (�������� ����� ������� ��������),
  ��� ������� ���� ������������(�����)

*/



/**
 * Pimp idiom for resurses.
 * TODO disable copy and move� see note by ~ResurceManager()  
 */
class ResurceManager
{
public:
	ResurceManager();
	
	std::unique_ptr<ResourceHolder_NumberAutoIncKey<EResurceType::Texture>> mTexture;
	std::unique_ptr<ResourceHolder_NumberAutoIncKey<EResurceType::Font>> mFonts;
	std::unique_ptr<ResourceHolder_NumberAutoIncKey<EResurceType::Image>> mImage;
//	std::unique_ptr<ResourceHolder_NumberAutoIncKey<EResurceType::Shader>> mShader;
	std::unique_ptr<ResourceHolder_NumberAutoIncKey<EResurceType::Sound>> mSound;

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
