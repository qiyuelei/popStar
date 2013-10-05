//
//  LeveStartLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#include "LeveStartLayer.h"
LeveStartLayer::LeveStartLayer(){}
LeveStartLayer::~LeveStartLayer(){}
bool LeveStartLayer::init(){
    if (CCLayer::init()) {
        
       // CCSprite* sp = CCSprite::create("Icon.png");
       // sp->setPosition(ccp(-100,160));
       // addChild(sp);
       // sp->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, ccp(240, 160)), 2.0f) ,NULL));
        showTargetScore();
        return true;
    }else{
        return false;
    }
}
void LeveStartLayer::showTargetScore(){
    labelTTF = CCLabelTTF::create("Level 1      Target score is        1000", "Airal", 40, CCSizeMake(300, 200),kCCTextAlignmentCenter);
    labelTTF->setPosition(ccp(-100, 160));
    labelTTF->setScale(0.5);
    labelTTF->setRotation(-90);
    addChild(labelTTF);
    labelTTF->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(240, 160)), 1.0f) ,CCDelayTime::create(2.0f),CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(-100, 160)), 1.0f) ,CCCallFunc::create(this, callfunc_selector(LeveStartLayer::showTargetScoreDone)),NULL));

}
void LeveStartLayer::showTargetScoreDone(){
    removeChild(labelTTF);
}
CCLabelTTF* LeveStartLayer::getlabelTTF(){
    return labelTTF;
}