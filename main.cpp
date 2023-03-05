#include "Utils.hpp"
#include "Tank.hpp"
#include "Bullet.hpp"
#include <stdio.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Texture* background = nullptr;
SDL_Rect background_rect = { 0, 0, WIDTH, HEIGHT };

// Walls on map that prohibit ride on it
SDL_Rect props[] = {
  { 55, 50, 228, 112 },
  { 430, 75, 200, 249 },
  { 275, 417, 637, 75 },
  { 711, 54, 215, 281 },
  { 56, 240, 270, 112 },
  { 97, 492, 80, 51 },
  { 56, 437, 43, 51 },
  { 14, 408, 43, 51 },
};

Tank* first_player = nullptr;
std::vector<Bullet*> first_player_bullets;

Tank* second_player = nullptr;
std::vector<Bullet*> second_player_bullets;

int ammo_spawn_pos[12][2] = {
  { 400, 500 },
  { 750, 500 },
  { 70, 190 },
  { 360, 190 },
  { 520, 30 },
  { 800, 25 },
  { 660, 190 },
  { 660, 360 },
  { 960, 360 },
  { 960, 190 },
  { 100, 380 },
  { 380, 370 }
};
int element = std::rand() % 12;
SDL_Texture* ammo = nullptr;
SDL_Rect ammo_rect = {
  ammo_spawn_pos[element][0],
  ammo_spawn_pos[element][1],
  20,
  20
};

// Variables for text rendering

SDL_Texture* text_texture = nullptr;
TTF_Font* font = nullptr;

// Scores' black rect

SDL_Rect p1_score_rect = { 12, 510, 215, 60 };
SDL_Rect p2_score_rect = { 799, 510, 215, 60 };
SDL_Rect p1_icon = { WIDTH / 2 - 55, 520, 20, 20 };
SDL_Rect p2_icon = { WIDTH / 2 + 35, 520, 20, 20 };

// Variables for sounds

Mix_Music* main_music = nullptr;

Mix_Chunk* shot_sound = nullptr;
Mix_Chunk* pickup_sound = nullptr;
Mix_Chunk* explosion_sound = nullptr;

bool init() {

  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    return false;
  }

  window = SDL_CreateWindow( "Tanks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );

  if ( window == nullptr ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return false;
  }
  
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

  if ( renderer == nullptr ) {
    printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
    return false;
  }

  SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

  if ( TTF_Init() == -1 ) {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    return false;
  }

  font = TTF_OpenFont( "./Assets/main_font.ttf", 38 );

  if ( font == nullptr ) {
    printf( "Could not open font! TTF_Error: %s\n", TTF_GetError() );
    return false;
  }

  if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    return false;
  }

  main_music = Mix_LoadMUS( "./Assets/back_music.wav" );

  if ( main_music == nullptr ) {
    printf( "Unable to load music: %s! SDL_mixer Error: %s\n", "back_music.wav", Mix_GetError() );
  }

  shot_sound = Mix_LoadWAV( "./Assets/shot_sound.wav" );
  pickup_sound = Mix_LoadWAV( "./Assets/pickup_sound.wav" );
  explosion_sound = Mix_LoadWAV( "./Assets/explosion_sound.wav" );

  if ( shot_sound == nullptr || pickup_sound == nullptr || explosion_sound == nullptr ) {
    printf( "Unable to load sound %s! SDL_mixer Error: %s\n", "shot_sound.wav or pickup_sound.wav or explosion_sound.wav", Mix_GetError() );
    return false;
  }

  background = Utils::loadTexture( renderer, "./Assets/background.bmp" );

  element = std::rand() % 12;
  
  first_player = new Tank(
			  renderer,
			  ammo_spawn_pos[element][0],
			  ammo_spawn_pos[element][1],
			  Tank::Player_type::Player_1
			  );

  if ( first_player == nullptr )
    return false;

  element = std::rand() % 12;
  
  second_player = new Tank(
			   renderer,
			   ammo_spawn_pos[element][0],
			   ammo_spawn_pos[element][1],
			   Tank::Player_type::Player_2
			   );

  if ( second_player == nullptr )
    return false;

  ammo = Utils::loadTexture( renderer, "./Assets/spawn_ammo.bmp" );

  if ( ammo == nullptr )
    return false;
  
  return true;
}

void renderText( SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, SDL_Color color ) {
  
  SDL_Surface* surf = TTF_RenderText_Blended( font, text.c_str(), color );

  text_texture = SDL_CreateTextureFromSurface( renderer, surf );

  SDL_FreeSurface( surf );
  surf = nullptr;

  SDL_Rect text_box;
  text_box.x = x;
  text_box.y = y;
  text_box.w = w;
  text_box.h = h;

  SDL_RenderCopy( renderer, text_texture, nullptr, &text_box );
}

bool inputLogic( SDL_Event e ) {
  
  while ( SDL_PollEvent( &e ) != 0 ) {
      
    if ( e.type == SDL_QUIT )
      return true;
      
    if ( e.type == SDL_KEYDOWN ) {

      SDL_Keycode key_code = e.key.keysym.sym;

      if ( key_code == SDLK_q ) {
	return true;
      }

      if ( key_code == SDLK_SPACE && first_player->getAmmo() > 0 && e.key.repeat == 0 ) {
	Mix_PlayChannel( -1, shot_sound, 0 );
	first_player->setState( true );
	first_player->fire();
      }

      if ( key_code == SDLK_KP_0 && second_player->getAmmo() > 0 && e.key.repeat == 0 ) {
	Mix_PlayChannel( -1, shot_sound, 0 );
	second_player->setState( true );
	second_player->fire();
      }
      
    }
  }

  const Uint8* key_states = SDL_GetKeyboardState( nullptr );

  first_player->control( key_states, props, (sizeof(props)/sizeof(*props)) );

  second_player->control( key_states, props, (sizeof(props)/sizeof(*props)) );

  return false;
}

void gameLogic() {

  if ( Mix_PlayingMusic() == 0 ) {
    Mix_PlayMusic( main_music, 1 );
  }

  element = std::rand() % 12;
  
  if ( first_player->getState() ) {
    Bullet* bullet = new Bullet( renderer );
    bullet->set_direction( static_cast<Utils::Direction>( first_player->dir ), first_player->getRect() );
    first_player_bullets.push_back( bullet );
    first_player->setState( false );
  }

  for ( int i = 0; i < (int)first_player_bullets.size(); i++ ) {
    first_player_bullets[i]->send();

    if ( first_player_bullets[i]->is_hit( props, (int)(sizeof(props)/sizeof(*props)) ) ) {
      
      first_player_bullets.erase( first_player_bullets.begin() + i );
      
    }

    if ( first_player_bullets[i]->is_hit( second_player->getRect() ) ) {

      if ( Utils::check_collision( second_player->getRect(), first_player_bullets[i]->getRect() ) ) {

	Mix_PlayChannel( -1, explosion_sound, 0 );
	
	second_player->setX( ammo_spawn_pos[element][0] );
	second_player->setY( ammo_spawn_pos[element][1] );
	first_player->addScore();
      }

      first_player_bullets.erase( first_player_bullets.begin() + i );
    }
  }

  if ( second_player->getState() ) {
    Bullet* bullet = new Bullet( renderer );
    bullet->set_direction( static_cast<Utils::Direction>( second_player->dir ), second_player->getRect() );
    second_player_bullets.push_back( bullet );
    second_player->setState( false );
  }

  for ( int i = 0; i < (int)second_player_bullets.size(); i++ ) {
    second_player_bullets[i]->send();

    if ( second_player_bullets[i]->is_hit( props, (int)(sizeof(props)/sizeof(*props)) ) ) {
      
      second_player_bullets.erase( second_player_bullets.begin() + i );
      
    }

    if ( second_player_bullets[i]->is_hit( first_player->getRect() ) ) {

      if ( Utils::check_collision( first_player->getRect(), second_player_bullets[i]->getRect() ) ) {

	Mix_PlayChannel( -1, explosion_sound, 0 );
	
	first_player->setX( ammo_spawn_pos[element][0] );
	first_player->setY( ammo_spawn_pos[element][1] );
	second_player->addScore();
      }

      second_player_bullets.erase( second_player_bullets.begin() + i );
    }
  }

  if ( Utils::check_collision( first_player->getRect(), ammo_rect ) ) {

    Mix_PlayChannel( -1, pickup_sound, 0 );
    
    ammo_rect.x = ammo_spawn_pos[element][0];
    ammo_rect.y = ammo_spawn_pos[element][1];
    
    first_player->setAmmo( 5, '+' );
  }

  if ( Utils::check_collision( second_player->getRect(), ammo_rect ) ) {

    Mix_PlayChannel( -1, pickup_sound, 0 );

    ammo_rect.x = ammo_spawn_pos[element][0];
    ammo_rect.y = ammo_spawn_pos[element][1];
    
    second_player->setAmmo( 5, '+' );
  }
}

void render() {

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear( renderer );

  SDL_RenderCopy( renderer, background, nullptr, &background_rect );

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 200 );
  
  SDL_RenderFillRect( renderer, &p1_score_rect );
  SDL_RenderFillRect( renderer, &p2_score_rect );

  SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
  SDL_RenderFillRect( renderer, &p1_icon );

  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
  SDL_RenderFillRect( renderer, &p2_icon );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

  SDL_RenderCopy( renderer, ammo, nullptr, &ammo_rect );
  
  for ( int i = 0; i < (int)first_player_bullets.size(); i++ ) {
    first_player_bullets[i]->spawn( first_player->dir );
  }

  for ( int i = 0; i < (int)second_player_bullets.size(); i++ ) {
    second_player_bullets[i]->spawn( second_player->dir );
  }

  second_player->draw();
  
  first_player->draw();

  std::string p1_ammo_amount = "P1 AMMO LEFT: " + std::to_string( first_player->getAmmo() );

  std::string p2_ammo_amount = "P2 AMMO LEFT: " + std::to_string( second_player->getAmmo() );

  std::string score = std::to_string( first_player->getScore() ) + " : " + std::to_string( second_player->getScore() );

  renderText( renderer, p1_ammo_amount.c_str(), 18, 500, 200, 80, { 255, 255, 255, 255 } );
  renderText( renderer, p2_ammo_amount.c_str(), 810, 500, 200, 80, { 255, 255, 255, 255 } );

  renderText( renderer, score.c_str(), WIDTH / 2 - 30, 500, 60, 60, { 255, 0, 0, 255 } );

  // Destroy texture as it is creating every frame
  
  SDL_DestroyTexture( text_texture );
  text_texture = nullptr;
  
  SDL_RenderPresent( renderer );
  
  SDL_Delay( 10 );
}

void run() {

  bool game_over = false;
  SDL_Event event;

  while ( !game_over ) {

    game_over = inputLogic( event );

    gameLogic();

    render();
  }
  
}

void close()
{
  std::vector<Bullet*>().swap( first_player_bullets );
  std::vector<Bullet*>().swap( second_player_bullets );

  Mix_FreeChunk( shot_sound );
  Mix_FreeChunk( pickup_sound );
  shot_sound = nullptr;
  pickup_sound = nullptr;

  Mix_FreeMusic( main_music );
  main_music = nullptr;

  //SDL_DestroyTexture( text_texture );
  //text_texture = nullptr;
  TTF_CloseFont( font );
  font = nullptr;
  
  SDL_DestroyTexture( ammo );
  delete second_player;
  delete first_player;
  SDL_DestroyTexture( background );
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
  
  ammo = nullptr;
  second_player = nullptr;
  first_player = nullptr;
  background = nullptr;
  renderer = nullptr;
  window = nullptr;

  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}

int main( int argc, char* argv[] ) {

  srand(time(0));

  if ( !init() ) {
    printf( "Failed to initialize!" );
  }
  else {
    run();
  }

  close();
  
  return 0;
}
