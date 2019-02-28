#include <SDL.h>
#include <vector>
#include "clock.h"
#include "ioMod.h"
#include "renderContext.h"
#include "viewport.h"
#include "world.h"

class Engine {
 public:
  Engine();
  ~Engine();
  void play();
  void switchSprite();

  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;

 private:
  const RenderContext &rc;
  const IoMod &io;
  Clock &clock;
  SDL_Renderer *const renderer;
  std::vector<World> backgrounds;
  std::vector<Drawable *> sprites;
  Viewport &viewport;
  int currentSprite;
  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
