#include "image.h"
#include "drawable.h"
#include "ioMod.h"
#include "renderContext.h"
#include "viewport.h"

Image::Image(SDL_Surface *surf)
    : renderer(RenderContext::getInstance().getRenderer()),
      surface(surf),
      texture(nullptr),
      view{0, 0, surf->w, surf->h} {
  regenerateTexture();
}

void Image::regenerateTexture() {
  if (texture != nullptr) SDL_DestroyTexture(texture);
  RenderContext &renderContext = RenderContext::getInstance();
  texture = SDL_CreateTextureFromSurface(renderContext.getRenderer(), surface);
}

void Image::draw(int x, int y) const { draw(x, y, 1.0f); }

void Image::draw(int x, int y, float scale) const {
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  int tempHeight = scale * view.h;
  int tempWidth = scale * view.w;
  SDL_Rect dest = {x, y, tempWidth, tempHeight};
  SDL_RenderCopy(renderer, texture, &view, &dest);
}

void Image::draw(int sx, int sy, int dx, int dy) const {
  SDL_Rect src = {sx, sy, view.w, view.h};
  SDL_Rect dst = {dx, dy, getWidth(), getHeight()};
  SDL_RenderCopy(renderer, texture, &src, &dst);
}
