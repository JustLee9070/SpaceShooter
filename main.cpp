#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(){

    //window and renderer
    SDL_Init(SDL_INIT_VIDEO);
    float WIDTH = 800.0f, HEIGHT = 600.0f;
    SDL_Window* window = SDL_CreateWindow("Space Shooter", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Texture* playerShipTex = IMG_LoadTexture(renderer, "assets/images/playerShip.png");
    SDL_Texture* playerShipDestructTex = IMG_LoadTexture(renderer, "assets/animation/playerShipDestruct.png");

    //player ship parameters
    float playerShipX, playerShipY, playerShipSize, playerShipHealth, playerShipSpeed, playerShipDamage;

    srand(static_cast<unsigned>(time(nullptr)));

    //enemy ship parameters
    struct enemyShip
    {
        float x, y, size;
    };
    std::vector<enemyShip> enemyShips;
    

    //bullet parameters
    struct bullet
    {
        float x, y, sizeX, sizeY, speed, damage;
    };
    std::vector<bullet> bullets;
    float fireCooldown = 0.20f;
    float fireTimer = 0.0f;

    struct star
    {
        float x, y, size, speed;
    };
    std::vector<star> stars;


    //game parameters
    Uint64 prevTime;
    bool running = true, gameOver = false, destroying = false;
    int destroyFrame = 0;
    float destroyTimer = 0.0f;

    const int destroyFrameCount = 16;
    const float destroyFrameTime = 0.08f;

    const int destroyFrameWidth = 256;
    const int destroyFrameHeight = 256;
    const int destroyColumns = 4;

    //reset function
    auto resetGame = [&](){

        playerShipSize = 75.0f;
        playerShipX = (WIDTH - playerShipSize) / 2.0f;
        playerShipY = (HEIGHT - playerShipSize) - 10.0f;
        playerShipHealth = 100.0f;
        playerShipDamage = 20.0f;
        playerShipSpeed = 200.0f;

        bullets.clear();
        fireTimer = 0.0f;

        destroying = false;
        destroyFrame = 0;
        destroyTimer = 0.0f;

        stars.clear();
        for(int i = 0; i < 100; i++)
        {
            
            star newStar;

            newStar.x = static_cast<float>(rand() % static_cast<int>(WIDTH));
            newStar.y = static_cast<float>(rand() % static_cast<int>(HEIGHT));

            newStar.size = static_cast<float>((rand() % 3) + 1);
            newStar.speed = static_cast<float>((rand() % 150) + 50);

            stars.push_back(newStar);

        }

        prevTime = SDL_GetTicks();

    };    

    resetGame();

    //main game loop
    while (running)
    {
        SDL_Event event;
        
        while (SDL_PollEvent(&event))
        {
            if (SDL_EVENT_QUIT == event.type)
            {
                running = false;
            }
        }
        
        //delta time calculation
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - prevTime) / 1000.0f;
        prevTime = currentTime;

        //ship controls 
        const bool *keyboardState = SDL_GetKeyboardState(nullptr);
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            playerShipX -= playerShipSpeed * deltaTime;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            playerShipX += playerShipSpeed * deltaTime;
        }

        //to keep ship within the window
        if(playerShipX <= 0)
        {
            playerShipX = 0;
        }
        if (playerShipX >= WIDTH - playerShipSize)
        {
            playerShipX = WIDTH - playerShipSize;
        }
        

        //shooting
        fireTimer -= deltaTime;
        if (keyboardState[SDL_SCANCODE_SPACE] && fireTimer <= 0.0f)
        {
            bullet newBullet;
            newBullet.sizeX = 2.0f;
            newBullet.sizeY = 20.0f;
            newBullet.speed = 500.0f;
            newBullet.damage = playerShipDamage;

            newBullet.x = playerShipX + (playerShipSize / 2.0f) - (newBullet.sizeX / 2.0f);
            newBullet.y = playerShipY - newBullet.sizeY;

            bullets.push_back(newBullet);

            fireTimer = fireCooldown;

        }
        
        for(auto &b : bullets)
        {
            b.y -= b.speed * deltaTime;
        }
        for (int i = bullets.size() - 1; i >= 0 ; i--)
        {
            if(bullets[i].y + bullets[i].sizeY < 0)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        //background stars
        for(auto &s : stars)
        {
            s.y += s.speed * deltaTime;

            if(s.y > HEIGHT)
            {
                s.y = -s.size;
                s.x = static_cast<float>(rand() % static_cast<int>(WIDTH));
            }

        }

        //destruction animation
        

        //enemyships

        //enemyship to bullet interaction
        
        //rendering
        SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        for(const auto &b : bullets)
        {
            SDL_FRect bulletRect = {b.x, b.y, b.sizeX, b.sizeY};
            SDL_RenderFillRect(renderer, &bulletRect);
        }

        SDL_FRect playerShip = {playerShipX, playerShipY, playerShipSize, playerShipSize};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(const auto &s : stars)
        {
            SDL_FRect starRect = {s.x, s.y, s.size, s.size};

            if(!SDL_HasRectIntersectionFloat(&starRect, &playerShip))
            {
                SDL_RenderFillRect(renderer, &starRect);
            }

        }
        
        SDL_RenderTexture(renderer, playerShipTex, nullptr, &playerShip);

        SDL_RenderPresent(renderer);

    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}