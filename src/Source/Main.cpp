#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Collision.h"
#include "Game.h"
#include "GameState.h"
//#include "Score.h"
//#include "Date.h"

int main(){
    // Start Game
    Game game;
    game.push_state(new MenuState(&game));
    game.game_loop();

    return 0;
}

