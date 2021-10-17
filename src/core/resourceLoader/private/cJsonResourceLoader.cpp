#include "core/resourceLoader/private/cJsonResourceLoader.hpp"

#include <iostream>
#include <fstream>

namespace NResourceLoader
{

cJsonResourceLoader::cJsonResourceLoader()
: mDoc{}
, mStatus(false)
{

}
	
bool cJsonResourceLoader::setFile(const std::string& fileName)
{
	std::ifstream is(fileName);
	mStatus = is.is_open();

	if (mStatus)
	{
		try
		{
			mDoc = nlohmann::json::parse(is);
			mStatus = true;
		}
		catch (nlohmann::json::exception& e)
		{
			mStatus = false;

			//LOG

			std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;

			throw;
		}
	}
	else
	{
		mStatus = false;

		//LOG
		throw std::runtime_error("cJsonResourceLoader::setFile - Can't parse file '" + fileName + "' with error #");
			//+ std::to_string(mStatus) + " : " + mDoc.ErrorStr());
	}
	return mStatus;
}

bool cJsonResourceLoader::setString(const std::string& json)
{

	try
	{
		mDoc = nlohmann::json::parse(json);
		mStatus = true;
	}
	catch (nlohmann::json::exception& e)
	{
		mStatus = false;

		//LOG

		std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;

		throw;
	}

	return mStatus;
}
	
namespace
{
namespace NJsonToken
{
	const char* FILE_NAME = "file_name";
	const char* ID = "id";

	const char* TYPE = "type";


	const char* TEXTURE = "Texture";
	const char* IMAGE = "Image";
	const char* FONT = "Font";
	const char* SHADER = "Shader";
	const char* SOUND = "Sound";
}


}

bool cJsonResourceLoader::addResource(NResurceManagement::ResourceManager& resourceManager)
{
	/*
// create an array using push_back
json j;
j.push_back("foo");
j.push_back(1);
j.push_back(true);

// also use emplace_back
j.emplace_back(1.78);

// iterate the array
for (json::iterator it = j.begin(); it != j.end(); ++it) {
  std::cout << *it << '\n';
}

// range-based for
for (auto& element : j) {
  std::cout << element << '\n';
}

// getter/setter
const auto tmp = j[0].get<std::string>();
j[1] = 42;
bool foo = j.at(2);

// comparison
j == R"(["foo", 1, true, 1.78])"_json;  // true

// other stuff
j.size();     // 4 entries
j.empty();    // false
j.type();     // json::value_t::array
j.clear();    // the array is empty again

// convenience type checkers
j.is_null();
j.is_boolean();
j.is_number();
j.is_object();
j.is_array();
j.is_string();

// create an object
json o;
o["foo"] = 23;
o["bar"] = false;
o["baz"] = 3.141;

// also use emplace
o.emplace("weather", "sunny");

// special iterator member functions for objects
for (json::iterator it = o.begin(); it != o.end(); ++it) {
  std::cout << it.key() << " : " << it.value() << "\n";
}

// the same code as range for
for (auto& el : o.items()) {
  std::cout << el.key() << " : " << el.value() << "\n";
}

// even easier with structured bindings (C++17)
for (auto& [key, value] : o.items()) {
  std::cout << key << " : " << value << "\n";
}

// find an entry
if (o.contains("foo")) {
  // there is an entry with key "foo"
}

// or via find and an iterator
if (o.find("foo") != o.end()) {
  // there is an entry with key "foo"
}

// or simpler using count()
int foo_present = o.count("foo"); // 1
int fob_present = o.count("fob"); // 0

// delete an entry
o.erase("foo");
	
	*/

	if (mStatus)
	{

		for (auto& element : mDoc) {
			std::cout << element << '\n';

			//const auto tmp = element. attribute_name();

			//const auto tmp = element.get<std::string>();

			std::cout << element << '\n';

		}
	}
	return mStatus;
}

	
} // namespace NResourceLoader

