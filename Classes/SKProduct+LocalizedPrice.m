//
//  SKProduct+LocalizedPrice.m
//  test_cocos2d
//
//  Created by long shenghua on 13-9-23.
//  Copyright (c) 2013年 long shenghua. All rights reserved.
//

#import "SKProduct+LocalizedPrice.h"

@implementation SKProduct (LocalizedPrice)

- (NSString *)localizedPrice
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:self.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:self.price];
    NSLog(@"price %@",self.price);
    [numberFormatter release];
    return formattedString;
}

@end