
/** - How to use the archive:
 * 
 * Where it wish add , for example, SDL_image and SDL_mixer on an archive, 
 * add the lines below. It will be included automatically and multiplatform way. 
 * (If makefile provided be used).
 * 
 * #define INCLUDE_SDL_IMAGE
 * #define INCLUDE_SDL_MIXER
 * #include "SDL_include.h"
 *
 */


/************************************************
 *					SDL.h						*
 *************************************************/
#ifdef INCLUDE_SDL
extern "C" {
#ifdef _WIN32
#include <SDL2/SDL.h>
#elif __ANDROID__
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL
}
#endif  // INCLUDE_SDL

/************************************************
 *				 SDL_image.h					*
 *************************************************/
#ifdef INCLUDE_SDL_IMAGE
extern "C" {
#ifdef _WIN32
#include <SDL2/SDL_image.h>
#elif __ANDROID__
#include <SDL_image.h>
#elif __APPLE__
#include <SDL2/SDL_image.h>
#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_image.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_IMAGE
}
#endif  // INCLUDE_SDL_IMAGE

/************************************************
 *				 SDL_mixer.h					*
 *************************************************/
#ifdef INCLUDE_SDL_MIXER
extern "C" {
#ifdef _WIN32
#include <SDL2/SDL_mixer.h>
#elif __ANDROID__
#include <SDL_mixer.h>
#elif __APPLE__
#include <SDL2/SDL_mixer.h>
#include "TargetConditionals.h"
#elif __linux__
#include <SDL2/SDL_mixer.h>
#else
#error "Unknown compiler"
#endif
#undef INCLUDE_SDL_MIXER
}
#endif  // INCLUDE_SDL_MIXER
