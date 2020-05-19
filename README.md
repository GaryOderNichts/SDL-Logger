### SDL Logger
Print debug text to Screen  

# Example usage:
```c
SDL_Init(SDL_INIT_VIDEO);
TTF_Init();

SDL_Window* window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

SDL_ConsoleInit(window);

for (int i = 0; i < 100; i++)
    SDL_ConsolePrintf("Hello %d", i);

SDL_ConsoleUninit();

SDL_DestroyWindow(window);

TTF_Quit();
SDL_Quit();
```

# Note:
Adjusting MAX_LINES and MAX_CHARS_PER_LINE may be required  
Defining GNU_SOURCE may be required  