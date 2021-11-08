//
//  MTViewController.m
//  MTCache
//
//  Created by zjq on 11/08/2021.
//  Copyright (c) 2021 zjq. All rights reserved.
//

#import "MTViewController.h"
#import <MTCache/MTCache.h>
#import "MTCache+Data.h"
#import "MTLoginModel.h"
@interface MTViewController ()

@end

@implementation MTViewController

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

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
