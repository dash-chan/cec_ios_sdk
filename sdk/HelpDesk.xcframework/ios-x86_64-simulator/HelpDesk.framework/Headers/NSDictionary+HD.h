//
//  NSDictionary+HD.h
//  helpdesk_sdk
//
//  Created by afanda on 8/22/17.
//  Copyright © 2017 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (HD)

+ (NSDictionary *)dictionaryWithString:(NSString *)string;
- (BOOL)isDictionaryContainsKey:(NSString *)key;
- (instancetype)getDictionaryValue:(NSString *)key;

+ (NSString*)convertToJSONData:(id)infoDict;


@end
