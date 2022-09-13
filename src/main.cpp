#include "core/Game.hpp"
#include "scenes/GameScene.hpp"

#include <SFML/Graphics.hpp>

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Appenders/DebugOutputAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/RollingFileAppender.h>

#include <memory>
#include <filesystem>

namespace NDefaultParam
{
	const sf::VideoMode mode = sf::VideoMode(1366u, 768u);
	//const sf::VideoMode mode = sf::VideoMode( 1366u, 768u );
	//const sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	//const sf::VideoMode mode = sf::VideoMode(*1024u, 768u);
	constexpr char* title = "Roguelike Template";
	constexpr sf::Uint32 style = sf::Style::Default /*sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize*/;
	constexpr unsigned int FPS = 60;


	//LOGING
	constexpr char* logFileName = "Roguelike.csv";
#ifdef NDEBUG
	constexpr plog::Severity logLevel = plog::error; //select one from: none, fatal, error	
#else
	constexpr plog::Severity logLevel = plog::debug;
#endif
}


/*

provide macro LOG_FATAL_AND_THROW
to replace it
   LOG_FATAL << "ResourceHolder_NumberAutoIncKey::loadFromFile - Can't add resurse from file " + filename;
   throw std::runtime_error("ResourceHolder_NumberAutoIncKey::loadFromFile - Can't add resurse from file " + filename);


*/



// Entry point of the application.
int main()
{
#ifdef _MSC_VER 
	static plog::DebugOutputAppender<plog::TxtFormatter> debugOutputAppender;
#endif // _MSC_VER
	static plog::RollingFileAppender<plog::CsvFormatter> fileAppender(NDefaultParam::logFileName/*,size_t maxFileSize = 0, int maxFiles = 0*/);
	plog::init(NDefaultParam::logLevel, &fileAppender)
#ifdef _MSC_VER
		.addAppender(&debugOutputAppender)
#endif // _MSC_VER
		;

	LOG_INFO << "=======================================================================================================";
	LOG_INFO << " Title: " << NDefaultParam::title;
	LOG_INFO << " VideoMode: " << NDefaultParam::mode.width << " x " << NDefaultParam::mode.height <<" @ " << NDefaultParam::mode.bitsPerPixel;
	LOG_INFO << " FPS: " << NDefaultParam::FPS;
	LOG_INFO << " current_path: " << std::filesystem::absolute(std::filesystem::current_path()).string();
	LOG_INFO << "---------------------------------";
	LOG_INFO << " LOGGIG ";
	LOG_INFO << "        FileName: " << NDefaultParam::logFileName;
	LOG_INFO << "        Level: " << NDefaultParam::logLevel;
	LOG_INFO << "=======================================================================================================";


	/**  todo
	* 1 avoid creation windows directly - push into game, 
	    OR provide read param class and read param from disk
	* 2 get rid sf:: refers - provide adapter
	* 4 base scene or game is resurse managed
	* */


	// Create the main game object.
	sf::RenderWindow window(NDefaultParam::mode, NDefaultParam::title, NDefaultParam::style);
	Game game(&window, NDefaultParam::FPS);

	game.setScene(std::make_shared<GameScene>(game));

	game.run();

	// Exit the application.
	return EXIT_SUCCESS;
}