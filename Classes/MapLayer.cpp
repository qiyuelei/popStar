//
//  MapLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-16.
//
//

#include "MapLayer.h"
MapLayer::MapLayer(){
    PaopaoArray = CCArray::create();
    CC_SAFE_RETAIN(PaopaoArray);
}
MapLayer::~MapLayer(){
    CC_SAFE_RELEASE_NULL(PaopaoArray);
}
bool MapLayer::init(){
    if (CCLayer::init()) {
        
        parent = CCSpriteBatchNode::create("sekuai.png", 200);
        m_pSpriteTexture = parent->getTexture();
        addChild(parent);
       // m_pSpriteTexture = CCTextureCache::sharedTextureCache()->addImage("sekuai.png");
       // initMap(4);
        
       // CCSprite* sp = CCSprite::create("Icon.png");
        //sp->setPosition(ccp(200, 200));
       // addChild(sp);
       // initMap(4);
       // this->schedule(schedule_selector(MapLayer::movePaopaoStart), 3.0f);
        return true;
    }else{
        return false;
    }

}
void MapLayer::initMap(int corlorNum){
   // CCLog("corlorNum:%i",corlorNum);
   // for (int j = 0; j<10; j++) {
        
   
    for (int i=0; i<100; i++) {
    addPaopao(ccp(-32, 160), corlorNum);
    }
    curPaopaoId = 0;
    curColNum = 0;
    curRowNum = 0;
   // this->schedule(schedule_selector(MapLayer::MakeMovePoint), 0.01f);

//}
}
CCSpriteBatchNode* MapLayer::getparent(){
    return parent;
}
void MapLayer::movePaopaoStart(){
    this->schedule(schedule_selector(MapLayer::MakeMovePoint), 0.03f);
   // this->unschedule(schedule_selector(MapLayer::movePaopaoStart));;
}
void MapLayer::MakeMovePoint(){
    //CCPoint point1 = CCPointMake(-32, 160);
    if (curPaopaoId % 2) {
        CCPoint point21 = CCPointMake(-32, 16+32*curRowNum);
        CCPoint point31 = CCPointMake(464-32*curColNum, 16+32*curRowNum);
        movePaopao(point21,point31,curPaopaoId);
    }else{
        CCPoint point22 = CCPointMake(-32, 304-32*curRowNum);
        CCPoint point32 = CCPointMake(464-32*curColNum, 304-32*curRowNum);
        movePaopao(point22,point32,curPaopaoId);
    }
    if (curPaopaoId == 99) {
        this->unschedule(schedule_selector(MapLayer::MakeMovePoint));
    }
    curPaopaoId++;
    curRowNum++;
    rowNum++;
    ColNum++;
    if (rowNum % 2) {
        curRowNum = curRowNum-1;
    }
    if (rowNum == 10) {
        rowNum = 0;
    }
    if (ColNum == 10) {
        curColNum++;
        curRowNum = 0;
        ColNum = 0;
    }
}
void MapLayer::movePaopao(CCPoint point2,CCPoint point3,int paopaoId){
    NormalPaoPao* _myPaopao = (NormalPaoPao*)PaopaoArray->objectAtIndex(paopaoId);
    _myPaopao->runAction(CCSequence::create(CCMoveTo::create(0.03f, point2),CCMoveTo::create(0.03f, point3),NULL));
}
void MapLayer::addPaopao(CCPoint location,int corlorNum){
    int _paopaoType = arc4random()%corlorNum;
    NormalPaoPao* _Paopao = (NormalPaoPao*)NormalPaoPao::createPaoPao(_paopaoType,0,0,m_pSpriteTexture);
    _Paopao->setPosition(location);
    _Paopao->setScale(0.5);
    _Paopao->setTag(3);
    _Paopao->setRotation(-90);
   // parent->addChild(_Paopao);
    addChild(_Paopao);

    PaopaoArray->addObject(_Paopao);
}
CCArray* MapLayer::getPaopaoArray(){
    return PaopaoArray;
}