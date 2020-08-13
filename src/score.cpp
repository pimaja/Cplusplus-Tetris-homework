#include "score.h"
#include <cstdlib>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
   mScoreText.setFont(mFont);
   mScoreText.setCharacterSize(30);
   mScoreText.setColor(sf::Color::White);
   mScoreText.setStyle(sf::Text::Bold);
   mScoreText.setString("0");
   mScoreText.setPosition(10,10);
}

void Score::addNoLinesCompleted(int n)
{
  // Vaš kod.
  mScore=n*10;
}

void Score::setGameOver()
{
  // Vaš kod.
  mGameOverText.setFont(mFont);
  mGameOverText.setCharacterSize(30);
  mGameOverText.setColor(sf::Color::White);
  mGameOverText.setStyle(sf::Text::Bold);
  mGameOverText.setString("Game over");
  mGameOverText.setPosition(mScoreText.getPosition().x,mScoreText.getPosition().y+30);
}

void Score::update()
{
  // Vaš kod.
  std::string str=std::to_string(mScore);
  mScoreText.setString(str);
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
  states.transform*=getTransform();
  target.draw(mScoreText,states);
  target.draw(mGameOverText,states);
}