//
//  GameBg.cpp
//  PopStar
//
//  Created by long shenghua on 13-9-11.
//
//

#include "GameBg.h"

GameBg::GameBg(){}
GameBg::~GameBg(){}
bool GameBg::init(){
    if (CCLayer::init()) {
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        loadTTF();        
        //this->schedule(schedule_selector(GameBg::showTTF),3.0f);
        //showTTF();

        return true;
    }else{
        return false;
    }
}
void GameBg::loadTTF(){

 //   CCSprite* curGameModeIcon = CCSprite::create("game_bg.png");
    curGameModeIcon = CCSprite::create("jiemianbeijing.png");
    curGameModeIcon->setAnchorPoint(ccp(0.5,0.5));
    curGameModeIcon->setPosition(ccp(240,160));
    curGameModeIcon->setScale(0.5);
    curGameModeIcon->setRotation(-90);
    this->addChild(curGameModeIcon,10);
    
    scoreTTF = CCLabelTTF::create("0", "Arial", 45);
   // scoreTTF->setPosition(ccp(85, 137));
    scoreTTF->setPosition(ccp(80, 85));
    scoreTTF->setColor(ccc3(0, 0, 0));
    scoreTTF->setRotation(-90);
    scoreTTF->setScale(0.3);
    this->addChild(scoreTTF);
    
    bestScoreTTF = CCLabelTTF::create("0", "Arial", 45);
    //bestScoreTTF->setPosition(ccp(43, 172));
    bestScoreTTF->setPosition(ccp(40, 250));
    bestScoreTTF->setColor(ccc3(0, 0, 0));
    bestScoreTTF->setRotation(-90);
    bestScoreTTF->setScale(0.3);
    this->addChild(bestScoreTTF);
    
    targetScoreTTF = CCLabelTTF::create("0", "Arial", 45);
    targetScoreTTF->setPosition(ccp(40, 130));
    targetScoreTTF->setColor(ccc3(0, 0, 0));
    targetScoreTTF->setRotation(-90);
    targetScoreTTF->setScale(0.3);
    this->addChild(targetScoreTTF);
    
    stageTTF = CCLabelTTF::create("0", "Arial", 45);
    stageTTF->setPosition(ccp(40, 30));
    stageTTF->setColor(ccc3(0, 0, 0));
    stageTTF->setRotation(-90);
    stageTTF->setScale(0.3);
    this->addChild(stageTTF);
    
    selScoreTTF = CCLabelTTF::create("", "Arial", 45);
    selScoreTTF->setPosition(ccp(88, 210));
    selScoreTTF->setColor(ccc3(255, 0, 0));
    selScoreTTF->setRotation(-90);
    selScoreTTF->setScale(0.3);
    this->addChild(selScoreTTF);
    
    //curGameModeIcon = CCSprite::create("Icon.png");
    // curGameModeIcon->setPosition(ccp(85, 12));
    // curGameModeIcon->setScale(0.3);
    // this->addChild(curGameModeIcon);
   // this->setPosition(ccp(480, 0));
}
void GameBg::moveLayer(){
    
}
void GameBg::showTTF(){
    this->setPosition(ccp(0, 0));
       // this->unschedule(schedule_selector(GameBg::showTTF));
        //this->addChild(sp);
       // this->addChild(scoreTTF);
       // this->addChild(bestScoreTTF);
}
CCLabelTTF* GameBg::GetscoreTTF(){
    return scoreTTF;
}
CCLabelTTF* GameBg::GetbestScoreTTF(){
    return bestScoreTTF;
}
CCLabelTTF* GameBg::GettargetScoreTTF(){
    return targetScoreTTF;
}
CCLabelTTF* GameBg::GetstageTTF(){
    return stageTTF;
}
CCLabelTTF* GameBg::GetselScoreTTF(){
    return selScoreTTF;
}
CCSprite* GameBg::GetcurGameModeIcon(){
    return curGameModeIcon;
}
CCSprite* GameBg::getbg(){
    return bg;
}

