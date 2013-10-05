//
//  ChannelClass.cpp
//  shareCocos2dx
//
//  Created by long shenghua on 13-9-26.
//
//

#include "ChannelClass.h"
#include "ShareViewController.h"

void shareMothed(int bestScore)
{
    ShareViewController* share = [[ShareViewController alloc]init];
    printf("ffff\n");
    [share shareToSinaWeiboClickHandler:bestScore];
    //[share shareToWeixinClickHandler];
    //[share shareToFacebookClickHandler];
}
void shareFacebookMothed(int bestScore){
    ShareViewController* share = [[ShareViewController alloc]init];
    [share shareToFacebookClickHandler:bestScore];
        //printf("facebook\n");

}

void ChannelClass::channel()
{
    shareMothed(1009);
}
void ChannelClass::Sharefacebook(int bestScore){
    shareFacebookMothed(bestScore);
   // shareMothed(bestScore);
}
