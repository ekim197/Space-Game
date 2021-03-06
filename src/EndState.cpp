#include "GameState.h"

using namespace Resource;

EndState::EndState(Game* game, PlayState* prev): MenuState(game, 1), prevState(prev), isNewScoreInserted(false){
    // Title
    title.setPosition(VIEW_WIDTH/40.0, game->topView() + VIEW_HEIGHT/20.0);
    title.setString("GAMEOVER");

	//Sound
	if (!soundList.getStatusOfMusic(RESOURCE_PATH + "Audio/GameOver.wav")) {
		soundList.stopAllSounds();
		soundList.playSound(RESOURCE_PATH + "Audio/GameOver.wav");
	}

    // Buttons
    buttons[0].setFont(font[0]);
    buttons[0].setCharacterSize(75 * VIEW_RATIO);
    buttons[0].setFillColor(sf::Color::White);
    buttons[0].setPosition(VIEW_WIDTH/40.0, game->topView() + VIEW_HEIGHT * 3.0/4.0);
    buttons[0].setString("Back to Menu");

    // Get name
    name.setFont(font[4]);
    name.setCharacterSize(45 * VIEW_RATIO);
    name.setFillColor(sf::Color::White);
    name.setPosition(VIEW_WIDTH * 3.0/40.0, game->topView() + VIEW_HEIGHT/2.0);
    name.setString("Type in Your Name\nPress Enter to Submit");

    game->gamePlayer.setGold(prevState->player.getGold());
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
        // TextEntered
        case sf::Event::TextEntered:
                if (event.text.unicode < 128 && nameStr.size() < 15){
                    if(event.text.unicode == '\b' && nameStr.size() > 0)
                        nameStr.pop_back();
                    else if(event.text.unicode == ' ')
                        nameStr += "_";
                    else
                        nameStr += static_cast<char>(event.text.unicode);
                    name.setString(nameStr);
                }
        break;
        // KeyPressed
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Return && !isNewScoreInserted){
                char nameChar[16];
                memset(nameChar, '_', 16);
                strcpy(nameChar, nameStr.c_str());
                Score newScore(nameChar , -prevState->player.getPosition().y);
                scoreManage(newScore);
                isNewScoreInserted = true;
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

    // Draw Name
    game->window.draw(name);

    // Draw Title
    game->window.draw(title);

    // Fade
    if(fadeTimer < 6)
        fadeIn(5);
}

void EndState::scoreManage(Score newScore){
    // Read High_Score.bin
    std::ifstream fin(highScoreFile, std::ios::binary | std::ios::in);
    if (!fin){
        std::cerr << "Unable to open input binary file " << highScoreFile << '\n';
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
