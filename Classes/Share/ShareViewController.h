//
//  ShareViewController.h
//  shareCocos2dx
//
//  Created by long shenghua on 13-9-26.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ShareViewController : UIViewController
{
    int newRecord;
}
-(void)shareMothed;
- (void)shareToSinaWeiboClickHandler:(int)bestScore;
- (void)shareToWeixinClickHandler;
- (void)shareToFacebookClickHandler:(int)bestScore;
-(void)loginSina;
- (void)initializePlat;


@end
