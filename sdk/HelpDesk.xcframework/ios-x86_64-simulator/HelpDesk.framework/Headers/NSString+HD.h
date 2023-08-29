//
//  NSString+HD.h
//  helpdesk_sdk
//
//  Created by afanda on 8/22/17.
//  Copyright © 2017 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (HD)

+ (NSString *)stringWithDictionary:(NSDictionary *)dic;
+ (BOOL)isBlankString:(NSString *)aStr;
@end
