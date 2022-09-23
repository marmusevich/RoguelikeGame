#include "core/Game.hpp"
#include "scenes/GameScene.hpp"

#include <SFML/Graphics.hpp>

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Appenders/DebugOutputAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/RollingFileAppender.h>

#include <argparse/argparse.hpp>
#include <tomlplusplus/toml.h>

#include <memory>
#include <filesystem>
#include <exception>
#include <string>



/*
provide macro LOG_FATAL_AND_THROW
to replace it
   LOG_FATAL << "ResourceHolder_NumberAutoIncKey::loadFromFile - Can't add resurse from file " + filename;
   throw std::runtime_error("ResourceHolder_NumberAutoIncKey::loadFromFile - Can't add resurse from file " + filename);
*/


namespace
{
namespace NDefaultParam
{
	const sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	constexpr char* title = "Roguelike Template";
	constexpr uint32_t style = sf::Style::Default;
	constexpr unsigned int FPS = 60;

	constexpr char* configFileName = "roguelike.toml";

	//LOGING
	constexpr char* logFileName = "roguelike.log";//.csv
#ifdef NDEBUG
	constexpr plog::Severity logLevel = plog::error; //select one from: none, fatal, error	
#else
	constexpr plog::Severity logLevel = plog::debug;
#endif
}

struct sArgs : public argparse::Args 
{
	std::string& config_path = kwarg("c,config", "path to config *.toml file").set_default(NDefaultParam::configFileName);
	std::string& log_path = kwarg("l,log", "path to config *.log or *.csv file").set_default(NDefaultParam::logFileName);
};

struct sConfig
{
	sf::VideoMode mode = NDefaultParam::mode;
	bool fullscreen = false;
	std::string title = NDefaultParam::title;
	unsigned int FPS = NDefaultParam::FPS;

	bool parse(const std::string_view& config_path)
	{
		try
		{
			auto config = toml::parse_file(config_path);

			auto _title = config["title"].value_or(NDefaultParam::title);
			auto _FPS = config["FPS"].value_or(NDefaultParam::FPS);
			auto _fullscreen = config["fullscreen"].value_or(false);
			auto _defMode = config["defMode"].value_or(true);
			auto _width = config["mode"]["width"].value_or(NDefaultParam::mode.width);
			auto _height = config["mode"]["height"].value_or(NDefaultParam::mode.height);
			auto _bitsPerPixel = config["mode"]["bitsPerPixel"].value_or(0);

			//no throw before, so set value
			title = _title;
			FPS = _FPS;
			fullscreen = _fullscreen;

			if (_defMode)
			{
				mode = NDefaultParam::mode;
			}
			else
			{
				if (_bitsPerPixel == 0)
				{
					mode = sf::VideoMode(_width, _height);
				}
				else
				{
					mode = sf::VideoMode(_width, _height, _bitsPerPixel);
				}
			}
			return true;
		}
		catch (const std::exception e)
		{
			LOG_ERROR << "Error parse config : " , e.what();
			return false;
		}
		catch (...)
		{
			return false;
		}
		return false;
	}
};
}

// Entry point of the application.
int main(int argc, char* argv[])
{
	// Handibg command line arguments
	sArgs args{};
	try
	{
		args.parse(argc, argv, /*raise_on_error*/ true);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "failed to parse arguments: " << e.what() << std::endl;
		std::cerr << "used default!!! " << std::endl;
		//return -1;
	}

	//init loggig
#ifdef _MSC_VER 
	static plog::DebugOutputAppender<plog::TxtFormatter> debugOutputAppender;
#endif // _MSC_VER
	static plog::RollingFileAppender<plog::TxtFormatter/*CsvFormatter*/> fileAppender(args.log_path.c_str()/*,size_t maxFileSize = 0, int maxFiles = 0*/);
	plog::init(NDefaultParam::logLevel, &fileAppender)
#ifdef _MSC_VER
		.addAppender(&debugOutputAppender)
#endif // _MSC_VER
		;

	//read config
	sConfig config{};
	if (!config.parse(args.config_path))
	{
		LOG_ERROR << "Error parse config, used default";
	}
	
	LOG_INFO << "=======================================================================================================";
	LOG_INFO << " Title: " << config.title;
	LOG_INFO << " VideoMode: " << config.mode.width << " x " << config.mode.height <<" @ " << config.mode.bitsPerPixel;
	LOG_INFO << " FPS: " << config.FPS;
	LOG_INFO << " Fullscreen: " << config.fullscreen;
	LOG_INFO << " Current path: " << std::filesystem::absolute(std::filesystem::current_path()).string();
	LOG_INFO << "---------------------------------";
	LOG_INFO << " Config file " << args.config_path;
	LOG_INFO << "---------------------------------";
	LOG_INFO << " LOGGIG ";
	LOG_INFO << "        FileName: " << args.log_path;
	LOG_INFO << "        Level: " << NDefaultParam::logLevel;
	LOG_INFO << "=======================================================================================================";


	/**  todo
	* 1 avoid creation windows directly - push into game, 
	    OR provide read param class and read param from disk
	* 2 get rid sf:: refers - provide adapter
	* 4 base scene or game is resurse managed
	* */


	// Create the main game object.
	sf::RenderWindow window(config.mode, config.title, config.fullscreen ? sf::Style::Fullscreen : NDefaultParam::style);
	Game game(&window, config.FPS);

	game.setScene(std::make_shared<GameScene>(game));
	game.run();

	// Exit the application.
	return EXIT_SUCCESS;
}