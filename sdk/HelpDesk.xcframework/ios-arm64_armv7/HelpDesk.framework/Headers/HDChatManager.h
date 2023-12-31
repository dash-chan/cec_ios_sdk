//
//  Chat.h
//  helpdesk_sdk
//
//  Created by 赵 蕾 on 16/3/29.
//  Copyright © 2016年 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HDChatManagerDelegate.h"
#import "HDConversation.h"
#import "HDError.h"
/*
 *  获取配置接口对应参数
 */
typedef NS_ENUM (NSInteger, HDOptionConfig) {
    HDOption_Satisfaction_ProblemSolvingEvaluationOn = 1,    /**< 问题解决评价 开关    */
    HDOption_Satisfaction_GreetingMsgEnquiryInvite          ,    /**< 请对我的服务做出评价 文案   */
    HDOption_Satisfaction_EvaluteSolveWord       ,    /**< 问题解决评价引导语    */
};

@interface HDChatManager : NSObject

/**
 正在会话的conversationId，只读
 */
@property (nonatomic,copy,readonly) NSString *currentConversationId __attribute__((deprecated("已过期")));
/**
 toUser
 */
@property (nonatomic,copy) NSString *toUser;
/**
  收到的最后 lastMessage的 ServiceSessionId
 */
@property (nonatomic,copy) NSString *serviceSessionId;

#pragma mark - 第二通道

- (void)startPollingCname:(NSString *)cname __attribute__((deprecated("已过期, 请使用bindChatWithConversationId")));

/**
 开启第二通道,参数为会话ID
 @param conversationId 会话ID,一般为IM服务号
 */
- (void)bindChatWithConversationId:(NSString *)conversationId;

- (void)endPolling __attribute__((deprecated("已过期, 请使用unbind")));

/**
 关闭第二通道
 */
- (void)unbind;


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
- (void)addDelegate:(id<HDChatManagerDelegate>)aDelegate
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
- (void)removeDelegate:(id<HDChatManagerDelegate>)aDelegate;

#pragma mark - Conversation

/*!
 *  \~chinese
 *  从数据库中获取所有的会话，执行后会更新内存中的会话列表
 *
 *  同步方法，会阻塞当前线程
 *
 *  @result 会话列表<HDConversation>
 *
 *  \~english
 *  Load all conversations from DB, will update conversation list in memory after this method is called
 *
 *  Synchronization method will block the current thread
 *
 *  @result Conversation list<HDConversation>
 */
- (NSArray *)loadAllConversations;

/*!
 *  \~chinese
 *  获取一个会话
 *
 *  @param aConversationId  会话ID
 *
 *  @result 会话对象
 *
 *  \~english
 *  Get a conversation
 *
 *  @param aConversationId  Conversation id
 *  @param aIfCreate        Whether create conversation if not exist
 *
 *  @result Conversation
 */
- (HDConversation *)getConversation:(NSString *)aConversationId;
/*!
 *  \~chinese
 *  删除会话
 *
 *  @param aConversationId  会话ID
 *  @param aDeleteMessage   是否删除会话中的消息
 *
 *  @result 是否成功
 *
 *  \~english
 *  Delete a conversation
 *
 *  @param aConversationId  Conversation id
 *  @param aDeleteMessage   Whether delete messages
 *
 *  @result Whether deleted successfully
 */
- (BOOL)deleteConversation:(NSString *)aConversationId
            deleteMessages:(BOOL)aDeleteMessage;


/**
 * 获取当前会话id
 * @param aUsername         IM服务号
 * @param aCompletionBlock  发送完成回调block,如果当前有会话，则返回，没有时，返回nil, 表示当前无有效会话
 */

- (void)fetchCurrentSessionId:(NSString *)aUsername
                   completion:(void(^)(NSString *sessionId, HDError *aError))aCompletionBlock;
/**
 * 获取当前访客id
 * @param aUsername         IM服务号
 * @param aCompletionBlock  发送完成回调block,如果当前有会话，则返回，没有时，返回nil, 表示当前无有效会话
 */

- (void)fetchCurrentVisitorId:(NSString *)imServiceNum
                   completion:(void(^)( HDError *aError,NSString *visitorId))aCompletionBlock;
/**
 * 获取当前会话
 * @param aUsername         IM服务号
 * @param aCompletionBlock  发送完成回调block,如果当前有会话，则返回，没有时，返回nil, 表示当前无有效会话
 */
- (void)fetchCurrentServiceSession:(NSString *)aUsername
                   completion:(void(^)(id responseObject, HDError *aError))aCompletionBlock;
/**
 * 获取消息内的 会话id
 * @param message         消息对象
 */
- (NSString *)fetchMessageSessionId:(HDMessage *)message;

#pragma mark - Message

/*!
 *  \~chinese
 *  获取消息附件路径, 存在这个路径的文件，删除会话时会被删除
 *
 *  @param aConversationId  会话ID
 *
 *  @result 附件路径
 *
 *  \~english
 *  Get message attachment path for the conversation, files in this path will also be deleted when delete the conversation
 *
 *  @param aConversationId  Conversation id
 *
 *  @result Attachment path
 */
- (NSString *)getMessageAttachmentPath:(NSString *)aConversationId;

/*!
 *  \~chinese
 *  发送消息
 *
 *  @param aMessage         消息
 *  @param aProgressBlock   附件上传进度回调block
 *  @param aCompletionBlock      发送完成回调block
 *
 *  \~english
 *  Send a message
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The block of attachment upload progress
 *  @param aCompletionBlock         The block of send complete
 */
- (void)sendMessage:(HDMessage *)aMessage
           progress:(void (^)(int progress))aProgressBlock
         completion:(void (^)(HDMessage *aMessage, HDError *aError))aCompletionBlock;

/*!
 *  \~chinese
 *  发送访客状态
 *
 *  @param aMessage         消息
 *  @param aProgressBlock   附件上传进度回调block
 *  @param aCompletionBlock      发送完成回调block
 *
 *  \~english
 *  Send a message
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The block of attachment upload progress
 *  @param aCompletionBlock         The block of send complete
 */
- (void)sendReportCMDMessage:(HDMessage *)aMessage
           progress:(void (^)(int progress))aProgressBlock
         completion:(void (^)(HDMessage *aMessage, HDError *aError))aCompletionBlock;



/*!
 *  \~chinese
 *  重发送消息
 *
 *
 *  @param aMessage            消息
 *
 *  \~english
 *  Resend Message
 *
 *
 *  @param aMessage            Message instance
 */
- (void)resendMessage:(HDMessage *)aMessage
             progress:(void (^)(int progress))aProgressCompletion
           completion:(void (^)(HDMessage *message,
                                HDError *error))aCompletion;

/*!
 *  \~chinese
 *  更新消息到DB
 *
 *  @param aMessage  消息
 *  @param aCompletionBlock 完成的回调
 *
 *  \~english
 *  Update message
 *
 *  @param aMessage  Message
 *  @param aSuccessBlock    The callback block of completion
 *
 */
- (void)updateMessage:(HDMessage *)aMessage
           completion:(void (^)(HDMessage *aMessage, HDError *aError))aCompletionBlock;

// 获取技能组菜单界面skillgroup-menu
- (void)getSkillGroupMenuWithCompletion:(void(^)(NSDictionary *info, HDError *error))aCompletion;

// 获取技能组菜单界面skillgroup-menu
- (void)getSkillGroupMenuWithVisitorUserName:(NSString *)visitorUserName Completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;
// 获取 APP关联设置：个性化会话设置增加获取技能组菜单界面skillgroup-menu visitorUserName 用户名 aServerNumber ： im服务号 也就是to
- (void)getAppRelevanceSkillGroupMenuWithVisitorUserName:(NSString *)visitorUserName withImServerNumber:(NSString *)aServerNumber Completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;

// 获取企业欢迎语 设置语种
- (void)getEnterpriseWelcomeWithVisitorUserName:(NSString *)visitorUserName WithCompletion:(void(^)(NSString *welcome, HDError *error))aCompletion;

// 获取 APP关联设置：个性化会话设置增加企业欢迎语 visitorUserName 用户名 aServerNumber ： im服务号 也就是to
- (void)getAppRelevanceEnterpriseWelcomeWithVisitorUserName:(NSString *)visitorUserName withImServerNumber:(NSString *)aServerNumber Completion:(void(^)(NSString *welcome, HDError *error))aCompletion;

// 获取企业欢迎语
- (void)getEnterpriseWelcomeWithCompletion:(void(^)(NSString *welcome, HDError *error))aCompletion;

// 获取机器人欢迎语 翻译使用api
- (void)getRobotWelcomeWithImServerNumber:(NSString *)aServerNumber withVisitorUserName:(NSString *)visitorUserName
                               completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;
// 获取机器人欢迎语
- (void)getRobotWelcomeWithImServerNumber:(NSString *)aServerNumber
                               completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;

// 个性化会话设置增加企业欢迎语
- (void)getEnterpriseWelcomeWithAssociation:(NSString *)appkey
                               completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;

// 根据类型获取会话
- (void)asyncFetchSessionWithConversationId:(NSString *)aConversationsId
                                sessionType:(HSessionType)aSessionType
                                 completion:(void(^)(NSArray *sessions, HDError *error))aCompletion;

- (void)downloadMessageThumbnail:(HDMessage *)aMessage
                        progress:(void (^)(int progress))aProgressBlock
                      completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock __attribute__((deprecated("已过期, 请使用downloadThumbnail")));


/*!
 *  \~chinese
 *  下载消息附件（语音，视频，图片原图，文件），SDK会自动下载语音消息，所以除非自动下载语音失败，用户不需要自动下载语音附件
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message attachment(voice, video, image or file), SDK downloads attachment automatically, no need to download attachment manually unless automatic download failed
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)hd_downloadAttachment:(HDMessage *)aMessage
                  progress:(void (^)(int progress))aProgressBlock
                completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;
/*!
 *  \~chinese
 *  下载缩略图（图片消息的缩略图或视频消息的第一帧图片），SDK会自动下载缩略图，所以除非自动下载失败，用户不需要自己下载缩略图
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message thumbnail (thumbnail of image message or first frame of video image), SDK downloads thumbails automatically, no need to download thumbail manually unless automatic download failed.
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)hd_downloadThumbnail:(HDMessage *)aMessage
                 progress:(void (^)(int progress))aProgressBlock
               completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;
/*!
 *  \~chinese
 *  下载缩略图（图片消息的缩略图或视频消息的第一帧图片），SDK会自动下载缩略图，所以除非自动下载失败，用户不需要自己下载缩略图
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message thumbnail (thumbnail of image message or first frame of video image), SDK downloads thumbails automatically, no need to download thumbail manually unless automatic download failed.
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)downloadThumbnail:(HDMessage *)aMessage
                 progress:(void (^)(int progress))aProgressBlock
               completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;

/*!
 *  \~chinese
 *  下载消息附件（语音，视频，图片原图，文件），SDK会自动下载语音消息，所以除非自动下载语音失败，用户不需要自动下载语音附件
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message attachment(voice, video, image or file), SDK downloads attachment automatically, no need to download attachment manually unless automatic download failed
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)downloadAttachment:(HDMessage *)aMessage
                  progress:(void (^)(int progress))aProgressBlock
                completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;

- (void)downloadMessageAttachment:(HDMessage *)aMessage
                         progress:(void (^)(int progress))aProgressBlock
                       completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock __attribute__((deprecated("已过期, 请使用downloadAttachment")));
/**
 
 设置语音消息为已播放
 
 @param message 需要设置的消息
 */
- (void)setMessageListened:(HDMessage *)message;

#pragma mark - 自定义表情包


/**
 获取表情包列表
 
 @param completion 完成回调
 */
- (void)getEmojiPackageListCompletion:(void(^)(NSArray <NSDictionary *> *emojiPackages,HDError *error))completion;


/**
 获取单个表情包的表情文件
 
 @param packageId 表情包id
 @param completion 完成回调
 */
- (void)getEmojisWithPackageId:(NSString *)packageId
                    completion:(void(^)(NSArray <NSDictionary *> *emojis,HDError *error))completion;


/**
 把访客输入的内容传到服务器
 
 @param completion 完成回调
 */
- (void)postContent:(NSString *)content conversationId:(NSString *)conversationId completion:(void(^)(id responseObject,HDError *error))completion;



#pragma mark - Menu
/**
 获取询前引导菜单
 @param aConversationId 会话id
 @param completion 完成回调
 */
- (void)asyncFetchMenuWithConversationId:(NSString *)aConversationId
                              completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;


#pragma mark - Appraise

/**
 获取评价度选项
 
 @param aCompletion 完成回调
 */
- (void)asyncFetchEvaluationDegreeInfoWithCompletion:(void(^)(NSDictionary *info, HDError *error))aCompletion;


/**
 构造主动评价消息
 
 @param aCompletion 完成回调
 */
- (void)asyncSendInviteEvaluationMessage:(NSString *)aUsername
                              completion:(void(^)(HDMessage *message, HDError *error))aCompletion;

// 提交机器人服务质量
- (void)asyncPostRobotQuality:(HDMessage *)aMsg
                        solve:(BOOL)isSolve
                         tags:(NSArray *)aTags
                   completion:(void(^)(NSDictionary *info, HDError *error))aCompletion;

// 获取未解决标签 
- (void)asyncFetchRobotQualityTags:(HDMessage *)aMsg
                        completion:(void(^)(NSDictionary *tags, HDError *error))aCompletion;

//获取灰度
- (void)getJgrayscaleJsonCompletion:(void(^)(id responseObject,NSError *error))completion;

//获取配置对应的接口
- (void)getOptionsConfig:(HDOptionConfig)option WithServiceSessionId:(NSString *)serviceSessionId Completion:(void (^)(id responseObject, HDError *error))aCompletion;
// 获取问题解决评价 标签
- (void)getResolutionParamServiceSessionId:(NSString *)serviceSessionId Completion:(void (^)(id responseObject, HDError *error))aCompletion;

/*!
 *  \~chinese
 *  将所有未读消息设置为已读
 *
 *  @param serviceSessionId   会话id。如果不传 走默认sdk 里边存储的会话id
 *
 *  \~english
 *  Mark all message as read
 *
 *  @param serviceSessionId
 *
 */
- (void)markAllMessagesAsRead:(NSString *)serviceSessionId Completion:(void (^)(id responseObject, HDError *error))aCompletion;;
/*!
 *  \~chinese
 *   获取当前消息是否是 VEC 消息  yes 是vec 消息。no 不是vec 消息
 */
- (BOOL)isVECMessage:(HDMessage *)message;



/// 根据消息获取会话id
/// @param message  需要解析哪个消息 里的会话id
-(NSString *)getMessageServiceSessionId:(HDMessage *)message;

/// 关闭会话
/// @param sessionId  会话id
/// @param visitorId 访客id
/// @param aCompletion  结果回调
-(void)cec_closeServiceSessionId:(NSString *)sessionId withImServiceNum:(NSString *)imServiceNum Completion:(void (^)(id responseObject, HDError *error))aCompletion;


#pragma mark ======================= 视频中的聊天消息相关api  start==================================
/*!
 *  \~chinese
 *  发送vec消息
 *
 *  @param aMessage         消息
 *  @param aProgressBlock   附件上传进度回调block
 *  @param aCompletionBlock      发送完成回调block
 *
 *  \~english
 *  Send a message
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The block of attachment upload progress
 *  @param aCompletionBlock         The block of send complete
 */
- (void)vec_sendMessage:(HDMessage *)aMessage
           progress:(void (^)(int progress))aProgressBlock
         completion:(void (^)(HDMessage *aMessage, HDError *aError))aCompletionBlock;

/*!
 *  \~chinese
 *  更新vec 消息到DB
 *
 *  @param aMessage  消息
 *  @param aCompletionBlock 完成的回调
 *
 *  \~english
 *  Update message
 *
 *  @param aMessage  Message
 *  @param aSuccessBlock    The callback block of completion
 *
 */
- (void)vec_updateMessage:(HDMessage *)aMessage
           completion:(void (^)(HDMessage *aMessage, HDError *aError))aCompletionBlock;
/*!
 *  \~chinese
 *  拉取vec消息
 *  @param aCompletionBlock      拉取完成回调block
 *
 *  \~english
 *  get  a message

 *  @param aCompletionBlock         The block of send complete
 */
- (void)vec_getMessageWithPlanBCompletion:(void (^)(NSArray *, NSArray *))aCompletionBlock;

/*!
 *  \~chinese
 *  vec 下载缩略图（图片消息的缩略图或视频消息的第一帧图片），SDK会自动下载缩略图，所以除非自动下载失败，用户不需要自己下载缩略图
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message thumbnail (thumbnail of image message or first frame of video image), SDK downloads thumbails automatically, no need to download thumbail manually unless automatic download failed.
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)vec_hd_downloadThumbnail:(HDMessage *)aMessage
                 progress:(void (^)(int progress))aProgressBlock
               completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;

/*!
 *  \~chinese
 *  重发送消息
 *
 *
 *  @param aMessage            消息
 *
 *  \~english
 *  Resend Message
 *
 *
 *  @param aMessage            Message instance
 */
- (void)vec_resendMessage:(HDMessage *)aMessage
             progress:(void (^)(int progress))aProgressCompletion
           completion:(void (^)(HDMessage *message,
                                HDError *error))aCompletion;

/*!
 *  \~chinese
 *  下载消息附件（语音，视频，图片原图，文件），SDK会自动下载语音消息，所以除非自动下载语音失败，用户不需要自动下载语音附件
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressBlock      附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message attachment(voice, video, image or file), SDK downloads attachment automatically, no need to download attachment manually unless automatic download failed
 *
 *
 *  @param aMessage            Message instance
 *  @param aProgressBlock      The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)vec_hd_downloadAttachment:(HDMessage *)aMessage
                  progress:(void (^)(int progress))aProgressBlock
                completion:(void (^)(HDMessage *message, HDError *error))aCompletionBlock;


#pragma mark ======================= 视频中的聊天消息相关api  end==================================
-(void)__supplementaryDataDBHMessages;
@end

