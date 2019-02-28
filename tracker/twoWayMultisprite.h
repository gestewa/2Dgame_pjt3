#ifndef TWOWAYMULTISPRITE_H
#define TWOWAYMULTISPRITE_H

#include "multisprite.h"

class TwoWayMultiSprite : public MultiSprite {
 public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite(const TwoWayMultiSprite&) = delete;
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&) = delete;
  void draw();
  void update(Uint32 ticks);
  void checkBoundary();

 private:
  bool isRight;
  int worldWidth;
  std::vector<Image*> right;
  std::vector<Image*> left;
};

#endif