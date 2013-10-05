//
//  FirstScene.cpp
//  popStar
//
//  Created by long shenghua on 13-9-11.
//
//

#include "FirstScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


FirstScene::FirstScene(){}
FirstScene::~FirstScene(){}
bool FirstScene::init(){
    if ( !CCLayer::init() )
    {
        return false;
    }
   // CCLog("test:%i",test1);
    initData();
    gameMenuStat = true;
    homeMenuStat = true;
    
    CCSpriteBatchNode* parent = CCSpriteBatchNode::create("baixing_da.png", 50);
    m_pSpriteTexture = parent->getTexture();
    addChild(parent, 0, 1);
    
    initBackGround();
    addStar(1,CCPoint(20,100),3);
    addStar(1,CCPoint(118,300),2);
    addStar(0.5,CCPoint(20,200),1);
    addStar(0.3,CCPoint(100,15),1);
    initHomeMenu();
    initGameMenu();
    initOtherMenu();
    
    soundLayer = SoundLayer::create();
    addChild(soundLayer);
    
    soundLayer->playBgSound(1);
    //if (CCUserDefault::sharedUserDefault()->getIntegerForKey("backGroundMusic") == 1) {
     //   CCLog("music");
       // SimpleAudioEngine::sharedEngine()->playEffect("good.wav");
    //   SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.wav", true);
   // }
    
    return true;
}
void FirstScene::initBackGround(){
    CCSprite* bg = CCSprite::create("first_bg.png");
    bg->setPosition(ccp(240,160));
    bg->setRotation(-90);
    bg->setScale(0.5);
    addChild(bg);
}
void FirstScene::addStar(float scale,CCPoint location,int starType){
    CCSprite* star = CCSprite::createWithTexture(m_pSpriteTexture);
    star->setPosition(location);
    star->setScale(scale);
    addChild(star);
    
    if (starType == 1) {
        CCRotateTo* rotate1 = CCRotateTo::create(3.0f, 180);
        CCRotateTo* rotate2 = CCRotateTo::create(3.0f, 360);
        CCSequence* seq = CCSequence::create(rotate1,rotate2,NULL);
        CCRepeatForever* repeat = CCRepeatForever::create(seq);
        star->runAction(repeat);
    }else if (starType == 2){
        CCScaleTo* scale1 = CCScaleTo::create(3.0f, scale);
        CCScaleTo* scale2 = CCScaleTo::create(3.0f, 0.1);
        CCSequence* seq2 = CCSequence::create(scale1,scale2,NULL);
        CCRepeatForever* repeat2 = CCRepeatForever::create(seq2);
        star->runAction(repeat2);
    }else if(3){
         CCScaleTo* scale1 = CCScaleTo::create(3.0f, scale);
         CCRotateTo* rotate1 = CCRotateTo::create(2.0f, 180);
         CCSpawn* spwn1 = CCSpawn::create(scale1,rotate1,NULL);
        
         CCScaleTo* scale2 = CCScaleTo::create(3.0f, 0.1);
         CCRotateTo* rotate2 = CCRotateTo::create(3.0f, 360);
         CCSpawn* spwn2 = CCSpawn::create(scale2,rotate2,NULL);
        
         CCSequence* seq = CCSequence::create(spwn1,spwn2,NULL);
         CCRepeatForever* repeat2 = CCRepeatForever::create(seq);
         star->runAction(repeat2);
    }
}
void FirstScene::initGameMenu(){
    
}
void FirstScene::initOtherMenu(){
    
    CCMenuItemImage *btnOn = CCMenuItemImage::create("youshengyin.png", "wushengyin.png");
    CCMenuItemImage *btnOff = CCMenuItemImage::create("wushengyin.png", "youshengyin.png");
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("backGroundMusic",0)==0) {
        pAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(FirstScene::menuBackGroundMusicback), btnOff,btnOn,NULL);
    }else{
        pAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(FirstScene::menuBackGroundMusicback), btnOn,btnOff,NULL);
    }
    pAudio->setPosition(ccp(20,20));
    pAudio->setScale(0.2);
    pAudio->setRotation(-90);
    
    
    CCMenuItemImage *MusicbtnOn = CCMenuItemImage::create("youyinyue.png", "wuyinyue.png");
    CCMenuItemImage *MusicbtnOff = CCMenuItemImage::create("wuyinyue.png", "youyinyue.png");
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic",0)==0) {
        pMusicAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(FirstScene::menuAudioCallback), MusicbtnOff,MusicbtnOn,NULL);
    }else{
        pMusicAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(FirstScene::menuAudioCallback), MusicbtnOn,MusicbtnOff,NULL);
    }
    pMusicAudio->setPosition(ccp(20,45));
    pMusicAudio->setScale(0.2);
    pMusicAudio->setRotation(-90);
    
    // create menu, it's an autorelease object
    CCMenu* pOtherMenu = CCMenu::create(pAudio,pMusicAudio, NULL);
    pOtherMenu->setPosition( CCPointZero );
    this->addChild(pOtherMenu, 10);
}
void FirstScene::initHomeMenu(){
    
    CCMenuItemImage *pSm = CCMenuItemImage::create("sm_before.png", "sm_after.png",this,menu_selector(FirstScene::fnSm));
    pSm->setPosition(ccp(210,160));
    pSm->setRotation(-90);
    pSm->setScale(0.4);
    
    CCMenuItemImage *pCm = CCMenuItemImage::create("cm_before.png", "cm_after.png",this,menu_selector(FirstScene::fnCm));
    pCm->setPosition(ccp(255,160));
    pCm->setRotation(-90);
    pCm->setScale(0.4);
    
    CCMenuItemImage *pChm = CCMenuItemImage::create("ch_before.png", "ch_after.png",this,menu_selector(FirstScene::fnChm));
    pChm->setPosition(ccp(300,160));
    pChm->setRotation(-90);
    pChm->setScale(0.4);
    
    pHomeMenu = CCMenu::create(pSm,pChm,pCm, NULL);
    pHomeMenu->setPosition( CCPointZero );
    this->addChild(pHomeMenu, 10);

 //SmMenu==============================================;
    CCMenuItemImage* pSmNewGame = CCMenuItemImage::create("Smnew_before.png", "Smnew_after.png",this,menu_selector(FirstScene::fnSmNewGame));
    pSmNewGame->setPosition(ccp(210,160));
    pSmNewGame->setRotation(-90);
    pSmNewGame->setScale(0.4);
    
    
    CCMenuItemImage* pSmResume = CCMenuItemImage::create("Smcontinue_before.png", "Smcontinue_after.png",this,menu_selector(FirstScene::fnSmContinue));
    pSmResume->setPosition(ccp(255,160));
    pSmResume->setRotation(-90);
    pSmResume->setScale(0.4);
    
    CCMenuItemImage* pSmBack = CCMenuItemImage::create("Smback_before.png", "Smback_after.png",this,menu_selector(FirstScene::fnSmBack));
    pSmBack->setPosition(ccp(300,160));
    pSmBack->setRotation(-90);
    pSmBack->setScale(0.4);
    
    
      // create menu, it's an autorelease object
    pSmMenu = CCMenu::create(pSmNewGame,pSmResume,pSmBack, NULL);
    pSmMenu->setPosition(ccp(0, 320));
    this->addChild(pSmMenu, 10);
    
    //CmMenu=============================================;
    CCMenuItemImage* pCmNewGame = CCMenuItemImage::create("Cmnew_before.png", "Cmnew_after.png",this,menu_selector(FirstScene::fnCmNewGame));
    pCmNewGame->setPosition(ccp(210,160));
    pCmNewGame->setRotation(-90);
    pCmNewGame->setScale(0.4);
    
    
    CCMenuItemImage* pCmResume = CCMenuItemImage::create("Cmcontinue_before.png", "Cmcontinue_after.png",this,menu_selector(FirstScene::fnCmContinue));
    pCmResume->setPosition(ccp(255,160));
    pCmResume->setRotation(-90);
    pCmResume->setScale(0.4);
    
    CCMenuItemImage* pCmBack = CCMenuItemImage::create("Cmback_before.png", "Cmback_after.png",this,menu_selector(FirstScene::fnCmBack));
    pCmBack->setPosition(ccp(300,160));
    pCmBack->setRotation(-90);
    pCmBack->setScale(0.4);
    
    
    // create menu, it's an autorelease object
    pcmMenu = CCMenu::create(pCmNewGame,pCmResume,pCmBack, NULL);
    pcmMenu->setPosition(ccp(0, 320));
    this->addChild(pcmMenu, 10);
    
    //ChmMenu==========================================;
    CCMenuItemImage* pChmNewGame = CCMenuItemImage::create("Chmnew_bafore.png", "Chmnew_after.png",this,menu_selector(FirstScene::fnChmNewGame));
    pChmNewGame->setPosition(ccp(210,160));
    pChmNewGame->setRotation(-90);
    pChmNewGame->setScale(0.4);
    
    
    CCMenuItemImage* pChmResume = CCMenuItemImage::create("Chmcontinue_before.png", "Chmcontinue_after.png",this,menu_selector(FirstScene::fnChmContinue));
    pChmResume->setPosition(ccp(255,160));
    pChmResume->setRotation(-90);
    pChmResume->setScale(0.4);
    
    CCMenuItemImage* pChmBack = CCMenuItemImage::create("Chmback_before.png", "Chmback_after.png",this,menu_selector(FirstScene::fnChmBack));
    pChmBack->setPosition(ccp(300,160));
    pChmBack->setRotation(-90);
    pChmBack->setScale(0.4);
    
    
    // create menu, it's an autorelease object
    pchmMenu = CCMenu::create(pChmNewGame,pChmResume,pChmBack, NULL);
    pchmMenu->setPosition(ccp(0, 320));
    this->addChild(pchmMenu, 10);
}
void FirstScene::fnPlayer(int GameParameter){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", GameParameter);
    CCUserDefault::sharedUserDefault()->flush();
    //CCScene* sc = GameScene::scene();
    CCScene* sc = MainGameScene::scene();
   // CCTransitionShrinkGrow *fade = CCTransitionShrinkGrow::create(1.5f, sc);
   // CCTransitionPageTurn *fade = CCTransitionPageTurn::create(0.3f, sc,true);
    sc->setRotation(90);
    sc->setPosition(ccp(80, 80));
    CCDirector::sharedDirector()->replaceScene(sc);
}
void FirstScene::fnSm(){
    if (homeMenuStat) {
        homeMenuStat = false;
        gameMenuStat = true;
        MenuMoveIn(pSmMenu,pHomeMenu);
            }
}
void FirstScene::fnCm(){
    if (homeMenuStat) {
        homeMenuStat = false;
        gameMenuStat = true;
        MenuMoveIn(pcmMenu,pHomeMenu);
    }
}
void FirstScene::fnChm(){
    if (homeMenuStat) {
        homeMenuStat = false;
        gameMenuStat = true;
        MenuMoveIn(pchmMenu,pHomeMenu);
    }
}
void FirstScene::menuAudioCallback(){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic",0) == 1) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("soundMusic", 0);
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    }else{
        CCUserDefault::sharedUserDefault()->setIntegerForKey("soundMusic", 1);
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    }
    CCUserDefault::sharedUserDefault()->flush();
}
void FirstScene::menuBackGroundMusicback(){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("backGroundMusic",0) == 1) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("backGroundMusic", 0);
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }else{
        CCUserDefault::sharedUserDefault()->setIntegerForKey("backGroundMusic", 1);
        //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.wav", true);
        soundLayer->playBgSound(1);
    }
    CCUserDefault::sharedUserDefault()->flush();
}
void FirstScene::fnSmNewGame(){
    fnPlayer(11);
}
void FirstScene::fnSmContinue(){
    fnPlayer(12);
}
void FirstScene::fnSmBack(){
      if (gameMenuStat) {
        gameMenuStat = false;
        homeMenuStat = true;
        MenuMoveIn(pHomeMenu, pSmMenu);
          }
}

void FirstScene::fnCmNewGame(){
    fnPlayer(21);
}
void FirstScene::fnCmContinue(){
    fnPlayer(22);
}
void FirstScene::fnCmBack(){
    if (gameMenuStat) {
        gameMenuStat = false;
        homeMenuStat = true;
        MenuMoveIn(pHomeMenu, pcmMenu);
    }
}

void FirstScene::fnChmNewGame(){
    fnPlayer(31);
}
void FirstScene::fnChmContinue(){
    fnPlayer(32);
}
void FirstScene::fnChmBack(){
    if (gameMenuStat) {
        gameMenuStat = false;
        homeMenuStat = true;
        MenuMoveIn(pHomeMenu, pchmMenu);
    }
}

void FirstScene::MenuMoveIn(CCMenu* InMenu,CCMenu* OutMenu){
    if (OutMenu == pHomeMenu) {
     CCMoveTo* moveOut = CCMoveTo::create(0.5f, CCPointMake(OutMenu->getPositionX(), OutMenu->getPositionY()-320));
    OutMenu->runAction(CCEaseBackIn::create(CCSequence::create(moveOut,NULL)));
    }else{
      CCMoveTo* moveOut = CCMoveTo::create(0.5f, CCPointMake(OutMenu->getPositionX(), OutMenu->getPositionY()+320));
    OutMenu->runAction(CCEaseBackIn::create(CCSequence::create(moveOut,NULL)));
    }
    
    if (InMenu == pHomeMenu) {
         CCMoveTo* moveIn = CCMoveTo::create(0.5f, CCPointMake(InMenu->getPositionX(), InMenu->getPositionY()+320));
            InMenu->runAction(CCEaseBackIn::create(CCSequence::create(moveIn,NULL)));
    }else{
         CCMoveTo* moveIn = CCMoveTo::create(0.5f, CCPointMake(InMenu->getPositionX(), InMenu->getPositionY()-320));
            InMenu->runAction(CCEaseBackIn::create(CCSequence::create(moveIn,NULL)));
    }
    
    //OutMenu->runAction(CCEaseBackIn::create(CCSequence::create(move1,NULL)));
}

void FirstScene::MenuMoveOut(CCMenu* menu){}
void FirstScene::initData(){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("firstTime") == 0) {
        CCLog("firstTime");
        CCUserDefault::sharedUserDefault()->setIntegerForKey("firstTime",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("backGroundMusic",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("soundMusic",1);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageSm",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreSm",0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreSm",0);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageCm",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreCm",0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreCm",0);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageChm",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreChm",0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreChm",0);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("magicStarNum",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum",1);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("magicChanNum",1);

        CCUserDefault::sharedUserDefault()->flush();
    }else{
       // CCLog("second");

    }
}
CCScene* FirstScene::scene(){
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FirstScene *layer = FirstScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    scene->setRotation(90);
    scene->setPosition(ccp(80, 80));
    // return the scene
    return scene;

}