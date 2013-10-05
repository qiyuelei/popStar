//
//  InAppPurchaseManager.m
//  test_cocos2d
//
//  Created by long shenghua on 13-9-23.
//  Copyright (c) 2013年 long shenghua. All rights reserved.
//

#import "InAppPurchaseManager_old.h"
#define kInAppPurchaseProUpgradeProductId @"com.long.popStar.MagicPopx3"

@implementation InAppPurchaseManager

- (void)requestProUpgradeProductData
{
    NSLog(@"requestProUpgradeProductData");
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.long.popStar.MagicPopx1" ];
    productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    
    // we will release the request object in the delegate callback
}

#pragma mark -
#pragma mark SKProductsRequestDelegate methods

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	
    NSArray *products = response.products;
    proUpgradeProduct = [products count] == 1 ? [[products firstObject] retain] : nil;
    if (proUpgradeProduct)
    {
       // NSLog(@"Product title: %@" , proUpgradeProduct.localizedTitle);
       // NSLog(@"Product description: %@" , proUpgradeProduct.localizedDescription);
       // NSLog(@"Product price: %@" , proUpgradeProduct.price);
        NSLog(@"Product id: %@" , proUpgradeProduct.productIdentifier);
       // NSLog(@"number:%@",[self localizedPrice:proUpgradeProduct]);
        
       // SaveDefaults = [NSUserDefaults standardUserDefaults];
        [SaveDefaults setValue:proUpgradeProduct.price forKey:@"price"];
    }
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    
    // finally release the reqest we alloc/init’ed in requestProUpgradeProductData
    [productsRequest release];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerProductsFetchedNotification object:self userInfo:nil];
}


#pragma -
#pragma Public methods
- (void)loadStore
{
  //  NSLog(@"loadStore");
    // restarts any purchases if they were interrupted last time the app was open
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    // get the product description (defined in early sections)
    [self requestProUpgradeProductData];
}

//
// call this before making a purchase
//
- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}

//
// kick off the upgrade transaction
//
- (void)purchaseProUpgrade
{
    NSLog(@"app:%@",kInAppPurchaseProUpgradeProductId);
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:kInAppPurchaseProUpgradeProductId];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

#pragma -
#pragma Purchase helpers

//
// saves a record of the transaction by storing the receipt to disk
//
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
    if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseProUpgradeProductId])
    {
        // save the transaction receipt to disk
        [[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:@"proUpgradeTransactionReceipt" ];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

//
// enable pro features
//
- (void)provideContent:(NSString *)productId
{
    NSLog(@"provideContent");
    if ([productId isEqualToString:kInAppPurchaseProUpgradeProductId])
    {
        // enable the pro features
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"isProUpgradePurchased" ];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

//
// removes the transaction from the queue and posts a notification with the transaction result
//
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    NSLog(@"finishTransaction");
    // remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:transaction, @"transaction" , nil];
    if (wasSuccessful)
    {
        purchaseStat = 1;
        NSLog(@"wasSuccessful");
        // send out a notification that we’ve finished the transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionSucceededNotification object:self userInfo:userInfo];
    }
    else
    {
        purchaseStat = 2;
        NSLog(@"purchasefailed");
        // send out a notification for the failed transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionFailedNotification object:self userInfo:userInfo];
    }
}

//
// called when the transaction was successful
//
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"completeTransaction");
    [self recordTransaction:transaction];
    [self provideContent:transaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has been restored and and successfully completed
//
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"restoreTransaction");
    [self recordTransaction:transaction.originalTransaction];
    [self provideContent:transaction.originalTransaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has failed
//
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"failedTransaction");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        // error!
        [self finishTransaction:transaction wasSuccessful:NO];
    }
    else
    {
        // this is fine, the user just cancelled, so don’t notify
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
}

#pragma mark -
#pragma mark SKPaymentTransactionObserver methods

//
// called when the transaction status is updated
//
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    NSLog(@"paymentQueue");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
            default:
                break;
        }
    }
}

//
//test
//
-(void)getProduct:(NSString *)_str{
    SaveDefaults = [NSUserDefaults standardUserDefaults];
    [SaveDefaults setValue:@"" forKey:@"price"];
    str = [NSString stringWithFormat:@"%@",_str];
  //  NSLog(@"test:%@",str);
    productIdentifiers = [NSSet setWithObject:str];
    [self loadStore];
   // NSSet *productIdentifiers = [NSSet setWithObject:str ];
   // productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
  //  productsRequest.delegate = self;
  //  [productsRequest start];
    
    // we will release the request object in the delegate callback
}
//
//
//
-(void)testLogWithint:(int)_int{
   // str = [NSString stringWithFormat:@"%d",_int];
     // NSLog(@"inttest:%@",str);

    switch (_int) {
        case 0:
             NSLog(@"%d",_int);
            break;
        case 1:
           NSLog(@"%d",_int);
            [self testLogWithstr:@"com.long.popStar.MagicPopx1"];
            break;
        case 2:
            NSLog(@"%d",_int);
            [self testLogWithstr:@"com.long.popStar.MagicPopx2"];
            break;
        default:
            NSLog(@"%d",_int);
            break;
    }
}
//
//
//
-(void)testSaveData{
    NSLog(@"testSaveData");
    NSString * str = @"abc";
    NSString* astr = @"efg";

    NSArray* Array = [NSArray arrayWithObjects:str,astr,Nil];
    
    //save
    SaveDefaults = [NSUserDefaults standardUserDefaults];
    [SaveDefaults setObject:Array forKey:@"SaveKey"];
    
    str = @"a";
    astr = @"'";
    
   // NSInteger* isbuy = 2;
   // NSUserDefaults* SaveBuyStat = [NSUserDefaults standardUserDefaults];
    //[SaveBuyStat setInteger:isbuy forKey:@"isbuyStat"];

}
-(int)testgetIsbuy{
    NSInteger* isbuy;
    NSUserDefaults* SaveBuyStat = [NSUserDefaults standardUserDefaults];
    isbuy = [SaveBuyStat integerForKey:@"isbuyStat"];
    int x = isbuy;
            NSLog(@"%d",x);
    return x;
}
-(void)testLoadData{
   // NSLog(@"testLoadData");
    NSArray* Array;
    NSUserDefaults* SaveDefaults = [NSUserDefaults standardUserDefaults];
    Array = [SaveDefaults objectForKey:@"SaveKey"];
    NSString * str;
    NSString* astr;
    str = [Array objectAtIndex:0];
    astr = [Array objectAtIndex:1];
   // NSLog(@"str:%@",str);
   // NSLog(@"astr:%@",astr);
    
}
//
//
//
- (NSString *)localizedPrice:(SKProduct *)proUpgradeProduct
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:proUpgradeProduct.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:proUpgradeProduct.price];
    NSLog(@"price %@",proUpgradeProduct.price);
    [numberFormatter release];
    return formattedString;
}
//
//
//
-(NSString *)responPrice{
   return [SaveDefaults valueForKey:@"price"];
}

//
//purchase Product
//
-(void)purchaseProduct:(NSString *)_str{
    
    purchaseStat = 0;
    
   // SaveDefaults = [NSUserDefaults standardUserDefaults];
   // [SaveDefaults setValue:@"" forKey:@"purchaseStat"];
   // BOOL isCanPurchase = [self canMakePurchases];
    if ([self canMakePurchases] == true) {
        NSLog(@"can purchase");
        //kInAppPurchaseProUpgradeProductId = _str;
        [self purchaseProUpgrade];
    }else{
        NSLog(@"no purchase");
    }

}
-(int)responPurchaseStat{
    return purchaseStat;
}
@end