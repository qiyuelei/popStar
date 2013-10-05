//
//  SoundLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#ifndef __popStar__SoundLayer__
#define __popStar__SoundLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class SoundLayer:public CCLayer {
    
public:
    SoundLayer();
    ~SoundLayer();
    virtual bool init();
    CREATE_FUNC(SoundLayer);
    
    void playBgSound(int audioType);
    void playEffect(int audioType);
    void stopBgSound(int audioType);
    void stopEffect(int audioType);
};

#endif /* defined(__popStar__SoundLayer__) */
