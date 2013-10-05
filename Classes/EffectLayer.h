//
//  EffectLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-27.
//
//

#ifndef __popStar__EffectLayer__
#define __popStar__EffectLayer__

#include "cocos2d.h"
USING_NS_CC;

class EffectLayer:public CCLayer {
    
public:
    EffectLayer();
    ~EffectLayer();
    virtual bool init();
    CREATE_FUNC(EffectLayer);
    
    CCLabelTTF* MagicStarTTF;
    CCLabelTTF* getMagicStarTTF();
    CCSprite* MagicStarSprite;
    CCSprite* getMagicStarSprite();
    void loadEquipmentNum();
    
    void onExit();
    void onEnter();
};


#endif /* defined(__popStar__EffectLayer__) */
