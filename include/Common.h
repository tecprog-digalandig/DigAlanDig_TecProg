#ifndef COMMON_H
#define COMMON_H
#define INCLUDE_SDL
#include <json.hpp>
#include "SDL_include.h"

using json = nlohmann::json;

namespace Common {
enum Layer { BG = 1, DEFAULT = 2, FG = 4, LIGHT = 8, HUD = 16 };
enum ItemType { gold = 1, diamond, petroleum };

// From SDL wiki
char *file_read(const char *filename);
void read_Json(json &j, const std::string &file);

}  // namespace Common
#endif  // COMMON_H
