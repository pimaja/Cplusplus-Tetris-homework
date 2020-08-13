#include "board.h"

// Vaš kod dolazi ovdje
Board::Board(){
        //Konstrukcija mreže
        mGrid.setPrimitiveType(sf::Lines);
        mGrid.resize(64);
        //Početak mreže
        mOriginX=51;
        mOriginY=51;
        //Dimenzije ćelija
        mDx=18.9;
        mDy=18.95;
        float coor1=51;	//Pomoćna varijabla za konstrukciju
        //Najprije zadajemo horizontalne linije mreže, a zatim vertikalne
        for(int i=0;i+1<64;i+=2){
                if(i==42) coor1=51;
                if(i<42){
                        mGrid[i]=sf::Vector2f(51,coor1);
                        mGrid[i+1]=sf::Vector2f(250,coor1);
                        coor1+=mDy+1;	//Dimenzija ćelije+širina linije
                }
                else{
                        mGrid[i]=sf::Vector2f(coor1,51);
                        mGrid[i+1]=sf::Vector2f(coor1,450);
                        coor1+=mDx+1;	//Dimenzija ćelije+širina linije
                }
        }
        //Postavljamo početno stanje logičkog prikaza mreže(mreža je prazna)
        for(int i=0;i<20;++i)
                for(int j=0;j<10;++j)
                        mGridContent[i][j]=EMPTY;
        //Postavljamo popunu mreže(mGridFill) na defaultno stanje
        float coor2=51+mDy/2;
        coor1=51+mDx/2;
        for(int i=0;i<20;++i){
                for(int j=0;j<10;++j){
                        mGridFill[i][j].setSize(sf::Vector2f(18.9f,18.95f));
                        mGridFill[i][j].setFillColor(sf::Color::Transparent);
                        mGridFill[i][j].setOrigin(mGridFill[i][j].getLocalBounds().width/2,mGridFill[i][j].getLocalBounds().height/2);
                        mGridFill[i][j].setPosition(coor1,coor2);
                        coor1+=(mDx+1+0.055);	//Korekcija od +0.055 kako bi mreža ispravno izgledala
                }
                coor1=51+mDx/2;
                coor2+=(mDy+1+0.026);	//Korekcija od +0.026 kako bi mreža ispravno izgledala
        }
}

bool Board::checkSpace(bool mLeftPressed,bool mUpPressed, bool mRightPressed,bool mSpacePressed) const{
    auto type = mPiece.mType;
    auto rotacija = mPiece.mRotacija;
    auto x = mPiece.mXposition;
    auto y = mPiece.mYposition;
    if(x==0 && y==0){
            for(int i=0;i<4;++i)
                    for(int j=3;j<7;++j)
                            if(mGridContent[i][j]!=EMPTY) return false;
            return true;
    }
    else if(!mLeftPressed && !mUpPressed && !mRightPressed && !mSpacePressed){
            for(int i=0;i<Tetrimino::MAT_SIZE;++i)
                    for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && (y+i>=20 || x-2+j<0 || x-2+j>=10))
                                return false;
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && mGridContent[y+i][x-2+j]!=EMPTY)
                                return false;
                    }
            return true;
    }
    else if(mLeftPressed){
            for(int i=0;i<Tetrimino::MAT_SIZE;++i)
                    for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && (y-1+i>=20 || x-3+j<0 || x-3+j>=10))
                                return false;
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && mGridContent[y-1+i][x-3+j]!=EMPTY)
                                return false;
                    }
            return true;
    }
    else if(mUpPressed){
            for(int i=0;i<Tetrimino::MAT_SIZE;++i)
                    for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]==0 &&
                                    Tetrimino::mDijelovi[type][(rotacija+1)%4][i][j]!=0 &&
                                    (y-1+i>=20 || x-2+j<0 || x-2+j>=10))
                                return false;
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]==0 &&
                                    Tetrimino::mDijelovi[type][(rotacija+1)%4][i][j]!=0 &&
                                    mGridContent[y-1+i][x-2+j]!=EMPTY)
                                return false;
                    }
            return true;
    }
    else if(mRightPressed){
            for(int i=0;i<Tetrimino::MAT_SIZE;++i)
                    for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && (y-1+i>=20 || x-1+j<0 || x-1+j>=10))
                                return false;
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && mGridContent[y-1+i][x-1+j]!=EMPTY)
                                return false;
                    }
            return true;
    }
    else if(mSpacePressed){
            for(int i=0;i<Tetrimino::MAT_SIZE;++i)
                    for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && (y+i>=20 || x-2+j<0 || x-2+j>=10))
                                return false;
                            if(Tetrimino::mDijelovi[type][rotacija][i][j]!=0 && mGridContent[y+i][x-2+j]!=EMPTY)
                                return false;
                    }
            return true;
    }
    else return false;
}

void Board::spawnPiece(){
        int type;
        type=mUniformDist(mRNE);
        if(type==Tetrimino::Types::O){
                mPiece.mType=Tetrimino::Types::O;
               /* mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::I){
                mPiece.mType=Tetrimino::Types::I;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::S){
                mPiece.mType=Tetrimino::Types::S;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::Z){
                mPiece.mType=Tetrimino::Types::Z;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::L){
                mPiece.mType=Tetrimino::Types::L;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::J){
                mPiece.mType=Tetrimino::Types::J;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        else if(type==Tetrimino::Types::T){
                mPiece.mType=Tetrimino::Types::T;
                /*mPiece.mRotacija=0;
                mPiece.mXposition=5;
                mPiece.mYposition=1;
                mPiece.mClock.restart();*/
        }
        mPiece.mRotacija=0;
        mPiece.mXposition=5;
        mPiece.mYposition=1;
        mPiece.mClock.restart();
}

bool Board::isGameOver() const{
        return mGameOver;
}

int Board::getNoLinesCompleted() const{
        return mNoLinesCompleted;
}

virtual void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const override{
    states.transform*=getTransform();
    target.draw(mGrid,states);
    for(int i=0;i<20;++i)
            for(int j=0;j<10;++j)
                    target.draw(mGridFill[i][j],states);
}

void Board::placePiece(){
        for(int i=0;i<Tetrimino::MAT_SIZE;++i)
            for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                if(Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0){
                        mGridFill[mPiece.mYposition-1+i][mPiece.mXposition-2+j].setFillColor(Tetrimino::mColors[mPiece.mType]);
                        mGridContent[mPiece.mYposition-1+i][mPiece.mXposition-2+j]=Tetrimino::Types::SIZE;
                }
            }
}

void Board::removePiece(){
        for(int i=0;i<Tetrimino::MAT_SIZE;++i)
            for(int j=0;j<Tetrimino::MAT_SIZE;++j){
                if(Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0){
                        mGridFill[mPiece.mYposition-1+i][mPiece.mXposition-2+j].setFillColor(sf::Color::Transparent);
                        mGridContent[mPiece.mYposition-1+i][mPiece.mXposition-2+j]=EMPTY;
                }
            }
}

// Pomakni komad ako je moguće. Vrati true ako je pomak izvršen, inače false.
bool Board::movePiece(int x,int y,bool mLeftPressed,bool mUpPressed,bool mRightPressed,bool mSpacePressed){
        if(!checkSpace(mLeftPressed,mUpPressed,mRightPressed,mSpacePressed))
            return false;
        mPiece.move(x,y);
        return true;
}

// Rotiraj komad. Vrati true ako je rotacija izvršena, inače false.
bool Board::rotatePiece(bool mLeftPressed,bool mUpPressed,bool mRightPressed,bool mSpacePressed){
        if(!checkSpace(mLeftPressed,mUpPressed,mRightPressed,mSpacePressed))
            return false;
        mPiece.rotate();
        return true;
}

// Da li je linija y prazna ili nije ?
bool Board::isLineFull(int y) const{
        for(int j=0;j<10;j++)
                if(mGridContent[y][j]==EMPTY) return false;
        return true;
}

// Obriši kompletne linije i vrati broj obrisanih linija
int Board::clearLines(){
        int erased=0;
        for(int line=0;line<20;++line){
            if(isLineFull(line)){
                if(line==0){
                        for(int j=0;j<10;++j){
                                mGridContent[0][j]=EMPTY;
                                mGridFill[0][j].setFillColor(sf::Color::Transparent);
                        }
                }
                else{
                for(int i=line;i-1>=0;--i)
                        for(int j=0;j<10;++j){
                                mGridContent[i][j]=mGridContent[i-1][j];
                                mGridFill[i][j].setFillColor(mGridFill[i-1][j].getFillColor());
                        }
                for(int j=0;j<10;++j){
                                mGridContent[0][j]=EMPTY;
                                mGridFill[0][j].setFillColor(sf::Color::Transparent);
                        }
                }
                ++erased;
            }
        }
        return erased;
}

void Board::update(bool mLeftPressed,bool mUpPressed,bool mRightPressed,bool mSpacePressed){
        if(!checkSpace(false,false,false,false) && mPiece.mXposition==0 && mPiece.mYposition==0){
            mGameOver=true;
        }
        else{
            if(checkSpace(mLeftPressed,mUpPressed,mRightPressed,mSpacePressed) && mPiece.mXposition==0 && mPiece.mYposition==0){
                spawnPiece();
                placePiece();
            }
            else{
                bool nend=true;
                proteklo_vrijeme+=mPiece.mClock.restart();
                if(proteklo_vrijeme.asSeconds()>=mDt) {
                    removePiece();
                    nend=movePiece(0,1,false,false,false,false);
                    proteklo_vrijeme=sf::Time::Zero;
                }
                if(mLeftPressed) {
                    removePiece();
                    movePiece(-1,0,true,false,false,false);
                }
                else if(mUpPressed) {
                    removePiece();
                    rotatePiece(false,true,false,false);
                }
                else if(mRightPressed) {
                    removePiece();
                    movePiece(1,0,false,false,true,false);
                }
                else if(mSpacePressed) {
                    removePiece();
                    while(movePiece(0,1,false,false,false,true));
                    nend=false;
                }
                if(!(mPiece.mXposition==0 && mPiece.mYposition==0))
                    placePiece();
                if(!nend) {
                    mPiece.mXposition=0;
                    mPiece.mYposition=0;
                }
                mNoLinesCompleted+=clearLines();
            }
        }
}
