# MTCache
一个轻量级数据缓存库

## CocoaPods集成
```
pod 'MTCache', '~>1.0.0'
```
## 使用说明

/// scheme
static NSString *const diskScheme          = @"d";  //磁盘Scheme @"d://"
static NSString *const memoryScheme        = @"m";  //内存Scheme @"m://"
static NSString *const diskAndMemoryScheme = @"dm"; //磁盘和内存Scheme @"dm://"
/// arguments
static NSString *const arg_user    = @"user";   //BOOL类型 数据是否为当前登录用户私有（跟随用户存储），默认0
static NSString *const arg_class   = @"class";  //id类型 存储模型数据时的模型类
static NSString *const arg_default = @"default";//id类型 跟随存储的数据类型 给存储类型设置默认值
static NSString *const arg_copy    = @"copy";   //BOOL类型 是否深拷贝 储存到内存时有效 默认0

## 使用demo
添加按功能逻辑模块添加对应的MTCache类目
.h中的代码
```
#import "MTCache.h"
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
```
.m中的代码
```
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-implementation"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#pragma clang diagnostic ignored "-Wint-conversion"

#import "MTCache+Data.h"

@implementation MTCache (Data)
///dm表示该数据需要同时写入内存和磁盘中保存。
MTCACHE_OBJ_IMP(NSString *,userId, @"dm://userID")

MTCACHE_OBJ_IMP(NSString *,socketHost, @"dm://socketHost")
///例子2 储存ObjC类模型
///多个参数时使用&连接
///user=1 表示该数据为登录用户私有，其他登录用户读取不到
///copy=1 表示该数据保存到当前内存缓存中时需要先进行深拷贝操作
MTCACHE_OBJ_IMP(MTLoginModel *,userInfo, @"dm://userInfo?class=MTLoginModel&user=1&copy=1")
///例子3 储存基本数据类型
///基本数据类型储存时可设置默认值
MTCACHE_NUMBER_IMP(int, heartbeatTime, @"m://heartbeatTime?default=120");

MTCACHE_NUMBER_IMP(long, byteCount, @"m://byteCount?default=1024000000000");

MTCACHE_NUMBER_IMP(double, serviceTime, @"m://serviceTime?default=1636023546.352");

MTCACHE_BOOL_IMP(BOOL, isSocketDidConnect, @"m://isSocketDidConnect?default=0")

@end

#pragma clang diagnostic pop
```

##声明完后具体使用的demo
MTLoginModel类具体可在demo项目中查看
```
- (void)viewDidLoad
{
    [super viewDidLoad];
    ///设置类代理以便获取userId
    MTCache.delegate = MTLoginModel.class;
    
    [self cache];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)cache {
    ///模拟向服务器获取socket连接地址
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        MTCache.socketHost = @"http://192.168.1.164";
        MTCache.heartbeatTime = 60;
        MTCache.byteCount  = 20480000;
        MTCache.serviceTime = [[NSDate date] timeIntervalSince1970];
    });
    
    ///模拟socket连接成功后的回调
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.15 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        MTCache.isSocketDidConnect = YES;
    });
    
    ///模拟登录成功后设置userID
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        MTCache.userId = @"638";
        MTLoginModel *model = [[MTLoginModel alloc]init];
        model.userId        = 638;
        model.age           = 25;
        model.nickname      = @"花都拿拉曼";
        MTCache.userInfo    = model;
    });
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"***********分割线************");
        NSLog(@"userId = %@",MTCache.userId);
        NSLog(@"socketHost = %@",MTCache.socketHost);
        NSLog(@"MTCache.userInfo.nickname = %@",MTCache.userInfo.nickname);
        NSLog(@"MTCache.userInfo.age = %d",MTCache.userInfo.age);
        NSLog(@"MTCache.userInfo.userId = %lld",MTCache.userInfo.userId);
        NSLog(@"heartbeatTime = %d",MTCache.heartbeatTime);
        NSLog(@"byteCount = %ld",MTCache.byteCount);
        NSLog(@"socketHost = %lf",MTCache.serviceTime);
        NSLog(@"isSocketDidConnect = %d",MTCache.isSocketDidConnect);
        
        /// 清除数据
        [MTCache clearUserAllDataInDisk];
        [MTCache clearAllDataInMemory];
    });
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(4 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        /// 验证清除数据后的效果
        NSLog(@"***********分割线1************");
        NSLog(@"userId = %@",MTCache.userId);
        NSLog(@"socketHost = %@",MTCache.socketHost);
        NSLog(@"MTCache.userInfo.nickname = %@",MTCache.userInfo.nickname);
        NSLog(@"MTCache.userInfo.age = %d",MTCache.userInfo.age);
        NSLog(@"MTCache.userInfo.userId = %lld",MTCache.userInfo.userId);
        NSLog(@"heartbeatTime = %d",MTCache.heartbeatTime);
        NSLog(@"byteCount = %ld",MTCache.byteCount);
        NSLog(@"socketHost = %lf",MTCache.serviceTime);
        NSLog(@"isSocketDidConnect = %d",MTCache.isSocketDidConnect);
    });
}
```
@end
