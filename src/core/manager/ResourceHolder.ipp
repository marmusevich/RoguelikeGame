template <EResurceType TYPE>
ResourceHolder<TYPE>::ResourceHolder()
	: mResourceMap()
	, mCurIndex(static_cast<tResurceID>(0))
{

}

template <EResurceType TYPE>
tResurceID ResourceHolder<TYPE>::Load(const std::string& filename)
{
	for (auto it = mResourceMap.cbegin(); it != mResourceMap.cend(); ++it)
	{
		if (it->second.first == filename)
		{
			return it->first;
		}
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	std::unique_ptr<tResource> resource = std::make_unique<tResource>();
	if (resource->loadFromFile(filename))
	{
		auto isInserted = mResourceMap.emplace(mCurIndex + 1, std::make_pair(filename, std::move(resource)));
		if (isInserted.second)
		{
			//ok!
			mCurIndex++;
			return mCurIndex;
		}
		else
		{
			//LOG
			throw std::runtime_error("ResourceHolder::Load - Can't add resurse from file " + filename);
		}
	}
	else
	{
		//LOG
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	//error occured, must NOT reach any way
	return -1;
}

template <EResurceType TYPE>
const typename ResourceHolder<TYPE>::tResource& ResourceHolder<TYPE>::Get(tResurceID id) const
{
	auto it = mResourceMap.find(id);

	if (it == mResourceMap.end())
	{
		//LOG
		throw std::runtime_error("ResourceHolder::Get - Can't get with id  " + std::to_string(id));
	}

	return *(it->second.second);
}

template <EResurceType TYPE>
void ResourceHolder<TYPE>::Remove(tResurceID id)
{
	auto it = mResourceMap.find(id);
	if (it != mResourceMap.end())
	{
		mResourceMap.erase(it);
	}
	// LOG or ?
	//throw std::runtime_error("ResourceHolder::Remove - Can't delete with id  " + std::to_string(id));
}

template <EResurceType TYPE>
void ResourceHolder<TYPE>::Clear()
{
	mResourceMap.clear();
	mCurIndex = static_cast<tResurceID>(0);
}
