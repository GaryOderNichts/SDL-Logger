/**
 * SDL_Logger by GaryOderNichts
 */ 

#ifndef SDL_LOGGER_H
#define SDL_LOGGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

void SDL_ConsoleInit(SDL_Window* window);

void SDL_ConsolePrintf(const char *format, ...);

void SDL_ConsoleUninit();

#endif