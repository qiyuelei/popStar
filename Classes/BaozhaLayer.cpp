//
//  BaozhaLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-15.
//
//

#include "BaozhaLayer.h"
Particle::Particle(){}
Particle::~Particle(){}
bool Particle::init(){
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 0))) {
        
       // CCTexture2D* test = CCTextureCache::sharedTextureCache()->addImage("Icon.png");
        //initLitterStar();
        
        //this->setTouchEnabled(true);
        addParticleExplosion(ccp(200, 200), 1);
         CCSprite* sp = CCSprite::create("Icon.png");
         sp->setPosition(ccp(100,160));
         addChild(sp);
        return true;
    }else{
        return false;
    }
}

void Particle::addParticleExplosion(CCPoint location,int PaopaoType){
   // CCLog("explosion");
    m_emitter = CCParticleExplosion::create();
    m_emitter->retain();
    addChild(m_emitter, 10);
    
    switch (PaopaoType) {
        case 0:
            starTexture = LitterStar1;
            break;
        case 1:
            //starTexture = LitterStar2;
            starTexture = CCTextureCache::sharedTextureCache()->addImage("lanxingxing.png");
            break;
        case 2:
            starTexture = LitterStar3;
            break;
        case 3:
            starTexture = LitterStar4;
            break;
        case 4:
            starTexture = LitterStar5;
            break;
        case 5:
            starTexture = LitterStar6;
            break;
        case 6:
            starTexture = LitterStar6;
            break;
        default:
            starTexture = LitterStar1;
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

    
     setEmitterPosition(location);
    
}
void Particle::ccTouchesEnded(CCSet *touches,CCEvent *event)
{
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = this->convertTouchToNodeSpace(touch);
    
   // ParticleExplosion(location);
    //setEmitterPosition(location);
}
void Particle::setEmitterPosition(CCPoint location){
    m_emitter->setPosition(location);
}

void Particle::initLitterStar(){
    LitterStar1 = CCTextureCache::sharedTextureCache()->addImage("huangxingxing.png");
    LitterStar2 = CCTextureCache::sharedTextureCache()->addImage("lanxingxing.png");
    LitterStar3 = CCTextureCache::sharedTextureCache()->addImage("lvxingxing.png");
   // LitterStar4 = CCTextureCache::sharedTextureCache()->addImage("hongxingxing.png");
   // LitterStar5 = CCTextureCache::sharedTextureCache()->addImage("chengxingxing.png");
   // LitterStar6 = CCTextureCache::sharedTextureCache()->addImage("fensexingxing.png");
    //LitterStar6 = CCTextureCache::sharedTextureCache()->addImage("Icon.png");



}
//CCScene* Particle::scene(){
 //   CCScene* scene = CCScene::create();
  //  Particle* layer = Particle::create();
 //   scene->addChild(layer);
 //   return scene;
//}