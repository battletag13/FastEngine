//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  The animation module holds various functions and classes to help with
//  sprite animation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_ANIMATOR_COMPONENT_H_
#define FASTENGINE_ANIMATOR_COMPONENT_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Logger/logger.h"
#include "../Utility/time.h"
#include "../Utility/vector2D.h"
#include "ecs.h"
#include "spritesheet_renderer.h"

namespace fast_engine {

namespace animation {
struct Keyframe {
  Keyframe(double durationMS)
      : visual(true), frameNumber(-1), durationMS(durationMS) {}
  Keyframe(double durationMS, int frameNumber)
      : visual(true), frameNumber(frameNumber), durationMS(durationMS) {}
  Keyframe(double durationMS, double rotationAngle, Vector2D position,
           Vector2D scale)
      : visual(false), durationMS(durationMS), rotationAngle(rotationAngle),
        position(position), scale(scale) {}

  bool visual;
  int frameNumber;
  double durationMS;
  double rotationAngle;
  Vector2D position;
  Vector2D scale;
};

class Animation {
public:
  Animation(const char *name, Transform *transform, bool looping = false,
            bool visual = false)
      : currentKeyframe(0), looping(looping), playing(false), visual(visual),
        name(std::string(name)), transform(transform) {
    updateSpritesheetRenderer();
  }

  // Animation editing
  void pushVisualFrame(int frame, double durationMS) {
    // Adding a visual keyframe
    keyframes.push_back(Keyframe(durationMS, frame));
  }
  void pushStateChangeFrame(double durationMS, double rotationAngle,
                            Vector2D position, Vector2D scale) {
    // Adding state change keyframe
    keyframes.push_back(Keyframe(durationMS, rotationAngle, position, scale));
  }
  void pushWaitFrame(double durationMS) {
    // Adding a wait keyframe
    keyframes.push_back(durationMS);
  }

  void update() {
    if (playing && keyframes.size() > 0) {

      // Interpolate between the next frame which may be state/visual frame
      Keyframe &keyframe = keyframes[currentKeyframe];
      double left = keyframe.durationMS - timer.count();
      if (left <= 0) {
        // Make sure any remaining interpolation is just snapped to place and
        // then move to the next keyframe
        if (!keyframe.visual) {
          lastPosition = lastPosition + keyframe.position;
          transform->setPosition(lastPosition);

          lastScale = lastScale * keyframe.scale;
          transform->setScale(lastScale);

          lastRotationAngle = lastRotationAngle + keyframe.rotationAngle;
          transform->setAngleOfRotation(lastRotationAngle);
        }
        if (++currentKeyframe >= keyframes.size()) {
          if (looping)
            restart();
          else {
            pause();
          }
        }
        frameFinished = false;
        timer.reset();

        if (keyframe.durationMS != 0 || !keyframe.visual)
          return;
      }

      if (keyframe.visual && keyframe.frameNumber != -1 && !frameFinished) {
        frameFinished = true;
        spritesheetRenderer->setSprite(keyframe.frameNumber);
      }
      if (!keyframe.visual) {
        transform->setPosition(lastPosition +
                               keyframe.position *
                                   (1 - left / keyframe.durationMS));
        transform->setScale(lastScale +
                            (keyframe.scale * lastScale - lastScale) *
                                (1 - left / keyframe.durationMS));
        transform->setAngleOfRotation(lastRotationAngle +
                                      keyframe.rotationAngle *
                                          (1 - left / keyframe.durationMS));
      }
    }
  }

  void setLooping(bool looping) { this->looping = looping; }
  void setVisual(bool visual) { this->visual = visual; }

  void updateSpritesheetRenderer() {
    spritesheetRenderer =
        &transform->gameObject->getComponent<SpritesheetRenderer>();
  }

  // Animation display

  // Reset animation
  void cancel() {
    timer.reset();
    playing = false;
  }
  // Start animation
  void play() {
    timer.start();
    playing = true;
    currentKeyframe = 0;
    lastPosition = startPosition = transform->getPosition();
    lastScale = startScale = transform->getScale();
    lastRotationAngle = startRotationAngle = transform->getAngleOfRotation();
    frameFinished = false;
  }
  // Stop animation
  void pause() {
    timer.stop();
    playing = false;
  }
  // Reset animation then start playing again
  void restart() {
    if (visual) {
      lastPosition = startPosition;
      lastScale = startScale;
      lastRotationAngle = startRotationAngle;

      transform->setPosition(lastPosition);
      transform->setScale(lastScale);
      transform->setAngleOfRotation(lastRotationAngle);
    }
    timer.reset();
    play();
  }

  std::string &getName() { return name; }
  bool isPlaying() { return playing; }

private:
  double duration;
  int currentKeyframe;
  bool looping;
  bool playing;
  bool frameFinished;
  bool visual;

  std::string name;
  std::vector<Keyframe> keyframes;

  MilisecondsTimer timer;
  Transform *transform;
  SpritesheetRenderer *spritesheetRenderer;

  double lastRotationAngle, startRotationAngle;
  Vector2D lastPosition, startPosition;
  Vector2D lastScale, startScale;
};
} // namespace animation

class Animator : public Component {
public:
  Animator()
      : spritesheetRenderer(nullptr), currentlyPlayingAnimation(nullptr) {}
  virtual void start() override { checkRenderer(); }
  virtual void update() override {
    if (currentlyPlayingAnimation != nullptr)
      currentlyPlayingAnimation->update();
  }

  // Checks if a SpritesheetRenderer exists and adds it if possible
  void checkRenderer() {
    if (!gameObject->hasComponent<SpritesheetRenderer>()) {
      Logger::getInstance()->logWarning(
          "Animator created with no existing spritesheet renderer!\nCall "
          "checkRenderer to attempt to fix the issue.");
    } else {
      spritesheetRenderer = &gameObject->getComponent<SpritesheetRenderer>();
      for (auto animation : animations) {
        animation.second->updateSpritesheetRenderer();
      }
    }
  }

  // Animation control
  void playAnimation(const char *name) {
    std::string animationName(name);
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->cancel();
    }
    // Play animation if possible
    auto animationIter = animations.find(animationName);
    if (animationIter != animations.end()) {
      currentlyPlayingAnimation = &(*animationIter->second);
      currentlyPlayingAnimation->play();
      currentlyPlayingAnimation->restart();
    } else {
      Logger::getInstance()->logWarning("Animation of name " + animationName +
                                        " not found!");
    }
  }
  void pauseAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->pause();
    } else {
      Logger::getInstance()->logWarning("No animation currently playing!");
    }
  }
  void resumeAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->play();
    } else {
      Logger::getInstance()->logWarning("No animation currently paused!");
    }
  }
  void cancelAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->cancel();
      currentlyPlayingAnimation = nullptr;
    } else {
      Logger::getInstance()->logWarning("No animation currently playing!");
    }
  }

  // Creates a blank animation
  animation::Animation &createAnimation(const char *name, bool looping = false,
                                        bool visual = false) {
    std::string animationName = std::string(name);
    animation::Animation *animation = new animation::Animation(
        name, &gameObject->getComponent<Transform>(), looping, visual);
    std::shared_ptr<animation::Animation> animationUPtr{animation};
    animations.insert(std::make_pair(animationName, std::move(animationUPtr)));
    return *animations.at(animationName);
  }
  // Creates an animation with a count and startSprite
  animation::Animation &createStillAnimation(const char *name, int count,
                                             double duration,
                                             int startSprite = 0,
                                             bool looping = false,
                                             bool visual = false) {
    std::string animationName = std::string(name);
    animation::Animation *animation = new animation::Animation(
        name, &gameObject->getComponent<Transform>(), looping, visual);

    double eachDuration = duration / count;
    for (int i = 0; i < count; ++i) {
      animation->pushVisualFrame(startSprite + i, eachDuration);
    }

    std::shared_ptr<animation::Animation> animationUPtr{animation};
    animations.insert(std::make_pair(animationName, std::move(animationUPtr)));
    return *animations.at(animationName);
  }

private:
  SpritesheetRenderer *spritesheetRenderer;
  animation::Animation *currentlyPlayingAnimation;
  std::unordered_map<std::string, std::shared_ptr<animation::Animation>>
      animations;
};

} // namespace fast_engine

#endif
