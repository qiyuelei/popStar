//
//  MapLayer.h
//  popStar
//
//  Created by long shenghua on 13-9-16.
//
//

#ifndef __popStar__MapLayer__
#define __popStar__MapLayer__

#include "cocos2d.h"
#include "PaoPao.h"
USING_NS_CC;

class MapLayer: public CCLayer {
    
public:
    MapLayer();
    ~MapLayer();
    virtual bool init();
    CREATE_FUNC(MapLayer);
    
    CCSpriteBatchNode*  parent;
    CCSpriteBatchNode* getparent();
    CCTexture2D* m_pSpriteTexture;
    CCArray* PaopaoArray;
    int curPaopaoId;
    int curRowNum;
    int curColNum;
    int rowNum;
    int ColNum;
    int corlorNum = 3;
    
    int getcorlorNum();
    
    void initMap(int corlorNum);
    void movePaopaoStart();
    void addPaopao(CCPoint location,int corlorNum);
    void movePaopao(CCPoint point2,CCPoint point3,int paopaoId);
    void MakeMovePoint();
    CCArray* getPaopaoArray();
};

#endif /* defined(__popStar__MapLayer__) */
