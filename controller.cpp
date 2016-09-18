#include "controller.h"
#include "generateFrames.h"
#include<iostream>
#include<string>

const float BOTTOM_LANDING = 20;

GameController* GameController::instance = NULL;
 
GameController:: GameController(): screen(NULL), landImg(NULL), astroImg(NULL), roverImg(NULL)
{}

GameController::~GameController() 
{
    SDL_FreeSurface(screen);
    delete landImg;
    delete astroImg;
    delete roverImg;
}

GameController* GameController::getInstance() 
{
  if(!instance){
    instance = new GameController;
  }
  return instance;
}

void GameController::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
    }
    atexit(SDL_Quit);
}

void GameController::animation(const unsigned int& width, const unsigned int& height, const float& velocity,
                               const unsigned int& DT, const bool makeVideo)
{
    screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);
    if (screen == NULL) {
      throw std::string("Unable to set video mode: ")+SDL_GetError();
    }
    
    landImg = new Pixie(0.0, 0.0, 0.0);
    astroImg = new Pixie(470.0, 0.0, velocity);
    roverImg = new Pixie(0, screen->h - BOTTOM_LANDING, -velocity*1.2);
    
    landImg->loadPixie("images/marsland.png", false);
    
    astroImg->setColor(0, 0, 0);
    astroImg->loadPixie("images/astronaut.png", true);
    
    astroImg->setColor(91, 155, 213);
    roverImg->loadPixie("images/rover.png", true);
    
    SDL_Event event;
    bool done = false;
    bool freshFrame = false;
    
    GenerateFrames genFrames(screen);
        
    while (!done) {
      while ( SDL_PollEvent(&event) ) {
        if (event.type == SDL_QUIT) done = true;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        }
      }
      
      bool update = updateScreen(DT);
      if(update){
          if((astroImg->getY() <= (screen->h - BOTTOM_LANDING - astroImg->getPixieImage()->h))){
              astroImg->movePos(DT, 1.8);
              freshFrame = true;
          }        
          else {
              //Move rover here
              roverImg->movePos(DT, 0);
              freshFrame = true;
          }
       
          if(freshFrame)
          {
            freshFrame = false;
            
            draw(landImg->getPixieImage(), screen, landImg->getX(), landImg->getY());
            draw(astroImg->getPixieImage(), screen, astroImg->getX(), astroImg->getY());
            draw(roverImg->getPixieImage(), screen, roverImg->getX() - roverImg->getPixieImage()->h, roverImg->getY() - roverImg->getPixieImage()->h);
            
            SDL_Flip(screen);
            
            if(makeVideo)
            {
                genFrames.makeFrame();
            }
          }
       }
    }
}

void GameController::draw(SDL_Surface* image, SDL_Surface* screen, float x, float y)
{
    Uint16 w = image->w;
    Uint16 h = image->h;
    Sint16 xCoord = static_cast<Sint16>(x);
    Sint16 yCoord = static_cast<Sint16>(y);
    SDL_Rect src = { 0, 0, w, h };
    SDL_Rect dest = {xCoord, yCoord, 0, 0 };
    SDL_BlitSurface(image, &src, screen, &dest);
}

bool GameController::updateScreen(const unsigned int& DT)
{
    bool elapsed = false;
    static unsigned int remainder = 0u;
    static unsigned int currentTicks = 0u;
    static unsigned int prevTicks = SDL_GetTicks();
    currentTicks = SDL_GetTicks();
    unsigned int elapsedTicks = currentTicks - prevTicks + remainder;

    if( elapsedTicks > DT ) {
        elapsed = true;
        prevTicks = currentTicks;
        remainder = elapsedTicks - DT;
    }
    return elapsed;
}


    

    
