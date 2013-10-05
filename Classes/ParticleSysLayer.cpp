//
//  ParticleSysLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-30.
//
//

#include "ParticleSysLayer.h"
ParticleSysLayer::ParticleSysLayer(){
    m_particleBatchNode = CCParticleBatchNode::create("LineLight01.png");
    m_tomatoBatchNode = CCParticleBatchNode::create("Tomato.png");
    m_chargeBatchNode = CCParticleBatchNode::create("Charge.png");
    m_nebiaBatchNode = CCParticleBatchNode::create("Nebia.png");
    CC_SAFE_RETAIN(m_particleBatchNode);
    CC_SAFE_RETAIN(m_tomatoBatchNode);
    CC_SAFE_RETAIN(m_chargeBatchNode);
    CC_SAFE_RETAIN(m_nebiaBatchNode);
    
    m_magicBallBatchNode = CCParticleBatchNode::create("MagicBall.png");
    CC_SAFE_RETAIN(m_magicBallBatchNode);
}
ParticleSysLayer::~ParticleSysLayer(){
    CC_SAFE_RELEASE_NULL(m_particleBatchNode);
    CC_SAFE_RELEASE_NULL(m_tomatoBatchNode);
    CC_SAFE_RELEASE_NULL(m_chargeBatchNode);
    CC_SAFE_RELEASE_NULL(m_nebiaBatchNode);
    CC_SAFE_RELEASE_NULL(m_magicBallBatchNode);
}
bool ParticleSysLayer::init(){
    if (CCLayer::init()) {
        
        
        //CCSprite* sp = CCSprite::create("Icon.png");
       // sp->setPosition(ccp(100, 100));
        //addChild(sp);
        
        this->addChild(m_particleBatchNode);
        this->addChild(m_tomatoBatchNode);
        this->addChild(m_chargeBatchNode);
        this->addChild(m_nebiaBatchNode);
        this->addChild(m_magicBallBatchNode);
        
        //CCParticleBatchNode* _pp = CCParticleBatchNode::create("LineLight01.plist");
       // CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("LineLight01.plist");
        
      //  mParticle->setPosition(CCPointZero);
       // mParticle->setAutoRemoveOnFinish(true);
       // m_particleBatchNode->addChild(mParticle);
        
       // this->addChild(_pp);
       // _pp->addChild(_psq);
        
        return true;
    }else{
        return false;
    }
}
void ParticleSysLayer::ParticlePlay(int ParticleType, cocos2d::CCPoint location){

        CCLog("particletype:%i",ParticleType);
        CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("LineLight01.plist");
        mParticle->setPosition(location);
        mParticle->setAutoRemoveOnFinish(true);
        m_particleBatchNode->addChild(mParticle);
    

    //mParticle->setPosVar(ccp(0, 200));
    //mParticle->setPosVar(ccp(200, 0));

    
}
void ParticleSysLayer::TomatoPlay(int paopaoType, cocos2d::CCPoint location){

    CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("Tomato.plist");
    mParticle->setTextureWithRect(m_tomatoBatchNode->getTexture(), CCRectMake(64*paopaoType, 0, 64, 64));
    mParticle->setPosition(location);
    //mParticle->setDuration(2.0f);
    mParticle->setAutoRemoveOnFinish(true);
    m_tomatoBatchNode->addChild(mParticle);
}
void ParticleSysLayer::ChargePlay(int paopaoType, cocos2d::CCPoint location){
   // CCLog("paopaoType:%i",paopaoType);
    CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("Charge.plist");
    mParticle->setTextureWithRect(m_chargeBatchNode->getTexture(), CCRectMake(31*paopaoType, 0, 31, 31));
    mParticle->setPosition(location);
    //mParticle->setDuration(2.0f);
    mParticle->setAutoRemoveOnFinish(true);
    m_chargeBatchNode->addChild(mParticle);
}
void ParticleSysLayer::NebiaPlay(int paopaoType, cocos2d::CCPoint location){
    
    CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("Nebia.plist");
    // mParticle->setTextureWithRect(m_chargeBatchNode->getTexture(), CCRectMake(0, 0, 64, 64));
    mParticle->setPosition(location);
    mParticle->setAutoRemoveOnFinish(true);
    m_nebiaBatchNode->addChild(mParticle);
}
void ParticleSysLayer::MagicBallPlay(int paopaoType, cocos2d::CCPoint location){
    
    CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("MagicBall.plist");
    // mParticle->setTextureWithRect(m_chargeBatchNode->getTexture(), CCRectMake(0, 0, 64, 64));
    mParticle->setPosition(location);
    mParticle->setAutoRemoveOnFinish(true);
    mParticle->setZOrder(1);
    m_magicBallBatchNode->addChild(mParticle);
}