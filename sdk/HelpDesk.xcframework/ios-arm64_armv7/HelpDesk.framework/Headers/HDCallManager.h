//
//  HDAgoraCallManager.h
//  HelpDeskLite
//
//  Created by houli on 2022/1/6.
//  Copyright © 2022 hyphenate. All rights reserved.
#import <Foundation/Foundation.h>
#import "HDCallManagerDelegate.h"
#import "HDGrayModel.h"
#import "HDThirdAgentModel.h"
#define kGrayVecIndependentVideo @"vecIndependentVideo"
NS_ASSUME_NONNULL_BEGIN
@interface HDCallManager : NSObject
@property (nonatomic, strong) HDKeyCenter *keyCenter;
@property (nonatomic, strong) NSString * conversationId;
@property (nonatomic, strong) HDThirdAgentModel * thirdAgentModel;
@property (nonatomic, strong) NSMutableDictionary * agentDicModel;
@property (nonatomic, strong) NSString * visitorUserId;
// vec专用使用属性
// im服务号
@property (nonatomic, strong) NSString * vec_imServiceNum;
@property (nonatomic, strong) NSString * vec_configId;;
@property (nonatomic, strong) NSString * rtcSessionId;

+ (instancetype _Nullable )shareInstance;

/*!
 *  \~chinese
 *  发起视频邀请，发起后，客服会收到申请，客服同意后，会自动给访客拨过来。
 *
 *  @param aImId   会话id
 *  @param aContent   文本内容
 *
 */
- (HDMessage *)cec_creteVideoInviteMessageWithImServiceNum:(NSString *)imServiceNum
                                       content:(NSString *)aContent;


/*!
 *  \~chinese
 *  发起视频邀请，发起后，客服会收到申请，客服同意后，会自动给访客拨过来。
 *
 *  @param  imServiceNum im服务号
 *  @param aContent   文本内容
 *
 */
- (HDMessage *)vec_creteVideoInviteMessageWithImServiceNum:(NSString *)imServiceNum
                                       content:(NSString *)aContent;




/*!
 *  \~chinese
 *   vec 独立访客端 接收 坐席主动发过来的 视频邀请
 *
 *  @param ImServiceNum   im服务号
 *  @param aContent   文本内容
 *
 */
- (HDMessage *)vec_visitorAcceptInvitationMessageWithImServiceNum:(NSString *)imServiceNum
                                       content:(NSString *)aContent;

/*!
 *  \~chinese
 *   vec 独立访客端
 *     坐席回呼。访客拒绝接通 发送的消息
 *  @param aImId   会话id
 *  @param aContent   文本内容
 *
 */
- (HDMessage *)vec_agentCallBackVisitorRejectInvitationMessageWithRtcSessionId:(NSString *)rtcSessionId withImServiceNum:(NSString *)imServiecNum content:(NSString *)aContent;


/*!
 *  \~chinese
 *   vec 独立访客端  结束视频会话。 未接通前 振铃放弃
 *
 *  @param rtcSession   会话id
 *  @param imServiecNum   im服务号
 *
 */
- (HDMessage *)vec_ringGiveUpMessageWithRtcSessionId:(NSString *)rtcSessionId withImServiceNum:(NSString *)imServiecNum withCallId:(NSString *)callId;
/*!
 *  \~chinese
 *   vec 独立访客端  VISITOR_REJECT   访客拒接（振铃过程中访客主动挂断）
 *
 *  @param rtcSession   会话id
 *  @param imServiecNum   im服务号
 *
 */
- (HDMessage *)vec_rejectMessageWithRtcSessionId:(NSString *)rtcSessionId withImServiceNum:(NSString *)imServiecNum withCallId:(NSString *)callId;
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
 */
- (void)addDelegate:(id<HDCallManagerDelegate>_Nullable)aDelegate
      delegateQueue:(dispatch_queue_t _Nullable )aQueue;

/*!
 *  \~chinese
 *  移除回调代理
 *
 *  @param aDelegate  要移除的代理
 *
 *  \~english
 *  Remove delegate
 *
 */
- (void)removeDelegate:(id<HDCallManagerDelegate>_Nullable)aDelegate;

/*!
 *  \~chinese
 *  获取灰度管理
 *
 *  @param grayName  灰度的名称
 *
 *  \~english
 *  Remove delegate
 *
 */
- (HDGrayModel *)getGrayName:(NSString *)grayName;

/*!
 *  \~chinese
 *  初始化灰度管理接口 调用这个接口以后 可以使用getGrayName 获取对应的灰度信息 也可以自己解析responseObject
 *
 */
- (void)initGrayCompletion:(void(^)(id responseObject,HDError *error))completion;

/*!
 *  \~chinese
 *  获取rtcSession
 *
 */
- (NSString *)getRtcSession;

/*!
 *  \~chinese
 *  获取visitorUserId 
 */
- (NSString *)getVisitorUserId;
/*!
 *  \~chinese
 *  vec 获取初始样式以及功能设置
 */
- (void)vec_getInitConfigId:(NSString *)configId Completion:(void(^)(id  responseObject, HDError *error))aCompletion;

/*!
 *  \~chinese
 *  vec 访客挂断接口   /v1/kefurtc/tenant/{tenantId}/session/{rtcSessionId}/visitor/{visitorId}/close
 */
- (void)vec_hangUpSessionId:(NSString *)rtcSessionId WithImServiceNum:(NSString *)imServiceNum Completion:(void(^)(id  responseObject, HDError *error))aCompletion;

/*!
 *  \~chinese
 *   vec 提交签名
 */
- (void)vec_commitSignData:(NSData *)data withImserviceNum:(NSString *)imServiceNum withFlowId:(NSString *)flowId Completion:(void(^)(id  responseObject, HDError *error))aCompletion;


/*!
 *  \~chinese
 *    vec 信息推送 上报接口
 */
- (void)vec_pushBusinessReportImServiceNum:(NSString *)imServiceNum WithFlowId:(NSString *)flowId withAction:(NSString *)action  withType:(NSString *)type  withUrl:(NSString *)url withContent:(NSString *)content Completion:(void(^)(id  responseObject, HDError *error))aCompletion;

/*!
 *  \~chinese
 *    vec排队人数 访客端
 */
- (void)vec_getVisitorCurrentWaitingSessionid:(NSString *)rtcSessionId Completion:(void(^)(id  responseObject, HDError *error))aCompletion;
/*!
 *  \~chinese
 *    vec访客提交评价接口 访客端
 *    /v1/kefurtc/tenant/{tenantId}/enquiry/visitor/submit
 */
- (void)vec_submitVisitorEnquirySessionid:(NSString *)rtcSessionId withScore:(NSInteger)score withComment:(NSString *)comment withTagData:(NSArray *)tagData Completion:(void(^)(id  responseObject, HDError *error))aCompletion;


/*!
 *  \~chinese
 *   vec 独立访客端 远程协助 回传状态
 *
 *  @param imserviceNum   im服务号
 *  @param aContent   文本内容
 *
 */
- (HDMessage *)vec_visitorCallBackStateCmdMessageWithImserviceNum:(NSString *)imserviceNum withOn:(BOOL)on  withAction:(NSString *)action content:(NSString *)aContent;
                                               
/*!
 *  \~chinese
 *   vec 独立访客端 获取插件信息
 */
- (void)vec_getConfigInfoCompletion:(void(^)(id  responseObject, HDError *error))aCompletion;
/*!
 *  \~chinese
 *   访客端 获取灰度接口
 */
- (void)hd_getJgrayscaleJsonCompletion:(void (^)(id responseObject, NSError *error))completion;

/*!
 *  \~chinese
 *   vec 访客端  获取视频超时 时间
 */
- (void)hd_getVideoLineUpTimeOutCompletion:(void (^)(id responseObject, HDError *error))completion;
/*!
 *  \~chinese
 *   获取 屏幕共享 控制应用内 和 应用外接口
 */
- (void)hd_getShareSreenSettingCompletion:(void (^)(id responseObject, HDError *error))completion;


/*!
 *  \~chinese
 *     上报 sdk 版本 以及 版本支持的那些功能
 */
- (void)hd_uploadSdkVersionVisitorUserName:(NSString *)visitorUserName Completion:(void (^)(id responseObject, HDError *error))completion;

@end

NS_ASSUME_NONNULL_END
