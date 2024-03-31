#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Rect makeRectangle(int xPos, int yPos, int width, int height)
{
    SDL_Rect rect;
    rect.x = xPos;
    rect.y = yPos;
    rect.w = width;
    rect.h = height;

    return rect;
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Surface *citySurface = NULL;
    SDL_Texture *cityTexture = NULL;

    SDL_Surface *bardSurface = NULL;
    SDL_Texture *bardTexture = NULL;

    int running = 1;

    SDL_CreateWindowAndRenderer(900, 600, 0, &window, &renderer);

    if (window == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    if (renderer == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    SDL_SetWindowTitle(window, "Farm");

    citySurface = IMG_Load("./images/city.png");

    if (citySurface == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    cityTexture = SDL_CreateTextureFromSurface(renderer, citySurface);

    if (cityTexture == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    SDL_FreeSurface(citySurface);

    bardSurface = IMG_Load("./images/bard.png");

    if (bardSurface == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    bardTexture = SDL_CreateTextureFromSurface(renderer, bardSurface);

    if (bardTexture == NULL)
    {
        printf("Error: %s ", SDL_GetError());
        return -1;
    }

    SDL_FreeSurface(bardSurface);

    SDL_Rect bardRectDownSource[6];
    SDL_Rect bardRectLeftSource[6];
    SDL_Rect bardRectRightSource[6];
    SDL_Rect bardRectUpSource[6];

    int bardX = 0;

    for (int i = 0; i < 6; i++)
    {
        bardRectDownSource[i] = makeRectangle(bardX, 0, 50, 72);
        bardRectLeftSource[i] = makeRectangle(bardX, 72, 50, 72);
        bardRectRightSource[i] = makeRectangle(bardX, 144, 50, 72);
        bardRectUpSource[i] = makeRectangle(bardX, 216, 50, 72);

        bardX += 50;

    }    

    SDL_Rect bardRectDestination = makeRectangle(0, 0, 50, 72);

    SDL_Rect grassRectSource = makeRectangle(0, 0, 30, 30);

    SDL_Rect bushRectSource = makeRectangle(65, 30, 30, 30);

    SDL_Rect plantRectSource = makeRectangle(96, 1312, 30, 30);

    SDL_Rect tableRectSource = makeRectangle(160, 0, 256 - 162, 62);

    SDL_Rect tableRectDestination = makeRectangle(318, 350, 256 - 162, 62);

    SDL_Rect houseTopRectSource = makeRectangle(0, 735, 95, 832 - 735);

    SDL_Rect houseTopRectDestination = makeRectangle(350, 150, 95, 832 - 735);

    SDL_Rect houseDoorRectSource = makeRectangle(95, 735, 160 - 95, 800 - 735);

    SDL_Rect houseDoorRectDestination = makeRectangle(350, 245, 95, 800 - 735);

    SDL_Rect houseGardenRectSource = makeRectangle(95, 832, 255 - 95, 960 - 832);

    SDL_Rect houseGardenRectDestination = makeRectangle(318, 210, 255 - 95, 960 - 832);

    int frame = 0;

    int isMovingRight = 1;
    int isMovingLeft = 0;
    int isMovingDown = 0;
    int isMovingUp = 0;

    while (running)
    {
        SDL_Event event;

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            running = 0;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                isMovingRight = 1;
                isMovingLeft = 0;
                isMovingDown = 0;
                isMovingUp = 0;

                frame++;

                bardRectDestination.x += 10;

                if (SDL_HasIntersection(&bardRectDestination, &houseTopRectDestination))
                {
                    bardRectDestination.x -= 10;
                }

                if (bardRectDestination.x >= 850)
                {
                    bardRectDestination.x = 850;
                }

                if (frame == 5)
                {
                    frame = 0;
                }

                SDL_RenderCopy(renderer, bardTexture, &bardRectRightSource[frame], &bardRectDestination);
            }

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                isMovingRight = 0;
                isMovingLeft = 1;
                isMovingDown = 0;
                isMovingUp = 0;

                frame++;

                bardRectDestination.x -= 10;

                if (SDL_HasIntersection(&bardRectDestination, &houseTopRectDestination))
                {
                    bardRectDestination.x += 10;
                }

                if (bardRectDestination.x <= 0)
                {
                    bardRectDestination.x = 0;
                }

                if (frame == 5)
                {
                    frame = 0;
                }

                SDL_RenderCopy(renderer, bardTexture, &bardRectLeftSource[frame], &bardRectDestination);
            }

            if (event.key.keysym.sym == SDLK_UP)
            {
                isMovingRight = 0;
                isMovingLeft = 0;
                isMovingDown = 0;
                isMovingUp = 1;

                frame++;

                bardRectDestination.y -= 10;

                if (SDL_HasIntersection(&bardRectDestination, &houseTopRectDestination))
                {
                    bardRectDestination.y += 10;
                }

                if (bardRectDestination.y <= 0)
                {
                    bardRectDestination.y = 0;
                }

                if (frame == 5)
                {
                    frame = 0;
                }

                SDL_RenderCopy(renderer, bardTexture, &bardRectUpSource[frame], &bardRectDestination);
            }

            if (event.key.keysym.sym == SDLK_DOWN)
            {
                isMovingRight = 0;
                isMovingLeft = 0;
                isMovingDown = 1;
                isMovingUp = 0;

                frame++;

                bardRectDestination.y += 10;

                if (SDL_HasIntersection(&bardRectDestination, &houseTopRectDestination))
                {
                    if (bardRectDestination.y >= 85)
                    {
                        bardRectDestination.y -= 15;
                    }
                }

                if (bardRectDestination.y >= 600 - 72)
                {
                    bardRectDestination.y = 600 - 72;
                }

                if (frame == 5)
                {
                    frame = 0;
                }

                SDL_RenderCopy(renderer, bardTexture, &bardRectDownSource[frame], &bardRectDestination);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        for (int row = 0; row < 30; row++)
        {
            for (int col = 0; col < 20; col++)
            {

                SDL_Rect grassRectDestination = makeRectangle(30 * row, 30 * col, 30, 30);

                SDL_RenderCopy(renderer, cityTexture, &grassRectSource, &grassRectDestination);

                if (row % 3 == 0 && col % 2 == 0)
                {
                    SDL_Rect bushRectDestination = makeRectangle(30 * row, 30 * col, 30, 30);

                    SDL_RenderCopy(renderer, cityTexture, &bushRectSource, &bushRectDestination);
                }

                if (row > 20 && row < 29 && col > 5 && col < 13)
                {
                    SDL_Rect plantRectDestination = makeRectangle(30 * row, 30 * col, 30, 30);

                    SDL_RenderCopy(renderer, cityTexture, &plantRectSource, &plantRectDestination);
                }
            }
        }

        SDL_RenderCopy(renderer, cityTexture, &houseGardenRectSource, &houseGardenRectDestination);

        SDL_RenderCopy(renderer, cityTexture, &houseTopRectSource, &houseTopRectDestination);

        SDL_RenderCopy(renderer, cityTexture, &houseDoorRectSource, &houseDoorRectDestination);

        SDL_RenderCopy(renderer, cityTexture, &tableRectSource, &tableRectDestination);

        if (isMovingRight)
        {
            SDL_RenderCopy(renderer, bardTexture, &bardRectRightSource[frame], &bardRectDestination);
        }

        if (isMovingLeft)
        {
            SDL_RenderCopy(renderer, bardTexture, &bardRectLeftSource[frame], &bardRectDestination);
        }

        if (isMovingDown)
        {
            SDL_RenderCopy(renderer, bardTexture, &bardRectDownSource[frame], &bardRectDestination);
        }

        if (isMovingUp)
        {
            SDL_RenderCopy(renderer, bardTexture, &bardRectUpSource[frame], &bardRectDestination);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(cityTexture);

    SDL_DestroyTexture(bardTexture);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}