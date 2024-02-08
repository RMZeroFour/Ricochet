#pragma once

#include "game/texture.h"

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <unordered_map>

class TextureCache
{
public:
	TextureCache() : _textures{} { }

public:
	void Register(const std::string& key, SDL_Texture* tex)
	{
		_textures.emplace(key, TexturePtr{ tex });
	}
	
	Texture Fetch(const std::string& key) const
	{
		const TexturePtr& ptr{ _textures.at(key) };
		
		int w, h;
		SDL_QueryTexture(ptr.get(), nullptr, nullptr, &w, &h);
		
		return { ptr.get(), 0, 0, w, h };
	}
	
	Texture Fetch(const std::string& key, int x, int y, int w, int h) const
	{
		const TexturePtr& ptr{ _textures.at(key) };
		return { ptr.get(), x, y, w, h };
	}
	
	void Unregister(const std::string& key)
	{
		_textures.erase(key);
	}
	
	void UnregisterAll()
	{
		_textures.clear();
	}
	
private:
	struct SDL_TextureDeleter
	{
		void operator()(SDL_Texture* tex) { SDL_DestroyTexture(tex); }
	};
	using TexturePtr = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>;

	std::unordered_map<std::string, TexturePtr> _textures;
};