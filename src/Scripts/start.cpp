//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  This is the entrypoint for any games created with FastEngine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//

// Core includes
#include "start.h"
#include "engineAPI.h"

// Other includes
#include "playerManager_DEMO.h"

// Used for addGameObject
Manager *manager = Manager::getInstance();

void start() {
  // Game starts here!

  // Demo code
  GameObject &player = manager->addGameObject();
  player.addComponent<SpriteRenderer>("src/Res/player.png", Vector2D(64, 64));
  player.addComponent<PlayerManager>();
  // End demo code
}
