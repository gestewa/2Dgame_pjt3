#include "twoWayMultisprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include "multisprite.h"

TwoWayMultiSprite::TwoWayMultiSprite(const std::string& name)
    : MultiSprite(name + "/right"),
      isRight(true),
      worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
      right(ImageFactory::getInstance().getImages(name + "/right")),
      left(ImageFactory::getInstance().getImages(name + "/left")) {}

void TwoWayMultiSprite::draw() { MultiSprite::draw(); }

void TwoWayMultiSprite::update(Uint32 ticks) {
  MultiSprite::update(ticks);
  checkBoundary();
}

void TwoWayMultiSprite::checkBoundary() {
  if (getVelocityX() < 0) {
    if (isRight) {
      images = left;
      isRight = false;
    }
  } else {
    if (!isRight) {
      images = right;
      isRight = true;
    }
  }
}
