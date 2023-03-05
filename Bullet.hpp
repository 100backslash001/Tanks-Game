#include "Utils.hpp"

class Bullet {
public:
  Bullet( SDL_Renderer* ren );
  ~Bullet();

  enum BulletDir { UP_fire, DOWN_fire, LEFT_fire, RIGHT_fire } bullet_dir;

  /*
    Getters and setters of the Bullet class
  */
  int getX();
  int getY();
  int getWidth();
  int getHeight();
  SDL_Rect& getRect();
  bool getState();
  void setX( int x, char sign = '=' );
  void setY( int y, char sign = '=' );
  void setState( bool state );
  
  void spawn( int tank_dir );

  bool is_hit( SDL_Rect objects[], int array_length );
  bool is_hit( SDL_Rect& tank );
  void set_direction( Utils::Direction dir, SDL_Rect& gun );
  void send();

private:
  SDL_Rect transform;
  SDL_Renderer* renderer;
  SDL_Texture* texture[4];
  bool state = false;

  void _resize();
};
