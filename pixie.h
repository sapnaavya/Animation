#include<iostream>
#include<csrting>
#include<SDL.h>
#include<SDL_image.h>
#include "generateFrames.h"

class pixie
  {
   private:
    float x_axis;
    float y_axis;
    int red;
    int green;
    int blue;
   // float slope;
    SDL_Surface* image;
    SDL_Surface* LoadImage(const std::string& filename, bool setColorKey);
   // float incr_x=0.5;
   // float x_velocity = 300;
   // const unsigned int DT = 17u;

   public:
    pixie();
    Pixie(const float&x, const&y, const float& slopee, bool setColorKey);
    Pixie(const Pixie&);
    Pixie& operator=(const Pixie&);
    void setPosition(const float& x, const float& y);
    void setColor(const int&r, const int&g, const int&b);
    void setImagePath(const std::string& filename, bool setColorKey);
    SDL_Surface* getPixieImage();
    float getX();
    float getY();
    const std:: string& getName();
    ~pixie();
    void updateCoordinate(const float& velocity, const unsigned int& frames );
    void initialize();
    void init();
    
  };
