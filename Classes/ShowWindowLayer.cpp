//
//  ShowWindowLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-30.
//
//

#include "ShowWindowLayer.h"
ShowWindowLayer::ShowWindowLayer(){
    bgBatchNode = CCSpriteBatchNode::create("ShowWinBg.png");
    CC_SAFE_RETAIN(bgBatchNode);
    shareBatchNode = CCSpriteBatchNode::create("ShowShareBg.png");
    CC_SAFE_RETAIN(bgBatchNode);
}
ShowWindowLayer::~ShowWindowLayer(){
    CC_SAFE_RELEASE_NULL(bgBatchNode);
    CC_SAFE_RELEASE_NULL(shareBatchNode);
}
bool ShowWindowLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }else{
        
       // CCSprite* sp = CCSprite::create("Icon.png");
       // sp->setPosition(ccp(100, 100));
       // addChild(sp);
        
       // bgBatchNode = CCSpriteBatchNode::create("icon.png");
       // bgBatchNode->setTag(1001);
       // addChild(bgBatchNode);
       // m_bgTexture = bgBatchNode->getTexture();
       // addChild(shareBatchNode);
       // m_shareTexture = shareBatchNode->getTexture();

        
        
       // showPurchaseFail(1);
        
        
        return true;
    }
}
void ShowWindowLayer::showPurchaseFail(int ProductId){
    showWinBg();

}
void ShowWindowLayer::showPurchaseSuccess(int ProductId){
    showWinBg();
    //this->schedule(schedule_selector(ShowWindowLayer::removeObject), 3.0f);
    CCLog("ProductId:%i",ProductId);
    
}
void ShowWindowLayer::showMenu(){


}
void ShowWindowLayer::menuCloseCallBack(){}
void ShowWindowLayer::menuGoOnGameBtn(){}
void ShowWindowLayer::menuRePurchaseBtn(){}
void ShowWindowLayer::showWinBg(){
    CCSprite* showWinBg = CCSprite::createWithTexture(m_bgTexture);
    showWinBg->setPosition(ccp(240, 160));
    //showWinBg->setScale(0.5);
    showWinBg->setScaleX(0.7);
    showWinBg->setScaleY(0.5);
    //showWinBg->setTag(1002);
    
   // CCSprite* showWinBg1 = CCSprite::createWithTexture(m_bgTexture);
    CCSprite* showSharebg = CCSprite::createWithTexture(m_shareTexture);
    showSharebg->setPosition(ccp(405, 160));
    //showSharebg->setScaleX(0.8);
    //showSharebg->setScaleY(0.5);
    showSharebg->setRotation(-90);
   // showSharebg->setTag(1002);
   
    CCMenuItemImage *closeBtn = CCMenuItemImage::create("showWinClose.png", "showWinClose.png",this,menu_selector(ShowWindowLayer::okBtnCallBack));
    closeBtn->setPosition(ccp(60,280));
    closeBtn->setRotation(90);
    //okBtn->setZOrder(100);
    closeBtn->setScale(0.5);
    
    CCMenuItemImage *okBtn = CCMenuItemImage::create("showWinBtn.png", "showWinBtn.png",this,menu_selector(ShowWindowLayer::okBtnCallBack));
    okBtn->setPosition(ccp(350,160));
    okBtn->setRotation(90);
    //okBtn->setZOrder(100);
    okBtn->setScale(0.5);
    okBtn->setVisible(false);
    
    CCMenu* pShowMenu = CCMenu::create(okBtn,closeBtn,NULL);
    pShowMenu->setPosition(CCPointZero);
    //this->addChild(pShowMenu);
    
    CCSprite* productImg = CCSprite::create("magic_Star.png");
    productImg->setPosition(ccp(170, 160));
    productImg->setScale(0.5);
    productImg->setRotation(-90);
    
    CCLabelTTF* productNum = CCLabelTTF::create("x8", "Arial", 50);
    productNum->setPosition(ccp(185, 200));
    productNum->setScale(0.5);
    productNum->setRotation(-90);
    
    CCLabelTTF* productDec = CCLabelTTF::create("This is MagicStar", "Arial", 35);
    productDec->setPosition(ccp(230, 160));
    productDec->setScale(0.3);
    productDec->setRotation(-90);
    
    CCLabelTTF* productName = CCLabelTTF::create("MagicStar", "Arial", 50);
    productName->setPosition(ccp(100, 160));
    productName->setScale(0.5);
    productName->setRotation(-90);
    
    CCLabelTTF* purchaseStatTTF = CCLabelTTF::create("MagicStar", "Arial", 35);
    purchaseStatTTF->setPosition(ccp(350,160));
    purchaseStatTTF->setScale(0.3);
    purchaseStatTTF->setRotation(-90);
    
    showNode = CCNode::create();
    showNode->setTag(1003);

    showNode->addChild(showWinBg);
    //showNode->addChild(showSharebg);
    showNode->addChild(purchaseStatTTF);
    showNode->addChild(pShowMenu);
    showNode->addChild(productImg);
    showNode->addChild(productNum);
    showNode->addChild(productDec);
    showNode->addChild(productName);
    
    addChild(showNode);
    //addChild(showSharebg);
    //bgBatchNode->addChild(showNode);
    //bgBatchNode->addChild(showWinBg1);
   // bgBatchNode->addChild(showWinBg);
}
void ShowWindowLayer::removeObject(){
    this->unschedule(schedule_selector(ShowWindowLayer::removeObject));
   this->removeChildByTag(1003, false);
}
void ShowWindowLayer::okBtnCallBack(){
    CCLog("ShowWindowLayer::okBtnCallBack");
}