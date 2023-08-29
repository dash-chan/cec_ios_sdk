//
//  ChatClient.h
//  helpdesk_sdk
//
//  Created by ZXG on 16/3/29.
//  Copyright © 2016年 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "HDMessage.h"
#import "HDMessage+Content.h"
#import "HDMessage+Menu.h"
#import "HDChatManager.h"
#import "HDOptions.h"
#import "HDClientDelegate.h"
#import "HDLeaveMsgManager.h"
#import "HDConversation.h"
#import "HDError.h"
#import "HDPushOptions.h"
#import "HDjudgeTextMessageSubType.h"
#import "HDMessageHelper.h"
#import "HDPushManager.h"
/*
 *  上报类型用户状态
 */
typedef NS_ENUM (NSInteger, HDUserStatus) {
    HDUserStatusOnLine     = 0,    /** 在线   */
    HDUserStatusOffLine,           /** 离线  */
};
// resued concept
@interface HDClient :NSObject<HDClientDelegate>
/*!
 *  \~chinese
 *  当前登录账号
 *
 *  \~english
 *  Current logined account
 */
@property (nonatomic, strong, readonly) NSString *currentUsername;

/**
 当前SDK 版本
 */
@property (nonatomic, copy) NSString *sdkVersion;

/**
 当前IM版本号
 */
@property (nonatomic, copy) NSString *imSdkVersion;

/**
 开启等待提示
 */
@property (nonatomic, assign) BOOL enableVisitorWaitCount;

/**
 是否 访客加速 默认 加速 yes
 */
@property (nonatomic, assign) BOOL enableVisitorAccelerator;


/*!
 *  \~chinese
 *  推送设置
 *
 *  \~english
 *  Apple Push Notification Service setting
 */
@property (nonatomic, strong, readonly) HDPushOptions *hdPushOptions;

/*!
 *  \~chinese
 *  聊天消息管理模块
 *
 *  \~english
 *  Chat module
 */
@property (nonatomic, strong, readonly) HDChatManager *chatManager;

/*!
 *  \~chinese
 *  推送管理模块
 *
 *  \~english
 *  Chat module
 */
@property (nonatomic, strong, readonly) HDPushManager *pushManager;

/*!
 *  \~chinese
 *  用户是否已登录
 *
 *  \~english
 *  Whether user has logged in
 */
@property (nonatomic, readonly) BOOL isLoggedInBefore;


/*!
 *  \~chinese
 *  获取SDK实例
 *
 *  \~english
 *  Get SDK single instance
 */
+ (instancetype)sharedClient;

#pragma mark - Delegate

/*!
 *  \~chinese
 *  添加回调代理
 *
 *  @param aDelegate  要添加的代理
 *  @param aQueue     执行代理方法的队列
 *
 *  \~english
 *  Add delegate
 *
 *  @param aDelegate  Delegate
 *  @param aQueue     The queue of call delegate method
 */
- (void)addDelegate:(id<HDClientDelegate>)aDelegate
      delegateQueue:(dispatch_queue_t)aQueue;

/*!
 *  \~chinese
 *  移除回调代理
 *
 *  @param aDelegate  要移除的代理
 *
 *  \~english
 *  Remove delegate
 *
 *  @param aDelegate  Delegate
 */
- (void)removeDelegate:(id<HDClientDelegate>)aDelegate;

#pragma mark - Initialize SDK

- (void)releaseResource;

/*!
 *  \~chinese
 *  初始化sdk
 *
 *  @param aOptions  SDK配置项
 *
 *  @result 错误信息
 *
 *  \~english
 *  Initialization sdk
 *
 *  @param aOptions  SDK setting options
 *
 *  @result Error
 */
- (HDError *)initializeSDKWithOptions:(HDOptions *)aOptions;

/*!
 *  \~chinese
 *  初始化sdk im 和客服 共存 需要 使用im 初始化独有参数时 使用
 *
 *  @param aOptions  SDK配置项
 *
 *  @result 错误信息
 *
 *  \~english
 *  Initialization sdk
 *
 *  @param aOptions  SDK setting options
 *
 *  @result Error
 */
- (HDError *)initializeSDKWithOptions:(HDOptions *)aOptions withToImoptions:(EMOptions *)imoptios;

/*!
  \~chinese
 *  用户是否已登录
 同步方法，会阻塞当前线程.
 *  \~english
 *  Whether user has logged in
 */
- (BOOL)getIsLoggedInBefore;
/*!
  \~chinese
 *  用户是否已登录
    异步方法
    @param aCompletionBlock   是否已登录
 *  \~english
 *  Whether user has logged in
 */
- (void)getIsLoggedInBeforeCompletion:(void (^)(BOOL isLoggedInBefore))aCompletionBlock;
#pragma mark - Register

/*!
 *  \~chinese
 *  注册用户
 *
 *  同步方法，会阻塞当前线程. 不推荐使用，建议后台通过REST注册
 *
 *  @param aUsername  用户名
 *  @param aPassword  密码
 *
 *  @result 错误信息
 *
 *  \~english
 *  Register a new user
 *
 *  Synchronization method will block the current thread. It is not recommended, advise to register new user through REST API
 *
 *  @param aUsername  Username
 *  @param aPassword  Password
 *
 *  @result Error
 */
- (HDError *)registerWithUsername:(NSString *)aUsername
                         password:(NSString *)aPassword;

/*!
 *  \~chinese
 *  注册用户
 *
 *  不推荐使用，建议后台通过REST注册
 *
 *  @param aUsername        用户名
 *  @param aPassword        密码
 *  @param aCompletionBlock 完成的回调
 *
 *  \~english
 *  Register a new IM user
 *
 *  To ensure good reliability, registering new IM user via REST API from developer backend is highly recommended
 *
 *  @param aUsername        Username
 *  @param aPassword        Password
 *  @param aCompletionBlock The callback of completion block
 *
 */
- (void)registerWithUsername:(NSString *)aUsername
                    password:(NSString *)aPassword
                  completion:(void (^)(NSString *aUsername, HDError *aError))aCompletionBlock;

#pragma mark - Login

/*!
 *  \~chinese
 *  登录
 *
 *  同步方法，会阻塞当前线程
 *
 *  @param aUsername  用户名
 *  @param aPassword  密码
 *
 *  @result 错误信息
 *
 *  \~english
 *  Login
 *
 *  Synchronization method will block the current thread
 *
 *  @param aUsername  Username
 *  @param aPassword  Password
 *
 *  @result Error
 */
- (HDError *)loginWithUsername:(NSString *)aUsername
                      password:(NSString *)aPassword;


- (void)loginWithUsername:(NSString *)aUsername
                 password:(NSString *)aPassword
               completion:(void (^)(HDError *error))aCompletionBlock;

/*!
 *  \~chinese
 *  登录
 *
 *  同步方法，会阻塞当前线程
 *
 *  @param aUsername  用户名
 *  @param aToken  token
 *
 *  @result 错误信息
 *
 *  \~english
 *  Login
 *
 *  Synchronization method will block the current thread
 *
 *  @param aUsername  Username
 *  @param aToken  token
 *
 *  @result Error
 */
- (HDError *)loginWithUsername:(NSString *)aUsername
                        token:(NSString *)aToken;

/**
 *  \~chinese
 *  用户使用 token 登录。该方法支持自动登录。
 *
 *  异步方法。
 *
 *  @param aUsername        用户名，长度不超过 64 个字符。请确保你对该参数设值。支持的字符包括英文字母（a-z），数字（0-9），下划线（_），英文横线（-），英文句号（.）。该参数不区分大小写，大写字母会被自动转为小写字母。如果使用正则表达式设置该参数，则可以将表达式写为：^[a-zA-Z0-9_-]+$。
 *  @param aToken           The token。
 *  @param aCompletionBlock 该方法完成调用的回调。如果该方法调用失败，会包含调用失败的原因。
 *
 *  \~english
 *  A user logs in to the chat server with a token. This method support automatic login.
 *
 *  This is an asynchronous method.
 *
 *  @param aUsername        The username. The maximum length is 64 characters. Ensure that you set this parameter. Supported characters include the 26 English letters (a-z), the ten numbers (0-9), the underscore (_), the hyphen (-), and the English period (.). This parameter is case insensitive, and upper-case letters are automatically changed to low-case ones. If you want to set this parameter as a regular expression, set it as ^[a-zA-Z0-9_-]+$.
 *  @param aToken           The token for logging in to the chat server.
 *  @param aCompletionBlock The completion block, which contains the username and the error message if the method fails.
 *
 */
- (void)loginWithUsername:(NSString *_Nonnull)aUsername
                    token:(NSString *_Nonnull)aToken
               completion:(void (^_Nullable)(NSString * _Nonnull aUsername, HDError *_Nullable aError))aCompletionBlock;
#pragma makr - Logout

/*!
 *  \~chinese
 *  退出
 *
 *  同步方法，会阻塞当前线程
 *
 *  @param bIsUnbindDeviceToken 是否解除device token的绑定，解除绑定后设备不会再收到消息推送
 *         如果传入YES, 解除绑定失败，将返回error
 *
 *  @result 错误信息
 *
 *  \~english
 *  Logout
 *
 *  Synchronization method will block the current thread
 *
 *  @param bIsUnbindDeviceToken Whether unbind device token, device will don't receive message push after unbind token, if input YES, unbind failed will return error
 *
 *  @result Error
 */
- (HDError *)logout:(BOOL)bIsUnbindDeviceToken;

/*!
 *  \~chinese
 *  登出
 *
 *  @param aIsUnbindDeviceToken 是否解除device token的绑定，解除绑定后设备不会再收到消息推送
 *         如果传入YES, 解除绑定失败，将返回error
 *  @param aCompletionBlock 完成的回调
 *
 *  \~english
 *  Logout
 *
 *  @param aIsUnbindDeviceToken     Whether to unbind the device token, the device will no longer receive push notifications after unbinding, If YES is passed in, unbinding fails and error will be returned
 *  @param aCompletionBlock         The callback of completion block
 */
- (void)logout:(BOOL)aIsUnbindDeviceToken
               completion:(void (^)(HDError *error))aCompletionBlock;

#pragma mark - Apns

/*!
 *  \~chinese
 *  绑定device token
 *
 *  同步方法，会阻塞当前线程
 *
 *  @param aDeviceToken  要绑定的token
 *
 *  @result 错误信息
 *
 *  \~english
 *  Bind device token
 *
 *  Synchronization method will block the current thread
 *
 *  @param aDeviceToken  Device token to bind
 *
 *  @result Error
 */
- (HDError *)bindDeviceToken:(NSData *)aDeviceToken;


/*!
 *  \~chinese
 *  绑定device token
 *
 *  @param aDeviceToken     要绑定的token
 *  @param aCompletionBlock 完成的回调
 *
 *  \~english
 *  Device token binding is required to enable Apple push notification service
 *
 *  @param aDeviceToken         Device token to bind
 *  @param aCompletionBlock     The callback block of completion
 */
- (void)registerForRemoteNotificationsWithDeviceToken:(NSData *)aDeviceToken
                                           completion:(void (^)(HDError *aError))aCompletionBlock;

#pragma mark - iOS

/*!
 *  \~chinese
 *  iOS专用，程序进入后台时，需要调用此方法断开连接
 *
 *  @param aApplication  UIApplication
 *
 *  \~english
 *  iOS only, should call this method to disconnect from server when app enter backgroup
 *
 *  @param aApplication  UIApplication
 */
- (void)applicationDidEnterBackground:(id)aApplication;

/*!
 *  \~chinese
 *  iOS专用，程序进入前台时，需要调用此方法进行重连
 *
 *  @param aApplication  UIApplication
 *
 *  \~english
 *  iOS only, should call this method to re-connect to server when app restore to foreground
 *
 *  @param aApplication  UIApplication
 */
- (void)applicationWillEnterForeground:(id)aApplication;

/*!
 *  \~chinese
 *   设置 访客初始语种
 *   传递语言代码 可以参考 文档 http://docs.easemob.com/cs/100agentmode/10conversation#智能翻译
 *   @param language  语言代码
 *   @param visitorUserName  访客用户名
 */
- (void)hd_SetVisitorLanguage:(NSString *)language withVisitorUserName:(NSString *)visitorUserName  completion:(void (^)(id responseObject ,HDError *aError))aCompletionBlock;

#pragma mark - Change AppKey

/*!
 *  \~chinese
 *  修改appkey
 *
 *  @param aAppkey  appkey
 *
 *  @result 错误信息
 *
 *  \~english
 *  change appkey
 *
 *  @param aAppkey  appkey
 *
 *  @result Error
 */
- (HDError *_Nullable)changeAppKey:(NSString *_Nullable)appKey;

/**
 改变tenantId

 @param tenantId
 @return error
 */
- (void)changeTenantId:(NSString *_Nullable)tenantId;

/**
 改变configId

 @param configId
 @return error
 */
- (void)changeConfigId:(NSString *_Nullable)configId;


/**
 * 获取当前客服服务器地址 host
 *
 */
- (NSString *_Nullable)kefuRestServer;


/**
 * 获取IM用户的token
 *
 */
- (NSString *_Nullable) accessToken;

/**
 * 获取当前客服 使用的 tenantId
 *
 */
- (NSString *_Nullable)kefuTenantId;
/**
 * 获取当前客服 使用的 configid
 *
 */
- (NSString * _Nullable)kefuConfigId;
/*!
 *  \~chinese
 *  留言管理模块
 *
 *  \~english
 *  LeaveMsgManager module
 */
@property (nonatomic, strong, readonly) HDLeaveMsgManager * _Nullable leaveMsgManager;

/*!
 *  \~chinese
 *      需要轮询的时候 获取的后台配置的轮询时间
 */
- (void)getReportEventTime:(NSString *)eventId attributes:(NSDictionary *)attributes Completion:(void (^)(id responseObject, HDError *error))completion;
/*!
 *  \~chinese
 *     上报 用户行为接口 vec 独立视频使用  上报用户在线行为
 */
- (void)vec_sendReportEventImServiceNum:(NSString *)imServiceNum;

/*!
 *  \~chinese
 *     上报 用户行为接口 vec 独立视频使用  上报用户离线行为
 */
- (void)vec_offLineReportEventVisitorUserName:(NSString *)visitorUserName withImServiecNum:(NSString *)imServiecNum ;


/*!
 *  \~chinese
 *     上报 用户行为接口 cec使用  上报用户在线行为
 */
- (void)cec_sendReportEventImServiceNum:(NSString *)imServiceNum;

/*!
 *  \~chinese
 *     上报 用户行为接口 cec使用  上报用户离线行为
 */
- (void)cec_offLineReportEventVisitorUserName:(NSString *)visitorUserName withImServiecNum:(NSString *)imServiecNum ;


- (void)uploadSdkVersionVisitorUserName:(NSString *)visitorUserName;

#pragma mark - deprecated
@property (nonatomic, readonly) BOOL isAutoLogin __attribute__((deprecated("已过期")));
@property (nonatomic, strong, readonly) HDChatManager *chat __attribute__((deprecated("已过期, 请使用chatManager")));
@property (nonatomic, readonly) BOOL isConnected __attribute__((deprecated("已过期")));
@property (nonatomic,copy) NSString *currentVersion __attribute__((deprecated("已过期, 请使用sdkVersion")));
@property (nonatomic,copy) NSString *imCurrentVersion __attribute__((deprecated("已过期, 请使用imSdkVersion")));

- (NSString *)getUserToken __attribute__((deprecated("已过期, 请使用accessToken")));
- (HDError *)setApnsNickname:(NSString *)aNickname __attribute__((deprecated("已过期, 请使用HDPushManager: updatePushDisplayName")));

- (HDPushOptions *)getPushOptionsFromServerWithError:(HDError **)pError __attribute__((deprecated("已过期, 请使用HDPushManager: getPushOptionsFromServerWithError:")));
- (HDError *)updatePushOptionsToServer:(HDPushOptions *)HDPushOptions  __attribute__((deprecated("已过期")));



@end
