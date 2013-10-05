//
//  DialogLayer.h
//  Defender
//
//  Created by long shenghua on 13-7-26.
//
//

#ifndef __Defender__DialogLayer__
#define __Defender__DialogLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class DialogLayer: public CCLayerColor
{
    // 模态对话框菜单
    CCMenu *m_pMenu;
    // 记录菜单点击
    bool m_bTouchedMenu;
    
public:
    DialogLayer();
    ~DialogLayer();
    
    virtual bool init();
    // 初始化对话框内容
    void initDialog();
    
    CREATE_FUNC(DialogLayer);
    //LAYER_NODE_FUNC(DialogLayer);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
};

#endif /* defined(__Defender__DialogLayer__) */
