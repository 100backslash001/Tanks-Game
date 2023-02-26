#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <thread>

#define WIDTH 1024
#define HEIGHT 576

class Utils {

public:

  static SDL_Texture* loadTexture( SDL_Renderer* renderer, std::string path_to_file );
  static bool check_collision( SDL_Rect& object, SDL_Rect& collide_with, std::string direction );
  static bool check_collision( SDL_Rect& object, SDL_Rect& collide_with );
  static bool check_collision( SDL_Rect& object, std::vector<SDL_Rect> collide_with );

};

#endif /* UTILS_H */
