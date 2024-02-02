#pragma once

#include <SDL2/SDL_rect.h>

// Aligns the center of 'rect' with the center of 'ref'
inline void AlignCenterTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x + (ref.w - rect.w) / 2;
	rect.y = ref.y + (ref.h - rect.h) / 2;
}

// Aligns the top-left corner of 'rect' with the top-left corner of 'ref'
inline void AlignTopLeftTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x;
	rect.y = ref.y;
}

// Aligns the top-right corner of 'rect' with the top-right corner of 'ref'
inline void AlignTopRightTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x + ref.w - rect.w;
	rect.y = ref.y;
}

// Aligns the bottom-left corner of 'rect' with the bottom-left corner of 'ref'
inline void AlignBottomLeftTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x;
	rect.y = ref.y + ref.h - rect.h;
}

// Aligns the bottom-right corner of 'rect' with the bottom-right corner of 'ref'
inline void AlignBottomRightTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x + ref.w - rect.w;
	rect.y = ref.y + ref.h - rect.h;
}

// Aligns the top edge of 'rect' with the top edge of 'ref'
inline void AlignTopTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.y = ref.y;
}

// Aligns the bottom edge of 'rect' with the bottom edge of 'ref'
inline void AlignBottomTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.y = ref.y + ref.h - rect.h;
}

// Aligns the left edge of 'rect' with the left edge of 'ref'
inline void AlignLeftTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x;
}

// Aligns the right edge of 'rect' with the right edge of 'ref'
inline void AlignRightTo(SDL_Rect& rect, const SDL_Rect& ref)
{
	rect.x = ref.x + ref.w - rect.w;
}

// Sets the top-left corner of 'rect' to the specified coordinates (x, y)
inline void SetTopLeft(SDL_Rect& rect, int x, int y)
{
	rect.x = x;
	rect.y = y;
}

// Sets the top-right corner of 'rect' to the specified coordinates (x, y)
inline void SetTopRight(SDL_Rect& rect, int x, int y)
{
	rect.x = x - rect.w;
	rect.y = y;
}

// Sets the bottom-left corner of 'rect' to the specified coordinates (x, y)
inline void SetBottomLeft(SDL_Rect& rect, int x, int y)
{
	rect.x = x;
	rect.y = y - rect.h;
}

// Sets the bottom-right corner of 'rect' to the specified coordinates (x, y)
inline void SetBottomRight(SDL_Rect& rect, int x, int y)
{
	rect.x = x - rect.w;
	rect.y = y - rect.h;
}

// Sets the center of 'rect' to the specified coordinates (x, y)
inline void SetCenter(SDL_Rect& rect, int x, int y)
{
	rect.x = x - rect.w / 2;
	rect.y = y - rect.h / 2;
}

// Increases the size of 'rect' by the specified width and height
inline void Inflate(SDL_Rect& rect, int width, int height)
{
	rect.x -= width / 2;
	rect.y -= height / 2;
	rect.w += width;
	rect.h += height;
}

// Translates 'rect' by the specified x and y values
inline void Translate(SDL_Rect& rect, int x, int y)
{
	rect.x += x;
	rect.y += y;
}

// Scales the size of 'rect' by the specified factor
inline void Scale(SDL_Rect& rect, float scaleFactor)
{
	rect.w = static_cast<int>(rect.w * scaleFactor);
	rect.h = static_cast<int>(rect.h * scaleFactor);
}