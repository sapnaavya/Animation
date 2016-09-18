#include<iostream>
#include<cstring>
#include<SDL.h>
#include "generateFrames.h"
#include "pixie.h"

 Pixie :: Pixie():x_pos(0.0),y_pos(0.0),image(NULL)
  {
  }

 Pixie ::Pixie(const float& x, const float& y, , const std::string& filename, bool setColorKe):xpos(x),xpos(y),image(loadImage(filename, setColorKey)
 {
 }
 
 Pixie::~Pixie()
  {
   SDL_FreeSurface(image);
   image = NULL;
   } 
 void Pixie :: setPosition(const float& x, const float& y, const float& angle)
   {
   x_axis = x;
   y_axis = y;
   }
 void Pixie :: setColor(const int& r, const int& g, const int& b)
  {
  red = r;
  green =g;
  blue = b;
  }
 void Pixie ::setImagePath(const std:: string& filename, bool setColorkey)
  {
   image = loadImage(filename, setColorKey);
  }
 SDL_Surface* Pixie ::loadImage(const std::string& filename, bool setColorKey)
  {
  SDL_Surface* temp = IMG_Load(filename.c_str());
   if (temp == NULL) 
  {
    throw std::string("Unable to load bitmap.")+SDL_GetError();
  }
  if ( setColorKey )
   {
    Uint32 colorkey = SDL_MapRGB(temp->format, 0,0,0);
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
   }
  SDL_Surface *image = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return image;
  }
  SDL_Surface* Pixie::getPixieImage()
  {
  return image;
  }
  float Pixie:: getX()
  {
  return x_axis;
  }
  float Pixie::getY()
  {
  return y_axis;
  }
  const std::string& getName()
  {
   return name;
  }
 void Pixie:: updateCoordinate(const float& velocity, const unsigned int& frames)
  {
  float incr = velocity* frames* 0.01;
  x_axis-= incr;
  y_axis+= incr
  }


