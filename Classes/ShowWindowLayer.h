//
//  ShowWindowLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-30.
//
//

#ifndef __popStar__ShowWindowLayer__
#define __popStar__ShowWindowLayer__

#include "cocos2d.h"
USING_NS_CC;

class ShowWindowLayer:public CCLayer {
    
public:
    ShowWindowLayer();
    ~ShowWindowLayer();
    virtual bool init();
    CREATE_FUNC(ShowWindowLayer);
    
    CCSpriteBatchNode* bgBatchNode;
    CCTexture2D* m_bgTexture;
    
    CCSpriteBatchNode* shareBatchNode;
    CCTexture2D* m_shareTexture;
    
    CCNode* showNode;
    
    void showPurchaseFail(int ProductId);
    void showPurchaseSuccess(int ProductId);
    void showMenu();
    void showWinBg();
    void okBtnCallBack();
    
private:
    void menuCloseCallBack();
    void menuGoOnGameBtn();
    void menuRePurchaseBtn();
    void removeObject();
};

#endif /* defined(__popStar__ShowWindowLayer__) */
