#include <string>
#include "image.h"
#include "viewport.h"

class World {
 public:
  World(const std::string& name, int fact);
  void update();
  void draw() const;
  World& operator=(const World&) = delete;

 private:
  Image* const image;
  int factor;
  unsigned imageWidth;
  float viewX;
  float viewY;
  const Viewport& view;
};
