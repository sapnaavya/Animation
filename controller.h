#include "pixie.h"
#include<SDL.h>

class GameGameController
{
    public:
        static GameController* getInstance();
        ~GameController();
        
        void init();
        void animation(const unsigned int& width, const unsigned int& height, const float& velocity, const unsigned int& DT, const bool makeVideo);

    private:
       GameController();
       GameController(const GameController&);
       GameController& operator=(const GameController&);
       
       static GameController* instance;
       SDL_Surface* screen;
       Pixie* landImg;
       Pixie* astroImg;
       Pixie* roverImg;
       
       void draw(SDL_Surface* image, SDL_Surface screen, float x= 0.0, float y= 0.0);  void animation();
       bool updateScreen(const unsigned int& DT);
};

