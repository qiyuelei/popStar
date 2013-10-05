//
//  TestIAPScene.cpp
//  popStar
//
//  Created by long shenghua on 13-9-23.
//
//

#include "TestIAPScene.h"
#import "InAppPurchaseManager.h"

InAppPurchaseManager* inAppPurchaseManage;


TestIAPScene::TestIAPScene(){}
TestIAPScene::~TestIAPScene(){}
bool TestIAPScene::init(){
    if (CCLayer::init()) {
        
      //  CCSprite* sp = CCSprite::create("Icon.png");
      //  sp->setPosition(ccp(240, 200));
      //  addChild(sp);
        //inAppPurchaseLayer = InAppPurchaseLayer::create();
        //this->addChild(inAppPurchaseLayer);
       // TestLayer* testLayer = TestLayer::create();
     //  this->addChild(testLayer,10);
            testId = 0;
        inAppPurchaseManage = [[InAppPurchaseManager alloc]init];
        //[inAppPurchaseManage loadStore];
        
        iAPDialogLayer = IAPDialogLayer::create();
        addChild(iAPDialogLayer);
        
        for (int i = 0; i<1; i++) {
            switch (i) {
                case 0:
                   // [inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx1"];
                    break;
                case 1:
                   // [inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx2"];
                    break;
                case 2:
                   // [inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx3"];
                    break;
                case 3:
                   // [inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx4"];
                    break;
                default:
                    //[inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx3"];
                    break;
            }
        }
        //[inAppPurchaseManage testLogWithstr:@"com.long.popStar.MagicPopx3"];
       // [inAppPurchaseManage testLogWithint:1];
       // [inAppPurchaseManage testSaveData];
       // [inAppPurchaseManage testLoadData];
       // [inAppPurchaseManage testgetIsbuy];
       // [inAppPurchaseManage purchaseProUpgrade];
        
        this->setTouchEnabled(true);
        return true;
    }else{
        return false;
    }



}

void TestIAPScene::ccTouchesEnded(CCSet *touches,CCEvent *event)
{
    CCLog("touch");
    //_mapLayer->initMap(4);
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = this->convertTouchToNodeSpace(touch);
    //char _productIdentifiers[128];
    //string _productIdentifiers = "com.long.popStar.MagicPopx2";
   // iAPDialogLayer->removeProduct();
    testId++;
    if (testId > 3) {
        testId = 1;
    }
    
    //loadProduct(testId);
    purchaseProduct(testId);
    //requestProduct(testId);
    //inAppPurchaseLayer->loadProduct(_productIdentifiers);
    //[inAppPurchaseManage loadStore];
   // [inAppPurchaseManage canMakePurchases];
    //[inAppPurchaseManage purchaseProUpgrade];
   //int x = [inAppPurchaseManage testgetIsbuy];
   // CCLog("x:%i",x);
    
}
void TestIAPScene::loadProduct(int productionId){
   // string productIdentifiers = "com.long.popStar.MagicPopx1";

    //1.showProduct
    iAPDialogLayer->showProduct();
    //2.requestStore
    switch (productionId) {
        case 1:
        [inAppPurchaseManage getProduct:@"com.long.popStar.MagicPopx1"];
            break;
        case 2:
            [inAppPurchaseManage getProduct:@"com.long.popStar.MagicPopx2"];
            break;
        case 3:
            [inAppPurchaseManage getProduct:@"com.long.popStar.MagicPopx3"];
            break;
        default:
            break;
    }
   // [inAppPurchaseManage getProduct:[NSString stringWithUTF8String:productIdentifiers.c_str()]];
    //3.responeStore
    this->schedule(schedule_selector(TestIAPScene::responStore));
}
void TestIAPScene::responStore(){
   // NSString* nsprice = [inAppPurchaseManage responPrice];
   // float ft = [nsprice floatValue];
    //if (ft > 0) {
       // CCLog("ok");
    //    char cprice[128];
     //   sprintf(cprice, "%0.2f",ft);
     //   iAPDialogLayer->getpriceTTF()->setString(cprice);
      //  this->unschedule(schedule_selector(TestIAPScene::responStore));
    //}else{
    //    iAPDialogLayer->getpriceTTF()->setString("Loading...");
       // CCLog("null");
    //}



}
void TestIAPScene::purchaseProduct(int productionId){
    CCLog("purchaseProduct");
    [inAppPurchaseManage purchaseProduct:productionId];
    this->schedule(schedule_selector(TestIAPScene::responPrice));
    this->schedule(schedule_selector(TestIAPScene::responPurchaseStat));
}
void TestIAPScene::responPurchaseStat(){
    int purchaseStat = [inAppPurchaseManage responPurchaseStat];
   // CCLOG("purchaseStat:%i",purchaseStat);
    if (purchaseStat>0) {
        this->unschedule(schedule_selector(TestIAPScene::responPurchaseStat));
        iAPDialogLayer->getPurchaseStatTTF()->setString("purchase success");
    }else if (purchaseStat == -1){
        this->unschedule(schedule_selector(TestIAPScene::responPurchaseStat));
        iAPDialogLayer->getPurchaseStatTTF()->setString("purchase cancle");
    }else{
        iAPDialogLayer->getPurchaseStatTTF()->setString("purchase Loading");
    }
   // CCLog("responPurchaseStat");
   // int purchaseStat = [inAppPurchaseManage responPurchaseStat];
    //CCLog("purchaseStat:%i",purchaseStat);
}
void TestIAPScene::requestProduct(int productionId){
    [inAppPurchaseManage requestProduct:productionId];
}
void TestIAPScene::responPrice(){
    float productPrice = [inAppPurchaseManage responPrice];
  //  CCLOG("productPrice:%0.2f",productPrice);
    if (productPrice > 0) {
    this->unschedule(schedule_selector(TestIAPScene::responPrice));
        char price[128];
        sprintf(price, "%0.2f",productPrice);
        iAPDialogLayer->getpriceTTF()->setString(price);
    }else{
        iAPDialogLayer->getpriceTTF()->setString("priceLoading");
    }
}
CCScene* TestIAPScene::scene(){
    CCScene* scene = CCScene::create();
    TestIAPScene* layer = TestIAPScene::create();
    scene->addChild(layer);
    return scene;


}