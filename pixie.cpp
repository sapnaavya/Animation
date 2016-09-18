#include "pixie.h"
#include<iostream>
#include<SDL_image.h>

Pixie::Pixie() :x_axis(0.0), y_axis(0.0), velocity(0.0), red(255), green(255), blue(255), image(NULL)
{}

Pixie::Pixie(const float& x, const float& y, const float& speed) : x_axis(x), y_axis(y), velocity(speed), red(255), green(255), blue(255), image(NULL)
{}

Pixie::~Pixie()
{
    SDL_FreeSurface(image);
    image = NULL;    
}

void Pixie::setCoordinates(const float& x, const float& y)
{
    x_axis = x;
    y_axis = y;
}

void Pixie::setColor(const int& r, const int& g, const int& b)
{
    red = r;
    green = g;
    blue = b;
}

void Pixie::loadPixie(const std:: string& filename, bool bColorKey)
{
    image = getImage(filename, bColorKey);
}

SDL_Surface* Pixie::getImage(const std::string& filename, bool bColorKey)
{
    SDL_Surface* temp = IMG_Load(filename.c_str());
    if (temp == NULL) 
    {
        throw std::string("Unable to load bitmap.")+SDL_GetError();
    }
    if (bColorKey)
    {
        Uint32 colorkey = SDL_MapRGB(temp->format, red, green, blue);
        SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    }
    
    SDL_Surface* image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return image;
}

SDL_Surface* Pixie::getPixieImage()
{
    return image;
}

float Pixie::getX()
{
    return x_axis;
}

float Pixie::getY()
{
    return y_axis;
}

void Pixie::movePos(const unsigned int& rate, const float& yFactor)
{
    float incr = velocity*rate* 0.001;
    x_axis-= incr;
    y_axis+= yFactor*incr;
}


