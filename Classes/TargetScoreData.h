//
//  TargetScoreData.h
//  popStar
//
//  Created by long shenghua on 13-9-20.
//
//

#ifndef __popStar__TargetScoreData__
#define __popStar__TargetScoreData__

#include "cocos2d.h"

USING_NS_CC;
class TargetScoreData:public CCLayer {
    
public:
    TargetScoreData();
    ~TargetScoreData();
    virtual bool init();
    CREATE_FUNC(TargetScoreData);
    int targetScore;
    int gettargetScore(int gameMode,int curStage);
    
    void equipmentProcess(int equipmentType,int mothed,int equipmentNum);
};

#endif /* defined(__popStar__TargetScoreData__) */
