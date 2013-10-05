//
//  PauseLayer.h
//  Defender
//
//  Created by long shenghua on 13-7-26.
//
//

#ifndef __Defender__PauseLayer__
#define __Defender__PauseLayer__

#include <iostream>
#include "cocos2d.h"
#include "FirstScene.h"
using namespace cocos2d;

class PauseLayer:public CCLayer {
    
public:
    static CCScene* scene(CCRenderTexture *sqr, bool isflip);
    virtual bool init();
    CREATE_FUNC(PauseLayer);
    
    CCMenuItemToggle *pAudio;
    void getPause(CCRenderTexture *sqr, bool isflip);
private:
    void menuResume();
    void menuBackCallback();
    void menuAudioCallback(CCObject *pSender);
    void menuHelpCallback(CCObject *pSender);
    void BgSound(int audio);
};

#endif /* defined(__Defender__PauseLayer__) */
