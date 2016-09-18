#include <string>
#include <SDL.h>
#include <SDL_image.h>

class GenerateFrames {
public:
  GenerateFrames(SDL_Surface* s) : 
    screen(s), USERNAME("sapnapg"), MAX_FRAMES(500), frameCount(0) {}
  void makeFrame();
  unsigned int getFrameCount() const { return frameCount; }
  unsigned int getMaxFrames() const { return MAX_FRAMES; }
private:
  SDL_Surface* screen;
  const std::string USERNAME;
  const int unsigned MAX_FRAMES;
  unsigned int frameCount;
  GenerateFrames(const GenerateFrames&);
  GenerateFrames& operator=(const GenerateFrames&);
};
