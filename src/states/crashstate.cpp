#include "states/crashstate.h"

#include "buildinfo.h"
#include "helpers/log_wrappers.h"

#include <SDL2/SDL_messagebox.h>

#include <string>

namespace
{
	void ShowCrashMessageBox(GameData& _game)
	{
		std::string message
		{
			"Sorry, " Ricochet_NAME " has crashed due to an error.\n"
			"Please check the logs for more information." 
		};
		
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatality!", message.c_str(),
			_game.sdl.has_value() ? _game.sdl.value().window : nullptr);
	}
	
	void OutputCrashLogs(GameData& _game)
	{
		std::string message
		{
			"Oh no, the game has suffered an unrecoverable"
			" fatal condition and now must terminate!"
		};
		LOG_ERROR(_game.logger, message);
		
		message = "In other words, there was an error.";
		LOG_ERROR(_game.logger, message);
		
		message = "We're trying our best to avoid situations"
		          " like these for players, but evidently we"
		          " missed something.";
		LOG_ERROR(_game.logger, message);
	
		message = "Could you please report this to us so we"
		          " can get to fixing it as soon as possible?";
		LOG_ERROR(_game.logger, message);
		
		message = "Just open up an issue at {}, with the title"
		          " \"The game died lol\", a short description of"
		          " the crash, and the contents of your log file."
		          " and we'll get back to you.";
		LOG_ERROR(_game.logger, message, Ricochet_HOMEPAGE_URL);
	
		message = "Thank you for playing {}.";
		LOG_ERROR(_game.logger, message, Ricochet_NAME);
	}
}

Transition CrashState::Process()
{
	OutputCrashLogs(_game);
	ShowCrashMessageBox(_game);
	
	return Quit();
}