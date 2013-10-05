//
//  MainGameScene.h
//  popStar
//
//  Created by long shenghua on 13-9-16.
//
//

#ifndef __popStar__MainGameScene__
#define __popStar__MainGameScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MapLayer.h"
#include "GameBg.h"
#include "FirstScene.h"
#include "LeveStartLayer.h"
#include "SoundLayer.h"
#include "TargetScoreData.h"
#include "EffectLayer.h"
#include "ParticleSysLayer.h"
#include "ChannelClass.h"
//#include "ShowWindowLayer.h"
USING_NS_CC;
using namespace CocosDenshion;

class MainGameScene:public CCLayer {
    
public:
    MainGameScene();
    ~MainGameScene();
    static CCScene* scene();
    virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    CREATE_FUNC(MainGameScene);
    
    ChannelClass* channel;
    
    MapLayer* _mapLayer;
    ParticleSysLayer* particleSysLayer;
   // ShowWindowLayer* showWindowLayer;
    SoundLayer* soundLayer;
    TargetScoreData* targetScoreData;
    CCArray* selPaopaoArray;
    
    CCSprite* bg;
    void loadLayer();
    void loadMenu();
    void loadMap();
    void loadBg();
    void loadLeveStartLayer();
    void loadBaozhaLayer();
    void loadData();
    void ccTouchesEnded(CCSet *touches,CCEvent *event);
    
    void findPaopao(CCPoint location,int paopaoType);
    void findPaopao_T(CCPoint location,int paopaoType);
    void findPaopao_R(CCPoint location,int paopaoType);
    void findPaopao_B(CCPoint location,int paopaoType);
    void findPaopao_L(CCPoint location,int paopaoType);
    
    void initselPaopaoArray();
    void clearPaopao();
    void movePaopaoFrLeftToRight();
    void addMark_Row(CCPoint location);
    void addMark_Col(float y);
    void movePaopao();
    void isGameOver();
    void checkGameOver(CCPoint location);
    void showGameOver();
    void showGameOverDone(CCLabelTTF* gameoverTTF);
    void showWin();
    void showWinDone(CCLabelTTF* winTTF);
    void showGood(int showId);
    void hideGood();
    void jiafen(cocos2d::CCPoint location,int value);
    void jiafenDone(cocos2d::CCNode *sender);
    CCSprite* showSprite;

    void playAudio(int audioType);
    
    void menuPausecallback();
    void menuShareCallback();
    void initModeMenu(int continueStat,int gameMode);
    void menuNewGameCallBack();
    void menuContinueCallBack();
    void menuBackCallBack();
    void menuDel(CCMenu* spender);
    void c_magicStarCallBack(CCObject* pSender);
    void initMagicStarMenu();
    
    CCMenuItemImage *pNewGame;
    CCMenuItemImage *pResume;
    CCMenuItemImage *pBack;
    CCMenu* pMenu;

    int curGameMode;
    bool gameStat;
    bool pauseStat;
    int continueStat;
    int gameMode;
    int corlorNum;
    
    int Score = 0;
    int targetScore = 0;
    int stage = 0;
    int bestScore = 0;
    int curStage=1;
    
    int curPaopaoId;
    int curRowNum;
    int curColNum;
    int rowNum;
    int ColNum;
    
    int maxX;
    int minX;
    
    int touchMothed;
    bool haveKey;
    bool isLastJiafen;
    int totalFen;
    float clearSpeed;
    int lastPaopaoNum;
    
    int magicStarType;
    int magicStarNum;
    int MenuStarRowY;
    CCPoint menuStar;
    
    int magicBlockNum;
    bool magicBlockStat;
    void magicBlockProcess(CCPoint location,int paopaoType);
    bool magicChanStat;
    void magicChanProcess(CCPoint location);
    void normalTouchProcess(CCPoint location);
    
    int magicChanNum;
    void equipmentSaveAndGet(int mothed);
    
    char targetScoreChar[128];
    char SelscoreChar[128];
    char ScoreChar[128];
    char stageChar[128];
    char bestScoreChar[128];
    
    int GameParameter;
    void setGameParameter(int GameParameter);
    void initConfig();
    
    GameBg* gameBgLayer;
    EffectLayer* effectLayer;
    CCMenuItemImage *magicBlock;
    CCMenuItemImage *magicChan;
    CCNode* MagicStarMenuNode;
    CCNode* EquipmentMenuNode;
    CCLabelTTF *e_magicStarTTF;
    CCLabelTTF *e_magicBlockTTF;
    CCLabelTTF *e_magicChanTTF;
    
    ////menuLayer
    void initEquipmentMenu();
    void loadMagicStarMenu();
    void loadEquipmentMenu();
    void moveEquipmentMenu();
    void moveMagicStarMenu();
    void menuMagicStarCallBack(CCObject* pSender);
    void menuMagicBlockCallBack(CCObject* pSender);
    void menuMagicChanCallBack(CCObject* pSender);
    void magicAction(CCObject* pSender);
    void c_magicStarLeaveBtnCallBack();
    void purchaseProduct(int productionId);
    void responPurchaseStat();
    void requestProductPrice(int productionId);
    void responProductPrice();
    int TryAgainPurchaseProductId;
    bool menuLock;
    CCTexture2D* m_star;
    
    /////showwindow
    CCSpriteBatchNode* showBgBatchNode;
    void loadPurshaseWinDow();
    void okBtnCallBack(CCObject* pSender);
    void closeBtnCallBack(CCObject* pSender);
    
private:
    void MakeMovePoint();
    void movePaopao(CCPoint point2,CCPoint point3,int paopaoId);
    
    void gameOverProcess();
    void lastPaopaoProcess();
    void showKey();
    void showKeyDone(cocos2d::CCNode *sender);
    
    void test();
    

};
#endif /* defined(__popStar__MainGameScene__) */
