#include "game.h"

Game::Game() : mWindow(sf::VideoMode(500,600), "Tetris")
{
    // Vaš kod dolazi ovdje (ako bude potrebe).
    mScore.setPosition(321,51);
    mBoard.setPosition(51,51);
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;

        case sf::Event::KeyPressed:
            // Vaš kod dolazi ovdje !!! 
            if(event.key.code==sf::Keyboard::Up){
                    mUpPressed = true;
            }
            if(event.key.code==sf::Keyboard::Space){
                    mSpacePressed = true;
            }
            if(event.key.code==sf::Keyboard::Left){
                    mLeftPressed = true;
            }
            if(event.key.code==sf::Keyboard::Right){
                    mRightPressed = true;
            }
	    break;
            case sf::Event::Resized:
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
            break;
        }
    }
}

void Game::update()
{
   // Updatiranje scene. Vaš kod dolazi ovdje 
   mBoard.update(mLeftPressed,mUpPressed,mRightPressed,mSpacePressed);
   if(mBoard.isGameOver()) mScore.setGameOver();
   mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
   mScore.update();
   mUpPressed=mSpacePressed=mLeftPressed=mRightPressed=false;
}

void Game::render()
{
     mWindow.clear();

     mWindow.draw(mBoard);
     mWindow.draw(mScore);

     mWindow.display();
}
