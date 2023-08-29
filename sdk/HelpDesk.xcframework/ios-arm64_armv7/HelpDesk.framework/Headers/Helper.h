//
//  Helper.h
//  helpdesk_sdk
//
//  Created by afanda on 6/21/17.
//  Copyright © 2017 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Helper : NSObject

+ (BOOL)isOfficialMessage:(HDMessage *)message;  //官方消息

+ (BOOL)isMarketingMessage:(HDMessage *)message; //营销消息

+ (BOOL)isNotificationMessage:(HDMessage *)message;  //是通知消息

+ (NSString *)getOfficialIdWithHMessage:(HDMessage *)message; //获取officialId

+ (NSString *)getMarketingIdWithHMessage:(HDMessage *)message; //获取marketingId

+ (NSArray *)fillAvatarUrl:(NSArray *)messages;

+ (NSString *)getFullPathWithPath:(NSString *)path;

+ (BOOL)notEmptyObject: (id)obj;
+ (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString;

@end
