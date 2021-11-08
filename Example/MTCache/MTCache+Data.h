//
//  MTCache+Data.h
//  MTCache
//
//  Created by mac on 2021/11/4.
//

#import <MTCache/MTCache.h>
@class MTLoginModel;
NS_ASSUME_NONNULL_BEGIN

@interface MTCache (Data)
/// 保存登录ID
MTCACHE_PROPERTY(NSString *, userId)
/// 保存socket服务器地址
MTCACHE_PROPERTY(NSString *, socketHost)
/// 保存当前登录用户的信息
MTCACHE_PROPERTY(MTLoginModel *, userInfo)

/// 保持socket连接的心跳时间单位s
MTCACHE_PROPERTY(int, heartbeatTime);
/// 文件传到的最大字节数
MTCACHE_PROPERTY(long,byteCount);
/// 当前服务器时间
MTCACHE_PROPERTY(double,serviceTime);
/// socket是否已连接
MTCACHE_PROPERTY(BOOL,isSocketDidConnect);

@end

NS_ASSUME_NONNULL_END
