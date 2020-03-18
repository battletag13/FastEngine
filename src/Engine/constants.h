//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Constants required by the engine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_CONSTANTS_H_
#define FASTENGINE_CONSTANTS_H_

#include <array>

namespace fe_config {

// Core config
constexpr int DEFAULT_WINDOW_WIDTH = 960;
constexpr int DEFAULT_WINDOW_HEIGHT = 640;
constexpr const char *DEFAULT_WINDOW_TITLE = "Fast Engine";
constexpr std::array<int, 4> DEFAULT_RENDERER_DRAW_COLOR = {104, 130, 158, 255};

// ECS config
constexpr int MAX_COMPONENTS = 512;

// Logger config
constexpr const char *DEFAULT_ERROR_MESSAGE = "An unknown error has occured!";
constexpr const char *LOG_FILE = "log.txt";
constexpr bool LOGGING_TO_FILE = false;

} // namespace fe_config

#endif
