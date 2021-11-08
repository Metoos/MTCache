//
//  MTLoginModel.m
//  MTCache
//
//  Created by mac on 2021/11/4.
//

#import "MTLoginModel.h"
#import "MTCache+Data.h"

@implementation MTLoginModel

+ (NSString *)userId {
    return MTCache.userId;
}

@end
