#include<string>
#include<SDL.h>

class Pixie
{
    public:
        Pixie();
        Pixie(const float& x, const float& y, const float& speed);
        Pixie(const Pixie&);
        Pixie& operator=(const Pixie&);
        ~Pixie();
        
        void setCoordinates(const float& x, const float& y);
        void setColor(const int&r, const int&g, const int&b);
        void loadPixie(const std::string& filename, bool bColorKey = false);
        
        SDL_Surface* getPixieImage();
        float getX();
        float getY();
        
        void movePos(const unsigned int& rate, const float& yFactor);
    
    private:
        float x_axis;
        float y_axis;
        float velocity;
        int red;
        int green;
        int blue;
        SDL_Surface* image;
        SDL_Surface* getImage(const std::string& filename, bool bColorKey = false);
};
