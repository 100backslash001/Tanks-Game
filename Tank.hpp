#include "Utils.hpp"

class Tank {

public:
  enum Directions { UP, DOWN, LEFT, RIGHT } dir;
  enum Player_type { Player_1, Player_2 } type;
  
  Tank( SDL_Renderer* ren, int x, int y, Player_type type );
  ~Tank();

  struct Vector2 {
    float x;
    float y;
  } movement;

  void draw();
  void control( const Uint8* key_states, SDL_Rect objects[], int objects_amount );
  void fire();

  int getX();
  int getY();
  int getWidth();
  int getHeight();
  SDL_Rect& getRect();
  int getAmmo();
  bool getState();
  int getScore();

  void setX( int x );
  void setY( int y );
  void addScore();
  void setAmmo( int amount, char sign );
  void setState( bool isFiring );

private:
  SDL_Rect transform;
  SDL_Texture* texture[4];
  SDL_Renderer* renderer;
  int ammo = 5;
  bool isFiring = false;
  int score = 0;
  
  void _move_up( SDL_Rect objects[], int array_length );
  void _move_down( SDL_Rect objects[], int array_length );
  void _move_left( SDL_Rect objects[], int array_length );
  void _move_right( SDL_Rect objects[], int array_length );
};
