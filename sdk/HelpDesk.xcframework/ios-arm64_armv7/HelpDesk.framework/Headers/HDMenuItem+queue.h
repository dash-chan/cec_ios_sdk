//
//  HDMenuItem+private.h
//  helpdesk_sdk
//
//  Created by 杜洁鹏 on 2019/9/2.
//  Copyright © 2019 hyphenate. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface HDMenuItem (queue)
@property (nonatomic, copy) NSString *menuId;
@property (nonatomic, copy) NSString *queueId;
@property (nonatomic, copy) NSString *queueType;
@property (nonatomic, copy) NSString *queueName;
@property (nonatomic, copy) NSDictionary *pluginConfig;
@property (nonatomic) BOOL isTransferManualGuide;
@end

NS_ASSUME_NONNULL_END
