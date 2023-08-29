//
//  HDClient+agoraCall.h
//  HelpDeskLite
//
//  Created by houli on 2022/1/6.
//  Copyright © 2022 hyphenate. All rights reserved.
//

#import "HDClient.h"
#import "HDCallManager.h"
#import "HDWhiteboardManager.h"
@interface HDClient (Call)
/*!
 *  \~chinese
 *  实时通讯模块
 *
 *  \~english
 *  call module
 */
@property (nonatomic, strong, readonly) HDCallManager *callManager;
/*!
 *  \~chinese
 *  白板通讯模块
 *
 *  \~english
 *  Whiteboard module
 */
@property (nonatomic, strong, readonly) HDWhiteboardManager *whiteboardManager;


@end


