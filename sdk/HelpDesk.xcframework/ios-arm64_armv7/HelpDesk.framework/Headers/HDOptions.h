//
//  HOptoins.h
//  helpdesk_sdk
//
//  Created by 赵 蕾 on 16/5/5.
//  Copyright © 2016年 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>



@interface HDOptions : NSObject

/*!
 *  \~chinese
 *  app唯一标识符
 *
 *  \~english
 *  Application's unique identifier
 */
@property (nonatomic, strong) NSString *appkey;

/*!
 *  \~chinese
 *  控制台是否输出log, 默认为NO
 *
 *  \~english
 *  Whether print log to console, default is NO
 */
@property (nonatomic, assign) BOOL enableConsoleLog;

/**
 *  \~chinese
 *  是否只使用 HTTPS 协议。默认值为 `NO`。
 *
 *  \~english
 *  Whether to only use the HTTPS protocol. The default value is `NO`.
 */
@property(nonatomic, assign) BOOL usingHttpsOnly;
/*!
 *  \~chinese
 *  租户ID
 *
 *  \~english
 *  tenantId
 */
@property (nonatomic,copy) NSString *tenantId;


/*!
 *  \~chinese
 *  插件配置id
 *
 *  \~english
 *  tenantId
 */
@property (nonatomic,copy) NSString *configId;

/**
 *  \~chinese
 *  是否自动下载图片和视频缩略图及语音消息，默认为 `YES`。
 *
 *  \~english
 *  Whether to automatically download image or video thumbnails and voice messages. The default value is `YES`.
 */
@property(nonatomic, assign) BOOL autoDownloadThumbnail;

/**
 *  \~chinese
 *  从数据库加载消息时是否按服务器时间排序，默认值为 `YES`，表示按按服务器时间排序。
 *
 *  \~english
 *  Whether to sort messages by server received time when loading message from database. The default value is `YES`.
 */
@property(nonatomic, assign) BOOL sortMessageByServerTime;

/**
 *  \~chinese
 * 是否自动上传或者下载消息中的附件，默认值为 `YES`。
 *
 *  \~english
 *  Whether to automatically upload or download the attachment in the message. The default value is `YES`.
 */
@property(nonatomic, assign) BOOL isAutoTransferMessageAttachments;

/**
 *  \~chinese
 * 是否打开FPA加速功能，默认关闭
 *
 *  \~english
 *  Whether to enable fpa feature. The default value is `NO`.
 */
@property(nonatomic, assign) BOOL enableFpa;

/**
 *  \~chinese
 *  iOS 特有属性，PushKit 的证书名称。
 *
 *  该参数只能在调用 `initializeSDKWithOptions` 时设置，且 app 运行过程中不可以修改。
 *
 *  \~english
 *  The certificate name of Apple PushKit Service.
 *
 *  Ensure that you set this parameter when calling `initializeSDKWithOptions`. During the app runtime, you can not change the settings.
 */
@property(nonatomic, copy) NSString *pushKitCertName;

/*!
 *  \~chinese
 *  iOS特有属性，推送证书的名称
 *
 *  只能在[HDClient initializeSDKWithOptions:]时设置，不能在程序运行过程中动态修改
 *
 *  \~english
 *  iOS only, push certificate name
 *
 *  Can only set when initialize SDK [HDClient initializeSDKWithOptions:], can't change it in runtime
 */
@property (nonatomic, strong) NSString *apnsCertName;

/***************SDK 私有部署属性*************/

/*!
 *  \~chinese
 *  是否允许使用DNS, 默认为YES
 *
 *  只能在[HDClient initializeSDKWithOptions:]中设置，不能在程序运行过程中动态修改。
 *
 *  \~english
 *  Whether to allow using DNS, default is YES
 *
 *  Can only be set when initializing the SDK [HDClient initializeSDKWithOptions:], cannot be altered in runtime
 */
@property (nonatomic, assign) BOOL enableDnsConfig;

/*!
 *  \~chinese
 *  IM服务器端口
 *
 *  enableDnsConfig为NO时有效。只能在[HDClient initializeSDKWithOptions:]中设置，不能在程序运行过程中动态修改
 *
 *  \~english
 *  IM server port
 *
 *  chatPort is Only effective when isDNSEnabled is NO.
 *  Can only be set when initializing the SDK with [HDClient initializeSDKWithOptions:], cannot be altered in runtime
 */
@property (nonatomic, assign) int chatPort;

/*!
 *  \~chinese
 *  IM服务器地址
 *
 *  enableDnsConfig为NO时生效。只能在[HDClient initializeSDKWithOptions:]中设置，不能在程序运行过程中动态修改
 *
 *  \~english
 *  IM server
 *
 *  chatServer is Only effective when isDNSEnabled is NO. Can only be set when initializing the SDK with [HDClient initializeSDKWithOptions:], cannot be altered in runtime
 */
@property (nonatomic, copy) NSString *chatServer;

/*!
 *  \~chinese
 *  REST服务器地址
 *
 *  enableDnsConfig为NO时生效。只能在[HDClient initializeSDKWithOptions:]中设置，不能在程序运行过程中动态修改
 *
 *  \~english
 *  REST server
 *
 *  restServer Only effective when isDNSEnabled is NO. Can only be set when initializing the SDK with [HDClient initializeSDKWithOptions:], cannot be altered in runtime
 */

@property (nonatomic, copy) NSString *restServer;

/**
 *  \~chinese
 *  DNS URL 地址。
 *
 *  enableDnsConfig为YES时生效，只能在 {@link HDClient initializeSDKWithOptions:} 中设置，不能在程序运行过程中动态修改。
 *
 *  \~english
 *  The DNS url.
 *
 *  This property is effective only when `enableDnsConfig` is `YES`.
 *  Can only be set when initializing the SDK with  {@link HDClient initializeSDKWithOptions:} , cannot be altered in runtime.
 */
@property (nonatomic, copy) NSString *dnsURL;


/**
 *  客服REST服务器地址,默认:https://kefu.easemob.com ,没有设置的情况下都使用默认地址
 *  只能在[HDClient initializeSDKWithOptions:]中设置，不能在程序运行过程中动态修改
 */
@property (nonatomic,copy) NSString *kefuRestServer;

/**
 是否需要待接入排队功能
 */
@property (nonatomic, assign) BOOL visitorWaitCount;


/**
 是否显示坐席输入状态
 */
@property (nonatomic, assign) BOOL showAgentInputState;

/**
 是否同时使用im 默认 no 不使用
 */
@property (nonatomic, assign) BOOL useIm;

/**
  如果是同时使用im 请一定要设置 客服后台app关联中对应的 im服务号
 */
@property (nonatomic, copy)  NSString *imServiceUser;

/**
 是否使用自动登录
 */
@property (nonatomic) BOOL isAutoLogin;

/**
 离开群组时是否删除该群所有消息, 默认为YES
*/
@property (nonatomic, assign) BOOL isDeleteMessagesWhenExitGroup;

/**
 离开聊天室时是否删除所有消息, 默认为YES
 */
@property (nonatomic, assign) BOOL isDeleteMessagesWhenExitChatRoom;

/**
 是否允许聊天室Owner离开, 默认为YES
 */
@property (nonatomic, assign) BOOL isChatroomOwnerLeaveAllowed;

/**
 用户自动同意群邀请, 默认为YES
 */
@property (nonatomic, assign) BOOL isAutoAcceptGroupInvitation;

/**
 自动同意好友申请, 默认为NO
 */
@property (nonatomic, assign) BOOL isAutoAcceptFriendInvitation;

/**
 是否需要消息接受方已读确认，缺省YES
 */
@property (nonatomic, assign) BOOL enableRequireReadAck;

/**
 是否发送消息送达回执, 默认为NO，如果设置为YES，SDK收到单聊消息时会自动发送送达回执
 */
@property (nonatomic, assign) BOOL enableDeliveryAck;
/*!
 *  \~chinese
 *  配置项扩展
 *
 *  \~english
 *  Options extension
 *
 */
@property (nonatomic, strong) NSDictionary *extension;
@end
