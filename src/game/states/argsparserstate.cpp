#include "game/states/argsparserstate.h"

#include "generated/buildinfo.h"
#include "game/states/loginitstate.h"

#include <argh.h>

#include <iostream>

namespace
{
	void PrintHelp()
	{
		std::cout << "Options:" << '\n';
		std::cout << "-h/--help" << "\t\t" << "Print commandline help and exit" << '\n';
		std::cout << "-a/--about" << "\t\t" << "Print program metadata and exit" << '\n';
		std::cout << "-l/--log <file>" << "\t\t" << "Redirect log output to <file>" << '\n';
	}

	void PrintAbout()
	{
		std::cout << Ricochet_NAME << " v" << Ricochet_VERSION << '\n';
		std::cout << Ricochet_DESCRIPTION << '\n';
		std::cout << "Project Website: " << Ricochet_HOMEPAGE_URL << '\n';
		std::cout << "Maintained By: " << Ricochet_MAINTAINER << '\n';
	}
}

Transition ArgsParserState::Process()
{
	_game.args.add_params({ "-l", "--log" });
	_game.args.parse(_argc, _argv);

	if (_game.args[{ "-h", "--help" }])
	{
		PrintHelp();
		return Quit();
	}
	else if (_game.args[{ "-a", "--about" }])
	{
		PrintAbout();
		return Quit();
	}

	return Switch<LogInitState>(_game);
}