//
//  GTCountSDK.h
//  GTCountSDK
//
//  Created by GeTui on 2017/7/18.
//  Copyright © 2017年 GeTui. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - 数据上报策略枚举值

/**
 数据上报策略枚举值
 */
typedef enum {
    
    GESHU_STRATEGY_REAL_TIME = 1,
    GESHU_STRATEGY_WIFI_ONLY,
    GESHU_STRATEGY_BATCH,
    GESHU_STRATEGY_LAUNCH_ONLY,
    GESHU_STRATEGY_PERIOD
    
} GeShuStatReportStrategyType;

#pragma mark - 

@interface GTCountSDK : NSObject

/**
 SDK 实例，用于获取和设置 SDK 相关配置属性。
 示例，设置上报策略：[[GTCountSDK sharedInstance] setReportStrategy:GESHU_STRATEGY_WIFI_ONLY];
 */
+ (instancetype)sharedInstance;

/**
 设置上报策略
 */
@property(nonatomic,assign)GeShuStatReportStrategyType reportStrategy;

/**
 统计上报策略为 BATCH 时，触发上报时最小缓存消息数，默认32条
 */
@property (nonatomic, assign)NSUInteger minBatchReportNumber;

/**
 上报策略为 PERIOD 时发送间隔，单位分钟，默认一天（60分钟）
 */
@property (nonatomic, assign)NSUInteger periodMinutes;

/**
 智能上报
 开启以后设备接入WIFI会实时上报
 否则按照全局策略上报
 默认打开
 */
@property (nonatomic, assign)BOOL smartReporting;

/**
 设置会话时长（默认 30000 ms,单位毫秒），在应用退到后台后停留时间超过会话时长，视为一次新的应用会话。
 */
@property (nonatomic, assign)NSUInteger sessionTime;

/**
 初始化启动接口
 
 @param appId 开发者后台生成的 appId
 @param channelId 渠道名称，默认为 'appstore'
 */
+ (void)startSDKWithAppId:(NSString *)appId withChannelId:(NSString *)channelId;

/**
 记录自定义事件的开始
 注意：需要跟 trackCustomKeyValueEventEnd:withArgs: 配对使用
 若多次调用则以最后一次开始的时间为准

 @param eventId 自定义事件 Id，需要在个数后台配置才能生效
 @param args 自定义属性，需与接口 trackCustomKeyValueEventEnd:withArgs: 传入的参数一致(同一个变量)，用于扩展统计需要
 */
+ (void)trackCustomKeyValueEventBegin:(NSString *)eventId withArgs:(NSDictionary *)args;

/**
 记录自定义事件的结束
 注意：需要跟 trackCustomKeyValueEventBegin:withArgs: 配对使用
 若多次调用则以第一次结束的时间为准
 
 @param eventId 自定义事件 Id，需要在个数后台配置才能生效
 @param args 自定义属性，需与接口 trackCustomKeyValueEventBegin:withArgs: 传入的参数一致(同一个变量)，用于扩展统计需要
 */
+ (void)trackCustomKeyValueEventEnd:(NSString *)eventId withArgs:(NSDictionary *)args;

/**
 计数事件统计

 @param eventId 事件 Id，需要在个数后台配置才能生效
 @param args 需要展示的键值对值
 */
+ (void)trackCountEvent:(NSString *)eventId withArgs:(NSDictionary *)args;

/**
 版本
 */
+(NSString *)sdkVersion;

@end
