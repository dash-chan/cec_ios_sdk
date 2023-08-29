//
//  YYModel.h
//  YYModel <https://github.com/ibireme/YYModel>
//
//  Created by ibireme on 15/5/10.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

#if __has_include(<HDYYModel/HDYYModel.h>)
FOUNDATION_EXPORT double HDYYModelVersionNumber;
FOUNDATION_EXPORT const unsigned char HDYYModelVersionString[];
#import <HDYYModel/NSObject+HDYYModel.h>
#import <HDYYModel/HDYYClassInfo.h>
#else
#import "NSObject+HDYYModel.h"
#import "HDYYClassInfo.h"
#endif
