//
//  PauseLayer.cpp
//  Defender
//
//  Created by long shenghua on 13-7-26.
//
//

#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
CCScene* PauseLayer::scene(cocos2d::CCRenderTexture *sqr, bool isflip)
{
    CCScene* scene = CCScene::create();
    
    CCSprite* _spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    //CCSprite* _spr = CCSprite::create("Icon.png");
    _spr->setAnchorPoint(CCPointZero);
    _spr->setPosition(CCPointZero);
    _spr->setFlipY(isflip);
    // _spr->setFlipX(isflip);
    _spr->setColor(ccGRAY);
    scene->addChild(_spr);
    
    
    PauseLayer* layer = PauseLayer::create();
    scene->addChild(layer);
    return scene;
}
bool PauseLayer::init()
{
    if (CCLayer::init()) {
        
        //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
         //SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        //CCMenuItemFont *resumeMenuItem = CCMenuItemFont::create("Resume", this, menu_selector(PauseLayer::menuResume));
        CCMenuItemImage* resumeMenuItem = CCMenuItemImage::create("Icon.png", "Icon.png",this,menu_selector(PauseLayer::menuResume));
        resumeMenuItem->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
        
        
        CCMenuItemImage *pBack = CCMenuItemImage::create("Icon.png", "Icon.png",this,menu_selector(PauseLayer::menuBackCallback));
        pBack->setPosition(ccp(winSize.width*0.5+200,winSize.height*0.5-130));
        
        CCMenuItemImage *pHelp = CCMenuItemImage::create("help_before.png", "help_after.png",this,menu_selector(PauseLayer::menuHelpCallback));
        pHelp->setPosition(ccp(winSize.width*0.5-200,winSize.height*0.5-130));
        
        CCMenuItemImage *btnOn = CCMenuItemImage::create("quiet_before.png", "voice_before.png");
        CCMenuItemImage *btnOff = CCMenuItemImage::create("voice_before.png", "quiet_before.png");
        
        if (CCUserDefault::sharedUserDefault()->getIntegerForKey("audio",0)==1) {
            pAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(PauseLayer::menuAudioCallback), btnOff,btnOn,NULL);
        }else{
            pAudio = CCMenuItemToggle::createWithTarget(this, menu_selector(PauseLayer::menuAudioCallback), btnOn,btnOff,NULL);
        }
        pAudio->setPosition(ccp(winSize.width*0.5-200,winSize.height*0.5-85));

         //CCMenu* m_pMenu = CCMenu::create(resumeMenuItem,pAudio,pBack,pHelp,NULL);
        CCMenu* m_pMenu = CCMenu::create(resumeMenuItem,pBack,NULL);
        m_pMenu->setPosition(CCPointZero);
        this->addChild(m_pMenu);
        return true;
    }else{
        return false;
    }
}
void PauseLayer::menuResume()
{
    //CCLog("Resume");
    // CCScene* scene = PauseLayer::create();
   // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
   // SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("checkPauseInt", 0);
    CCUserDefault::sharedUserDefault()->flush();
    CCDirector::sharedDirector()->popScene();
}
void PauseLayer::menuAudioCallback(cocos2d::CCObject *pSender)
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("audio",0)==1) {
        this->BgSound(0);
       // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
       // SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        CCUserDefault::sharedUserDefault()->setIntegerForKey("audio", 0);
    }else{
        this->BgSound(1);
         //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
         //SimpleAudioEngine::sharedEngine()->resumeAllEffects();
        CCUserDefault::sharedUserDefault()->setIntegerForKey("audio", 1);
    }
    CCUserDefault::sharedUserDefault()->flush();
    // CCLOG("audio:%i",audio);
}
void PauseLayer::BgSound(int audio)
{
   // CCLOG("audio:%i",audio);
    if (audio == 1) {
        // SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.caf", true);
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg1.caf", true);
       // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        //SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    }else{
       // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
       SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
}
void PauseLayer::menuBackCallback()
{
  //  SimpleAudioEngine::sharedEngine()->end();
   // CCScene *firstScene = FirstScene::create();
  //  CCDirector::sharedDirector()->replaceScene(firstScene);
}
void PauseLayer::menuHelpCallback(cocos2d::CCObject *pSender)
{
   // CCScene *helpScene = HelpLayer::create();
  //  CCDirector::sharedDirector()->replaceScene(helpScene);
   // HelpLayer *HelpLayer = HelpLayer::create();
    //this->addChild(HelpLayer);
    //CCScene *helpScene = HelpLayer::create();
   // CCDirector::sharedDirector()->replaceScene(helpScene);
}