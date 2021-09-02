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
-формат - все функции с маленькой буквы


для холдера
-ключ ресурса =  строка, доступ к ресурсу через имя ресурса, в конфиг файлах оперируем именами,
	и без афто генерации ключей
	обращение нужно только при иницилизации сцены чаще всего - производительность не пострадает
- специлизации функций для разных способов загрузкиб 2 параметр есть / нет, не нужные пометить = delete
- сделать функцию типа bool addRes(tResurceID id, tResource&& res); - мув семантика, добавить ресурс на прямую
- проверить а если такой ресурс по имени bool IsPresent(tResurceID id)
- получить количество ресурсов getCount

здесь
- возможно сделать семейство функций типа add*, load*, get*, isPresent* - длф каждого типа ресурса = getFont(...)
		или лучше get<Font>(...) --> нужны трейты
наверное вместо енума тип ресурсов лучше класы теги, не надо будет имя енума указывать (дедукция типов поможет наверное),
  или простой енум использовать(херня)

*/



/**
 * Pimp idiom for resurses.
 * TODO disable copy and moveб see note by ~ResurceManager()  
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
