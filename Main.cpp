#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Collision.h"
#include "Game.h"
#include "Gamestate.h"

int main(){
    Game game;
    game.push_state(new Menustate(&game));
    game.game_loop();

    return 0;
}

