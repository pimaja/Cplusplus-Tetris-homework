#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>

/** Klasa Board
 *
 *  Klasa implementira svu logiku Tetris igre.
 */
class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    Board();
    // Aktualizacija
    void update(bool mLeftPressed,bool mUpPressed, bool mRightPressed,bool mSpacePressed);
    // Pozicioniraj novi tetrimino na ploči.
    void spawnPiece();
    // Vraća true ako je igra gotova, inače false
    bool isGameOver() const;
    // Broj obrisanih linija od zadnje aktualizacije scene.
    int getNoLinesCompleted() const;
    void clearNoLinesCompleted() { mNoLinesCompleted = 0; }
    int times=150; //testiranje
private:
    static const int EMPTY = -1;
    static const int mCols = 10;       // Broj stupaca u mreži
    static const int mRows = 2* mCols; // Broj redaka u mreži

    sf::VertexArray mGrid;             // Linije koje čine mrežu.  
    int mGridContent[mRows][mCols];    // Logički prikaz mreže

    sf::RectangleShape mGridFill[mRows][mCols];	//Ispuna mreže

    sf::Time proteklo_vrijeme=sf::Time::Zero; //Proteklo vrijeme

    // Dimenzije mreže
    float mLeftMargin = 50.f;
    float mTopMargin = 50.0f;
    float mWidth=200.f;
    float mHeight=2*mWidth;
    // Početak mreže = gornji lijevi kut
    float mOriginX, mOriginY;
    // Dimenzije ćelija
    float mDx, mDy;
    // Vremenski interval između propadanja tetrimina.
    float mDt = 0.3f; // sekunde
    // Signalizacija da je igra završena
    bool mGameOver = false;
    // Broj linija obrisanih od jednom (0,1,2,3 ili 4)
    int mNoLinesCompleted = 0;

    // Generiranje slučajnog elementa.
    std::random_device r;
    std::default_random_engine mRNE{r()};
    std::uniform_int_distribution<> mUniformDist{0,6};

    // Komad koji pada
    Tetrimino mPiece;
    // Iscrtavanje
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    // Provjerava da li se komad može smjestiti na ploču.
    bool checkSpace(bool mLeftPressed,bool mUpPressed, bool mRightPressed,bool mSpacePressed) const;
    // Smjesti komad na ploču. Pretpostavlja se da je checkSpace(piece) vratio true.
    void placePiece();
    // Ukloni komad sa ploče.
    void removePiece();
    // Pomakni komad ako je moguće. Vrati true ako je pomak izvršen, inače false.
    bool movePiece(int x, int y, bool mLeftPressed, bool mUpPressed, bool mRightPressed, bool mSpacePressed);
    // Rotiraj komad. Vrati true ako je rotacija izvršena, inače false.
    bool rotatePiece(bool mLeftPressed,bool mUpPressed,bool mRightPressed,bool mSpacePressed);
    // Da li je linija y prazna ili nije ?
    bool isLineFull(int y) const;
    // Obriši kompletne linije i vrati broj obrisanih linija
    int clearLines();
    // Eventualno vaše dodatne metode dolaze ovdje.
    //Pomiče sve linije iznad linije line za jednu prema dolje i pritom briše liniju line (radi na poljima mGridContent i mGridFill)
    void moveLines(int line);
    // Privatne metode koje ne trebate možete slobodno ukloniti.

};

#endif // BOARD_H
