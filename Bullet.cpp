#include "Bullet.hpp"

Bullet::Bullet( SDL_Renderer* ren ) {
  
  this->renderer = ren;
  this->texture[0] = Utils::loadTexture( renderer, "./Assets/bullet_up.bmp" );
  this->texture[1] = Utils::loadTexture( renderer, "./Assets/bullet_bottom.bmp" );
  this->texture[2] = Utils::loadTexture( renderer, "./Assets/bullet_left.bmp" );
  this->texture[3] = Utils::loadTexture( renderer, "./Assets/bullet_right.bmp" );
}

Bullet::~Bullet() {
  
  for ( int i = 0; i < (int)sizeof( this->texture ) / (int)sizeof( *this->texture ); i++ ) {
    SDL_DestroyTexture( this->texture[i] );
    this->texture[i] = NULL;
  }

  SDL_DestroyRenderer( this->renderer );
  this->renderer = NULL;
}

void Bullet::spawn( int tank_dir ) {

  SDL_RenderCopy( this->renderer, this->texture[tank_dir], NULL, &this->transform );
  
}

int Bullet::getX() {
  return this->transform.x;
}

int Bullet::getY() {
  return this->transform.y;
}

int Bullet::getWidth() {
  return this->transform.w;
}

int Bullet::getHeight() {
  return this->transform.h;
}

SDL_Rect& Bullet::getRect() {
  return this->transform;
}

/*
  Returns current state, fired or not
*/

bool Bullet::getState() {
  return this->state;
}

void Bullet::setX( int x, char sign ) {

  if ( sign == '+' ) this->transform.x += x;

  if ( sign == '-' ) this->transform.x -= x;
  
  if ( sign == '=' ) this->transform.x = x;
}

void Bullet::setY( int y, char sign ) {

  if ( sign == '+' ) this->transform.y += y;

  if ( sign == '-' ) this->transform.y -= y;
  
  if ( sign == '=' ) this->transform.y = y;
}

/*
  Sets state of the bullet fired or not
*/

void Bullet::setState( bool state ) {
  this->state = state;
}

/*
  Check if bullet out of map
*/
bool Bullet::is_hit( SDL_Rect objects[], int array_length ) {

  bool is_collided = false;

  for ( int i = 0; i < array_length; i++ ) {
    is_collided = Utils::check_collision( this->getRect(), objects[i] );

    if ( is_collided ) {
      break;
    }
  }
  
  if ( this->getX() <= 10 || this->getX() + this->getWidth() >= WIDTH - 12
       || this->getY() <= 12 || this->getY() + this->getHeight() >= HEIGHT - 30
       || is_collided ) {
    return true;
  }

  return false;
}

/*
  Overload Bullet::is_hit
*/
bool Bullet::is_hit( SDL_Rect& tank ) {

  if ( Utils::check_collision( this->getRect(), tank ) ) {
    return true;
  }

  return false;
}

/*
  Throw bullet at specified direction
  1: UP
  2: Down
  3: Left
  4: Right
*/

void Bullet::set_direction( int dir, SDL_Rect& gun ) {
  
  if ( dir == 0 ) {
    this->bullet_dir = UP_fire;
    this->_resize();
    this->setX( gun.x + gun.w / 2 - this->getWidth() / 2 );
    this->setY( gun.y );
  }

  if ( dir == 1 ) {
    this->bullet_dir = DOWN_fire;
    this->_resize();
    this->setX( gun.x + gun.w / 2 - this->getWidth() / 2 );
    this->setY( gun.y + gun.h );
  }

  if ( dir == 2 ) {
    this->bullet_dir = LEFT_fire;
    this->_resize();
    this->setX( gun.x );
    this->setY( gun.y + gun.h / 2 - this->getHeight() / 2 );
  }

  if ( dir == 3 ) {
    this->bullet_dir = RIGHT_fire;
    this->_resize();
    this->setX( gun.x + gun.w );
    this->setY( gun.y + gun.h / 2 - this->getHeight() / 2 );
  }

}

/*
  Changes bullet size due to its direction
*/

void Bullet::_resize() {

  if ( this->bullet_dir == UP_fire || this->bullet_dir == DOWN_fire ) {
    this->transform.w = 6;
    this->transform.h = 11;
  }
  else {
    this->transform.w = 11;
    this->transform.h = 6;
  }
}

/*
  Calls from throw_bullet, defines which of four sides bullet goes
*/

void Bullet::send() {
  
  switch ( this->bullet_dir ) {
    case UP_fire:
      this->setY( 10, '-' );
      break;
    case DOWN_fire:
      this->setY( 10, '+' );
      break;
    case LEFT_fire:
      this->setX( 10, '-' );
      break;
    case RIGHT_fire:
      this->setX( 10, '+' );
      break;
    default:
      break;
  }
}
