//
//  GameScene.cpp
//  pop
//
//  Created by long shenghua on 13-9-5.
//
//

#include "GameScene.h"

enum {
    kTagParentNode = 10,
};
GameScene::GameScene(){
    PaopaoArray = CCArray::create();
    SelPaopaoArray = CCArray::create();
    CC_SAFE_RETAIN(PaopaoArray);
    CC_SAFE_RETAIN(SelPaopaoArray);

 }
GameScene::~GameScene(){
    CC_SAFE_RELEASE_NULL(PaopaoArray);
    CC_SAFE_RELEASE_NULL(SelPaopaoArray);
}
bool GameScene::init(){
    if ( !CCLayer::init() )
    {
        return false;
    }
    continueStat = 1;
    gameMode = 2;
    gameStat = true;
    winSize = CCDirector::sharedDirector()->getWinSize();
    setGameParameter(CCUserDefault::sharedUserDefault()->getIntegerForKey("GameParameter"));
    
    initGamebg();
    initConfig();


    parent = CCSpriteBatchNode::create("sekuai.png", 1000);
    m_pSpriteTexture = parent->getTexture();
    addChild(parent, 0, kTagParentNode);
    
    
    
    //this->schedule(schedule_selector(GameScene::initMap),1.0f);
    initMap();
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameScene::update),2.0f);
    
    initBaozhaLayer();
    
   // MenuGameSceneLayer* MenuLayer = MenuGameSceneLayer::create();
    //this->addChild(MenuLayer);
    
    //initMenu();
    initPauseMenu();
    return true;

}
void GameScene::setGameParameter(int GameParameter){
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
void GameScene::initConfig(){

    pauseStat = false;
    //curStage = 99;
   // curGameMode = 1;
   // sprintf(curGameModeTag, "%d",curStage);
    switch (curGameMode) {
        case 1:
            corlorNum = 4;
           // gameBgLayer->GetcurGameModeIcon()->initWithFile("Default.png");
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
    switch (curStage) {
        case 1:
            targetScore = 1000;
            break;
        case 2:
            targetScore = 3000;
            break;
        case 3:
            targetScore = 6000;
        case 4:
            targetScore = 8000;
            break;
        case 5:
            targetScore = 1000;
            break;
        case 6:
            targetScore = 13000;
            break;
        case 7:
            targetScore = 15000;
            break;
        case 8:
            targetScore = 17000;
            break;
        case 9:
            targetScore = 20000;
            break;
        case 10:
            targetScore = 24000;
            break;
        case 11:
            targetScore = 27000;
            break;
        case 12:
            targetScore = 30000;
            break;
        case 13:
            targetScore = 33000;
            break;
        case 14:
            targetScore = 35000;
            break;
        case 15:
            targetScore = 38000;
            break;
        case 16:
            targetScore = 40000;
            break;
        case 17:
            targetScore = 42000;
            break;
        case 18:
            targetScore = 45000;
            break;
        case 19:
            targetScore = 47000;
            break;
        case 20:
            targetScore = 50000;
            break;
        case 21:
            targetScore = 52000;
            break;
        case 22:
            targetScore = 54000;
            break;
        case 23:
            targetScore = 57000;
            break;
        case 24:
            targetScore = 60000;
            break;
        case 25:
            targetScore = 63000;
            break;
        case 26:
            targetScore = 65000;
            break;
        case 27:
            targetScore = 68000;
            break;
        default:
           targetScore =  targetScore+2000;
            break;
    }
    sprintf(ScoreChar, "%d",Score);
    gameBgLayer->GetscoreTTF()->setString(ScoreChar);
    
    sprintf(targetScoreChar, "%d",targetScore);
    gameBgLayer->GettargetScoreTTF()->setString(targetScoreChar);
    
    sprintf(stageChar, "%d",curStage);
    gameBgLayer->GetstageTTF()->setString(stageChar);
    
    sprintf(bestScoreChar, "%d",bestScore);
    gameBgLayer->GetbestScoreTTF()->setString(bestScoreChar);
    
   // CCLog("curGameMode:%i,curStage:%i,bestScore:%i,score:%i,targetScore:%i",curGameMode,curStage,bestScore,Score,targetScore);
}
void GameScene::initBaozhaLayer(){
    BaozhaLayer = Particle::create();
    this->addChild(BaozhaLayer);
   // BaozhaLayer->ParticleExplosion(CCPointMake(100, 200));
}

void GameScene::initMenu(){
    
   // MenuGameSceneLayer* MenuLayer = MenuGameSceneLayer::create();
   // this->addChild(MenuLayer);
    CCMenuItemImage *pPause = CCMenuItemImage::create("zanting_before.png", "zanting_after.png",this,menu_selector(GameScene::pause));
   // CCMenuItemImage *pPause = CCMenuItemImage::create("zanting.png", "Smnew_after.png",this,menu_selector(GameScene::pause));
    pPause->setPosition(ccp(82,308));
    pPause->setRotation(90);
    pPause->setZOrder(100);
    pPause->setScale(0.8);
  
    switch (curGameMode) {
        case 1:
            pNewGame = CCMenuItemImage::create("Smnew_before.png", "Smnew_after.png",this,menu_selector(GameScene::menuNewGame));
            pNewGame->setPosition(ccp(0-pNewGame->getContentSize().width,160));
            pNewGame->setRotation(-90);
            pNewGame->setScale(0.4);
            
            pResume = CCMenuItemImage::create("Smcontinue_before.png", "Smcontinue_after.png","continue_before_huise.png",this,menu_selector(GameScene::movePauseBtn));
            pResume->setPosition(ccp(250,320+pResume->getContentSize().height));
            pResume->setRotation(-90);
            pResume->setScale(0.4);
           // pResume->setEnabled(false);
            
            pBack = CCMenuItemImage::create("Smsave_before.png", "Smsave_after.png",this,menu_selector(GameScene::saveAndExit));
            pBack->setPosition(ccp(480+pResume->getContentSize().width,160));
            pBack->setRotation(-90);
            pBack->setScale(0.4);
            break;
        case 2:
            pNewGame = CCMenuItemImage::create("Cmnew_before.png", "Cmnew_after.png",this,menu_selector(GameScene::menuNewGame));
            pNewGame->setPosition(ccp(0-pNewGame->getContentSize().width,160));
            pNewGame->setRotation(-90);
            pNewGame->setScale(0.4);
            
            pResume = CCMenuItemImage::create("Cmcontinue_before.png", "Cmcontinue_after.png",this,menu_selector(GameScene::movePauseBtn));
            pResume->setPosition(ccp(250,320+pResume->getContentSize().height));
            pResume->setRotation(-90);
            pResume->setScale(0.4);
            
            pBack = CCMenuItemImage::create("Cmsave_before.png", "Cmsave_after.png",this,menu_selector(GameScene::saveAndExit));
            pBack->setPosition(ccp(480+pResume->getContentSize().width,160));
            pBack->setRotation(-90);
            pBack->setScale(0.4);
            break;
            

             case 3:
           // CCLog("chm");
            pNewGame = CCMenuItemImage::create("Chmnew_bafore.png", "Chmnew_after.png",this,menu_selector(GameScene::menuNewGame));
            pNewGame->setPosition(ccp(0-pNewGame->getContentSize().width,160));
            pNewGame->setRotation(-90);
            pNewGame->setScale(0.4);
            
            pResume = CCMenuItemImage::create("Chmcontinue_before.png", "Chmcontinue_after.png",this,menu_selector(GameScene::movePauseBtn));
            pResume->setPosition(ccp(250,320+pResume->getContentSize().height));
            pResume->setRotation(-90);
            pResume->setScale(0.4);
            
            pBack = CCMenuItemImage::create("Chmsave_before.png", "Chmsave_after.png",this,menu_selector(GameScene::saveAndExit));
            pBack->setPosition(ccp(480+pResume->getContentSize().width,160));
            pBack->setRotation(-90);
            pBack->setScale(0.4);
            break;
        default:            
            break;
    }

    
    CCMenu* pMenu = CCMenu::create(pResume,pPause,pBack,pNewGame, NULL);
    pMenu->setPosition( CCPointZero );
    pMenu->setZOrder(1000);
    this->addChild(pMenu, 10);
}
void GameScene::resume(){
    CCLog("resume");
}
void GameScene::pause(){
    CCLog("pause");
    if (pauseStat == false) {
    pauseStat = true;
    this->setTouchEnabled(false);
    //addPauseBtn();
        initModeMenu(continueStat, curGameMode);
        }
}
void GameScene::menuPause(){
    CCLog("menuPause");
}
void GameScene::addPauseBtn(){
    CCMoveTo* move3 = CCMoveTo::create(1.0f, CCPointMake(200, 160));
    CCSequence* seq3 = CCSequence::create(move3,NULL);
    pNewGame->runAction(CCEaseBackIn::create(seq3));
    
    CCMoveTo* move1 = CCMoveTo::create(1.0f, CCPointMake(250, 160));
    CCSequence* seq1 = CCSequence::create(move1,NULL);
    pResume->runAction(CCEaseBackIn::create(seq1));
    
    CCMoveTo* move2 = CCMoveTo::create(1.0f, CCPointMake(300, 160));
    CCSequence* seq2 = CCSequence::create(move2,NULL);
    pBack->runAction(CCEaseBackIn::create(seq2));
    
    //CCDirector::sharedDirector()->pause();
}
void GameScene::movePauseBtn(){
  
    CCMoveTo* move1 = CCMoveTo::create(0.5f, CCPointMake(pResume->getPositionX(), 320+pResume->getContentSize().height));
    CCSequence* seq1 = CCSequence::create(move1,NULL);
    pResume->runAction(seq1);
    
    CCMoveTo* move2 = CCMoveTo::create(0.5f, CCPointMake(0-pNewGame->getContentSize().width, 160));
    CCSequence* seq2 = CCSequence::create(move2,NULL);
    pNewGame->runAction(seq2);
    
    CCMoveTo* move3 = CCMoveTo::create(0.5f, CCPointMake(480+pBack->getContentSize().width, 160));
    CCSequence* seq3 = CCSequence::create(move3,NULL);
    pBack->runAction(seq3);
    
    
    this->setTouchEnabled(true);
    pauseStat = false;
}

void GameScene::ccTouchesEnded(CCSet *touches,CCEvent *event)
{
            CCTouch *touch = (CCTouch*)touches->anyObject();
            CCPoint location = touch->getLocationInView();
            location = this->convertTouchToNodeSpace(touch);
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
       if (_myPaoPao->boundingBox().containsPoint(location)) {
            if (_myPaoPao->checkStat==0) {
                initPaopaoArray();
                SelPaopaoArray->removeAllObjects();
                _myPaoPao->checkStat = 1;
                SelPaopaoArray->addObject(_myPaoPao);
                findPaopao(_myPaoPao->getPosition(), _myPaoPao->PaoPaoType);
                if (SelPaopaoArray->count()>1) {
                 selPaopao(1);
                  //  CCLog("selNum:%i,score:%i",SelPaopaoArray->count(),SelPaopaoArray->count()*SelPaopaoArray->count()*5);
                    sprintf(SelscoreChar, "%d blocks %d points",SelPaopaoArray->count(),SelPaopaoArray->count()*SelPaopaoArray->count()*5);

                }else{
                    sprintf(SelscoreChar, "%s","");
                }
                //gameBgLayer->GetselScoreTTF()->setString("1111");
                gameBgLayer->GetselScoreTTF()->setString(SelscoreChar);
                gameBgLayer->GetselScoreTTF()->visit();

            }else{
                if (SelPaopaoArray->count()>1) {
                    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
                     SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                    //SimpleAudioEngine::sharedEngine()->playEffect("a5.caf");
                    }
                    value = SelPaopaoArray->count()*5;
                    
                    Score = Score+SelPaopaoArray->count()*SelPaopaoArray->count()*5;
                    sprintf(ScoreChar, "%d",Score);
                    gameBgLayer->GetscoreTTF()->setString(ScoreChar);
                    gameBgLayer->GetscoreTTF()->visit();
                    if (Score >= targetScore) {
                        //PassNextStage
                        CCLog("passNextStage");
                    }
                    if (SelPaopaoArray->count()>=6 and SelPaopaoArray->count()<=8) {
                      //  CCLog("good");
                        showGood(1);
                    }else if (SelPaopaoArray->count()>=9 and SelPaopaoArray->count()<=10){
                       // CCLog("wow");
                        showGood(2);
                    }else if (SelPaopaoArray->count()>=11){
                       // CCLog("exce");
                        showGood(3);
                    }
                    
                    sprintf(SelscoreChar, "%s","");
                    gameBgLayer->GetselScoreTTF()->setString(SelscoreChar);
                    gameBgLayer->GetselScoreTTF()->visit();
               for (int k = 0; k< SelPaopaoArray->count(); k++) {
                    NormalPaoPao* _myPaoPao2 = (NormalPaoPao*)SelPaopaoArray->objectAtIndex(k);
                //   BaozhaLayer->ParticleExplosion(_myPaoPao2->getPosition(),_myPaoPao->PaoPaoType);
                   jiafen(_myPaoPao2->getPosition());
                   parent->removeChild(_myPaoPao2, true);
                   PaopaoArray->removeObject(_myPaoPao2);
                }
                SelPaopaoArray->removeAllObjects();
                MovePaopao_L();
                }
            }
        }
    }
    
}

void GameScene::movePaopao(){
    this->unschedule(schedule_selector(GameScene::movePaopao));
    for (int i = 0; i<10; i++) {
        bool isMove = false;
        int BasePointX = 464;
        int BasePointY = 16+32*i;
        for (int j = 0; j<PaopaoArray->count(); j++) {
            NormalPaoPao* _myPaopao = (NormalPaoPao*)PaopaoArray->objectAtIndex(j);
            if (_myPaopao->boundingBox().containsPoint(ccp(BasePointX, BasePointY))) {
                isMove = true;
            }
        }
        if (!isMove) {
            rowSpan = i;
            CCLog("rowSpan:%i",rowSpan);
            movePaopao_T();
        }
    }
   // _myPaopao->setPosition(targetPoint);
}
void GameScene::movePaopao_T(){
  //  CCLog("paopao_T");
    for (int k=0; k<10; k++) {
        int startMoveY = rowSpan+32+32*k;
        if (startMoveY > 314) {
            break;
        }
        for (int j = 0; j<10; j++) {
        int startMoveX = 464-32*j;
        
        CCPoint basePoint = CCPointMake(startMoveX, startMoveY);
        for (int i=0; i<PaopaoArray->count(); i++) {
            NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
            if (_myPaoPao->boundingBox().containsPoint(basePoint)) {
              //  int targetPointY = _myPaoPao->getPositionY()-32;
               // CCMoveTo* move1 = CCMoveTo::create(0.05f, ccp(_myPaoPao->getPositionX(),targetPointY-5));
               // CCMoveTo* move2 = CCMoveTo::create(0.05f, ccp(_myPaoPao->getPositionX(),targetPointY));
               // CCSequence* seq = CCSequence::create(move1,move2,NULL);
                
               // _myPaoPao->runAction(CCEaseBackIn::create(seq));
               // CCMoveTo* move3 = CCMoveTo::create(0.016f, ccp(_myPaoPao->getPositionX(),targetPointY));
                //_myPaoPao->runAction(CCSequence::create(move1,move2,move3,NULL));
               // CCEaseExponentialIn* ease = CCEaseExponentialIn::create(move1);
              //  _myPaoPao->runAction(CCSequence::create(ease,move2,move3,NULL));
                //_myPaoPao->runAction(CCEaseBackIn::create(CCSequence::create(CCMoveTo::create(0.2f, ccp(_myPaoPao->getPositionX(),_myPaoPao->getPositionY()-32)),NULL)));
                 _myPaoPao->runAction(CCEaseBackIn::create(CCSequence::create(CCMoveTo::create(0.2f, ccp(_myPaoPao->getPositionX(),_myPaoPao->getPositionY()-32)),NULL)));
                }
            }
            
        }
    }

}
void GameScene::MovePaopao_L(){
    for (int k= 0; k<10; k++) {
       // int y = 16+32*k;
        int y = 314-32*k;
    int moveNum = 0;
    int isPaopao = 0;
    int paopaoNum = 0;
    for (int j=0; j<10; j++) {
        int x = 464-32*j;
        CCPoint basePoint = CCPointMake(x, y);

        for (int i=0; i<PaopaoArray->count(); i++) {
            NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
           if (_myPaoPao->boundingBox().containsPoint(basePoint)) {
               // isPaopaoId = 1+1*j;
               isPaopao = 1;
                if (moveNum>0) {
                   // CCLog("need not move,j::%i,moveNum:%i",j,moveNum);
                  ///  _myPaoPao->runAction(CCSequence::create(CCMoveTo::create(0.2f, ccp(_myPaoPao->getPositionX()+32*moveNum,_myPaoPao->getPositionY())),NULL));
                   // int targetPointX = _myPaoPao->getPositionX()+32*moveNum;
                    float dt = moveNum*0.15;
                  //  CCMoveTo* move1 = CCMoveTo::create(0.08f, ccp(targetPointX+5,_myPaoPao->getPositionY()));
                  //  CCMoveTo* move2 = CCMoveTo::create(0.05f, ccp(targetPointX,_myPaoPao->getPositionY()));
                    //CCMoveTo* move3 = CCMoveTo::create(0.05f, ccp(targetPointX,_myPaoPao->getPositionY()));
                   // CCSequence* seq = CCSequence::create(move1,move2,NULL);
                   // _myPaoPao->runAction(seq);
                   // CCEaseExponentialIn* ease = CCEaseExponentialIn::create(move1);
                   // _myPaoPao->runAction(CCSequence::create(ease,move2,move3,NULL));
                    _myPaoPao->runAction(CCEaseBackIn::create(CCSequence::create(CCMoveTo::create(dt, ccp(_myPaoPao->getPositionX()+32*moveNum,_myPaoPao->getPositionY())),NULL)));
                }
            }
            
        }
        if (isPaopao == 0) {
            moveNum++;
        }else{
            paopaoNum++;
        }
       // CCLog("j:%i,isPaopao:%i,moveNum:%i",j,isPaopao,moveNum);
        isPaopao = 0;
    }
        if (paopaoNum == 0) {
          //  CCLog("k:%i,paopaoNum:%i,y:%i",k,paopaoNum,y);
            rowSpan = y;
           // this->schedule(schedule_selector(GameScene::movePaopao_T), 1.0f);
           // movePaopao_T(y);
            movePaopao_T();
           // this->schedule(schedule_selector(GameScene::movePaopao), 0.1f);
        }
    
    }
   // this->schedule(schedule_selector(GameScene::movePaopao), 0.05f);
}
void GameScene::selPaopao(int idy){
    for (int i=0; i<SelPaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)SelPaopaoArray->objectAtIndex(i);

        int idx = _myPaoPao->PaoPaoType;
        _myPaoPao->setTextureRect(CCRectMake(64 * idx,64 * idy,64,64));
        CCScaleTo* scale1 = CCScaleTo::create(0.3f, 0.53);
        CCScaleTo* scale2 = CCScaleTo::create(0.3f, 0.5);
        _myPaoPao->runAction(CCSequence::create(scale1,scale2,NULL));
    }
}
void GameScene::findPaopao(cocos2d::CCPoint location, int paopaoType){
    findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
    findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
    findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
    findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
}
void GameScene::findPaopao_T(CCPoint location,int paopaoType){
   // CCLog("find_T:%i",paopaoType);
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
          //  CCLog("paopaoType:%i",_myPaoPao->PaoPaoType);
            _myPaoPao->checkStat = 1;
           // _myPaoPao->setPosition(ccp(_myPaoPao->getPositionX()+5,_myPaoPao->getPositionY()));
            //CCScaleTo* scale1 = CCScaleTo::create(0.3f, 1.01);
            //CCScaleTo* scale2 = CCScaleTo::create(0.3f, 1);
           // _myPaoPao->runAction(CCSequence::create(scale1,scale2,NULL));
            SelPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
           // findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
                break;
        }

    }
}
void GameScene::findPaopao_R(CCPoint location,int paopaoType){
   // CCLog("find_R:%i",paopaoType);
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            SelPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            //findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
        }
    }
}
void GameScene::findPaopao_B(CCPoint location,int paopaoType){
  //  CCLog("find_B:%i",paopaoType);
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            SelPaopaoArray->addObject(_myPaoPao);
           // findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
        }
    }
}
void GameScene::findPaopao_L(CCPoint location,int paopaoType){
    //CCLog("find_L:%i",paopaoType);
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        if (_myPaoPao->boundingBox().containsPoint(location) && _myPaoPao->PaoPaoType == paopaoType && _myPaoPao->checkStat == 0) {
            _myPaoPao->checkStat = 1;
            SelPaopaoArray->addObject(_myPaoPao);
            findPaopao_T(CCPoint(location.x,location.y+32), paopaoType);
            //findPaopao_R(CCPoint(location.x+32,location.y), paopaoType);
            findPaopao_B(CCPoint(location.x,location.y-32), paopaoType);
            findPaopao_L(CCPoint(location.x-32,location.y), paopaoType);
        }
    }
}
void GameScene::initPaopaoArray(){
    for (int i=0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaoPao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        _myPaoPao->checkStat = 0;
        
       // for (int i=0; i<SelPaopaoArray->count(); i++) {
           // NormalPaoPao* _myPaoPao = (NormalPaoPao*)SelPaopaoArray->objectAtIndex(i);
            int idx = _myPaoPao->PaoPaoType;
            int idy = 0;
            _myPaoPao->setTextureRect(CCRectMake(64 * idx,64 * idy,64,64));
    }
}


void GameScene::initMap(){
    this->unschedule(schedule_selector(GameScene::initMap));
    int rowX = 480-16;
    int colY;
    for (int colNum = 1; colNum <= 10; colNum++) {
        for (int rowNum = 1; rowNum <= 10; rowNum++) {
         //   NormalPaoPao* _Paopao = NULL;
            
            if (rowNum == 1) {
               colY = 16;
            }else{
                colY = colY + 32;
            }
            addPaopao(CCPointMake(rowX, colY));
        }
        rowX = rowX - 32;
        
    }
}

void GameScene::addPaopao(CCPoint location){
   // mapSpan = mapSpan-10;
   int _paopaoType = arc4random()%corlorNum;
    NormalPaoPao* _Paopao = (NormalPaoPao*)NormalPaoPao::createPaoPao(_paopaoType,2,3,m_pSpriteTexture);
    _Paopao->setPosition(location);
   // _Paopao->setPosition(ccp(mapSpan, location.y));
    _Paopao->setScale(0.5);
    _Paopao->setTag(3);
    _Paopao->setRotation(-90);
    parent->addChild(_Paopao);
   // CCMoveTo* move1 = CCMoveTo::create(1.0f, location);
  //  CCSequence* seq = CCSequence::create(move1,NULL);
   // _Paopao->runAction(seq);
    PaopaoArray->addObject(_Paopao);
}
void GameScene::addBaozha(cocos2d::CCPoint location){
    CCLog("baozha");
}
void GameScene::update(){
    if (gameStat) {
    isGameOver();
    }
}
void GameScene::isGameOver(){
    bool gameOver = false;
    for (int k = 0; k< corlorNum; k++) {
    for (int i = 0; i<PaopaoArray->count(); i++) {
        NormalPaoPao* _myPaopao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        if (_myPaopao->PaoPaoType == k) {
          //  CCLog("isPaopao=========================================:%i,x:%f,y:%f",i,_myPaopao->getPositionX(),_myPaopao->getPositionY());
            for (int j = 0; j<PaopaoArray->count(); j++) {
                NormalPaoPao* _myPaopao2 = (NormalPaoPao*)PaopaoArray->objectAtIndex(j);
                if (_myPaopao2->PaoPaoType == k) {
                    //start check
                    int BaseX = _myPaopao->getPositionX()-_myPaopao2->getPositionX();
                    int BaseY = _myPaopao->getPositionY()-_myPaopao2->getPositionY();
                    BaseX = abs(BaseX);
                    BaseY = abs(BaseY);

                    if ((BaseY == 0 && BaseX == 32) or (BaseY == 32 && BaseX == 0)) {
                      //  CCLog("BBBBaseX:%i,BaseY:%i,t:%i,i:%i",BaseX,BaseY,abs(BaseX),i);
                        gameOver = true;
                    }
                }
            }
    }}}
    if (PaopaoArray->count() == 1) {
        gameOver = true;
    }
    if (!gameOver) {
        if (checkNum > 2) {
           // CCLog("game over");
            GameOverProcess();
            gameStat = false;
        }else{
         //   CCLog("break:%i",checkNum);
            checkNum ++;
        }
    }
}
void GameScene::GameOverProcess(){
    CCLog("PaopaoNum:%i",PaopaoArray->count());
    delPaopao();
}
void GameScene::delPaopao(){
    if (PaopaoArray->count()>0) {
        int i = PaopaoArray->count()-1;
        NormalPaoPao* _myPaopao = (NormalPaoPao*)PaopaoArray->objectAtIndex(i);
        parent->removeChild(_myPaopao, true);
        if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
          
           SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
        }
       // BaozhaLayer->ParticleExplosion(_myPaopao->getPosition(),_myPaopao->PaoPaoType);
        PaopaoArray->removeObject(_myPaopao);
    this->schedule(schedule_selector(GameScene::delPaopao), 0.2f);
    }else{
        CCLog("over");
        this->unschedule(schedule_selector(GameScene::delPaopao));
        if (Score >= targetScore) {
                  startNewStage();
        }else{
            showGameOver();
        }

    }

}
void GameScene::startNewStage(){
    curStage++;
    initConfig();
    initMap();
    gameStat = true;
}
void GameScene::saveAndExit(){
  //  CCLog("saveAndExit");

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
    
    CCMoveTo* move1 = CCMoveTo::create(0.5f, CCPointMake(0-pResume->getContentSize().width, 160));
    CCSequence* seq1 = CCSequence::create(move1,NULL);
    pResume->runAction(seq1);
    
    CCMoveTo* move2 = CCMoveTo::create(0.5f, CCPointMake(480+pBack->getContentSize().width, 160));
    CCSequence* seq2 = CCSequence::create(move2,NULL);
    pBack->runAction(seq2);
    
    
    //this->setTouchEnabled(true);
    pauseStat = false;
    
    CCScene* FirstScene = FirstScene::scene();
    CCDirector::sharedDirector()->replaceScene(FirstScene);
}
void GameScene::test(){
    CCLog("test");
}
void GameScene::testFinsh(){
    CCLog("testFinsh");
}
void GameScene::initGamebg(){
    gameBgLayer = GameBg::create();
    this->addChild(gameBgLayer);
}
void GameScene::showGood(int showId){
    switch (showId) {
        case 1:
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
                // SimpleAudioEngine::sharedEngine()->playEffect("xiaopaopao.wav");
                SimpleAudioEngine::sharedEngine()->playEffect("a5.caf");
            }
            showSprite = CCSprite::create("good.png");
            break;
        case 2:
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("soundMusic")==1) {
                SimpleAudioEngine::sharedEngine()->playEffect("good.wav");
            }
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
    addChild(showSprite);
    CCFadeOut* fadeout = CCFadeOut::create(3.0f);
    showSprite->runAction(fadeout);
    this->schedule(schedule_selector(GameScene::hideGood), 3.0f);
}
void GameScene::hideGood(){
    removeChild(showSprite);
    this->unschedule(schedule_selector(GameScene::hideGood));
}
void GameScene::menuNewGame(){
    fnPlayer(CCUserDefault::sharedUserDefault()->getIntegerForKey("GameParameter"));
}
void GameScene::fnPlayer(int GameParameter){
   // CCUserDefault::sharedUserDefault()->setIntegerForKey("GameParameter", GameParameter);
 //   CCUserDefault::sharedUserDefault()->flush();
    CCScene* sc = GameScene::scene();
   // CCTransitionTurnOffTiles *fade = CCTransitionTurnOffTiles::create(1.0f, sc);
    CCTransitionPageTurn *fade = CCTransitionPageTurn::create(1.0f, sc,true);
    CCDirector::sharedDirector()->replaceScene(fade);
}
void GameScene::initPauseMenu(){
    CCMenuItemImage *pPause = CCMenuItemImage::create("zanting_before.png", "zanting_after.png",this,menu_selector(GameScene::pause));
    //CCMenuItemImage *pPause = CCMenuItemImage::create("Icon.png", "zanting_after.png",this,menu_selector(GameScene::pause));
    // CCMenuItemImage *pPause = CCMenuItemImage::create("zanting.png", "Smnew_after.png",this,menu_selector(GameScene::pause));
    pPause->setPosition(ccp(82,305));
    pPause->setRotation(90);
    pPause->setZOrder(100);
    pPause->setScale(0.8);
    
    CCMenu* pMenuPause = CCMenu::create(pPause,NULL);
    pMenuPause->setPosition(CCPointZero);
    this->addChild(pMenuPause);
}
void GameScene::initModeMenu(int continueStat,int gameMode){
    CCLog("continueStat:%i,gameMode:%i",continueStat,gameMode);
    switch (gameMode) {
        case 1:
            pNewGame = CCMenuItemImage::create("Smnew_before.png", "Smnew_after.png",this,menu_selector(GameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Smcontinue_before.png", "Smcontinue_after.png","continue_before_huise.png",this,menu_selector(GameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Smsave_before.png", "Smsave_after.png",this,menu_selector(GameScene::menuBackCallBack));
            break;
        case 2:
            pNewGame = CCMenuItemImage::create("Cmnew_before.png", "Cmnew_after.png",this,menu_selector(GameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Cmcontinue_before.png", "Cmcontinue_after.png","continue_before_huise.png",this,menu_selector(GameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Cmsave_before.png", "Cmsave_after.png",this,menu_selector(GameScene::menuBackCallBack));
            break;
        case 3:
            pNewGame = CCMenuItemImage::create("Chmnew_bafore.png", "Chmnew_after.png",this,menu_selector(GameScene::menuNewGameCallBack));
            pResume = CCMenuItemImage::create("Chmcontinue_before.png", "Chmcontinue_after.png","continue_before_huise.png",this,menu_selector(GameScene::menuContinueCallBack));
            pBack = CCMenuItemImage::create("Chmsave_before.png", "Chmsave_after.png",this,menu_selector(GameScene::menuBackCallBack));
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
    pMenu->setZOrder(1000);
    this->addChild(pMenu, 10);
    pMenu->runAction(CCEaseBackOut::create(CCSequence::create(CCMoveTo::create(0.3f, ccp(0,0)),NULL)));
    
    
}

void GameScene::menuNewGameCallBack(){
    fnPlayer(CCUserDefault::sharedUserDefault()->getIntegerForKey("GameParameter"));
}
void GameScene::menuContinueCallBack(){
        pauseStat = false;
        this->setTouchEnabled(true);
    pMenu->runAction(CCEaseBackIn::create(CCSequence::create(CCMoveTo::create(0.3f, ccp(-480,0)),CCCallFuncN::create(this,callfuncN_selector(GameScene::menuDel)),NULL)));
    
}
void GameScene::menuBackCallBack(){
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
    CCDirector::sharedDirector()->replaceScene(FirstScene);

}
void GameScene::menuDel(CCObject spender){
    removeChild(pMenu);
}
void GameScene::jiafen(cocos2d::CCPoint location){
    char valueChar[128];
    sprintf(valueChar, "+%d",value);
    CCLabelTTF* valueTTF = CCLabelTTF::create(valueChar, "Arial", 30);
    valueTTF->setPosition(location);
    valueTTF->setRotation(-90);
    valueTTF->setScale(0.5);
    this->addChild(valueTTF);
    
    valueTTF->runAction(CCSequence::create(CCMoveTo::create(0.6, ccp(100,137)),CCCallFuncN::create(this, callfuncN_selector(GameScene::jiafenDone)),NULL));

}
void GameScene::jiafenDone(cocos2d::CCNode *sender){
    CCLabelTTF* _ttf = (CCLabelTTF*)sender;
    this->removeChild(_ttf);
}

void GameScene::showGameOver(){

   // char valueChar[128];
   // sprintf(valueChar, "+%d",value);
    CCLabelTTF* valueTTF = CCLabelTTF::create("Game Over", "Arial", 30);
    valueTTF->setPosition(ccp(100,160));
    valueTTF->setRotation(-90);
    valueTTF->setScale(0.2);

    this->addChild(valueTTF);
    
    CCMoveTo* move1 = CCMoveTo::create(2.0f, ccp(200, 160));
    CCScaleTo *scale1 = CCScaleTo::create(2.0, 0.5);
    //CCCallFuncN* funcN = CCCallFunc::create(this, callfunc_selector(GameScene::showGameOverDone));
    
    CCSpawn* spawn = CCSpawn::create(move1,scale1,NULL);
    //valueTTF->runAction(CCSequence::create(spawn,CCCallFuncN::create(this, callfunc_selector(GameScene::showGameOverDone)),NULL));
    valueTTF->runAction(CCSequence::create(spawn,CCCallFuncN::create(this, callfuncN_selector(GameScene::showGameOverDone)),NULL));



}
void GameScene::showGameOverDone(cocos2d::CCNode *sender){
    CCLog("GameOver");
    CCLabelTTF* valueTTF = (CCLabelTTF*)sender;
    this->removeChild(valueTTF);
    initModeMenu(0, curGameMode);
    
}

CCScene* GameScene::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    //layer->setGameParameter(GameParameter);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
  // return the scene
    return scene;
}