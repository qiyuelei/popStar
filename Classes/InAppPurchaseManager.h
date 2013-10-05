//
//  InAppPurchaseManager.h
//  popStar
//
//  Created by long shenghua on 13-9-25.
//
//

#import <Foundation/Foundation.h>

#import <StoreKit/StoreKit.h>

#define kInAppPurchaseManagerProductsFetchedNotification @"kInAppPurchaseManagerProductsFetchedNotification"
#define kInAppPurchaseManagerTransactionFailedNotification @"kInAppPurchaseManagerTransactionFailedNotification"
#define kInAppPurchaseManagerTransactionSucceededNotification @"kInAppPurchaseManagerTransactionSucceededNotification"

@interface InAppPurchaseManager : NSObject <SKProductsRequestDelegate>
{
    SKProduct *proUpgradeProduct;
    SKProductsRequest *productsRequest;
    float productPrice;
    int purchaseStat;
    int _productID;
    
    NSSet *productIdentifiers;
    NSString* kInAppPurchaseProUpgradeProductId;
    
    NSUserDefaults* SaveDefaults;
}
// public methods
- (void)loadStore;
- (BOOL)canMakePurchases;
- (void)purchaseProUpgrade;

// loadProduct
- (void)requestProduct:(int)productID;
- (float)responPrice;

// purchaseProduct;
- (void)purchaseProduct:(int)productID;
- (int)responPurchaseStat;

//viewresult
-(void)showPurchaseSecess;
@end
