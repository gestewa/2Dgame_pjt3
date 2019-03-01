#include "engine.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "frameGenerator.h"
#include "gameData.h"
#include "multisprite.h"
#include "sprite.h"
#include "twoWayMultisprite.h"

Engine::~Engine() {
  for (Drawable *s : sprites) {
    delete s;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine()
    : rc(RenderContext::getInstance()),
      io(IoMod::getInstance()),
      clock(Clock::getInstance()),
      renderer(rc.getRenderer()),
      backgrounds({
          World("back", Gamedata::getInstance().getXmlInt("back/factor")),
          World("sign", Gamedata::getInstance().getXmlInt("sign/factor")),
          World("table", Gamedata::getInstance().getXmlInt("table/factor")),
          World("fairy", Gamedata::getInstance().getXmlInt("fairy/factor")),
          World("fairy2", Gamedata::getInstance().getXmlInt("fairy2/factor")),
          World("fairy3", Gamedata::getInstance().getXmlInt("fairy3/factor")),
          World("fairy4", Gamedata::getInstance().getXmlInt("fairy4/factor")),
          World("fairy4", Gamedata::getInstance().getXmlInt("fairy4/factor")),
      }),
      sprites({
          new TwoWayMultiSprite("ViolentFairy"),
          new TwoWayMultiSprite("Dice"),
          new TwoWayMultiSprite("Dice1"),
          new TwoWayMultiSprite("Dice2"),
          new TwoWayMultiSprite("Dice3"),
          new TwoWayMultiSprite("Dice4"),
          new MultiSprite("RotatingDice"),
          new MultiSprite("RotatingDice2"),
      }),
      viewport(Viewport::getInstance()),
      currentSprite(0),
      makeVideo(false) {
  for (auto *s : sprites) {
    s->setScale(3);
  }
  Viewport::getInstance().setObjectToTrack(sprites[0]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  for (auto &b : backgrounds) {
    b.draw();
  }
  for (Drawable *s : sprites) {
    s->draw();
  }
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for (auto &b : backgrounds) {
    b.update();
  }
  for (Drawable *s : sprites) {
    s->update(ticks);
  }
  viewport.update();  // always update viewport last
}

void Engine::switchSprite() {
  currentSprite = (currentSprite + 1) % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8 *keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while (!done) {
    // The next loop polls for events, guarding against key bounce:
    while (SDL_PollEvent(&event)) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type == SDL_QUIT) {
        done = true;
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if (keystate[SDL_SCANCODE_P]) {
          if (clock.isPaused())
            clock.unpause();
          else
            clock.pause();
        }
        if (keystate[SDL_SCANCODE_T]) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        } else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if (ticks > 0) {
      clock.incrFrame();
      draw();
      update(ticks);
      if (makeVideo) {
        frameGen.makeFrame();
      }
    }
  }
}
