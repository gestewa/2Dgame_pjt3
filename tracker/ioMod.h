#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IoMod
{
public:
  static IoMod &getInstance();
  ~IoMod();
  SDL_Texture *readTexture(const std::string &filename);
  SDL_Surface *readSurface(const std::string &filename);
  void writeText(const std::string &, int, int) const;
  void writeText(const std::string &, int, int, const SDL_Color &) const;
  void writeText(const std::string &, int, int, int r, int g, int b) const;
  SDL_Renderer *getRenderer() const { return renderer; }
  IoMod(const IoMod &) = delete;
  IoMod &operator=(const IoMod &) = delete;

private:
  int init;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Color textColor;
  IoMod();
  void writeTextHelper(const std::string &msg, int x, int y, const SDL_Color &c) const;
};
