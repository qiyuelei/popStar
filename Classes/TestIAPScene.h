//
//  TestIAPScene.h
//  popStar
//
//  Created by long shenghua on 13-9-23.
//
//

#ifndef __popStar__TestIAPScene__
#define __popStar__TestIAPScene__

#include "cocos2d.h"
#include "IAPDialogLayer.h"
#include "stdcheaders.h"
USING_NS_CC;
using namespace std;

class TestIAPScene : public  CCLayer{
    
public:
    TestIAPScene();
    ~TestIAPScene();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(TestIAPScene);
    
    IAPDialogLayer* iAPDialogLayer;
    int testId;
    
    void ccTouchesEnded(CCSet *touches,CCEvent *event);
    void loadProduct(int productionId);
    void responStore();
    
    void purchaseProduct(int productionId);
    void responPurchaseStat();
    
    void requestProduct(int productionId);
    void responPrice();
};

#endif /* defined(__popStar__TestIAPScene__) */
