//
//  MTCache.h
//  MTCache
//
//  Created by mac on 2021/11/2.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

///在.h中可使用该宏快捷声明属性
#define MTCACHE_PROPERTY(type, name) \
@property (class) type name;\
@property type name;

///在.m中可使用该宏快捷实现声明属性的get与set方法
///NSObject对象数据使用该宏实现get与set方法
#define MTCACHE_OBJ_IMP(type, name, key) \
\
+ (void)set_##name:(type)name { \
[self setObject:name forKey:key];\
}\
\
+ (type)name { \
return [self objectForKey:key];\
}

///在.m中可使用该宏快捷实现声明属性的get与set方法
///基本数据类型（值类型）的数据使用该宏的实现方法
#define MTCACHE_NUMBER_IMP(type, name, key) \
\
+ (void)set_##name:(type)name { \
[self setObject:(void *)&name forKey:key objcType:@encode(type)];\
}\
\
+ (type)name { \
type *i = [self objectForKey:key objcType:@encode(type)];\
return *i;\
}

///在.m中可使用该宏快捷实现声明属性的get与set方法
///BOOL类型可直接用void *表示 与其他基本类型略有不同 这里单独处理
#define MTCACHE_BOOL_IMP(type, name, key) \
\
+ (void)set_##name:(type)name { \
[self setObject:(void *)name forKey:key objcType:@encode(type)];\
}\
\
+ (type)name { \
type *i = [self objectForKey:key objcType:@encode(type)];\
return *i;\
}

/// scheme
static NSString *const diskScheme          = @"d";  //磁盘Scheme @"d://"
static NSString *const memoryScheme        = @"m";  //内存Scheme @"m://"
static NSString *const diskAndMemoryScheme = @"dm"; //磁盘和内存Scheme @"dm://"
/// arguments
static NSString *const arg_user    = @"user";   //BOOL类型 数据是否为当前登录用户私有（跟随用户存储），默认0
static NSString *const arg_class   = @"class";  //id类型 存储模型数据时的模型类
static NSString *const arg_default = @"default";//id类型 跟随存储的数据类型 给存储类型设置默认值
static NSString *const arg_copy    = @"copy";   //BOOL类型 是否深拷贝 储存到内存时有效 默认0

/***** scheme使用demo *****/

///例子1 储存OC类
///表示该数据需要同时写入内存和磁盘中保存。
///MTCACHE_OBJ_IMP(NSString *,socketHost,@"dm://socketHost")

///例子2 储存模型类
///多个参数时使用&连接
///user=1 表示该数据为登录用户私有，其他登录用户读取不到
///copy=1 表示该数据保存到当前内存缓存中时需要先进行深拷贝操作
///MTCACHE_OBJ_IMP(MTLoginModel *,userInfo,@"dm://userInfo?class=MTLoginModel&user=1&copy=1")

///例子3 储存基本数据类型
///基本数据类型储存时可设置默认值
///MTCACHE_NUMBER_IMP(double,rowHeight,@"m://rowHeight?default=100.0")

@protocol MTCacheDelegate <NSObject>

/// 从外部获取到当前登录用户的ID
+ (NSString *)userId;

@end

@interface MTCache : NSObject

@property (class) Class<MTCacheDelegate> delegate;

+ (void)setObject:(nullable id)object forKey:(nonnull NSString *)key;

+ (nullable id)objectForKey:(nullable NSString *)key;

+ (void)setObject:(void *)object forKey:(nonnull NSString *)key objcType:(char *)objcType;

+ (void *)objectForKey:(nullable NSString *)key objcType:(nonnull char *)objcType;

/// 清除当前登录用户保存到磁盘中的所有数据（清除userId前调用）
+ (void)clearUserAllDataInDisk;
/// 清除指定用户保存到磁盘中的所有数据
+ (void)clearAllDataInDiskForUserId:(NSString *)userId;
/// 清除内存缓存中的所有数据 （清除所有使用MTCache库保存在内存中的数据，请谨慎调用）
+ (void)clearAllDataInMemory;
/// 清除磁盘中的所有数据（暂时不开放该方法）
//+ (void)clearAllDataInDisk;

@end

NS_ASSUME_NONNULL_END
