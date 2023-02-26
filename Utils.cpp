#include "Utils.hpp"

SDL_Texture* Utils::loadTexture( SDL_Renderer* renderer, std::string path_to_file ) {
  SDL_Surface* tmp = SDL_LoadBMP( path_to_file.c_str() );
  SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tmp );

  SDL_FreeSurface( tmp );
  tmp = NULL;

  return texture;
}

bool Utils::check_collision( SDL_Rect& object, SDL_Rect& collide_with, std::string direction ) {

  int colliderLeft, objectLeft;
  int colliderRight, objectRight;
  int colliderTop, objectTop;
  int colliderBottom, objectBottom;

  // Object's colider boundaries
  colliderLeft = object.x;
  colliderRight = object.x + object.w;
  colliderTop = object.y;
  colliderBottom = object.y + object.h;

  objectLeft = collide_with.x;
  objectRight = collide_with.x + collide_with.w + 5;
  objectTop = collide_with.y;
  objectBottom = collide_with.y + collide_with.h + 5;

  if ( direction == "UP" ) {
    if ( colliderTop >= objectBottom - 1 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderBottom <= objectTop + 5 ) {
      return false;
    }
  }
  else if ( direction == "DOWN" ) {
    if ( colliderBottom <= objectTop - 2 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderTop >= objectBottom - 6 ) {
      return false;
    }
  }
  else if ( direction == "LEFT" ) {
    if ( colliderLeft >= objectRight - 3 || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderRight <= objectLeft + 4 ) {
      return false;
    }
  }
  else if ( direction == "RIGHT" ) {
    if ( colliderRight <= objectLeft || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderLeft >= objectRight - 8 ) {
      return false;
    }
  }

  return true;
}

bool Utils::check_collision( SDL_Rect& object, SDL_Rect& collide_with ) {

  int colliderLeft, objectLeft;
  int colliderRight, objectRight;
  int colliderTop, objectTop;
  int colliderBottom, objectBottom;

  // Object's colider boundaries
  colliderLeft = object.x;
  colliderRight = object.x + object.w;
  colliderTop = object.y;
  colliderBottom = object.y + object.h;

  objectLeft = collide_with.x;
  objectRight = collide_with.x + collide_with.w + 5;
  objectTop = collide_with.y;
  objectBottom = collide_with.y + collide_with.h + 5;

  if ( colliderTop >= objectBottom - 1 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderBottom <= objectTop + 5 ) {
    return false;
  }
    
  if ( colliderBottom <= objectTop - 2 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderTop >= objectBottom - 6 ) {
    return false;
  }
  
  if ( colliderLeft >= objectRight - 3 || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderRight <= objectLeft + 4 ) {
    return false;
  }
    
  if ( colliderRight <= objectLeft || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderLeft >= objectRight - 8 ) {
    return false;
  }
  
  return true;
}

bool Utils::check_collision( SDL_Rect& object, std::vector<SDL_Rect> collide_with ) {

  for ( int i = 0; i < (int)collide_with.size(); i++ ) {

    int colliderLeft, objectLeft;
    int colliderRight, objectRight;
    int colliderTop, objectTop;
    int colliderBottom, objectBottom;

    // Object's colider boundaries
    colliderLeft = object.x;
    colliderRight = object.x + object.w;
    colliderTop = object.y;
    colliderBottom = object.y + object.h;

    objectLeft = collide_with[i].x;
    objectRight = collide_with[i].x + collide_with[i].w + 5;
    objectTop = collide_with[i].y;
    objectBottom = collide_with[i].y + collide_with[i].h + 5;

    if ( colliderTop >= objectBottom - 1 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderBottom <= objectTop + 5 ) {
      return false;
    }
    
    if ( colliderBottom <= objectTop - 2 || colliderLeft >= objectRight - 8 || colliderRight <= objectLeft + 4 || colliderTop >= objectBottom - 6 ) {
      return false;
    }
  
    if ( colliderLeft >= objectRight - 3 || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderRight <= objectLeft + 4 ) {
      return false;
    }
    
    if ( colliderRight <= objectLeft || colliderTop >= objectBottom - 6 || colliderBottom <= objectTop + 5 || colliderLeft >= objectRight - 8 ) {
      return false;
    }

  }
  
  return true;
}
