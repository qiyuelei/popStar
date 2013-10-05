//
//  SKProduct+LocalizedPrice.h
//  test_cocos2d
//
//  Created by long shenghua on 13-9-23.
//  Copyright (c) 2013年 long shenghua. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface SKProduct (LocalizedPrice)

@property (nonatomic, readonly) NSString *localizedPrice;

@end
