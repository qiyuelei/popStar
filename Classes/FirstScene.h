//
//  FirstScene.h
//  popStar
//
//  Created by long shenghua on 13-9-11.
//
//

#ifndef __popStar__FirstScene__
#define __popStar__FirstScene__

#include "cocos2d.h"
#include "GameScene.h"
#include "MainGameScene.h"
#include "BaozhaLayer.h"
#include "SoundLayer.h"

USING_NS_CC;
using namespace std;

class FirstScene:public CCLayer {
    
public:
    FirstScene();
    ~FirstScene();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(FirstScene);
    
    CCSpriteBatchNode* parent;
    CCTexture2D* m_pSpriteTexture;
    
    CCMenuItemToggle* pAudio;
    CCMenuItemToggle* pMusicAudio;
    
    CCMenu* pHomeMenu;
    CCMenu* pSmMenu;
    CCMenu* pcmMenu;
    CCMenu* pchmMenu;
    
    SoundLayer* soundLayer;
    
    bool gameMenuStat;
    bool homeMenuStat;
    
    void fnPlayer(int GameParameter);
private:
    void initBackGround();
    void addStar(float scale,CCPoint location,int starType);
    void initHomeMenu();
    void initGameMenu();
    void initOtherMenu();
    void initData();

    
    void fnSm();
    void fnCm();
    void fnChm();
    void menuAudioCallback();
    void menuBackGroundMusicback();
    
    void fnSmNewGame();
    void fnSmContinue();
    void fnSmBack();
    
    void fnCmNewGame();
    void fnCmContinue();
    void fnCmBack();
    
    void fnChmNewGame();
    void fnChmContinue();
    void fnChmBack();
    
    void MenuMoveIn(CCMenu* InMenu,CCMenu* OutMenu);
    void MenuMoveOut(CCMenu* menu);
};

#endif /* defined(__popStar__FirstScene__) */
