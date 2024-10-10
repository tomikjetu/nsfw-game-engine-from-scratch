#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>
#include <../../SDL2/include/SDL2/SDL_ttf.h>
#include <../../SDL2/include/SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

#include <Windows.h>
#include <time.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Vector2d.hpp"

void spawn(RenderWindow &window, std::vector<Entity> &Entities)
{
    int randomX, randomY;
    randomX = rand() % 1280;
    if (randomX + 128 > 1280)
        randomX -= 128;
    randomY = rand() % 720;
    if (randomY + 128 > 720)
        randomY -= 128;
    for (Entity e : Entities)
    {
        bool a = e.pos.x <= randomX && e.pos.x + 128 >= randomX;
        bool b = e.pos.y <= randomY && e.pos.y + 128 >= randomY;
        bool c = randomX <= e.pos.x && randomX >= e.pos.x - 128;
        bool d = randomY <= e.pos.y && randomY >= e.pos.y - 128;
        if (
            (a && b) || (c && d) || (a && d) || (c && b))
        {
            spawn(window, Entities);
            return;
        }
    }
    Entities.push_back(Entity(window.loadTexture("../res/images/target.png"), Vector2d(randomX, randomY), Scaler(1, 1)));
}

void drawScore(RenderWindow window, std::string text)
{
    TTF_Font *Sans = TTF_OpenFont("../res/fonts/Sans.ttf", 24);

    SDL_Color White = {0, 0, 0};

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);

    SDL_Texture *Message = SDL_CreateTextureFromSurface(window.getRenderer(), surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    TTF_SizeText(Sans, text.c_str(), &Message_rect.w, &Message_rect.h);

    SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Sans);
}

bool hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "VIDEO INIT ERROR: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG INIT ERROR: " << SDL_GetError() << std::endl;
    if (TTF_Init() == -1)
        std::cout << "TTF INIT ERROR: " << SDL_GetError() << std::endl;
    if (SDL_Init(SDL_INIT_AUDIO) > 0)
        std::cout << "AUDIO INIT ERROR: " << SDL_GetError() << std::endl;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Chunk *effect1 = Mix_LoadWAV("../res/sounds/effect1.wav");
    Mix_Chunk *effect2 = Mix_LoadWAV("../res/sounds/effect2.wav");
    Mix_Chunk *effect3 = Mix_LoadWAV("../res/sounds/effect3.wav");
    Mix_Chunk *milestone69 = Mix_LoadWAV("../res/sounds/milestone69.wav");

    SDL_ShowCursor(SDL_DISABLE);
    RenderWindow window("PUSSY DESTROYER", 1280, 720);
    int maxTargets = 40;

    HWND windowHandle = GetConsoleWindow();
    ShowWindow(windowHandle, SW_HIDE);

    Entity Cursor(window.loadTexture("../res/images/asian_dick.png"), Vector2d(0, 0), Scaler(0.5f, 0.5f));
    bool gameRunning = true;

    SDL_Event event;

    int mouseX, mouseY;

    int score = 0;

    std::vector<Entity> Entities;
    std::vector<Entity> Particles;
    srand(time(0));
    spawn(window, Entities);
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            if (event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int i = 0;
                for (Entity e : Entities)
                {
                    if (e.pos.x <= mouseX && e.pos.x + 128 >= mouseX && e.pos.y <= mouseY && e.pos.y + 128 >= mouseY)
                    {
                        Entities.erase(Entities.begin() + i);
                        SDL_DestroyTexture(e.getTex());
                        spawn(window, Entities);
                        score++;
                        if (hasEnding(std::to_string(score), "69"))
                        {
                            int limit = 15;
                            if (score == 6969)
                                limit = 69;
                            Mix_PlayChannel(-1, milestone69, 0);
                            for (int j = 0; j <= limit; j++)
                                Particles.push_back(Entity(window.loadTexture("../res/images/particle.png"), Vector2d(mouseX + rand() % 250 - 125, mouseY + rand() % 250 - 125), Scaler(1, 1)));
                        }

                        if (score % 10 == 0)
                        {
                            Mix_PlayChannel(-1, effect2, 0);
                            if (Entities.size() <= maxTargets && rand() % 10 == 6)
                            {
                                spawn(window, Entities);
                            }
                        }
                        else if (rand() % 2 == 0)
                            Mix_PlayChannel(-1, effect1, 0);
                        else
                            Mix_PlayChannel(-1, effect3, 0);

                        if (score == 100)
                        {
                            srand(time(0));
                            Cursor.setTex(window.loadTexture("../res/images/white_dick.png"));
                            spawn(window, Entities);
                        }
                        if (score == 1000)
                        {
                            spawn(window, Entities);
                            Cursor.setTex(window.loadTexture("../res/images/black_cock.png"));
                        }
                    }
                    i++;
                }
            }
        }

        Cursor.pos.set(Vector2d((float)mouseX * (1 / Cursor.getScaler().x), (float)mouseY * (1 / Cursor.getScaler().y)));

        window.clear();

        for (Entity e : Entities)
        {
            window.render(e);
        }
        window.render(Cursor);
        drawScore(window, "score: " + std::to_string(score));

        int i = 0;
        for (Entity Particle : Particles)
        {
            window.render(Particle);
            if (rand() % 10000 == 69)
                Particles.erase(Particles.begin() + i);
            i++;
        }

        SDL_SetRenderDrawColor(window.getRenderer(), 0xf9, 0x82, 0x9b, 255);
        window.display();
    }

    Mix_CloseAudio();
    Mix_FreeChunk(effect1);
    Mix_FreeChunk(effect2);
    Mix_FreeChunk(effect3);
    Mix_FreeChunk(milestone69);
    window.cleanUp();
    SDL_Quit();
    return 0;
}