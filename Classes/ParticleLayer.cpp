//
//  ParticleLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#include "ParticleLayer.h"
ParticleLayer::ParticleLayer(){}
ParticleLayer::~ParticleLayer(){}
bool ParticleLayer::init(){
    if (CCLayer::init()) {
        
       // CCSprite* sp = CCSprite::create("Icon.png");
       // sp->setPosition(ccp(100,160));
      //  addChild(sp);
        
        //addParticleExplosion(ccp(150, 150), 1);
        return true;
    }else{
        return false;
    }
}
void ParticleLayer::addParticleExplosion(CCPoint location,int PaopaoType){
    // CCLog("explosion");
    m_emitter = CCParticleExplosion::create();
    m_emitter->retain();
    addChild(m_emitter, 10);
    
    switch (PaopaoType) {
           // LitterStar1 = CCTextureCache::sharedTextureCache()->addImage("huangxingxing.png");
          //  LitterStar2 = CCTextureCache::sharedTextureCache()->addImage("lanxingxing.png");
          //  LitterStar3 = CCTextureCache::sharedTextureCache()->addImage("lvxingxing.png");
            // LitterStar4 = CCTextureCache::sharedTextureCache()->addImage("hongxingxing.png");
            // LitterStar5 = CCTextureCache::sharedTextureCache()->addImage("chengxingxing.png");
            // LitterStar6 = CCTextureCache::sharedTextureCache()->addImage("fensexingxing.png");
            //LitterStar6 = CCTextureCache::sharedTextureCache()->addImage("Icon.png");
            
            
        case 0:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("huangxingxing.png");
            break;
        case 1:
            //starTexture = LitterStar2;
            starTexture = CCTextureCache::sharedTextureCache()->addImage("lanxingxing.png");
            break;
        case 2:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("lvxingxing.png");
            break;
        case 3:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("hongxingxing.png");
            break;
        case 4:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("chengxingxing.png");
            break;
        case 5:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("fensexingxing.png");
            break;
        case 6:
            starTexture = CCTextureCache::sharedTextureCache()->addImage("fensexingxing.png");
            break;
        default:
           // starTexture = LitterStar1;
            break;
    }
    
    //m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Icon.png"));
    m_emitter->setTexture(starTexture);
    
    // m_emitter->setAutoRemoveOnFinish(true);
    m_emitter->setEmissionRate(90);
    m_emitter->setStartColor(ccc4f(1, 255, 255, 255));
    m_emitter->setStartColorVar(ccc4f(0, 0, 0, 0));
    
    m_emitter->setEndColor(ccc4f(1, 255, 255, 255));
    m_emitter->setEndColorVar(ccc4f(0, 0, 0, 0));
    
    // m_emitter->setPositionType(kCCPositionTypeGrouped);
    m_emitter->setGravity(ccp(240,0));
    
    m_emitter->setStartSize(5);
    m_emitter->setStartSizeVar(5);
    
    m_emitter->setEndSize(0);
    m_emitter->setEndSizeVar(0);
    m_emitter->setAutoRemoveOnFinish(true);
    
    m_emitter->setPosition(location);
    
}
