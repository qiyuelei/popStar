//
//  TargetScoreData.cpp
//  popStar
//
//  Created by long shenghua on 13-9-20.
//
//

#include "TargetScoreData.h"
TargetScoreData::TargetScoreData(){}
TargetScoreData::~TargetScoreData(){}
bool TargetScoreData::init(){
    if (CCLayer::init()) {

        return true;
    }else{
        return false;
    }
}


int TargetScoreData::gettargetScore(int gameMode,int curStage){
    if (gameMode == 1) {
        if (curStage == 1) {
            targetScore = 2000;
        }else if (curStage == 2){
            targetScore = 5000;
        }else if (curStage > 2 && curStage < 7){
            targetScore = 3000;
            targetScore = targetScore*curStage+500;
        }else if (curStage > 6 && curStage < 11){
            targetScore = 3000;
            targetScore = targetScore*curStage+1000;
        }else if (curStage > 10 && curStage < 16){
            targetScore = 3000;
            targetScore = targetScore*curStage+1500;
        }else if (curStage > 15 && curStage < 21){
            targetScore = 3000;
            targetScore = targetScore*curStage+2000;
        }else if (curStage > 20 && curStage < 26){
            targetScore = 3000;
            targetScore = targetScore*curStage+2500;
        }else if (curStage > 25 && curStage < 31){
            targetScore = 3000;
            targetScore = targetScore*curStage+3000;
        }else if (curStage > 30 && curStage < 36){
            targetScore = 3000;
            targetScore = targetScore*curStage+3500;
        }else if (curStage > 35){
            targetScore = 3000;
            targetScore = targetScore*curStage+4000;
        }
     }else if (gameMode == 2){
         if (curStage == 1) {
             targetScore = 1000;
         }else if (curStage == 2){
             targetScore = 3000;
         }else if (curStage > 2 && curStage < 7){
             targetScore = 2000;
             targetScore = targetScore*curStage;
         }else if (curStage > 6 && curStage < 11){
             targetScore = 2000;
             targetScore = targetScore*curStage+1000;
         }else if (curStage > 10 && curStage < 16){
             targetScore = 2000;
             targetScore = targetScore*curStage+1500;
         }else if (curStage > 15 && curStage < 21){
             targetScore = 2000;
             targetScore = targetScore*curStage+2000;
         }else if (curStage > 20 && curStage < 26){
             targetScore = 2000;
             targetScore = targetScore*curStage+2500;
         }else if (curStage > 25 && curStage < 31){
             targetScore = 2000;
             targetScore = targetScore*curStage+3000;
         }else if (curStage > 30 && curStage < 36){
             targetScore = 2000;
             targetScore = targetScore*curStage+3500;
         }else if (curStage > 35){
             targetScore = 2000;
             targetScore = targetScore*curStage+4000;
         }
        
    }else if (gameMode == 3){
        if (curStage == 1) {
            targetScore = 1000;
        }else if (curStage == 2){
            targetScore = 2200;
        }else if (curStage > 2 && curStage < 7){
            targetScore = 1200;
            targetScore = targetScore*curStage+200;
        }else if (curStage > 6 && curStage < 11){
            targetScore = 1200;
            targetScore = targetScore*curStage+500;
        }else if (curStage > 10 && curStage < 16){
            targetScore = 1200;
            targetScore = targetScore*curStage+1000;
        }else if (curStage > 15 && curStage < 21){
            targetScore = 1200;
            targetScore = targetScore*curStage+1500;
        }else if (curStage > 20 && curStage < 26){
            targetScore = 1200;
            targetScore = targetScore*curStage+2000;
        }else if (curStage > 25 && curStage < 31){
            targetScore = 1200;
            targetScore = targetScore*curStage+3000;
        }else if (curStage > 30 && curStage < 36){
            targetScore = 1200;
            targetScore = targetScore*curStage+3500;
        }else if (curStage > 35){
            targetScore = 1200;
            targetScore = targetScore*curStage+4000;
        }
        
    }

    return targetScore;

}
void TargetScoreData::equipmentProcess(int equipmentType, int mothed, int equipmentNum){
    CCLog("equipmentprocess");
    switch (mothed) {
        case 1:
            CCLog("jianum");
            switch (equipmentType) {
                case 1:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicStarNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicStarNum")+equipmentNum);
                    break;
                case 2:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum")+equipmentNum);
                    break;
                default:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicChanNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicChanNum")+equipmentNum);
                    break;
            }
            break;
            
        default:
            CCLog("jianNum");
            switch (equipmentType) {
                case 1:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicStarNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicStarNum")-equipmentNum);
                    break;
                case 2:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum")-equipmentNum);
                    break;
                default:
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("magicChanNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicChanNum")-equipmentNum);
                    break;
            }
            break;
    }
    CCUserDefault::sharedUserDefault()->flush();
}