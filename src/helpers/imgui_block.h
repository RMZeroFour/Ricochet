#pragma once

#include "generated/buildinfo.h"

#define IMGUI_BLOCK_BEGIN() if (Ricochet_ENABLE_IMGUI) {
#define IMGUI_BLOCK_END() }
