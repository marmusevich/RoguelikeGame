#ifndef SCR_CORE_MANAGER_RESOURCEHOLDER_HPP
#define SCR_CORE_MANAGER_RESOURCEHOLDER_HPP

#include "core/manager/ResourceType.hpp"
#include "core/manager/private/ResourceTraits.hpp"
#include "utils/NonCopyable.hpp"
#include "utils/NonMoveable.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

namespace NResurceManagement
{
/**
 * .
 */
template <EResourceType TYPE, typename RESTYPE  = typename TResourceTraits<TYPE>::TResource >
class TResourceHolder : NonCopyable, NonMoveable
{
private:
	using tMap = std::unordered_map<std::string, std::unique_ptr<RESTYPE>>;
public:
	TResourceHolder();

	template <typename... Targs>
	const RESTYPE& loadFromFile(const std::string& key, const std::string& filename, Targs&... args);

	bool acquire(const std::string& key, RESTYPE* res);

	bool isPresent(const std::string& key) const;

	const RESTYPE& get(const std::string& key) const;

	void remove(const std::string& key);

	void clear();

	std::size_t getCount() const;

private:
	mutable tMap mResourceMap;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   IMPL.
//////////////////////////////////////////////////////////////////////////////////////////////////////////


template <EResourceType TYPE, typename RESTYPE>
TResourceHolder<TYPE, RESTYPE>::TResourceHolder()
: mResourceMap()
{

}

template <EResourceType TYPE, typename RESTYPE>
template <typename... Targs>
const RESTYPE& TResourceHolder<TYPE, RESTYPE>::loadFromFile(const std::string& key, const std::string& filename, Targs&... args)
{
	auto it = mResourceMap.find(key);
	if (it == mResourceMap.end())
	{
		// At this point the Resource doesn't exists, so we'll create and add it.
		std::unique_ptr<RESTYPE> resource = std::make_unique<RESTYPE>();
		if (resource->loadFromFile(filename, args...))
		{
			auto isInserted = mResourceMap.emplace(key, std::move(resource));
			if (!isInserted.second)
			{
				//LOG
				throw std::runtime_error("ResourceHolder_NumberAutoIncKey::loadFromFile - Can't add resurse from file " + filename);
			}
			return *(isInserted.first->second);
		}
		else
		{
			//LOG
			throw std::runtime_error("ResourceHolder_NumberAutoIncKey::loadFromFile - Failed to load " + filename);
		}

	}
	return *(it->second);
}

template <EResourceType TYPE, typename RESTYPE>
bool TResourceHolder<TYPE, RESTYPE>::acquire(const std::string& key, RESTYPE* res)
{
	bool ret = res != nullptr;
	if (ret)
	{
		auto it = mResourceMap.find(key);
		ret = it == mResourceMap.end();
		if (ret)
		{
			std::unique_ptr<RESTYPE> resource{ res };
			auto isInserted = mResourceMap.emplace(key, std::move(resource));
			ret = isInserted.second;
		}
	}
	return ret;
}

template <EResourceType TYPE, typename RESTYPE>
bool TResourceHolder<TYPE, RESTYPE>::isPresent(const std::string& key) const
{
	return !(mResourceMap.find(key) == mResourceMap.end());
}

template <EResourceType TYPE, typename RESTYPE>
const RESTYPE& TResourceHolder<TYPE, RESTYPE>::get(const std::string& key) const
{
	auto it = mResourceMap.find(key);
	if (it == mResourceMap.end())
	{
		//LOG
		throw std::runtime_error("ResourceHolder_NumberAutoIncKey::get - Can't get with key =  " + key);
	}
	return *(it->second);
}

template <EResourceType TYPE, typename RESTYPE>
void TResourceHolder<TYPE, RESTYPE>::remove(const std::string& key)
{
	auto it = mResourceMap.find(key);
	if (it != mResourceMap.end())
	{
		mResourceMap.erase(it);
	}
	// LOG or ?
	//throw std::runtime_error("ResourceHolder_NumberAutoIncKey::Remove - Can't delete with id  " + std::to_string(id));
}

template <EResourceType TYPE, typename RESTYPE>
void TResourceHolder<TYPE, RESTYPE>::clear()
{
	mResourceMap.clear();
}


template <EResourceType TYPE, typename RESTYPE>
std::size_t TResourceHolder<TYPE, RESTYPE>::getCount() const
{
	return mResourceMap.size();
}

} // namespace NResurceManagement
#endif // SCR_CORE_MANAGER_RESOURCEHOLDER_HPP
