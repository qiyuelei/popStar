//
//  IAPDialogLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-25.
//
//

#ifndef __popStar__IAPDialogLayer__
#define __popStar__IAPDialogLayer__

#include "cocos2d.h"
USING_NS_CC;

class IAPDialogLayer:public CCLayer {
    
public:
    IAPDialogLayer();
    ~IAPDialogLayer();
    virtual bool init();
    CREATE_FUNC(IAPDialogLayer);
    
    CCLabelTTF* priceTTF;
    
    void showProduct();
    CCLabelTTF* getpriceTTF();
    void removeProduct();
 
    void showPurchaseStat();
    CCLabelTTF* getPurchaseStatTTF();
    void removePurchaseStat();
    CCLabelTTF* purchaseTTF;
    
};

#endif /* defined(__popStar__IAPDialogLayer__) */
