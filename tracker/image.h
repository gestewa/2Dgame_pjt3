#ifndef IMAGE__H
#define IMAGE__H

#include <SDL.h>
#include <iostream>
#include <string>

class Image {
 public:
  Image(SDL_Surface *);
  Image() = delete;

  void regenerateTexture();
  void draw(int x, int y) const;
  void draw(int x, int y, float scale) const;
  void draw(int sx, int sy, int dx, int dy) const;

  inline int getWidth() const { return surface->w; }
  inline int getHeight() const { return surface->h; }
  SDL_Surface *getSurface() const { return surface; }

 private:
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect view;
};

#endif
