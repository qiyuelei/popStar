//
//  ShareViewController.m
//  shareCocos2dx
//
//  Created by long shenghua on 13-9-26.
//
//


#import "ShareViewController.h"
#import <ShareSDK/ShareSDK.h>
#import "WXApi.h"

#define BUNDLE_NAME @"Resource"

#define IMAGE_NAME @"Icon"
#define IMAGE_EXT @"png"

#define CONTENT @"ShareSDK不仅集成简单、支持如QQ好友、微信、新浪微博、腾讯微博等所有社交平台，而且还有强大的统计分析管理后台，实时了解用户、信息流、回流率、传播效应等数据，详情见官网http://sharesdk.cn @ShareSDK"
#define SHARE_URL @"http://www.sharesdk.cn"


@interface ShareViewController ()

@end

@implementation ShareViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
-(void)loginSina
{
    [ShareSDK getUserInfoWithType:ShareTypeSinaWeibo authOptions :nil
                           result:^(BOOL result, id<ISSUserInfo> userInfo, id<ICMErrorInfo> error) { if (result)
                           {
                               NSLog(@"%@",userInfo.nickname);
                           }
                           else
                           {
                               NSLog(@"失败");
                           }
                           }];
    
}

-(void)shareMothed
{
    printf("fffbbbbbbbbbbb\n");
}

- (void)shareToFacebookClickHandler:(int)bestScore
{
   // NSLog(@"bestScore:%i",bestScore);
    //  [ShareSDK registerApp:@"977ce81d6a3"];
    [self initializePlat];
    NSString *astring = [[NSString alloc]initWithString:[NSString stringWithFormat:@"I'm playing PopStar Night，New record：%i， #PopStar Night#:https://itunes.apple.com/us/app/popstar-night/id712009916?ls=1&mt=8",bestScore]];
    //NSLog(@"astring:%@",astring);
    
    
    //创建分享内容
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:IMAGE_NAME ofType:IMAGE_EXT];
    id<ISSContent> publishContent = [ShareSDK content:astring
                                       defaultContent:@""
                                                image:[ShareSDK imageWithPath:imagePath]
                                                title:@"PopStar Night"
                                                  url:@"https://itunes.apple.com/us/app/popstar-night/id712009916?ls=1&mt=8"
                                          description:nil
                                            mediaType:SSPublishContentMediaTypeNews];
    
    [astring release];
    //创建弹出菜单容器
    id<ISSContainer> container = [ShareSDK container];
    [container setIPadContainerWithView:nil arrowDirect:UIPopoverArrowDirectionUp];
    
    id<ISSAuthOptions> authOptions = [ShareSDK authOptionsWithAutoAuth:YES
                                                         allowCallback:YES
                                                         authViewStyle:SSAuthViewStyleFullScreenPopup
                                                          viewDelegate:nil
                                               authManagerViewDelegate:nil];
    //在授权页面中添加关注官方微博
    [authOptions setFollowAccounts:[NSDictionary dictionaryWithObjectsAndKeys:
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeSinaWeibo),
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeTencentWeibo),
                                    nil]];
    
    
    NSArray* shareList = [ShareSDK getShareListWithType:
                                                        ShareTypeFacebook,
                                                        ShareTypeTwitter,
                                                        ShareTypeSinaWeibo,
                                                        ShareTypeTencentWeibo,
                                                        ShareTypeQQSpace,
                                                        ShareTypeKaixin,
                                                        ShareTypeLinkedIn,
                                                        ShareTypeRenren,
                                                        nil];
    
    
    //显示分享菜单
    [ShareSDK showShareViewWithType:ShareTypeFacebook
                          container:container
                            content:publishContent
                      statusBarTips:YES
                        authOptions:authOptions
                       shareOptions:[ShareSDK defaultShareOptionsWithTitle:nil
                                                           //oneKeyShareList:[NSArray defaultOneKeyShareList]
                                                           oneKeyShareList:shareList
                                                            qqButtonHidden:Nil
                                                     wxSessionButtonHidden:NO
                                                    wxTimelineButtonHidden:NO
                                                      showKeyboardOnAppear:NO
                                                         shareViewDelegate:nil
                                                       friendsViewDelegate:nil
                                                     picViewerViewDelegate:nil]
                             result:^(ShareType type, SSPublishContentState state, id<ISSStatusInfo> statusInfo, id<ICMErrorInfo> error, BOOL end) {
                                 if (state == SSPublishContentStateSuccess)
                                 {
                                     NSLog(@"发表成功");
                                 }
                                 else if (state == SSPublishContentStateFail)
                                 {
                                     NSLog(@"发布失败!error code == %d, error code == %@", [error errorCode], [error errorDescription]);
                                 }
                             }];
    
    
    
}


- (void)shareToWeixinClickHandler
{
   // [ShareSDK registerApp:@"a189d093a62"];
    [self initializePlat];
    
    
    //创建分享内容
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:IMAGE_NAME ofType:IMAGE_EXT];
    //NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"Icon" ofType:@"png"];
    id<ISSContent> publishContent = [ShareSDK content:@"我正在玩这款PopStar Night，新记录：11717"
                                       defaultContent:@""
                                                image:[ShareSDK imageWithPath:imagePath]
                                                title:@"PopStar Night"
                                                  url:@"https://itunes.apple.com/us/app/popstar-night/id712009916?ls=1&mt=8"
                                          description:nil
                                            mediaType:SSPublishContentMediaTypeNews];
                                               // mediaType:SSPublishContentMediaTypeText];
    
    //创建弹出菜单容器
    id<ISSContainer> container = [ShareSDK container];
    [container setIPadContainerWithView:nil arrowDirect:UIPopoverArrowDirectionUp];
    
    id<ISSAuthOptions> authOptions = [ShareSDK authOptionsWithAutoAuth:YES
                                                         allowCallback:YES
                                                         authViewStyle:SSAuthViewStyleFullScreenPopup
                                                          viewDelegate:nil
                                               authManagerViewDelegate:nil];
    //在授权页面中添加关注官方微博
    [authOptions setFollowAccounts:[NSDictionary dictionaryWithObjectsAndKeys:
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeSinaWeibo),
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeTencentWeibo),
                                    nil]];
    
    //显示分享菜单
    [ShareSDK showShareViewWithType:ShareTypeWeixiTimeline
                          container:container
                            content:publishContent
                      statusBarTips:YES
                        authOptions:authOptions
                       shareOptions:[ShareSDK defaultShareOptionsWithTitle:nil
                                                           oneKeyShareList:[NSArray defaultOneKeyShareList]
                                                            qqButtonHidden:Nil
                                                     wxSessionButtonHidden:NO
                                                    wxTimelineButtonHidden:NO
                                                      showKeyboardOnAppear:NO
                                                         shareViewDelegate:nil
                                                       friendsViewDelegate:nil
                                                     picViewerViewDelegate:nil]
                             result:^(ShareType type, SSPublishContentState state, id<ISSStatusInfo> statusInfo, id<ICMErrorInfo> error, BOOL end) {
                                 if (state == SSPublishContentStateSuccess)
                                 {
                                     NSLog(@"发表成功");
                                 }
                                 else if (state == SSPublishContentStateFail)
                                 {
                                     NSLog(@"发布失败!error code == %d, error code == %@", [error errorCode], [error errorDescription]);
                                 }
                             }];
 
    
    
}
- (void)shareToSinaWeiboClickHandler:(int)bestScore
{
     //   NSLog(@"bestScore:%i",bestScore);
  //  [ShareSDK registerApp:@"977ce81d6a3"];
    [self initializePlat];
    NSString *astring = [[NSString alloc]initWithString:[NSString stringWithFormat:@"I'm playing PopStar Night，New record：%i， #PopStar Night#:https://itunes.apple.com/us/app/popstar-night/id712009916?ls=1&mt=8",bestScore]];
    //NSLog(@"astring:%@",astring);

    
    //创建分享内容
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:IMAGE_NAME ofType:IMAGE_EXT];
    id<ISSContent> publishContent = [ShareSDK content:astring
                                       defaultContent:@""
                                                image:[ShareSDK imageWithPath:imagePath]
                                                title:@"PopStar Night"
                                                  url:@"https://itunes.apple.com/us/app/popstar-night/id712009916?ls=1&mt=8"
                                          description:nil
                                            mediaType:SSPublishContentMediaTypeNews];
    
        [astring release];
    //创建弹出菜单容器
    id<ISSContainer> container = [ShareSDK container];
    [container setIPadContainerWithView:nil arrowDirect:UIPopoverArrowDirectionUp];
    
    id<ISSAuthOptions> authOptions = [ShareSDK authOptionsWithAutoAuth:YES
                                                         allowCallback:YES
                                                         authViewStyle:SSAuthViewStyleFullScreenPopup
                                                          viewDelegate:nil
                                               authManagerViewDelegate:nil];
    //在授权页面中添加关注官方微博
    [authOptions setFollowAccounts:[NSDictionary dictionaryWithObjectsAndKeys:
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeSinaWeibo),
                                    [ShareSDK userFieldWithType:SSUserFieldTypeName value:@"ShareSDK"],
                                    SHARE_TYPE_NUMBER(ShareTypeTencentWeibo),
                                    nil]];
    
    //显示分享菜单
    [ShareSDK showShareViewWithType:ShareTypeSinaWeibo
                          container:container
                            content:publishContent
                      statusBarTips:YES
                        authOptions:authOptions
                       shareOptions:[ShareSDK defaultShareOptionsWithTitle:nil
                                                           oneKeyShareList:[NSArray defaultOneKeyShareList]
                                                            qqButtonHidden:Nil
                                                     wxSessionButtonHidden:NO
                                                    wxTimelineButtonHidden:NO
                                                      showKeyboardOnAppear:NO
                                                         shareViewDelegate:nil
                                                       friendsViewDelegate:nil
                                                     picViewerViewDelegate:nil]
                             result:^(ShareType type, SSPublishContentState state, id<ISSStatusInfo> statusInfo, id<ICMErrorInfo> error, BOOL end) {
                                 if (state == SSPublishContentStateSuccess)
                                 {
                                     NSLog(@"发表成功");
                                 }
                                 else if (state == SSPublishContentStateFail)
                                 {
                                     NSLog(@"发布失败!error code == %d, error code == %@", [error errorCode], [error errorDescription]);
                                 }
                             }];
    
  }


- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initializePlat
{
    [ShareSDK registerApp:@"a189d093a62"];
    //[self initializePlat];
    
    //添加微信应用  //long
    [ShareSDK connectWeChatWithAppId:@"wx5c86111de2377dd8"
                           wechatCls:[WXApi class]];
    
    //添加新浪微博应用
    [ShareSDK connectSinaWeiboWithAppKey:@"3201194191"
                               appSecret:@"0334252914651e8f76bad63337b3b78f"
                             redirectUri:@"http://appgo.cn"];
    
    //添加腾讯微博应用
    [ShareSDK connectTencentWeiboWithAppKey:@"801307650"
                                  appSecret:@"ae36f4ee3946e1cbb98d6965b0b2ff5c"
                                redirectUri:@"http://www.sharesdk.cn"];
    
    //添加QQ空间应用
    [ShareSDK connectQZoneWithAppKey:@"100371282"
                           appSecret:@"aed9b0303e3ed1e27bae87c33761161d"];
    
    //添加网易微博应用
    [ShareSDK connect163WeiboWithAppKey:@"T5EI7BXe13vfyDuy"
                              appSecret:@"gZxwyNOvjFYpxwwlnuizHRRtBRZ2lV1j"
                            redirectUri:@"http://www.shareSDK.cn"];
    
    //添加搜狐微博应用
    [ShareSDK connectSohuWeiboWithConsumerKey:@"SAfmTG1blxZY3HztESWx"
                               consumerSecret:@"yfTZf)!rVwh*3dqQuVJVsUL37!F)!yS9S!Orcsij"
                                  redirectUri:@"http://www.sharesdk.cn"];
    
    //添加豆瓣应用
    [ShareSDK connectDoubanWithAppKey:@"07d08fbfc1210e931771af3f43632bb9"
                            appSecret:@"e32896161e72be91"
                          redirectUri:@"http://dev.kumoway.com/braininference/infos.php"];
    
    //添加人人网应用
    [ShareSDK connectRenRenWithAppKey:@"fc5b8aed373c4c27a05b712acba0f8c3"
                            appSecret:@"f29df781abdd4f49beca5a2194676ca4"];
    
    //添加开心网应用
    [ShareSDK connectKaiXinWithAppKey:@"358443394194887cee81ff5890870c7c"
                            appSecret:@"da32179d859c016169f66d90b6db2a23"
                          redirectUri:@"http://www.sharesdk.cn/"];
    
    //添加Instapaper应用
    [ShareSDK connectInstapaperWithAppKey:@"4rDJORmcOcSAZL1YpqGHRI605xUvrLbOhkJ07yO0wWrYrc61FA"
                                appSecret:@"GNr1GespOQbrm8nvd7rlUsyRQsIo3boIbMguAl9gfpdL0aKZWe"];
    
    //添加有道云笔记应用
    [ShareSDK connectYouDaoNoteWithConsumerKey:@"dcde25dca105bcc36884ed4534dab940"
                                consumerSecret:@"d98217b4020e7f1874263795f44838fe"
                                   redirectUri:@"http://www.sharesdk.cn/"];
    
    //添加Facebook应用
    [ShareSDK connectFacebookWithAppKey:@"107704292745179"
                              appSecret:@"38053202e1a5fe26c80c753071f0b573"];
    
    //添加Twitter应用
    [ShareSDK connectTwitterWithConsumerKey:@"mnTGqtXk0TYMXYTN7qUxg"
                             consumerSecret:@"ROkFqr8c3m1HXqS3rm3TJ0WkAJuwBOSaWhPbZ9Ojuc"
                                redirectUri:@"http://www.sharesdk.cn"];
    
    //添加搜狐随身看应用
    [ShareSDK connectSohuKanWithAppKey:@"e16680a815134504b746c86e08a19db0"
                             appSecret:@"b8eec53707c3976efc91614dd16ef81c"
                           redirectUri:@"http://sharesdk.cn"];
    
    //添加Pocket应用
    [ShareSDK connectPocketWithConsumerKey:@"11496-de7c8c5eb25b2c9fcdc2b627"
                               redirectUri:@"pocketapp1234"];
    
    //添加印象笔记应用
    [ShareSDK connectEvernoteWithType:SSEverNoteTypeSandbox
                          consumerKey:@"sharesdk-7807"
                       consumerSecret:@"d05bf86993836004"];
    
    //添加LinkedIn应用
    [ShareSDK connectLinkedInWithApiKey:@"ejo5ibkye3vo"
                              secretKey:@"cC7B2jpxITqPLZ5M"
                            redirectUri:@"http://sharesdk.cn"];
}

@end