#include "GameState.h"

using namespace Resource;

OptionState::OptionState(Game* game, GameState* prev): MenuState(game, 4), prevState(prev){
    // Title
    title.setPosition(VIEW_WIDTH/20.0, game->topView() + VIEW_HEIGHT/20.0);
    title.setString("OPTIONS");

    // Buttons
    for(size_t i = 0; i < buttons.size(); i++){
        buttons[i].setFont(font[0]);
        buttons[i].setPosition(VIEW_WIDTH/20.0, game->topView() + VIEW_HEIGHT * 2.0/5.0 + i * 100.0 * VIEW_RATIO);
        buttons[i].setCharacterSize(75.0 * VIEW_RATIO);
        buttons[i].setFillColor(sf::Color::White);
    }

    buttons[0].setString("HIGHSCORES");
    buttons[1].setString("RESET PLAYER");
    buttons[2].setString("RESET SCORES");
    buttons[3].setString("BACK");
}

void OptionState::handle_input(){
    // Create Event
    sf::Event event;

    while(game->window.pollEvent(event)){
        switch (event.type){
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
        //check if text is hovered over
        case sf::Event::MouseMoved:
            for(auto& i : buttons){
                if(isTextClicked(i))
                    i.setFont(font[1]);
                else
                    i.setFont(font[0]);
            }
        break;
        default:
            break;
        }
    }
    // Key input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& clickTimer >= 0.2)
        game->pop_state();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)&& clickTimer >= 0.2)
        game->pop_state();
}

void OptionState::update(const float dt){
    // Fade
    timeIncrement(dt);

    // Click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if(isTextClicked(buttons[0]))
            printBinFile();
        else if(isTextClicked(buttons[1]))
            game->gamePlayer = game->defaultPlayer;
        else if(isTextClicked(buttons[2])){
            clearBinFile();
            game->pop_state();
        }
        else if(isTextClicked(buttons[3]))
            game->pop_state();
        clickTimer = 0;
    }
}

void OptionState::draw(){
    // Set rect
    sf::RectangleShape rect(sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    rect.setFillColor(sf::Color(30,30,30,230));
    rect.setPosition(0, game->topView());

    // Draw Background
    game->window.clear();
    prevState->draw();
    game->window.draw(rect);

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);
    game->window.draw(title);

    // Draw Scores
    if(!highScoreText.empty()){
        for(auto key: highScoreText)
            game->window.draw(key);
    }

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}

void OptionState::clearBinFile(){
    std::ofstream fout(Resource::highScoreFile, std::ios::binary | std::ios::trunc);
    if (!fout){
        std::cerr << "Unable to open output binary file " << Resource::highScoreFile<< '\n';
        exit(4);
    }
    fout.close();
}

void OptionState::printBinFile(){
    std::ifstream fin(Resource::highScoreFile, std::ios::binary | std::ios::in);
    if (!fin){
        std::cerr << "Unable to open output binary file " << Resource::highScoreFile<< '\n';
        exit(4);
    }

    Score highScore[10];
    unsigned numScores = 0;
    while(!fin.eof())
        fin.read(reinterpret_cast<char*>(&highScore[numScores++]), sizeof(highScore[numScores]));
    fin.close();
    numScores--; // Binary file reads an extra line

    // Outputs it into a string
    for (unsigned i = 0; i < numScores; ++i){
        std::stringstream sout;
        sout << std::left << std::setw(3) << i+1 << highScore[i];
        highScoreText.push_back(sf::Text());
        highScoreText[i].setFont(font[4]);
        highScoreText[i].setCharacterSize(40.0 * VIEW_RATIO);
        highScoreText[i].setString(sout.str());
        highScoreText[i].setPosition(VIEW_WIDTH * 9.0/20.0, game->topView() + VIEW_HEIGHT/3.0 + i * 50.0 * VIEW_RATIO);

        if(i == 0)
            highScoreText[i].setFillColor(sf::Color(255,215,0));
        else if(i == 1)
            highScoreText[i].setFillColor(sf::Color(192,192,192));
        else if(i == 2)
            highScoreText[i].setFillColor(sf::Color(205,127,50));
        else
            highScoreText[i].setFillColor(sf::Color(204, 255, 255));
    }



    fin.close();
}
