#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "generateFrames.h"

 const unsigned int WIDTH = 854u;
 const unsigned int HEIGHT = 480u;

 int main()
 {
 try
   {
   Pixie p1;
   Controller c1;
   p1.init();
   SDL_Event event;
   GenerateFrames genFrames(screen);
   c1.move();
   }
 catch(const std::string& msg)
  {
    std::cout << msg << std::endl; 
   }
 catch(...) 
  {
    std::cout << "oops" << std::endl;
  }
 }
  
