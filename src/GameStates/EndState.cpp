#include "GameState.h"

using namespace Resource;

EndState::EndState(Game* game, PlayState* prev): MenuState(game, 1), prevState(prev){
    // Title
    title.setPosition(50, game->view.getCenter().y - VIEW_HEIGHT/2 + 100);
    title.setString("GAME\n    OVER");

    // Buttons
    buttons[0].setFont(font[0]);
    buttons[0].setCharacterSize(100);
    buttons[0].setFillColor(sf::Color::White);
    buttons[0].setPosition(100, game->view.getCenter().y - VIEW_HEIGHT/2 + 850);
    buttons[0].setString("Back to Menu");

    // Get name
    char name[16] = "Brandon Nguyen";
    Score newScore(name , -prev->player.getPosition().y);

    // Score Management
    scoreManage(newScore);
}

void EndState::handle_input(){
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
        game->backToMainState();
}

void EndState::update(const float dt){
    // Fade
    timeIncrement(dt);

    // Click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer >= 0.25){
        if(isTextClicked(buttons[0]))
            game->backToMainState();
        clickTimer = 0;
    }
}

void EndState::draw(){
    // Set rect
    sf::RectangleShape rect(sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
    rect.setFillColor(sf::Color(30,30,30,150));
    rect.setPosition(0, game->view.getCenter().y - VIEW_HEIGHT/2);

    // Draw Background
    game->window.clear();
    prevState->draw();
    game->window.draw(rect);

    // Draw Buttons
    for (auto x : buttons)
        game->window.draw(x);

    // Draw Scores
    for (auto x : highScoreText)
        game->window.draw(x);

    // Draw Title
    game->window.draw(title);

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}

bool EndState::isTextClicked(sf::Text text){
    sf::IntRect rect(text.getPosition().x, text.getPosition().y - (game->view.getCenter().y - VIEW_HEIGHT/2), text.getGlobalBounds().width, text.getGlobalBounds().height + 20);

    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;
    return false;
}

void EndState::scoreManage(Score newScore){
    // Read High_Score.bin
    std::ifstream fin(highScoreFile, std::ios::binary | std::ios::in);
    if (!fin){
        std::cerr << "Unable to open input text file " << highScoreFile << '\n';
        exit(5);
    }
    unsigned numScores = 0;
    while(!fin.eof())
        fin.read(reinterpret_cast<char*>(&highScore[numScores++]), sizeof(highScore[numScores]));
    fin.close();
    numScores--; // Binary file reads an extra line

    // Insert score
    if (numScores < 10){
        highScore[numScores++] = newScore;
        updateScores = true;
    }
    else if (highScore[numScores - 1] < newScore){
        highScore[numScores - 1] = newScore;
        updateScores = true;
    }
    else
        updateScores = false;

    // Sort ScoreList
    if (updateScores){
        Score temp;
        bool isFound = false;

        for(unsigned i = 0; i < numScores - 1; i++){
            if(isFound){
                temp = highScore[i];
                highScore[i] = highScore[numScores - 1];
                highScore[numScores - 1] = temp;
            }
            if((highScore[i] < highScore[numScores - 1]) &&(!isFound)){
                temp = highScore[i];
                highScore[i] = highScore[numScores - 1];
                highScore[numScores - 1] = temp;
                isFound = true;
            }
        }
    }
    // Outputs it into a string
    for (unsigned i = 0; i < numScores; ++i){
        std::stringstream sout;
        sout << std::left << std::setw(3) << i+1 << highScore[i];
        highScoreText.push_back(sf::Text());
        highScoreText[i].setFont(font[4]);
        highScoreText[i].setCharacterSize(50);
        highScoreText[i].setString(sout.str());
        highScoreText[i].setPosition(VIEW_WIDTH - 1000, game->view.getCenter().y - VIEW_HEIGHT / 4 + i * 75);

        if(i == 0)
            highScoreText[i].setFillColor(sf::Color(255,215,0));
        else if(i == 1)
            highScoreText[i].setFillColor(sf::Color(192,192,192));
        else if(i == 2)
            highScoreText[i].setFillColor(sf::Color(205,127,50));
        else
            highScoreText[i].setFillColor(sf::Color(204, 255, 255));
    }

    // Writes ScoreList into binary score
    std::ofstream fout(highScoreFile, std::ios::binary | std::ios::out);
    if (!fout){
        std::cerr << "Unable to open output binary file " << highScoreFile << '\n';
        exit(6);
    }
    for(unsigned i = 0; i < numScores; i++){
        fout.write(reinterpret_cast<char*>(&highScore[i]), sizeof(highScore[i]));
    }
    fout.close();

}
