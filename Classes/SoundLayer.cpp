//
//  SoundLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#include "SoundLayer.h"
SoundLayer::SoundLayer(){}
SoundLayer::~SoundLayer(){}
bool SoundLayer::init(){
    if (CCLayer::init()) {
        
        
        
        return true;
    }else{
        return false;
    }
}

void SoundLayer::playBgSound(int audioType){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("backGroundMusic")==1) {
        
        switch (audioType) {
            case 1:
                SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2);
                SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.caf", true);
                //SimpleAudioEngine::sharedEngine()->playEffect("bgMusic.caf");
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 5:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 6:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 7:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 8:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            default:
                break;
        }
        
    }



}
void SoundLayer::playEffect(int audioType){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
        
        switch (audioType) {
            case 1:
                SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
                SimpleAudioEngine::sharedEngine()->playEffect("voice11.caf");
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("good.caf");
               // SimpleAudioEngine::sharedEngine()->playEffect("gameover.caf");
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("cool.caf");
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("wow.caf");
                break;
            case 5:
                SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.1);
                SimpleAudioEngine::sharedEngine()->playEffect("goon.caf");
                //SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
                break;
            case 6:
                SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.1);
                SimpleAudioEngine::sharedEngine()->playEffect("gameover.caf");
               // SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
                break;
            case 7:
                 SimpleAudioEngine::sharedEngine()->playEffect("voice12.caf");
                break;
            case 8:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            default:
                break;
        }
        
    }


}
void SoundLayer::stopBgSound(int audioType){}
void SoundLayer::stopEffect(int audioType){}