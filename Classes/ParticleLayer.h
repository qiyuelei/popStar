//
//  ParticleLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#ifndef __popStar__ParticleLayer__
#define __popStar__ParticleLayer__

#include "cocos2d.h"
USING_NS_CC;
class ParticleLayer:public CCLayer {
    
public:
    ParticleLayer();
    ~ParticleLayer();
    virtual bool init();
    CREATE_FUNC(ParticleLayer);
    CCParticleSystem*    m_emitter;
    CCSprite*            m_background;
    CCTexture2D* xinxinTexture;
    CCTexture2D* starTexture;
    void addParticleExplosion(CCPoint location,int PaopaoType);
};

#endif /* defined(__popStar__ParticleLayer__) */
