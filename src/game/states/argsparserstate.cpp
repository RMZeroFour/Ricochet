#include "game/states/argsparserstate.h"

#include "generated/buildinfo.h"
#include "game/states/loginitstate.h"

#include <iostream>

static void PrintHelp()
{
	std::cout << "Options:" << '\n';
	std::cout << "-h/--help" << '\t' << "Print this dialog" << '\n';
	std::cout << "-a/--about" << '\t' << "Print program metadata" << '\n';
}

static void PrintAbout()
{
	std::cout << Ricochet_NAME << " v" << Ricochet_VERSION << '\n';
	std::cout << Ricochet_DESCRIPTION << '\n';
	std::cout << Ricochet_HOMEPAGE_URL << '\n';
}

static void PrintInvalid(const std::string& arg)
{
	std::cout << "Invalid argument '" << arg << "' was given." << '\n';
	std::cout << "Use the -h argument to list all valid arguments." << '\n';
}

Transition ArgsParserState::Process()
{
	for (const std::string& arg : _game.args)
	{
		if (arg == "-h" || arg == "--help")
			PrintHelp();
		else if (arg == "-a" || arg == "--about")
			PrintAbout();
		else
			PrintInvalid(arg);
		
		return Quit();
	}
	
	return Push<LogInitState>(_game);
}