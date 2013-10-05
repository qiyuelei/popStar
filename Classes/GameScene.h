//
//  GameScene.h
//  pop
//
//  Created by long shenghua on 13-9-5.
//
//

#ifndef __pop__GameScene__
#define __pop__GameScene__

#include "cocos2d.h"
#include "PaoPao.h"
#include "GameBg.h"
#include "PauseLayer.h"
#include "BaozhaLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

class GameScene:public CCLayer {
    
public:
    GameScene();
    ~GameScene();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);

    virtual void menuPause();
    CCSize winSize;
    int checkNum;
    bool gameStat;
    bool pauseStat;
    int continueStat;
    int gameMode;
    
    int Score = 0;
    int targetScore = 0;
    int stage = 0;
    int bestScore = 0;
    
    char targetScoreChar[128];
    char SelscoreChar[128];
    char ScoreChar[128];
    char stageChar[128];
    char bestScoreChar[128];
    
    int GameParameter;
    
    int rowSpan;
    
    GameBg* gameBgLayer;
    Particle* BaozhaLayer;
    
    CCSprite* showSprite;
    
    int curStage;
    int corlorNum;
    int curGameMode;
    char curGameModeTag[128];
    bool isNewGame;
    int mapSpan;
    int value;
    
    void ccTouchesEnded(CCSet *touches,CCEvent *event);
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref 
    cocos2d::CCTexture2D* xiaoxin_pSpriteTexture; // weak ref
    CCSpriteBatchNode *parent;
    
    CCArray* PaopaoArray;
    CCArray* SelPaopaoArray;

     void setGameParameter(int GameParameter);
    
    void pause();
    void resume();
    void initModeMenu(int continueStat,int gameMode);
    void initPauseMenu();
    
    void menuNewGameCallBack();
    void menuContinueCallBack();
    void menuBackCallBack();
    
    void menuDel(CCObject spender);

    void jiafen(CCPoint location);
    void jiafenDone(cocos2d::CCNode *sender);
private:

    void getCurStage(bool isNewGame,int curGameMode);

    void test();
private:
    
    void initConfig();
    void initGamebg();
    void initMenu();
    void initBaozhaLayer();
    
    void initPaopaoArray();
    void findPaopao(CCPoint location,int paopaoType);
    void findPaopao_T(CCPoint location,int paopaoType);
    void findPaopao_R(CCPoint location,int paopaoType);
    void findPaopao_B(CCPoint location,int paopaoType);
    void findPaopao_L(CCPoint location,int paopaoType);
private:

    void addPaopao(CCPoint location);
    void addBaozha(CCPoint location);
    void testFinsh();
    void initMap();

    void selPaopao(int idy);
    void moveSelPaopao();

private:
    
    void movePaopao();
    void movePaopao_T();
    void MovePaopao_L();

private:
   
    void update();
    void isGameOver();
    void GameOverProcess();
    void delPaopao();
    
    void startNewStage();

    void saveAndExit();
    void addPauseBtn();
    void movePauseBtn();
    void menuNewGame();
    void fnPlayer(int GameParameter);
    
    CCMenuItemImage *pNewGame;
    CCMenuItemImage *pResume;
    CCMenuItemImage *pBack;
    CCMenu* pMenu;    
    
    void showGood(int showId);
    void hideGood();
    void showGameOver();
    void showGameOverDone(cocos2d::CCNode *sender);
 };

#endif /* defined(__pop__GameScene__) */
