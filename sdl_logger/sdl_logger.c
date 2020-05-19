/**
 * SDL_Logger by GaryOderNichts
 */ 

#include <stdlib.h>
#include <stdio.h>

#include "sdl_logger.h"

#include "../font/font.h"

#define MAX_LINES 21
#define MAX_CHARS_PER_LINE 90

static char* consoleArray[MAX_LINES];

TTF_Font* consoleFont;
SDL_Renderer* console_renderer;

void SDL_ConsoleInit(SDL_Window* window)
{
    SDL_RWops* fontops = SDL_RWFromConstMem(font, font_size);
    consoleFont = TTF_OpenFontRW(fontops, 1, 24);

    console_renderer = SDL_CreateRenderer(window, -1, 0);

    memset(consoleArray, 0, MAX_LINES * sizeof(char*));
}

void SDL_ConsolePrintf(const char *format, ...)
{
	char * tmp = NULL;

	va_list va;
	va_start(va, format);
	if((vasprintf(&tmp, format, va) >= 0) && tmp)
	{
        if(consoleArray[0])
            free(consoleArray[0]);

        for(int i = 1; i < MAX_LINES; i++)
            consoleArray[i-1] = consoleArray[i];

        if(strlen(tmp) > MAX_CHARS_PER_LINE)
            tmp[MAX_CHARS_PER_LINE] = 0;

        consoleArray[MAX_LINES - 1] = malloc(strlen(tmp) + 1);
        if(consoleArray[MAX_LINES - 1])
            strcpy(consoleArray[MAX_LINES-1], tmp);
	}
	va_end(va);

    SDL_RenderClear(console_renderer);

	for(int i = 0; i < MAX_LINES; i++)
    {
        if(consoleArray[i])
        {
            SDL_Surface* messageSurface = TTF_RenderText_Solid(consoleFont, consoleArray[i], (SDL_Color) {0, 255, 0, 255});
            SDL_Texture* message = SDL_CreateTextureFromSurface(console_renderer, messageSurface);
            SDL_Rect rect;
            rect.x = 10;
            rect.y = messageSurface->h * i + 10;
            rect.h = messageSurface->h;
            rect.w = messageSurface->w;
            SDL_RenderCopy(console_renderer, message, NULL, &rect);
            SDL_DestroyTexture(message);
            SDL_FreeSurface(messageSurface);
        }
    }

    SDL_RenderPresent(console_renderer);
}

void SDL_ConsoleUninit()
{
    for(int i = 0; i < MAX_LINES; i++)
    {
        if(consoleArray[i])
            free(consoleArray[i]);
    }

    SDL_DestroyRenderer(console_renderer);
}