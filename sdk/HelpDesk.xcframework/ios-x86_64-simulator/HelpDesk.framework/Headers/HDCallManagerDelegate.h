//
//  HDAgoraCallManagerDelegate.h
//  HelpDeskLite
//
//  Created by houli on 2022/1/6.
//  Copyright © 2022 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HDKeyCenter.h"
#import "HDMessage.h"
@protocol HDCallManagerDelegate <NSObject>

@optional

/*!
 *  \~chinese
 *  收到VEC 创建视频会话的事件
 *  @param rtcSessionId   视频会话的的rtcSessionId
 *
 *  \~english
 *  Receiving a Video request
 *
 */
- (void)onTicketDidReceiveRtcSessionCreateEvent:(NSString *)rtcSessionId;

/*!
 *  \~chinese
 *  收到VEC 创建视频会话的事件
 *  @param rtcSessionId   视频会话的的rtcSessionId
 *
 *  \~english
 *  Receiving a Video request
 *
 */
- (void)onVECTicketDidReceiveRtcSessionCreateEvent:(NSDictionary *)rtcSession;

/*!
 *  \~chinese
 *  接收到视频请求
 *  @param keyCenter   创建视频请求必要的参数
 *
 *  \~english
 *  Receiving a Video request
 *
 */
- (void)onCallReceivedParameter:(HDKeyCenter *)keyCenter withMessage:(HDMessage*)message;



/*!
 *  \~chinese
 *    第三方坐席进来 获取对应的坐席信息
 *  @param thirdAgentNickName   坐席昵称
 *
 *  \~english
 *  Receiving a Video request
 *
 */
- (void)onCallReceivedInvitation:(NSString *)thirdAgentNickName withUid:(NSString *)uid withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *     vec 独立访客端 收到 坐席拒绝的通知
 *
 */
- (void)onCallHangUpInvitationWithMessage:(HDMessage *)message;

/*!
 *  \~chinese
 *     vec 独立访客端 收到 坐席信息推送
 *
 */
- (void)onCallLinkMessagePush:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *     vec 独立访客端 收到 ocr 识别
 *
 */
- (void)onCallLOcrIdentify:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *     vec 独立访客端 收到 身份认证
 *
 */
- (void)onCallFaceIdentify:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *     vec 独立访客端 收到 数字签名
 *
 */
- (void)onCallSignIdentify:(NSDictionary *)dic withMessage:(HDMessage *)message;

/*!
 *  \~chinese
 *   收到满意度
 */
- (void)onEnquiryInviteParameter:(NSDictionary *)enquiryInvite withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *   麦克风 通知
 */
- (void)onMuteLocalAudioStreamParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *   摄像头
 */
- (void)onMuteLocalVideoStreamParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *   切换摄像头
 */
- (void)onSwitchCameraParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *   对焦、
 */
- (void)onFocusingOnParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;
/*!
 *  \~chinese
 *  开关闪光灯
 */
- (void)onCameraTorchOnParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;

/*!
 *  \~chinese
 *    flashlight
 *    手电筒
 */
- (void)onFlashlightParameter:(NSDictionary *)dic withMessage:(HDMessage *)message;


/*!
 *  \~chinese
 *    vecNewChatMsg
 *    视频通话中有新消息进来的cmd通知
 */
- (void)onVecNewChatCMDMsgWithMessage:(HDMessage *)message;

/*!
 *  \~chinese
 *    vecNewChatMsg
 *    视频排队 超时 接收到的cmd 通知
 */
- (void)onVECWaitTimeoutCloseKefuRtcWaitCallMsgWithMessage:(HDMessage *)message;

/*!
 *  \~chinese
 *       视频通话中 收到消息的通知
 *  @param aMessages  消息列表<HDMessage>
 *
 *  \~english
 *  Delegate method will be invoked when receiving new messages
 *
 *  @param aMessages  Receivecd message list<HDMessage>
 */
- (void)on_VecMessagesDidReceive:(NSArray *)aMessages;




@end 

