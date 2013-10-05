//
//  DialogLayer.cpp
//  Defender
//
//  Created by long shenghua on 13-7-26.
//
//

#include "DialogLayer.h"
DialogLayer::DialogLayer()
{
}

DialogLayer::~DialogLayer()
{
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
        
        this->initDialog();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void DialogLayer::initDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "", 35);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);
    
    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(DialogLayer::okMenuItemCallback));
    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
    
    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(DialogLayer::cancelMenuItemCallback));
    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));
    
    m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority - 1, true);
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    // CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    // 点击确定就退出（拷贝的原有方法）
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
}
