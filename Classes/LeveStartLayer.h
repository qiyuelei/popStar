//
//  LeveStartLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-18.
//
//

#ifndef __popStar__LeveStartLayer__
#define __popStar__LeveStartLayer__

#include "cocos2d.h"
USING_NS_CC;

class LeveStartLayer:public CCLayer {
    
public:
    LeveStartLayer();
    ~LeveStartLayer();
    virtual bool init();
    CREATE_FUNC(LeveStartLayer);
    
    void showTargetScore();
    void showTargetScoreDone();
    CCLabelTTF* labelTTF;
    CCLabelTTF* getlabelTTF();
};

#endif /* defined(__popStar__LeveStartLayer__) */
