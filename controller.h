#include<iostream>
#include<cstring>
#include<SDL.h>
#include "generateFrames.h"
class Pixie; 
class Controller
  {
  private:
   static Controller* control;
   SDL_Surface* screen;
   Pixie* landImg;
   Pixie* astroImg;
   Pixie* angryImg;
  // bool makevideo= false;
  // bool done= false;
  // bool freshframe= false;
   Controller();
   Controller( const Controller&);
   Controller& operator=(const Controller&);
   ~Controller();
   void draw(SDL_Surface* image, SDL_Surface screen, float x= 0.0, float y= 0.0);  void animation();
   bool update();
   void initializePixie();
};  
    	


   public:
    static Controller* getInstance();
    void init();
    void initPixie(const unsigned int& width, const unsigned& height); 
    void draw();
    void animation();
  };
 

