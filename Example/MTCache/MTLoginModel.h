//
//  MTLoginModel.h
//  MTCache
//
//  Created by mac on 2021/11/4.
//

#import <Foundation/Foundation.h>
#import <MTCache/MTCache.h>
NS_ASSUME_NONNULL_BEGIN

@interface MTLoginModel : NSObject<MTCacheDelegate>
+ (NSString *)userId;
@property (assign, nonatomic) int64_t userId;
@property (copy, nonatomic) NSString *nickname;
@property (assign, nonatomic) int age;

@end

NS_ASSUME_NONNULL_END
