//
//  IAPDialogLayer.cpp
//  popStar
//
//  Created by long shenghua on 13-9-25.
//
//

#include "IAPDialogLayer.h"
IAPDialogLayer::IAPDialogLayer(){}
IAPDialogLayer::~IAPDialogLayer(){}
bool IAPDialogLayer::init(){
    if (CCLayer::init()) {
        showProduct();
        showPurchaseStat();
        
        return true;
    }else{
        return false;
    }


}
void IAPDialogLayer::showProduct(){
    CCLog("showProduct");
    priceTTF = CCLabelTTF::create("price", "Arial", 32);
    priceTTF->setPosition(ccp(220, 220));
    addChild(priceTTF);
}
CCLabelTTF* IAPDialogLayer::getpriceTTF(){
    return priceTTF;
}
void IAPDialogLayer::removeProduct(){
    this->removeChild(priceTTF);
}

void IAPDialogLayer::showPurchaseStat(){
    purchaseTTF = CCLabelTTF::create("purchase", "Arial", 32);
    purchaseTTF->setPosition(ccp(200, 100));
    addChild(purchaseTTF);
}
CCLabelTTF* IAPDialogLayer::getPurchaseStatTTF(){
    return purchaseTTF;
}
void IAPDialogLayer::removePurchaseStat(){
    this->removeChild(purchaseTTF);
}