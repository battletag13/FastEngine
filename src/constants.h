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
constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 640;
constexpr const char *WINDOW_TITLE = "Fast Engine";
constexpr std::array<int, 4> DEFAULT_RENDERER_DRAW_COLOR = {104, 130, 158, 255};

} // namespace fe_config

#endif
