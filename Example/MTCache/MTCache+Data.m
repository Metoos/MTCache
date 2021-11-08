//
//  MTCache+Data.m
//  MTCache
//
//  Created by mac on 2021/11/4.
//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-implementation"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#pragma clang diagnostic ignored "-Wint-conversion"

#import "MTCache+Data.h"

@implementation MTCache (Data)

MTCACHE_OBJ_IMP(NSString *,userId, @"dm://userID")

MTCACHE_OBJ_IMP(NSString *,socketHost, @"dm://socketHost")

MTCACHE_OBJ_IMP(MTLoginModel *,userInfo, @"dm://userInfo?class=MTLoginModel&user=1&copy=1")

MTCACHE_NUMBER_IMP(int, heartbeatTime, @"m://heartbeatTime?default=120");

MTCACHE_NUMBER_IMP(long, byteCount, @"m://byteCount?default=1024000000000");

MTCACHE_NUMBER_IMP(double, serviceTime, @"m://serviceTime?default=1636023546.352");

MTCACHE_BOOL_IMP(BOOL, isSocketDidConnect, @"m://isSocketDidConnect?default=0")

@end

#pragma clang diagnostic pop
