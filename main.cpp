#include "controller.h"
#include <iostream>
#include <string>

const float X_VELOCITY = 100.0;
const unsigned int DT = 17u;
const unsigned int WIDTH = 854u;
const unsigned int HEIGHT = 480u;

int main()
{
    try
    {
        bool makeVideo = true;
        GameController::getInstance()->init();
        GameController::getInstance()->animation(WIDTH, HEIGHT, X_VELOCITY, DT, makeVideo);
    
        delete GameController::getInstance();
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
  
