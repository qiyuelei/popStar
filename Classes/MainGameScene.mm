//
//  MainGameScene.cpp
//  popStar
//
//  Created by long shenghua on 13-9-16.
//
//

#include "MainGameScene.h"

#import "InAppPurchaseManager.h"
InAppPurchaseManager* inAppPurchaseManager;
#include "stdcheaders.h"
using namespace std;



enum{
    MapLayerTag = 1,
    ParticleTag = 3,
    MagicMenuTag = 100,
    MagicStarMenuTag = 101,
    MagicBlockTag = 5,
    MagicStarTag = 6,
    MagicChanTag = 7,
    ShowPurchaseWindowTag = 103,
    productImgTag = 104,
    productDecTag = 105,
    productNameTag = 106,
    pShowMenuTag = 107,
    okBtnTag = 108,
    purchaseStatTTFTag = 109,
    okBtnTTFTag = 110,
    closeBtnTag = 111,
};
enum{
    MapLayerZorder = 10,
    LeveStartLayerZorder = 20,
    ParticleZorder = 51,
    ShowGoodZorder = 40,
    PauseMenuZorder = 50,
    EquipmentNum = 55,
    FenshuZorder = 45,
    keyZorder = 48,
    ShowWindowLayerZorder = 60,
    EquipmentMenuZorder = 59,
    ShowPurchaseWindowZorder = 61,
    okBtnTTFZorder = 62,
};

MainGameScene::MainGameScene(){
    //InAppPurchaseManager* inAppPurchaseManage;
    selPaopaoArray = CCArray::create();
    CC_SAFE_RETAIN(selPaopaoArray);
   // CCSpriteBatchNode* showBgBatchNode = CCSpriteBatchNode::create("ShowWinBg.png");
   // CC_SAFE_RETAIN(showBgBatchNode);
}
MainGameScene::~MainGameScene(){
    CC_SAFE_RELEASE_NULL(selPaopaoArray);
    //CC_SAFE_RELEASE_NULL(showBgBatchNode);
}
CCScene* MainGameScene::scene(){
    CCScene* scene = CCScene::create();
    MainGameScene* layer = MainGameScene::create();
    scene->addChild(layer);
  //  scene->setRotation(90);
 //   scene->setPosition(ccp(80, 80));
    return scene;
}
bool MainGameScene::init(){
    if (CCLayer::init()) {
        touchMothed = 0;
        curPaopaoId = 0;
        curRowNum = 0;
        curColNum = 0;
        rowNum = 0;
        ColNum = 0;
        clearSpeed = 0.3;
        haveKey = false;
        maxX = 409;
        //minX = 112;
        minX = maxX-32*9;
        magicStarType = -1;
        //magicStarNum = 5;
        MenuStarRowY = 40;
        menuStar = CCPointMake(0, 0);
        //magicBlockNum = 5;
        //menuLock = false;
        gameStat = true;
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
       // bg = CCSprite::create("jiemianbeijing.png");
       // bg->setAnchorPoint(ccp(0.5,0.5));
       // bg->setPosition(ccp(240,160));
       // bg->setScale(0.5);
      //  bg->setRotation(-90);
       // this->addChild(bg,10);
        setGameParameter(CCUserDefault::sharedUserDefault()->getIntegerForKey("GameParameter"));
        initConfig();
        loadLayer();
       // loadMap();
        //loadBg();
       // InAppPurchaseManager* inAppPurchaseManage;
      //  inAppPurchaseManage = [[InAppPurchaseManager alloc]init];
        this->schedule(schedule_selector(MainGameScene::loadBg), 7.0f);
        this->schedule(schedule_selector(MainGameScene::loadMap), 3.0f);
        inAppPurchaseManager = [[InAppPurchaseManager alloc]init];
        channel = new ChannelClass();
        //playAudio(1);
       // showKey();
        return true;
    }else{
        return false;
    }
}
void MainGameScene::loadLayer(){
       // CCLog("curGameMode:%i,curStage:%i,corlorNum:%i",curGameMode,curStage,corlorNum);
    LeveStartLayer* leveStartLayer = LeveStartLayer::create();
    char levelChar[128];
    //sprintf(targetScoreChar, "%d",targetScore);
   // gameBgLayer->GettargetScoreTTF()->setString(targetScoreChar);
    sprintf(levelChar,"Level %d      Target score is        %d",curStage,targetScore);
    leveStartLayer->getlabelTTF()->setString(levelChar);
   // leveStartLayer->getlabelTTF()->visit();
    addChild(leveStartLayer,LeveStartLayerZorder,LeveStartLayerZorder);
    
    //particleLayer = ParticleLayer::create();
    //addChild(particleLayer,ParticleZorder,ParticleTag);
    
    particleSysLayer = ParticleSysLayer::create();
    addChild(particleSysLayer,ParticleZorder);
    
    
    _mapLayer = MapLayer::create();
    _mapLayer->initMap(corlorNum);
    addChild(_mapLayer,MapLayerZorder,1);
    
    gameBgLayer = GameBg::create();
    //gameBgLayer->setPosition(ccp(480, 0));
    addChild(gameBgLayer);
    
    soundLayer = SoundLayer::create();
    addChild(soundLayer);
    
    effectLayer = EffectLayer::create();
    addChild(effectLayer,EquipmentNum);
    this->setTouchPriority(1);
    
   // showWindowLayer = ShowWindowLayer::create();
    //addChild(showWindowLayer,ShowWindowLayerZorder);

    loadPurshaseWinDow();
    
}
void MainGameScene::loadMap(){
    this->unschedule(schedule_selector(MainGameScene::loadMap));
    this->schedule(schedule_selector(MainGameScene::MakeMovePoint), 0.02f);
    //_mapLayer->movePaopaoStart();
}

void MainGameScene::MakeMovePoint(){
    //CCPoint point1 = CCPointMake(-32, 160);
    if (curPaopaoId % 2) {
       // CCLog("curColNum:%i,currowNum:%i",curColNum,curRowNum);
       // CCPoint point21 = CCPointMake(-32, 16+32*curRowNum);
        CCPoint point31 = CCPointMake(maxX-32*curColNum, 16+32*curRowNum);
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->PaopaoArray->objectAtIndex(curPaopaoId);
        _myPaopao->runAction(CCSequence::create(CCMoveTo::create(0.2f, point31),NULL));
      //_myPaopao->runAction(CCSequence::create(CCMoveTo::create(1.0f, ccp(100, 100)),NULL));
        //movePaopao(point21,point31,curPaopaoId);
    }else{
       // CCPoint point22 = CCPointMake(-32, 304-32*curRowNum);
        CCPoint point32 = CCPointMake(maxX-32*curColNum, 304-32*curRowNum);
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->PaopaoArray->objectAtIndex(curPaopaoId);
        _myPaopao->runAction(CCSequence::create(CCMoveTo::create(0.2f, point32),NULL));
       // movePaopao(point22,point32,curPaopaoId);
    }
    if (curPaopaoId == 99) {
        this->unschedule(schedule_selector(MainGameScene::MakeMovePoint));
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
void MainGameScene::movePaopao(CCPoint point2,CCPoint point3,int paopaoId){
    //CCLog("paopaoId:%i",paopaoId);
    //NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->PaopaoArray->objectAtIndex(paopaoId);
   // _myPaopao->setPosition(ccp(100, 100));
  // _myPaopao->runAction(CCSequence::create(CCMoveTo::create(1.0f, ccp(100, 100)),NULL));
   // _myPaopao->runAction(CCSequence::create(CCMoveTo::create(0.03f, point2),CCMoveTo::create(0.03f, point3),NULL));
}

void MainGameScene::loadBg(){
    this->unschedule(schedule_selector(MainGameScene::loadBg));
    //gameBgLayer->setPosition(ccp(0, 0));
    //loadMenu();
    
    sprintf(ScoreChar, "%d",Score);
    gameBgLayer->GetscoreTTF()->setString(ScoreChar);
    
    sprintf(targetScoreChar, "%d",targetScore);
    gameBgLayer->GettargetScoreTTF()->setString(targetScoreChar);
    
    sprintf(stageChar, "%d",curStage);
    gameBgLayer->GetstageTTF()->setString(stageChar);
    
    sprintf(bestScoreChar, "%d",bestScore);
    gameBgLayer->GetbestScoreTTF()->setString(bestScoreChar);
    
    
    gameBgLayer->GetcurGameModeIcon()->initWithFile("game_bg.png");
    gameBgLayer->GetcurGameModeIcon()->setZOrder(-1);
   // bg->initWithFile("game_bg.png");
    loadEquipmentMenu();
    moveEquipmentMenu();
    loadMagicStarMenu();
    effectLayer->loadEquipmentNum();
    loadMenu();

    this->setTouchEnabled(true);

}
void MainGameScene::loadMenu(){
    CCMenuItemImage *pPause = CCMenuItemImage::create("zanting_before.png", "zanting_after.png",this,menu_selector(MainGameScene::menuPausecallback));
    pPause->setPosition(ccp(82,305));
    pPause->setRotation(90);
    pPause->setZOrder(100);
    pPause->setScale(0.8);
    
    CCMenuItemImage *facebookShare = CCMenuItemImage::create("facebook.png", "facebook_after.png",this,menu_selector(MainGameScene::menuShareCallback));
    facebookShare->setPosition(ccp(55, 305));
    facebookShare->setRotation(-90);
    facebookShare->setScale(0.1);
    
    CCMenu* pMenuPause = CCMenu::create(pPause,facebookShare,NULL);
    pMenuPause->setPosition(CCPointZero);
    this->addChild(pMenuPause);
}
void MainGameScene::menuShareCallback(){
    //channel->channel();
    channel->Sharefacebook(bestScore);
}
void MainGameScene::menuPausecallback(){
    //CCLog("pause");
    if (pauseStat == false) {
        pauseStat = true;
          initModeMenu(1, curGameMode);
    }

}
void MainGameScene::ccTouchesEnded(CCSet *touches,CCEvent *event)
{
    if (gameStat == true) {
        
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = this->convertTouchToNodeSpace(touch);
    
    switch (touchMothed) {
        case 1:
           // CCLog("magicStartouch");
            if (magicStarType >= 0) {
            initselPaopaoArray();
            for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
                NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
                if (_myPaopao->boundingBox().containsPoint(location)) {
                    if (_myPaopao->PaoPaoType != magicStarType) {
                       // CCLog("change");

                        if (magicStarNum > 0) {
                            magicStarNum = magicStarNum - 1;
                            particleSysLayer->ChargePlay(magicStarType, _myPaopao->getPosition());
                            _myPaopao->PaoPaoType = magicStarType;
                            _myPaopao->setTextureRect(CCRectMake(64 * magicStarType,64 * 0,64,64));

                            char magicStarNumChar[128];
                            sprintf(magicStarNumChar, "%d",magicStarNum);
                            e_magicStarTTF->setString(magicStarNumChar);
                            
                        }
                        if (magicStarNum<=0) {
                            e_magicStarTTF->setString("+");
                        }
                        c_magicStarLeaveBtnCallBack();
                   }}
            } }
            break;
        case 2:
          //  CCLog("magicBlocktouch");
              initselPaopaoArray();
              for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
                  NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
            if (_myPaopao->boundingBox().containsPoint(location)) {
                touchMothed = 0;
                initEquipmentMenu();
                magicBlockProcess(location, _myPaopao->PaoPaoType);
            }
              }
            break;
        case 3:
          //  CCLog("magicChantouch");
            initselPaopaoArray();
            magicChanProcess(location);
            break;
            
        default:
          //  CCLog("Normaltouch");
            normalTouchProcess(location);
            break;
    }}
}
void MainGameScene::normalTouchProcess(cocos2d::CCPoint location){
    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaopao->boundingBox().containsPoint(location)) {
            if (_myPaopao->checkStat == 0) {
                initselPaopaoArray();
                _myPaopao->checkStat = 1;
                selPaopaoArray->addObject(_myPaopao);
                findPaopao(_myPaopao->getPosition(), _myPaopao->PaoPaoType);
                if (selPaopaoArray->count()>1) {
                    //selPaopao(1);
                    sprintf(SelscoreChar, "%d blocks %d points",selPaopaoArray->count(),selPaopaoArray->count()*selPaopaoArray->count()*5);
                    
                }else{
                    sprintf(SelscoreChar, "%s","");
                }
                gameBgLayer->GetselScoreTTF()->setString(SelscoreChar);
            }else{
                if (selPaopaoArray->count()>1) {
                    clearPaopao();
                }
                
            }
        }
    }
}
void MainGameScene::findPaopao(CCPoint location,int paopaoType){
    findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
    findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
    findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
    findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);

    if (selPaopaoArray->count()>1) {
        for (int j = 0; j<selPaopaoArray->count(); j++) {
            NormalPaoPao* _myPaopao = (NormalPaoPao*)selPaopaoArray->objectAtIndex(j);
            int idx = _myPaopao->PaoPaoType;
            _myPaopao->setTextureRect(CCRectMake(64 * idx,64 * 1,64,64));
            _myPaopao->runAction(CCSequence::create(CCScaleTo::create(0.1f, 0.6),CCScaleTo::create(0.1f, 0.5),NULL));
        }
    }
}
void MainGameScene::findPaopao_T(CCPoint location,int paopaoType){
    for (int i=0; i< _mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            selPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            // findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
            break;
        }
    }
}
void MainGameScene::findPaopao_R(CCPoint location,int paopaoType){
    for (int i=0; i< _mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            selPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
             findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            //findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
            break;
        }
    }
}
void MainGameScene::findPaopao_B(CCPoint location,int paopaoType){
    for (int i=0; i< _mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            selPaopaoArray->addObject(_myPaoPao);
           // findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
            break;
        }
    }

}
void MainGameScene::findPaopao_L(CCPoint location,int paopaoType){
    for (int i=0; i< _mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            selPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
           // findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
            break;
        }
    }
}

void MainGameScene::clearPaopao(){
    this->unschedule(schedule_selector(MainGameScene::isGameOver));
    //CCLog("clear");
    //0 score++
  int  value = selPaopaoArray->count()*5;
    
    Score = Score+selPaopaoArray->count()*selPaopaoArray->count()*5;
    sprintf(ScoreChar, "%d",Score);
    gameBgLayer->GetscoreTTF()->setString(ScoreChar);
    gameBgLayer->GetscoreTTF()->visit();
    if (Score >= targetScore) {
        if (haveKey == false) {
            haveKey = true;
            soundLayer->playEffect(7);
            showKey();
        }
        //PassNextStage
       // CCLog("passNextStage");
    }
    if (selPaopaoArray->count()>=6 and selPaopaoArray->count()<=8) {
        //  CCLog("good");
        soundLayer->playEffect(2);
        showGood(1);
    }else if (selPaopaoArray->count()>=9 and selPaopaoArray->count()<=10){
        // CCLog("wow");
        soundLayer->playEffect(4);
        showGood(2);
    }else if (selPaopaoArray->count()>=11){
        // CCLog("exce");
        soundLayer->playEffect(3);
        showGood(3);
    }
    
    sprintf(SelscoreChar, "%s","");
    gameBgLayer->GetselScoreTTF()->setString(SelscoreChar);
    gameBgLayer->GetselScoreTTF()->visit();
    
    //1.clear
    for (int j = 0; j<selPaopaoArray->count(); j++) {
        NormalPaoPao* _myPaopao2 = (NormalPaoPao*)selPaopaoArray->objectAtIndex(j);
        jiafen(_myPaopao2->getPosition(), value);
        _mapLayer->getPaopaoArray()->removeObject(_myPaopao2);
    }
    
    //2 addMark
    for (int i = 0; i<selPaopaoArray->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)selPaopaoArray->objectAtIndex(i);
        addMark_Row(_myPaopao->getPosition());
        soundLayer->playEffect(1);
        //mem
            particleSysLayer->TomatoPlay(_myPaopao->PaoPaoType, _myPaopao->getPosition());
      // particleLayer->addParticleExplosion(_myPaopao->getPosition(), _myPaopao->PaoPaoType);
      //  particleLayer->addParticleExplosion(_myPaopao->getPosition(), 1);
       // BaozhaLayer->ParticleExplosion(ccp(200, 200));
        _mapLayer->removeChild(_myPaopao);

    }
    //3.move
        movePaopao();
    //clear selPaopaoArray
   // initselPaopaoArray();
    //5.isGameOver
    this->schedule(schedule_selector(MainGameScene::isGameOver), 0.5f);
}
void MainGameScene::showGood(int showId){
    switch (showId) {
        case 1:
           // if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
                // SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
            //    SimpleAudioEngine::sharedEngine()->playEffect("a5.caf");
           // }
            showSprite = CCSprite::create("good.png");
            break;
        case 2:

            showSprite = CCSprite::create("wow.png");
            break;
        case 3:
            showSprite = CCSprite::create("cool.png");
            break;
        default:
            break;
    }
    //showSprite = CCSprite::create("good.png");
    showSprite->setPosition(ccp(200, 160));
    showSprite->setRotation(-90);
    addChild(showSprite,ShowGoodZorder);
    CCFadeOut* fadeout = CCFadeOut::create(3.0f);
    showSprite->runAction(fadeout);
    this->schedule(schedule_selector(MainGameScene::hideGood), 3.0f);
}
void MainGameScene::hideGood(){
    removeChild(showSprite);
    this->unschedule(schedule_selector(MainGameScene::hideGood));
}
void MainGameScene::addMark_Row(CCPoint location){
    bool isRowNull = true;
    for (int j = 0 ; j<10; j++) {
        float rowX = location.x - 32*j;
        bool isPaopaoNull = true;
        if (rowX < minX) {
            break;
        }
        for (int i = 0; i< _mapLayer->getPaopaoArray()->count(); i++) {
            NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
            if (_myPaopao->boundingBox().containsPoint(ccp(rowX, location.y))) {
                _myPaopao->colNum++;
                isPaopaoNull = false;
                isRowNull = false;
            }
       
        if (isPaopaoNull == false) {
            break;
        } }
    }
    if (location.x == maxX && isRowNull == true) {
       // CCLog("rowNull:%f",location.y);
        addMark_Col(location.y);
    }
}
void MainGameScene::addMark_Col(float y){
    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaopao->getPositionY()>y) {
            _myPaopao->rowNum++;
        }
    }
}
void MainGameScene::movePaopao(){
   // CCLog("moveNum:%i",_mapLayer->getPaopaoArray()->count());
    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaopao->rowNum > 0 or _myPaopao->colNum > 0) {
         //   _myPaopao->setScale(0.6);
            int jiaspanX = 0;
            int jiaspanY = 0;
            if (_myPaopao->colNum > 0) {jiaspanX = 2;}
            if (_myPaopao->rowNum > 0) {jiaspanY = 2;}
            CCMoveTo* move1 = CCMoveTo::create(0.05f, ccp(_myPaopao->getPositionX()+jiaspanX+32*_myPaopao->colNum, _myPaopao->getPositionY()-32*_myPaopao->rowNum-jiaspanY));
            CCMoveTo* move2 = CCMoveTo::create(0.05f, ccp(_myPaopao->getPositionX()+32*_myPaopao->colNum, _myPaopao->getPositionY()-32*_myPaopao->rowNum));
            _myPaopao->runAction(CCSequence::create(move1,move2,NULL));
           // CCLog("rowNum:%i,colNum:%i",_myPaopao->rowNum,_myPaopao->colNum);
            _myPaopao->rowNum = 0;
            _myPaopao->colNum = 0;
        }
    }
}
void MainGameScene::jiafen(cocos2d::CCPoint location,int value){
    char valueChar[128];
    sprintf(valueChar, "+%d",value);
    CCLabelTTF* valueTTF = CCLabelTTF::create(valueChar, "Arial", 30);
    valueTTF->setPosition(location);
    valueTTF->setRotation(-90);
    valueTTF->setScale(0.5);
    this->addChild(valueTTF,FenshuZorder);
    
    valueTTF->runAction(CCSequence::create(CCMoveTo::create(0.6, ccp(100,137)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::jiafenDone)),NULL));
    
}
void MainGameScene::jiafenDone(cocos2d::CCNode *sender){
    CCLabelTTF* _ttf = (CCLabelTTF*)sender;
    this->removeChild(_ttf);
}
void MainGameScene::isGameOver(){
    bool gameOverStat = false;
    //CCLog("isGameOver");

    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
 
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        CCPoint point1 = CCPointMake(_myPaopao->getPositionX()+32, _myPaopao->getPositionY());
        CCPoint point2 = CCPointMake(_myPaopao->getPositionX(), _myPaopao->getPositionY()+32);
        for (int j = 0; j<_mapLayer->getPaopaoArray()->count(); j++) {
            NormalPaoPao* _myPaopao2 = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(j);
            if (_myPaopao2->boundingBox().containsPoint(point1) && _myPaopao->PaoPaoType == _myPaopao2->PaoPaoType) {
               // CCLog("paopaoType:%i",_myPaopao->PaoPaoType);
                gameOverStat = true;
            }
            if (_myPaopao2->boundingBox().containsPoint(point2) && _myPaopao->PaoPaoType == _myPaopao2->PaoPaoType) {
               // CCLog("paopaoType:%i",_myPaopao->PaoPaoType);
                gameOverStat = true;
            }
        }
    }
    if (_mapLayer->getPaopaoArray()->count() == 1 or gameOverStat == false) {
        gameOverStat = true;
        //showGameOver();
        if (_mapLayer->getPaopaoArray()->count()<=10) {
          //  CCLog("lastJiafen");
            isLastJiafen = true;
            totalFen = 2000 - _mapLayer->getPaopaoArray()->count()*_mapLayer->getPaopaoArray()->count()*5;
            jiafen(ccp(300, 160), totalFen);
            
            Score = Score+totalFen;
            sprintf(ScoreChar, "%d",Score);
            gameBgLayer->GetscoreTTF()->setString(ScoreChar);
        }
        this->schedule(schedule_selector(MainGameScene::lastPaopaoProcess), 0.3f);
       // gameOverProcess();
        CCLog("showGameOver");
        gameStat  = false;
    }else{
       // CCLog("game go on");
    }
    lastPaopaoNum = _mapLayer->getPaopaoArray()->count();
    this->unschedule(schedule_selector(MainGameScene::isGameOver));
    
}
void MainGameScene::lastPaopaoProcess(){
    clearSpeed = clearSpeed-0.2/lastPaopaoNum;
    if (clearSpeed < 0.1) {
        clearSpeed = 0.09;
    }
    this->schedule(schedule_selector(MainGameScene::lastPaopaoProcess), clearSpeed);
   // CCLog("clearSpeed:%f",clearSpeed);
    bool isPaopao = true;
    for (int j = 0; j < 10; j++) {
        int rowX = minX+32*j;
        if (j == 9) {
            this->unschedule(schedule_selector(MainGameScene::lastPaopaoProcess));
           // CCLog("num:%i",_mapLayer->getPaopaoArray()->count());
            for (int jk = 0; jk< _mapLayer->getPaopaoArray()->count(); jk++) {
                NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(jk);
                soundLayer->playEffect(1);
                //mem
                particleSysLayer->TomatoPlay(_myPaopao->PaoPaoType, _myPaopao->getPosition());
               // particleLayer->addParticleExplosion(_myPaopao->getPosition(), _myPaopao->PaoPaoType);
                _mapLayer->removeChild(_myPaopao);
               // CCLog("x:%f,y:%f,i:%i",_myPaopao->getPositionX(),_myPaopao->getPositionY(),i);
                //_mapLayer->getPaopaoArray()->removeObject(_myPaopao);
                isPaopao = false;
                gameOverProcess();
               // break;
            }
        }else{
          //  CCLog("ok");
        for (int k = 0; k<10; k++) {
            int rowY = 16+32*k;
            for (int i = 0; i < _mapLayer->getPaopaoArray()->count(); i++) {
                NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
                if (_myPaopao->boundingBox().containsPoint(ccp(rowX, rowY))) {
                    soundLayer->playEffect(1);
                    //mem
                     particleSysLayer->TomatoPlay(_myPaopao->PaoPaoType, _myPaopao->getPosition());
                    //particleLayer->addParticleExplosion(_myPaopao->getPosition(), _myPaopao->PaoPaoType);
                    _mapLayer->removeChild(_myPaopao);
                   // if (isLastJiafen == true) {
                    //    jiafen(ccp(200, 160), 3);
                   // }
                    _mapLayer->getPaopaoArray()->removeObject(_myPaopao);
                    isPaopao = false;
                    break;
                }


            }
                if (isPaopao == false) {break;}
        }
                if (isPaopao == false) {break;}
    }
                if (isPaopao == false) {break;}
    }
    if (isPaopao == true) {
      //  CCLog("true");
        this->unschedule(schedule_selector(MainGameScene::lastPaopaoProcess));
        gameOverProcess();
    }

}
void MainGameScene::gameOverProcess(){
    if (Score >= targetScore) {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        soundLayer->playEffect(5);
      //  CCLog("nextStage");
        showWin();
        
    }else{
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        soundLayer->playEffect(6);
        showGameOver();
    }
}
void MainGameScene::showWin(){
    CCLabelTTF* valueTTF = CCLabelTTF::create("Win", "Arial", 60);
    valueTTF->setPosition(ccp(100,160));
    valueTTF->setRotation(-90);
    valueTTF->setScale(0.2);
    
    this->addChild(valueTTF);
    
    CCMoveTo* move1 = CCMoveTo::create(2.0f, ccp(200, 160));
    CCScaleTo *scale1 = CCScaleTo::create(2.0, 0.5);
    
    CCSpawn* spawn = CCSpawn::create(move1,scale1,NULL);
    CCDelayTime* waiting = CCDelayTime::create(2.0f);
    valueTTF->runAction(CCSequence::create(spawn,waiting,CCCallFuncN::create(this, callfuncN_selector(MainGameScene::showWinDone)),NULL));
}
void MainGameScene::showWinDone(cocos2d::CCLabelTTF *winTTF){
   // CCLabelTTF* valueTTF = (CCLabelTTF*)winTTF;
   // removeChild(valueTTF);
    switch (curGameMode) {
        case 1:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageSm", curStage+1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreSm", Score);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 12);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreSm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreSm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
        case 2:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageCm", curStage+1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 22);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreCm", Score);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreCm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreCm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        default:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageChm", curStage+1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreChm", Score);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 32);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreChm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreChm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
    }
   // CCLog("open next");
    CCScene* sc = MainGameScene::scene();
    sc->setRotation(90);
    sc->setPosition(ccp(80, 80));
    CCDirector::sharedDirector()->replaceScene(sc);
}
void MainGameScene::showGameOver(){
    CCLabelTTF* valueTTF = CCLabelTTF::create("Game Over", "Arial", 60);
    valueTTF->setPosition(ccp(100,160));
    valueTTF->setRotation(-90);
    valueTTF->setScale(0.2);
    
    this->addChild(valueTTF);
    
    CCMoveTo* move1 = CCMoveTo::create(2.0f, ccp(200, 160));
    CCScaleTo *scale1 = CCScaleTo::create(2.0, 0.5);
    
    CCSpawn* spawn = CCSpawn::create(move1,scale1,NULL);
    CCDelayTime* waiting = CCDelayTime::create(2.0f);
    valueTTF->runAction(CCSequence::create(spawn,waiting,CCCallFuncN::create(this, callfuncN_selector(MainGameScene::showGameOverDone)),NULL));
}
void MainGameScene::showGameOverDone(cocos2d::CCLabelTTF *gameoverTTF){
    CCLabelTTF* valueTTF = (CCLabelTTF*)gameoverTTF;
    removeChild(valueTTF);
   // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    initModeMenu(0, curGameMode);
}
void MainGameScene::showKey(){
    CCSprite* key = CCSprite::create("key.png");
    key->setPosition(ccp(240, 160));
    key->setRotation(-90);
    addChild(key,keyZorder);
    
    CCMoveTo* move1 = CCMoveTo::create(2.0f, ccp(83, 13));
    CCScaleTo *scale1 = CCScaleTo::create(2.0f, 0.1);
    
    CCSpawn* spawn = CCSpawn::create(move1,scale1,NULL);
    CCDelayTime* waiting = CCDelayTime::create(2.0f);
    key->runAction(CCSequence::create(spawn,waiting,CCCallFuncN::create(this, callfuncN_selector(MainGameScene::showKeyDone)),NULL));
}
void MainGameScene::showKeyDone(cocos2d::CCNode *sender){
    
}
void MainGameScene::initselPaopaoArray(){
    for (int i = 0; i<selPaopaoArray->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)selPaopaoArray->objectAtIndex(i);
        _myPaopao->checkStat = 0;
        int idx = _myPaopao->PaoPaoType;
        _myPaopao->setTextureRect(CCRectMake(64 * idx,64 * 0,64,64));
    }
    selPaopaoArray->removeAllObjects();
}
void MainGameScene::playAudio(int audioType){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
        
        switch (audioType) {
            case 1:
                SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.caf", true);
                //SimpleAudioEngine::sharedEngine()->playEffect("bgMusic.caf");
                break;
            case 2:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 3:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 4:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 5:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 6:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 7:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            case 8:
                SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                break;
            default:
                break;
        }

    }
}

void MainGameScene::initModeMenu(int continueStat,int gameMode){
   // CCLog("continueStat:%i,gameMode:%i",continueStat,gameMode);
    switch (gameMode) {
        case 1:
            pNewGame = CCMenuItemImage::create("Smnew_before.png", "Smnew_after.png",this,menu_selector(MainGameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Smcontinue_before.png", "Smcontinue_after.png","continue_before_huise.png",this,menu_selector(MainGameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Smsave_before.png", "Smsave_after.png",this,menu_selector(MainGameScene::menuBackCallBack));
            break;
        case 2:
            pNewGame = CCMenuItemImage::create("Cmnew_before.png", "Cmnew_after.png",this,menu_selector(MainGameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Cmcontinue_before.png", "Cmcontinue_after.png","continue_before_huise.png",this,menu_selector(MainGameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Cmsave_before.png", "Cmsave_after.png",this,menu_selector(MainGameScene::menuBackCallBack));
            break;
        case 3:
            pNewGame = CCMenuItemImage::create("Chmnew_bafore.png", "Chmnew_after.png",this,menu_selector(MainGameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Chmcontinue_before.png", "Chmcontinue_after.png","continue_before_huise.png",this,menu_selector(MainGameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Chmsave_before.png", "Chmsave_after.png",this,menu_selector(MainGameScene::menuBackCallBack));
            break;
            
        default:
            break;
    }
    //pNewGame = CCMenuItemImage::create("Smnew_before.png", "Smnew_after.png",this,menu_selector(MenuGameSceneLayer::menuNewGameCallBack));
    pNewGame->setPosition(ccp(200,160));
    pNewGame->setRotation(-90);
    pNewGame->setScale(0.4);
    
    //pResume = CCMenuItemImage::create("Smcontinue_before.png", "Smcontinue_after.png","continue_before_huise.png",this,menu_selector(MenuGameSceneLayer::menuContinueCallBack));
    pResume->setPosition(ccp(250,160));
    pResume->setRotation(-90);
    pResume->setScale(0.4);
    if (continueStat == 0) {
        pResume->setEnabled(false);
    }
    
    // pBack = CCMenuItemImage::create("Smsave_before.png", "Smsave_after.png",this,menu_selector(MenuGameSceneLayer::menuBackCallBack));
    pBack->setPosition(ccp(300,160));
    pBack->setRotation(-90);
    pBack->setScale(0.4);
    
    pMenu = CCMenu::create(pResume,pBack,pNewGame, NULL);
    pMenu->setPosition(ccp(-480,0));
   // pMenu->setZOrder(1000);
    this->addChild(pMenu, PauseMenuZorder);
    pMenu->runAction(CCEaseBackOut::create(CCSequence::create(CCMoveTo::create(0.3f, ccp(0,0)),NULL)));
    
    
}

void MainGameScene::menuNewGameCallBack(){
    switch (curGameMode) {
        case 1:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 11);
            CCUserDefault::sharedUserDefault()->flush();
            break;
        case 2:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 21);
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        default:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", 31);
            CCUserDefault::sharedUserDefault()->flush();
            break;
    }
// fnPlayer(CCUserDefault::sharedUserDefault()->getIntegerForKey("GameParameter"));
    CCScene* sc = MainGameScene::scene();
    sc->setRotation(90);
    sc->setPosition(ccp(80, 80));
    CCDirector::sharedDirector()->replaceScene(sc);
}
void MainGameScene::menuContinueCallBack(){
    pauseStat = false;
    this->setTouchEnabled(true);
    pMenu->runAction(CCEaseBackIn::create(CCSequence::create(CCMoveTo::create(0.3f, ccp(-480,0)),CCCallFuncN::create(this,callfuncN_selector(MainGameScene::menuDel)),NULL)));
    
}
void MainGameScene::menuBackCallBack(){
    switch (curGameMode) {
        case 1:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageSm", curStage);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreSm", Score);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreSm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreSm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
        case 2:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageCm", curStage);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreCm", Score);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreCm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreCm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        default:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageChm", curStage);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreChm", Score);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreChm",0) < Score) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("bestScoreChm", Score);
            }
            CCUserDefault::sharedUserDefault()->flush();
            break;
    }
    
    //this->setTouchEnabled(true);
    pauseStat = false;
    
    CCScene* FirstScene = FirstScene::scene();
    //FirstScene->setRotation(90);
    //FirstScene->setPosition(ccp(80, 80));
    CCDirector::sharedDirector()->replaceScene(FirstScene);
    
}
void MainGameScene::menuDel(CCMenu* spender){
    CCMenu* menu = (CCMenu*)spender;
    removeChild(menu);
    //removeChild(pMenu);
}
void MainGameScene::setGameParameter(int GameParameter){
    // CCLog("setGame");
    switch (GameParameter) {
        case 11:  //Sm->newGame
            curGameMode = 1;
            curStage = 1;
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreSm",0);
            Score = 0;
            break;
        case 12:  //Sm->continue
            curGameMode = 1;
            curStage = CCUserDefault::sharedUserDefault()->getIntegerForKey("curStageSm",0);
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreSm",0);
            Score = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreSm",0);
            break;
        case 21:  //Cm->newGame
            curGameMode = 2;
            curStage = 1;
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreCm",0);
            Score = 0;
            break;
        case 22:  //Cm->continue
            curGameMode = 2;
            curStage = CCUserDefault::sharedUserDefault()->getIntegerForKey("curStageCm",0);
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreCm",0);
            Score = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreCm",0);
            break;
        case 31:  //Chm->newGame
            curGameMode = 3;
            curStage = 1;
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreChm",0);
            Score = 0;
            break;
        case 32:  //Chm->continue
            curGameMode = 3;
            curStage = CCUserDefault::sharedUserDefault()->getIntegerForKey("curStageChm",0);
            bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bestScoreChm",0);
            Score = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreChm",0);
            break;
            
        default:
            curGameMode = 1;
            curStage = 1;
            Score = 0;
            break;
    }
    //  CCLog("curGameMode:%i,curStage:%i",curGameMode,curStage);
}
void MainGameScene::initConfig(){
    
    pauseStat = false;
    //curStage = 99;
    // curGameMode = 1;

// sprintf(curGameModeTag, "%d",curStage);
    switch (curGameMode) {
        case 1:
            corlorNum = 4;
            break;
        case 2:
            corlorNum = 5;
            break;
        case 3:
            corlorNum = 6;
            break;
            
        default:
            corlorNum = 7;
            break;
    }
    //corlorNum = 6;//test
    targetScoreData = TargetScoreData::create();
    targetScore = targetScoreData->gettargetScore(curGameMode, curStage);

}
#pragma mark -
#pragma mark Menu
void MainGameScene::loadMagicStarMenu(){
    CCSprite* MagicStarBg = CCSprite::create("magic_Star_bg.png");
    MagicStarBg->setPosition(ccp(455, 160));
    MagicStarBg->setRotation(-90);
    MagicStarBg->setScale(0.5);
    

    //MenuStarRowY = 40;
   // menuStar = CCPointMake(0, -320);
   // CCLog("corlornum:%i",corlorNum);
    switch (corlorNum) {
        case 5:
            MenuStarRowY = 40;
            menuStar = CCPointMake(0, -40);
            break;
        case 4:
            MenuStarRowY = 40;
            menuStar = CCPointMake(0, -80);
            break;
        default:
            MenuStarRowY = 40;
            menuStar = CCPointMake(0, 0);
            break;
    }
    CCSpriteBatchNode* starNode = CCSpriteBatchNode::create("sekuai.png");
    m_star = starNode->getTexture();
    
    CCMenuItemSprite* c_magicStar1 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*5, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*5, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar1->setPosition(ccp(455, MenuStarRowY*1));
    c_magicStar1->setTag(5);
    c_magicStar1->setScale(0.4);
    c_magicStar1->setRotation(-90);
    if (corlorNum<6) {c_magicStar1->setVisible(false);}

    

    CCMenuItemSprite* c_magicStar2 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*4, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*4, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar2->setPosition(ccp(455, MenuStarRowY*2));
    c_magicStar2->setTag(4);
    c_magicStar2->setScale(0.4);
    c_magicStar2->setRotation(-90);
    if (corlorNum<5) {c_magicStar2->setVisible(false);}
    
    CCMenuItemSprite* c_magicStar3 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*3, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*3, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar3->setPosition(ccp(455, MenuStarRowY*3));
    c_magicStar3->setTag(3);
    c_magicStar3->setScale(0.4);
    c_magicStar3->setRotation(-90);

    CCMenuItemSprite* c_magicStar4 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*2, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*2, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar4->setPosition(ccp(455, MenuStarRowY*4));
    c_magicStar4->setTag(2);
    c_magicStar4->setScale(0.4);
    c_magicStar4->setRotation(-90);

    CCMenuItemSprite* c_magicStar5 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*1, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*1, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar5->setPosition(ccp(455, MenuStarRowY*5));
    c_magicStar5->setTag(1);
    c_magicStar5->setScale(0.4);
    c_magicStar5->setRotation(-90);
    

    CCMenuItemSprite* c_magicStar6 = CCMenuItemSprite::create(CCSprite::createWithTexture(m_star, CCRect(64*0, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*0, 64*1, 64, 64)),this,menu_selector(MainGameScene::c_magicStarCallBack));
    c_magicStar6->setPosition(ccp(455, MenuStarRowY*6));
    c_magicStar6->setTag(0);
    c_magicStar6->setScale(0.4);
    c_magicStar6->setRotation(-90);
    
    CCMenuItemImage *c_magicStarLeaveBtn = CCMenuItemImage::create("magic_Star_close.png", "magic_Star_close.png",this,menu_selector(MainGameScene::c_magicStarLeaveBtnCallBack));
    c_magicStarLeaveBtn->setPosition(ccp(455, 295));
    c_magicStarLeaveBtn->setScale(0.5);
    c_magicStarLeaveBtn->setRotation(-90);
    
    CCMenu* pMagic = CCMenu::create(c_magicStar1,c_magicStar2,c_magicStar3,c_magicStar4,c_magicStar5,c_magicStar6,c_magicStarLeaveBtn,NULL);
    pMagic->setPosition(CCPointZero);
    pMagic->setTag(MagicStarMenuTag);
    //pMagic->setTag(100);
   // this->addChild(pEquipmentMenu);

    MagicStarMenuNode = CCNode::create();
    MagicStarMenuNode->addChild(MagicStarBg);
    MagicStarMenuNode->addChild(pMagic);
    MagicStarMenuNode->setPosition(ccp(0, -350));
    addChild(MagicStarMenuNode, 100);
    
    
    
}
void MainGameScene::moveEquipmentMenu(){
    if (EquipmentMenuNode->getPositionX()>0) {
       // CCLOG("test");
        EquipmentMenuNode->runAction(CCSequence::create(CCMoveTo::create(0.2f, ccp(0, 0)),NULL));
    }else{
        EquipmentMenuNode->runAction(CCSequence::create(CCMoveTo::create(0.2f, ccp(300, 0)),NULL));
    }

}
void MainGameScene::moveMagicStarMenu(){
    if (MagicStarMenuNode->getPositionY() == -350) {
        MagicStarMenuNode->runAction(CCSequence::create(CCMoveTo::create(0.2f, menuStar),NULL));
    }else{
        MagicStarMenuNode->runAction(CCSequence::create(CCMoveTo::create(0.2f, ccp(0, -350)),NULL));
    }
}
void MainGameScene::c_magicStarCallBack(CCObject *pSender){
    initMagicStarMenu();
        CCMenuItemSprite* magicStarItem = (CCMenuItemSprite*)pSender;
        magicStarType = magicStarItem->getTag();
       magicStarItem->initWithNormalSprite(CCSprite::createWithTexture(m_star, CCRect(64*magicStarType, 64*1, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*magicStarType, 64*0, 64, 64)),NULL,this,menu_selector(MainGameScene::c_magicStarCallBack));
         magicStarItem->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.4f, 0.35),CCScaleTo::create(0.4f, 0.45),NULL)));
}
void MainGameScene::initMagicStarMenu(){
    //CCLog("initmagicmenu");
    for (int i = 0; i< corlorNum; i++) {
        CCMenuItemSprite* magicStarItem =(CCMenuItemSprite*) MagicStarMenuNode->getChildByTag(MagicStarMenuTag)->getChildByTag(i);
        magicStarItem->initWithNormalSprite(CCSprite::createWithTexture(m_star, CCRect(64*i, 64*0, 64, 64)), CCSprite::createWithTexture(m_star, CCRect(64*i, 64*1, 64*1, 64)),NULL,this,menu_selector(MainGameScene::c_magicStarCallBack));
        magicStarItem->stopAllActions();
        magicStarItem->setScale(0.4);
    }
    magicStarType = -1;
}
void MainGameScene::test(){
    CCLOG("test");
}
void MainGameScene::loadEquipmentMenu(){
    CCMenuItemImage *magicStar = CCMenuItemImage::create("magic_Star.png", "magic_Star_after.png",this,menu_selector(MainGameScene::menuMagicStarCallBack));
    magicStar->setPosition(ccp(455,80));
    magicStar->setRotation(-90);
    magicStar->setTag(MagicStarTag);
    //magicStar->setZOrder(1000);
    magicStar->setScale(0.4);
    
    if (magicStarNum<=0) {
        e_magicStarTTF = CCLabelTTF::create("+", "Arial", 45);
    }else{
        char magicStarNumChar[128];
        sprintf(magicStarNumChar, "%d",magicStarNum);
        e_magicStarTTF = CCLabelTTF::create(magicStarNumChar, "Arial", 45);
    }

    e_magicStarTTF->setPosition(ccp(440, 96));
    e_magicStarTTF->setRotation(-90);
    e_magicStarTTF->setScale(0.3);
    // e_magicStarTTF->setColor(ccc3(90, 190, 40));
    
    CCSprite *e_magicStarBg = CCSprite::create("equipment_bg.png");
    e_magicStarBg->setPosition(ccp(440, 96));
    e_magicStarBg->setScale(0.3);
    
    magicChan = CCMenuItemImage::create("magic_Chan.png", "magic_Chan_after.png",this,menu_selector(MainGameScene::menuMagicChanCallBack));
    magicChan->setPosition(ccp(455,160));
    magicChan->setRotation(-90);
    magicChan->setTag(MagicChanTag);
    magicChan->setScale(0.4);
    if (magicChanNum <= 0) {
    e_magicChanTTF = CCLabelTTF::create("+", "Arial", 45);
    }else{
        char magicChanNumChar[128];
        sprintf(magicChanNumChar, "%d",magicChanNum);
        e_magicChanTTF = CCLabelTTF::create(magicChanNumChar, "Arial", 45);
    }
    e_magicChanTTF->setPosition(ccp(440, 176));
    e_magicChanTTF->setRotation(-90);
    e_magicChanTTF->setScale(0.3);
    // e_magicBlockTTF->setColor(ccc3(90, 190, 40));
    
    CCSprite *e_magicChanBg = CCSprite::create("equipment_bg.png");
    e_magicChanBg->setPosition(ccp(440, 176));
    e_magicChanBg->setScale(0.3);
    
    magicBlock = CCMenuItemImage::create("magic_Block.png", "magic_Block_after.png",this,menu_selector(MainGameScene::menuMagicBlockCallBack));
    magicBlock->setPosition(ccp(455,240));
    magicBlock->setRotation(-90);
    magicBlock->setTag(MagicBlockTag);
    magicBlock->setScale(0.4);
    
    if (magicBlockNum <= 0) {
        e_magicBlockTTF = CCLabelTTF::create("+", "Arial", 45);
    }else{
        char magicBlockNumChar[128];
        sprintf(magicBlockNumChar, "%d",magicBlockNum);
        e_magicBlockTTF = CCLabelTTF::create(magicBlockNumChar, "Arial", 45);
    }
    e_magicBlockTTF->setPosition(ccp(440, 256));
    e_magicBlockTTF->setRotation(-90);
    e_magicBlockTTF->setScale(0.3);
    // e_magicBlockTTF->setColor(ccc3(90, 190, 40));
    
    CCSprite *e_magicBlockBg = CCSprite::create("equipment_bg.png");
    e_magicBlockBg->setPosition(ccp(440, 256));
    e_magicBlockBg->setScale(0.3);
    

    
    CCMenu* pEquipmentMenu = CCMenu::create(magicStar,magicChan,magicBlock,NULL);
    pEquipmentMenu->setPosition(CCPointZero);
    pEquipmentMenu->setTag(MagicMenuTag);
    //this->addChild(pEquipmentMenu);
    
    EquipmentMenuNode = CCNode::create();
    EquipmentMenuNode->addChild(pEquipmentMenu);
    EquipmentMenuNode->addChild(e_magicStarBg);
    EquipmentMenuNode->addChild(e_magicChanBg);
    EquipmentMenuNode->addChild(e_magicBlockBg);
    
    EquipmentMenuNode->addChild(e_magicStarTTF);
    EquipmentMenuNode->addChild(e_magicChanTTF);
    EquipmentMenuNode->addChild(e_magicBlockTTF);
    EquipmentMenuNode->setPosition(ccp(300, 0));
    addChild(EquipmentMenuNode,EquipmentMenuZorder);
    
}
void MainGameScene::menuMagicStarCallBack(CCObject* pSender){
    initEquipmentMenu();
    if (magicStarNum > 0) {
        magicStarType = -1;

        switch (touchMothed) {
            case 1:
                touchMothed = 0;
                break;
                
            default:
                touchMothed = 1;
                moveMagicStarMenu();
                moveEquipmentMenu();
                break;
        }
    }else{
        CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
        CCLabelTTF* productName = (CCLabelTTF*)showNode->getChildByTag(productNameTag);
        productName->setString("MagicStar");
        CCSprite* productImg = (CCSprite*)showNode->getChildByTag(productImgTag);
        productImg->initWithFile("magic_Star.png");
        CCLabelTTF* productDec = (CCLabelTTF*)showNode->getChildByTag(productDecTag);
        productDec->setString("Change the color of a star");
        CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
        purchaseStatTTF->setString("Connect AppStore...");
        showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, 0)),NULL));
        
       // menuLock = true;
        this->setTouchEnabled(false);
        requestProductPrice(1);
        TryAgainPurchaseProductId = 1;
    }

}
void MainGameScene::menuMagicBlockCallBack(CCObject* pSender){
        initEquipmentMenu();
        if (magicBlockNum >0) {
           // initEquipmentMenu();
            CCMenuItemImage *magicBlock = (CCMenuItemImage*)pSender;
            switch (touchMothed) {
                case 2:
                    touchMothed = 0;
                    //magicBlockStat = false;
                    //touchMothed = 0;
                    break;
                    
                default:
                    touchMothed = 2;
                    CCScaleTo* scale1 = CCScaleTo::create(1.0f, 0.45);
                    CCRotateTo* rotate1 = CCRotateTo::create(1.0f, -90);
                    CCSpawn* spawn1 = CCSpawn::create(scale1,rotate1,NULL);
                    
                    CCScaleTo* scale2 = CCScaleTo::create(1.0f, 0.35);
                    CCRotateTo* rotate2 = CCRotateTo::create(1.0f, -90);
                    CCSpawn* spawn2 = CCSpawn::create(scale2,rotate2,NULL);
                    
                    magicBlock->initWithNormalImage("magic_Block_after.png", "magic_Block.png", NULL, this, menu_selector(MainGameScene::menuMagicBlockCallBack));
                    magicBlock->runAction(CCRepeatForever::create(CCSequence::create(spawn1,spawn2,NULL)));
                    break;
            }
        }else{
            CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
            CCLabelTTF* productName = (CCLabelTTF*)showNode->getChildByTag(productNameTag);
            productName->setString("MagicBlock");
            CCSprite* productImg = (CCSprite*)showNode->getChildByTag(productImgTag);
            productImg->initWithFile("magic_Block.png");
            CCLabelTTF* productDec = (CCLabelTTF*)showNode->getChildByTag(productDecTag);
            productDec->setString("Change the colors of four stars into the same color as the central star");
            CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
            purchaseStatTTF->setString("Connect AppStore...");
            showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, 0)),NULL));
            
           // menuLock = true;
            this->setTouchEnabled(false);
            requestProductPrice(2);
            TryAgainPurchaseProductId = 2;
        }
}

void MainGameScene::menuMagicChanCallBack(cocos2d::CCObject *pSender){
        initEquipmentMenu();
    if (magicChanNum >0) {
        CCMenuItemImage *magicChan = (CCMenuItemImage*)pSender;
        switch (touchMothed) {
            case 3:
                CCLog("test");
                touchMothed = 0;
                break;
                
            default:
                touchMothed = 3;
                CCScaleTo* scale1 = CCScaleTo::create(1.0f, 0.45);
                CCRotateTo* rotate1 = CCRotateTo::create(1.0f, -90);
                CCSpawn* spawn1 = CCSpawn::create(scale1,rotate1,NULL);
                
                CCScaleTo* scale2 = CCScaleTo::create(1.0f, 0.35);
                CCRotateTo* rotate2 = CCRotateTo::create(1.0f, -90);
                CCSpawn* spawn2 = CCSpawn::create(scale2,rotate2,NULL);
                
                magicChan->initWithNormalImage("magic_Chan_after.png", "magic_Chan.png", NULL, this, menu_selector(MainGameScene::menuMagicChanCallBack));
                magicChan->runAction(CCRepeatForever::create(CCSequence::create(spawn1,spawn2,NULL)));
                break;
        }
    }else{
        CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
        CCLabelTTF* productName = (CCLabelTTF*)showNode->getChildByTag(productNameTag);
        productName->setString("MagicShovel");
        CCSprite* productImg = (CCSprite*)showNode->getChildByTag(productImgTag);
        productImg->initWithFile("magic_Chan.png");
        CCLabelTTF* productDec = (CCLabelTTF*)showNode->getChildByTag(productDecTag);
        productDec->setString("Clear a star");
        CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
        purchaseStatTTF->setString("Connect AppStore...");
        showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, 0)),NULL));
        
        //menuLock = true;
        requestProductPrice(3);
        this->setTouchEnabled(false);
        TryAgainPurchaseProductId = 3;
    }
}
void MainGameScene::c_magicStarLeaveBtnCallBack(){
    initMagicStarMenu();
    touchMothed = 0;
    magicStarType = -1;
    moveEquipmentMenu();
    moveMagicStarMenu();
}
void MainGameScene::initEquipmentMenu(){
   // magicBlockStat = false;
    CCMenuItemImage* magicBlock = (CCMenuItemImage*)EquipmentMenuNode->getChildByTag(MagicMenuTag)->getChildByTag(MagicBlockTag);
    magicBlock->initWithNormalImage("magic_Block.png", "magic_Block_after.png", NULL, this, menu_selector(MainGameScene::menuMagicBlockCallBack));
    magicBlock->stopAllActions();
    magicBlock->setScale(0.4);
    
   // magicChanStat = false;
    CCMenuItemImage* maigicshovel =(CCMenuItemImage*)EquipmentMenuNode->getChildByTag(MagicMenuTag)->getChildByTag(MagicChanTag);
    maigicshovel->initWithNormalImage("magic_Chan.png", "magic_Chan_after.png", NULL, this, menu_selector(MainGameScene::menuMagicChanCallBack));
    maigicshovel->stopAllActions();
    maigicshovel->setScale(0.4);
    //touchMothed = 0;
}

#pragma mark -
#pragma mark MagicChan
void MainGameScene::magicChanProcess(cocos2d::CCPoint location){
   // CCLog("magicChanProcess");
    magicChanStat = false;
    initEquipmentMenu();
    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaopao->boundingBox().containsPoint(location)) {
            touchMothed = 0;
            //_myPaopao->setScale(0.8);
            _myPaopao->checkStat = 1;
            selPaopaoArray->addObject(_myPaopao);
            clearPaopao();
            //targetScoreData->equipmentProcess(3, 2, 1);
            magicChanNum = magicChanNum-1;
            if (magicChanNum <= 0) {
                e_magicChanTTF->setString("+");
            }else{
                char magicChanNumChar[128];
                sprintf(magicChanNumChar, "%d",magicChanNum);
                e_magicChanTTF->setString(magicChanNumChar);
            }

            
        }
    }
}

#pragma mark -
#pragma mark MagicBlock

void MainGameScene::magicBlockProcess(cocos2d::CCPoint location, int paopaoType){
   
    magicBlockNum = magicBlockNum - 1;
    
    char magicBlockNumChar[128];
    //magicBlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum", 0);
    if (magicBlockNum <= 0) {
        e_magicBlockTTF->setString("+");
    }else{
          sprintf(magicBlockNumChar, "%d",magicBlockNum);
            e_magicBlockTTF->setString(magicBlockNumChar);
    }
    CCPoint magicPoint;
    for (int j = 0; j<4; j++) {
        switch (j) {
            case 0:
          magicPoint = CCPointMake(location.x, location.y-32);
                break;
            case 1:
                magicPoint = CCPointMake(location.x, location.y+32);
                break;
            case 2:
                magicPoint = CCPointMake(location.x-32, location.y);
                break;
            default:
                magicPoint = CCPointMake(location.x+32, location.y);
                break;
        }

 //CCPoint magicPoint1 = CCPointMake(location.x, location.y+32);
    for (int i = 0; i<_mapLayer->getPaopaoArray()->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)_mapLayer->getPaopaoArray()->objectAtIndex(i);
        if (_myPaopao->boundingBox().containsPoint(magicPoint)) {
            if (_myPaopao->PaoPaoType != paopaoType) {
                
                particleSysLayer->ChargePlay(paopaoType, _myPaopao->getPosition());
               // magicBlockNum = magicBlockNum - 1;
               //CCLOG("magicStarNum:%i",magicStarNum);
               // CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum", CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum")-1);
               // CCUserDefault::sharedUserDefault()->flush();
                _myPaopao->PaoPaoType = paopaoType;
                _myPaopao->setTextureRect(CCRectMake(64 * paopaoType,64 * 0,64,64));
                //if (magicBlockNum<=0) {
                   // c_magicStarLeaveBtnCallBack();
               // }
            }}
    }
    }
}
#pragma mark -
#pragma mark ProductPrice and Purchase product
void MainGameScene::requestProductPrice(int productionId){
    [inAppPurchaseManager requestProduct:productionId];
    this->schedule(schedule_selector(MainGameScene::responProductPrice));
}
void MainGameScene::responProductPrice(){
    float productPrice = [inAppPurchaseManager responPrice];
    //CCLog("productPrice:%0.2f",productPrice);
    if (productPrice > 0) {
        this->unschedule(schedule_selector(MainGameScene::responProductPrice));
        char productPrictChar[128];
        sprintf(productPrictChar, "%0.2f",productPrice);
        CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
        CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
        purchaseStatTTF->setString("");
        CCSprite* okBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
        okBtn->setVisible(true);
        CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
        okBtnTTF->setString(productPrictChar);
        okBtnTTF->setZOrder(TryAgainPurchaseProductId);
    }

}
void MainGameScene::equipmentSaveAndGet(int mothed){
    switch (mothed) {
        case 1:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("magicStarNum",magicStarNum);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum",magicBlockNum);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("magicChanNum",magicChanNum);
            CCUserDefault::sharedUserDefault()->flush();
            break;
            
        default:
            magicStarNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("magicStarNum");
            magicBlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum");
            magicChanNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("magicChanNum");
            break;
    }
}
void MainGameScene::purchaseProduct(int productionId){
   // CCLog("purchaseProduct");
   // InAppPurchaseManager* inAppPurchaseManage;
    //inAppPurchaseManager = [[InAppPurchaseManager alloc]init];
    [inAppPurchaseManager purchaseProduct:productionId];
   // this->schedule(schedule_selector(TestIAPScene::responPrice));
    this->schedule(schedule_selector(MainGameScene::responPurchaseStat));
}
void MainGameScene::responPurchaseStat(){
    //int purchaseStat = -1;
    int purchaseStat = [inAppPurchaseManager responPurchaseStat];
     //CCLOG("purchaseStat:%i",purchaseStat);
    if (purchaseStat>0) {
        this->unschedule(schedule_selector(MainGameScene::responPurchaseStat));
        [inAppPurchaseManager showPurchaseSecess];
     //   CCLog("purchase:%i",purchaseStat);
        if (purchaseStat == 1) {
            CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
            CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
            purchaseStatTTF->setString("Purchase success");
            CCSprite* okBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
            okBtn->setVisible(true);
            CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
            okBtnTTF->setString("OK");
            okBtnTTF->setZOrder(okBtnTTFZorder);
            magicStarNum = magicStarNum + 5;
            
            char magicStarNumChar[128];
            sprintf(magicStarNumChar, "%d",magicStarNum);
            e_magicStarTTF->setString(magicStarNumChar);
        }else if (purchaseStat == 2){
            CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
            CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
            purchaseStatTTF->setString("Purchase success");
            CCSprite* okBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
            okBtn->setVisible(true);
            CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
            okBtnTTF->setString("OK");
            okBtnTTF->setZOrder(okBtnTTFZorder);
            magicBlockNum = magicBlockNum + 5;
            //magicBlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum") + 5;
            //CCUserDefault::sharedUserDefault()->setIntegerForKey("magicBlockNum", (CCUserDefault::sharedUserDefault()->getIntegerForKey("magicBlockNum") + 5));
           // CCUserDefault::sharedUserDefault()->flush();
            
            char magicBlockNumChar[128];
            sprintf(magicBlockNumChar, "%d",magicBlockNum);
            e_magicBlockTTF->setString(magicBlockNumChar);
           // showWindowLayer->showPurchaseSuccess(2);
        }else if (purchaseStat == 3){
            CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
            CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
            purchaseStatTTF->setString("Purchase success");
            CCSprite* okBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
            okBtn->setVisible(true);
            CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
            okBtnTTF->setString("OK");
            okBtnTTF->setZOrder(okBtnTTFZorder);
            //okBtnTTF->setZOrder(111);
            magicChanNum = magicChanNum+5;
            if (magicChanNum <= 0) {
                e_magicChanTTF->setString("+");
            }else{
                char magicChanNumChar[128];
                sprintf(magicChanNumChar, "%d",magicChanNum);
                e_magicChanTTF->setString(magicChanNumChar);
            }
        }
       // CCUserDefault::sharedUserDefault()->setIntegerForKey("magicStarNum", magicStarNum);


       // iAPDialogLayer->getPurchaseStatTTF()->setString("purchase success");
       // CCLOG("purchase Success, magicStarNum:%i,magicBlockNum:%i,magicChanNum:%i",magicStarNum,magicBlockNum);
    }else if (purchaseStat == -1){
        this->unschedule(schedule_selector(MainGameScene::responPurchaseStat));
        CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
        CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
        purchaseStatTTF->setString("Purchase Fail");
        CCSprite* okBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
        okBtn->setVisible(true);
        CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
        okBtnTTF->setString("Try Again");
        okBtnTTF->setZOrder(TryAgainPurchaseProductId);
        //CCSprite* TryAgainBtn = (CCSprite*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTTFTag);
        //TryAgainBtn->setVisible(true);
        //iAPDialogLayer->getPurchaseStatTTF()->setString("purchase cancle");
    }else{
        //iAPDialogLayer->getPurchaseStatTTF()->setString("purchase Loading");
    }
    // CCLog("responPurchaseStat");
    // int purchaseStat = [inAppPurchaseManage responPurchaseStat];
    //CCLog("purchaseStat:%i",purchaseStat);
}

#pragma mark -
#pragma mark ShowWin
void MainGameScene::loadPurshaseWinDow(){

    CCSprite* showWinBg = CCSprite::create("ShowWinBg.png");
    showWinBg->setPosition(ccp(240, 160));
    //showWinBg->setScale(0.5);
    showWinBg->setScaleX(0.7);
    showWinBg->setScaleY(0.5);
    //showWinBg->setTag(1002);
    
    CCMenuItemImage *closeBtn = CCMenuItemImage::create("showWinClose.png", "showWinClose_after.png",this,menu_selector(MainGameScene::okBtnCallBack));
    closeBtn->setPosition(ccp(60,280));
    closeBtn->setRotation(90);
    //okBtn->setZOrder(100);
    closeBtn->setScale(0.5);
    closeBtn->setTag(closeBtnTag);
    
    CCMenuItemImage *okBtn = CCMenuItemImage::create("showWinBtn.png", "showWinBtn_after.png",this,menu_selector(MainGameScene::okBtnCallBack));
    okBtn->setPosition(ccp(350,160));
    okBtn->setRotation(-90);
    //okBtn->setZOrder(100);
    okBtn->setScale(0.5);
    okBtn->setVisible(false);
    okBtn->setTag(okBtnTag);
    
    CCLabelTTF* okBtnTTF = CCLabelTTF::create("", "Airal", 45);
    okBtnTTF->setPosition(ccp(350, 160));
    okBtnTTF->setRotation(-90);
    okBtnTTF->setScale(0.3);
    //okBtnTTF->setTag(okBtnTTFTag);
    
    CCMenu* pShowMenu = CCMenu::create(okBtn,closeBtn,NULL);
    pShowMenu->setPosition(CCPointZero);
    //this->addChild(pShowMenu);
    
    CCSprite* productImg = CCSprite::create("magic_Star.png");
    productImg->setPosition(ccp(170, 160));
    productImg->setScale(0.5);
    productImg->setRotation(-90);
    
    CCLabelTTF* productNum = CCLabelTTF::create("x5", "Arial", 50);
    productNum->setPosition(ccp(185, 200));
    productNum->setScale(0.5);
    productNum->setRotation(-90);
    
    CCLabelTTF* productDec = CCLabelTTF::create("","Arial", 35,CCSizeMake(620, 100),kCCTextAlignmentCenter);
    productDec->setPosition(ccp(220, 160));
    productDec->setScale(0.3);
    productDec->setRotation(-90);
    
    CCLabelTTF* productName = CCLabelTTF::create("", "Arial", 50);
    productName->setPosition(ccp(100, 160));
    productName->setScale(0.5);
    productName->setRotation(-90);
    
    CCLabelTTF* purchaseStatTTF = CCLabelTTF::create("MagicStar", "Arial", 35);
    purchaseStatTTF->setPosition(ccp(300,160));
    purchaseStatTTF->setScale(0.3);
    purchaseStatTTF->setRotation(-90);
    
   CCNode* showNode = CCNode::create();
    //showNode->setTag(1003);
    
    showNode->addChild(showWinBg);
    //showNode->addChild(showSharebg);
    showNode->addChild(purchaseStatTTF,0,purchaseStatTTFTag);
    showNode->addChild(pShowMenu,0,pShowMenuTag);
    showNode->addChild(productImg,0,productImgTag);
    showNode->addChild(productNum);
    showNode->addChild(productDec,0,productDecTag);
    showNode->addChild(productName,0,productNameTag);
    showNode->addChild(okBtnTTF,okBtnTTFZorder,okBtnTTFTag);
    showNode->setPosition(ccp(0, -320));
    
    addChild(showNode,ShowPurchaseWindowZorder,ShowPurchaseWindowTag);
}
void MainGameScene::closeBtnCallBack(cocos2d::CCObject *pSender){
    CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
    CCMenuItemImage* okBtn = (CCMenuItemImage*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
    okBtn->setVisible(false);
    CCMenuItemImage* TryAgainBtn = (CCMenuItemImage*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTTFTag);
    TryAgainBtn->setVisible(false);
    this->setTouchEnabled(true);
    showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, -320)),NULL));
}
void MainGameScene::okBtnCallBack(CCObject* pSender){
    CCNode* showNode = (CCNode*)(this->getChildByTag(ShowPurchaseWindowTag));
    CCMenuItemImage* okBtn = (CCMenuItemImage*)showNode->getChildByTag(pShowMenuTag)->getChildByTag(okBtnTag);
    CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
    CCLabelTTF* okBtnTTF = (CCLabelTTF*)showNode->getChildByTag(okBtnTTFTag);
    //TryAgainBtn->setVisible(false);
    okBtn->setVisible(false);
    okBtnTTF->setString("");
    CCMenuItemImage* btn = (CCMenuItemImage*)pSender;
    switch (btn->getTag()) {
        case closeBtnTag:
            //CCLog("close");
           // menuLock = false;
            this->setTouchEnabled(true);
            showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, -320)),NULL));
            okBtn->setVisible(false);
            okBtnTTF->setString("");
            purchaseStatTTF->setString("");
            break;
        case okBtnTag:
           // CCLog("okBtn");
            if (okBtnTTF->getZOrder() == 1) {
                //CCLog("purchase magicStar");
                purchaseProduct(1);
                purchaseStatTTF->setString("Purchasing...");
               // this->setTouchEnabled(true);
                //showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, -320)),NULL));
            }else if (okBtnTTF->getZOrder() == 2){
               // CCLog("purchase magicblock");
                purchaseProduct(2);
                purchaseStatTTF->setString("Purchasing...");
            }else if (okBtnTTF->getZOrder() == 3){
                //CCLog("purchase magicshovel");
                purchaseProduct(3);
                purchaseStatTTF->setString("Purchasing...");
            }else{
                //CCLog("ok");
                //menuLock = false;
                this->setTouchEnabled(true);
                showNode->runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(0, -320)),NULL));
                //okBtn->setVisible(false);
               // okBtnTTF->setString("");
                purchaseStatTTF->setString("");
               // CCLog("TryAgain");
               // okBtnTTF->setString("");
                // CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
                // purchaseStatTTF->setString("Connect AppStore");
                // purchaseProduct(TryAgainPurchaseProductId);
            }

            break;
            
        default:
           // CCLog("TryAgain");
           // CCLabelTTF* purchaseStatTTF = (CCLabelTTF*)showNode->getChildByTag(purchaseStatTTFTag);
           // purchaseStatTTF->setString("Connect AppStore");
           // purchaseProduct(TryAgainPurchaseProductId);
            break;
    }
}
void MainGameScene::onExit(){
        //CCLog("onexit");
    equipmentSaveAndGet(1);
    CCLayer::onExit();
    

}
void MainGameScene::onEnter(){
    //this->schedule(schedule_selector(MainGameScene::loadMap), 5.0f);
   // CCLog("onEnter");
    equipmentSaveAndGet(2);
    CCLayer::onEnter();
}
