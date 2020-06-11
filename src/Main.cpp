#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Collision.h"
#include "Game.h"
#include "GameState.h"

int main(){
    // Start Game
    Game game;
    game.push_state(new MainMenuState(&game));
    game.game_loop();

    return 0;
}

