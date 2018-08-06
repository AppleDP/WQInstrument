//
//  WQSingle.h
//  WQGeneralMacro
//
//  Created by iOS on 17/11/14.
//  Copyright © 2017年 shenbao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WQInstrument.h"

#define ShareWQSingle [WQSingle shareWQSingle]
@interface WQSingle : NSObject
kWQSingleH()
@property (nonatomic, copy) NSString *name;
@end
