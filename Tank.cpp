#include "Tank.hpp"

Tank::Tank( SDL_Renderer* ren, int x, int y, Player_type type ) {
  this->renderer = ren;
  this->type = type;

  if ( type == Player_type::Player_1 ) {
    
    this->transform = { x, y, 30, 30 };
    this->texture[0] = Utils::loadTexture( renderer, "./Assets/main_tank.bmp" );
    this->texture[1] = Utils::loadTexture( renderer, "./Assets/main_tank_bottom.bmp" );
    this->texture[2] = Utils::loadTexture( renderer, "./Assets/main_tank_left.bmp" );
    this->texture[3] = Utils::loadTexture( renderer, "./Assets/main_tank_right.bmp" );
    
    this->movement.x = this->transform.x;
    this->movement.y = this->transform.y;
    
    this->dir = UP;
  }
  else {
    
    this->transform = { x, y, 30, 30 };
    this->texture[0] = Utils::loadTexture( renderer, "./Assets/enemy_tank_top.bmp" );
    this->texture[1] = Utils::loadTexture( renderer, "./Assets/enemy_tank_bottom.bmp" );
    this->texture[2] = Utils::loadTexture( renderer, "./Assets/enemy_tank_left.bmp" );
    this->texture[3] = Utils::loadTexture( renderer, "./Assets/enemy_tank_right.bmp" );
    
    this->movement.x = this->transform.x;
    this->movement.y = this->transform.y;
    
    this->dir = UP;
  }
}

Tank::~Tank() {
  
  for ( int i = 0; i < (int)sizeof( this->texture ) / (int)sizeof( *this->texture ); i++ ) {
    SDL_DestroyTexture( this->texture[i] );
    this->texture[i] = nullptr;
  }

  SDL_DestroyRenderer( this->renderer );
  this->renderer = nullptr;
}

/*
  Draw object's texture
*/

void Tank::draw() {

  SDL_RenderCopy( this->renderer, this->texture[this->dir], nullptr, &this->transform );
    
}

/*
  Move obect up
*/

void Tank::_move_up( SDL_Rect objects[], int array_length ) {

  this->dir = UP;

  bool is_colided = false;
  
  for ( int i = 0; i < array_length; i++ ) {
    is_colided = Utils::check_collision( this->getRect(), objects[i], Utils::Direction::UP );

    if ( is_colided ) {
      break;
    }
  }
  
  if ( this->movement.y <= 15 || is_colided ) {
    this->movement.y = this->getY();
  }
  else {
    this->movement.y -= 1.0f;
    this->setY( this->movement.y );
  }
}

/*
  Move obect down
*/

void Tank::_move_down( SDL_Rect objects[], int array_length ) {

  this->dir = DOWN;

  bool is_colided = false;
  
  for ( int i = 0; i < array_length; i++ ) {
    is_colided = Utils::check_collision( this->getRect(), objects[i], Utils::Direction::DOWN );

    if ( is_colided ) {
      break;
    }
  }
  
  if ( this->movement.y + this->getHeight() >= HEIGHT - 35 || is_colided ) {
    this->movement.y = this->getY();
  }
  else {
    this->movement.y += 1.0f;
    this->setY( this->movement.y );
  }
}

/*
  Move obect to the left
*/

void Tank::_move_left( SDL_Rect objects[], int array_length ) {

  this->dir = LEFT;

  bool is_colided = false;
  
  for ( int i = 0; i < array_length; i++ ) {
    is_colided = Utils::check_collision( this->getRect(), objects[i], Utils::Direction::LEFT );
    
    if ( is_colided ) {
      break;
    }
  }
  
  if ( this->movement.x < 20 || is_colided ) {
    this->movement.x = this->getX();
  }
  else {
    this->movement.x -= 1.0f;
    this->setX( this->movement.x );
  }
}

/*
  Move obect to the right
*/

void Tank::_move_right( SDL_Rect objects[], int array_length ) {
  
  this->dir = RIGHT;

  bool is_colided = false;
  
  for ( int i = 0; i < array_length; i++ ) {
    is_colided = Utils::check_collision( this->getRect(), objects[i], Utils::Direction::RIGHT );

    if ( is_colided ) {
      break;
    }
  }
  
  if ( this->movement.x + this->getWidth() >= WIDTH - 20 || is_colided ) {
    this->movement.x = this->getX();
  }
  else {
    this->movement.x += 1.0f;
    this->setX( this->movement.x );
  }
}

/*
  Fire bullets
*/
// TODO: Make with some logic
void Tank::fire() {
  this->setAmmo( 1, '-' );
}

/*
  Returns current x position of the object
*/

int Tank::getX() {
  return this->transform.x;
}

/*
  Returns current y position of the object
*/

int Tank::getY() {
  return this->transform.y;
}

/*
  Returns width of the object
*/

int Tank::getWidth() {
  return this->transform.w;
}

/*
  Returns height of the object
*/

int Tank::getHeight() {
  return this->transform.h;
}

/*
  Returns whole rect/collider of the object
*/

SDL_Rect& Tank::getRect() {
  return this->transform;
}

/*
  Returns current ammount of ammo
*/

int Tank::getAmmo() {
  return this->ammo;
}

/*
  Returns current state of fire
*/

bool Tank::getState() {
  return this->isFiring;
}

/*
  Returns current score
*/

int Tank::getScore() {
  return this->score;
}

/*
  Set x to the passed value
*/

void Tank::setX( int x ) {
  this->movement.x = x;
  this->transform.x = x;
}

/*
  Set y to the passed value
*/

void Tank::setY( int y ) {
  this->movement.y = y;
  this->transform.y = y;
}

/*
  Add or sub some ammo
*/

void Tank::setAmmo( int amount, char sign ) {
  if ( sign == '+' && this->ammo < 26 ) this->ammo += amount;
  if ( this->ammo > 25 ) this->ammo -= ( this->ammo - 25 );
  if ( sign == '-' && this->ammo >= 0 ) this->ammo -= amount;
}

/*
  Sets states of firing
*/

void Tank::setState( bool isFiring ) {
  this->isFiring = isFiring;
}

/*
  Sets score
*/

void Tank::addScore() {
  this->score += 1;
}

void Tank::control( const Uint8* key_states, SDL_Rect objects[], int objects_amount ) {

  if ( this->type == Player_type::Player_1 ) {

    if ( key_states[SDL_SCANCODE_W] && !( key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_D] ) ) this->_move_up( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_S] && !( key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_D] ) ) this->_move_down( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_A] && !( key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_S] ) ) this->_move_left( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_D] && !( key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_S] ) ) this->_move_right( objects, objects_amount );
    
  }

  if ( this->type == Player_type::Player_2 ) {

    if ( key_states[SDL_SCANCODE_KP_8] && !( key_states[SDL_SCANCODE_KP_4] || key_states[SDL_SCANCODE_KP_6] ) ) this->_move_up( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_KP_5] && !( key_states[SDL_SCANCODE_KP_4] || key_states[SDL_SCANCODE_KP_6] ) ) this->_move_down( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_KP_4] && !( key_states[SDL_SCANCODE_KP_8] || key_states[SDL_SCANCODE_KP_5] ) ) this->_move_left( objects, objects_amount );
    if ( key_states[SDL_SCANCODE_KP_6] && !( key_states[SDL_SCANCODE_KP_8] || key_states[SDL_SCANCODE_KP_5] ) ) this->_move_right( objects, objects_amount );

  }
}
