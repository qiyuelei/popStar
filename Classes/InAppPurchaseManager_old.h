//
//  InAppPurchaseManager.h
//  test_cocos2d
//
//  Created by long shenghua on 13-9-23.
//  Copyright (c) 2013年 long shenghua. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <storekit/SKPaymentTransaction.h>
#import <SKProduct+LocalizedPrice.h>

#define kInAppPurchaseManagerProductsFetchedNotification @"kInAppPurchaseManagerProductsFetchedNotification"
#define kInAppPurchaseManagerTransactionFailedNotification @"kInAppPurchaseManagerTransactionFailedNotification"
#define kInAppPurchaseManagerTransactionSucceededNotification @"kInAppPurchaseManagerTransactionSucceededNotification"


NSString* str;
int newId;
@interface InAppPurchaseManager : NSObject <SKProductsRequestDelegate>
{
    SKProduct *proUpgradeProduct;
    SKProductsRequest *productsRequest;
    NSSet *productIdentifiers;
    NSUserDefaults* SaveDefaults;
    
    int purchaseStat;
   // NSSet *kInAppPurchaseProUpgradeProductId;
    //NSString *kInAppPurchaseProUpgradeProductId;
}

// public methods
- (void)loadStore;
- (BOOL)canMakePurchases;
- (void)purchaseProUpgrade;
- (void)getProduct:(NSString*)_str;
- (void)testLogWithint:(int)_int;
- (void)testSaveData;
- (void)testLoadData;
- (int)testgetIsbuy;
- (NSString *)localizedPrice:(SKProduct*)proUpgradeProduct;
- (NSString *)responPrice;

- (void)purchaseProduct:(NSString*)_str;
- (int)responPurchaseStat;
@end
