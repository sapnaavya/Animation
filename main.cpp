// Brian Malloy and Chris Malloy
// This example illustrates an approach to capturing 60 frames
// per second to form a smooth, efficient animation.
// The resulting frame rate of the generated movie exactly matches 
// the frame rate captured in the program below.
// By setting makeVideo to true on line 88, frame capture begins at
// the beginning of the program and ends when the animation completes.

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "generateFrames.h"

const unsigned int WIDTH = 854u;
const unsigned int HEIGHT = 480u;

const float START_Y = 10.0;
const float INCR_X = 0.3;
const float X_VELOCITY = 150.0;

// Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
  }
  atexit(SDL_Quit);
}

SDL_Surface* getImage(const std::string& filename, bool setColorKey) {
  SDL_Surface *temp = 	IMG_Load(filename.c_str());
  if (temp == NULL) {
    throw std::string("Unable to load bitmap.")+SDL_GetError();
  }
  if ( setColorKey ) {
    Uint32 colorkey = SDL_MapRGB(temp->format, 255,255,255);
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  SDL_Surface *image = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return image;
}

void draw(SDL_Surface* image, SDL_Surface* screen, 
          float x = 0.0, float y = 0.0) {
  Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(x);
  Sint16 yCoord = static_cast<Sint16>(y);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);
}

bool update(float& x, float&y) {
  static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks < DT ) return false; // ***

  float incr = X_VELOCITY * DT * 0.001; // ***
  x += incr + 1;
  y += incr;

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  return true; // ***
}

int main() {
  try {
    init();
    SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_DOUBLEBUF);
    if (screen == NULL) {
      throw std::string("Unable to set video mode: ")+SDL_GetError();
    }
    SDL_Surface *mars = getImage("images/sapnapg.png", false);
    SDL_Surface *astronaut = getImage("images/astronaut.jpg", true);


    float x = -astronaut->w;
    float y = START_Y;
    SDL_Event event;
    bool makeVideo = false;
    bool done = false;
    bool freshFrame = false; // ***
    GenerateFrames genFrames(screen);
    while ( !done) {
      while ( SDL_PollEvent(&event) ) {
        if (event.type == SDL_QUIT) done = true;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        }
      }
      if ( y <= 406.0-astronaut->h ) {
        freshFrame = update(x,y);
      }
      else {
        makeVideo = false;
      }
    
      if(freshFrame){
        freshFrame=false;
        if ( makeVideo ) {
          genFrames.makeFrame();
        }
      }
      draw(mars, screen);
      draw(astronaut, screen, x, y);
      SDL_Flip(screen);
    }
    SDL_FreeSurface(mars);
    SDL_FreeSurface(astronaut);
  }
  catch(const std::string& msg) { std::cout << msg << std::endl;  }
  catch(...) { std::cout << "oops" << std::endl;  }
}
