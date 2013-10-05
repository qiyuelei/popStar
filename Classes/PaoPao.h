//
//  PaoPao.h
//  pop
//
//  Created by long shenghua on 13-9-5.
//
//

#ifndef __pop__PaoPao__
#define __pop__PaoPao__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class PaoPao:public CCSprite {
    
public:
    PaoPao();
    ~PaoPao();
    
    int PaoPaoType;
    int rowNum;
    int colNum;
    int checkStat;
   // int unId;
};

class NormalPaoPao: public PaoPao {
    
public:
    NormalPaoPao();
    ~NormalPaoPao();
    static NormalPaoPao* createPaoPao(int PaoPaoType,int rowNum,int colNum,CCTexture2D* m_pSpriteTexture);
};
#endif /* defined(__pop__PaoPao__) */
