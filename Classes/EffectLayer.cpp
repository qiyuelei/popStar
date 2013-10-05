//
//  EffectLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-27.
//
//

#include "EffectLayer.h"

EffectLayer::EffectLayer(){}
EffectLayer::~EffectLayer(){}
bool EffectLayer::init(){
    if (CCLayer::init()) {
        
        
       // CCSprite* sp = CCSprite::create("Icon.png");
       // sp->setPosition(ccp(100, 100));
       // addChild(sp);
        
        
        
        
        return true;
    }else{
        return false;
    }
}
void EffectLayer::loadEquipmentNum(){
    MagicStarSprite = CCSprite::create("Icon.png");
    MagicStarSprite->setPosition(ccp(100, 100));
    MagicStarSprite->setScale(0.5);
   // addChild(MagicStarSprite);
    
    MagicStarTTF = CCLabelTTF::create("1", "Arial", 55);
    MagicStarTTF->setPosition(ccp(100, 100));
   //addChild(MagicStarTTF);
    
}
CCSprite* EffectLayer::getMagicStarSprite(){
    return MagicStarSprite;
}
CCLabelTTF* EffectLayer::getMagicStarTTF(){
    return MagicStarTTF;
}

void EffectLayer::onExit(){
    CCLayer::onExit();
}
void EffectLayer::onEnter(){
    //this->schedule(schedule_selector(MainGameScene::loadMap), 5.0f);
    //CCLog("onEnter");
    CCLayer::onEnter();
}