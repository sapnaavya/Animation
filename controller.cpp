#include<iostream>
#include<cstring>
#include "generateFrames.h"
#include "Controller.h"

const float X_VELOCITY = 200.0;
/ Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***

Controller* Controller ::instance =NULL;
 
Controller:: Controller(): screen(NULL), background(NULL), astronaut(NULL),rover(NULL)
 {
  
 }
  Controller* Controller::getInstance() 
 {
  if(!instance)
    instance = new Controller;
    return instance;
  
 }
  delete getIntance();
 
 void Controller:: init()
 {
if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
  }
  atexit(SDL_Quit);
 }
 
 void Controller::initPixie( const unsigned int& width, const unsigned int& height)
 {
 screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);
    if (screen == NULL) {
      throw std::string("Unable to set video mode: ")+SDL_GetError();
    }
   landImg = new Pixie("marsland",0,0,0,0,"images/marsland.png",false);
   astroImg = new Pixie("shuttle",470,0,0,0,"images/astronaut.png",true);
}
void Controller::draw(SDL_Surface* image, SDL_Surface* screen, float x, float y)
 {
Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(x);
  Sint16 yCoord = static_cast<Sint16>(y);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);
}
---------------------
void Controller::drawOnScreen()
--------------------- 
----------------------
void Controller::animation()
 {
 SDL_Event event;
    bool done = false;

    unsigned int i = 0;
    while ( !done) {
      while ( SDL_PollEvent(&event) ) {
        if (event.type == SDL_QUIT) done = true;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        }
      }
--------------------------------
bool Controller:: update()
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


    

    
