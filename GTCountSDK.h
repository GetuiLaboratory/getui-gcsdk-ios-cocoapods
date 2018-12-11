//
//  GTCountSDK.h
//  GTCountSDK
//
//  Created by j on 2017/7/18.
//  Copyright © 2017年 GeTui. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - 接口监控相关数据结构

/**
 接口监控的错误码
 */
typedef enum {
    /**
     接口调用成功
     */
    GESHU_SUCCESS = 0,
    
    /**
     接口调用失败
     */
    GESHU_FAILURE = 1,
    
    /**
     接口调用出现逻辑错误
     */
    GESHU_LOGIC_FAILURE = 2
    
} GeShuAppMonitorErrorType;

#pragma mark -

/**
 接口统计的数据结构
 */
@interface GeShuAppMonitorStat : NSObject

/**
 接口名称
 */
@property (nonatomic, strong) NSString *name;

/**
 请求包大小（单位 byte ）
 */
@property uint32_t requestPackageSize;

/**
 响应包大小（单位 byte ）
 */
@property uint32_t responsePackageSize;

/**
 调用耗时
 */
@property uint64_t consumedMilliseconds;

/**
 返回码
 */
@property int32_t returnCode;

/**
 返回值类型
 */
@property GeShuAppMonitorErrorType resultType;

/**
 上报采样率，默认 1，含义为百分百采样
 */
@property uint32_t sampling;

@end

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

/**
 接口监控
 */
+ (void)reportAppMonitorStat:(GeShuAppMonitorStat *)appMonitorStat;

/**
 网速监控
 @param domainDic 域名列表
 @example : NSDictionary *dominaDic = @{@"www.getui.com":@(80),@"127.0.0.1":@(80)};
 */
+ (void)reportSpeed:(NSDictionary *)domainDic;

/**
 用户自定义属性
 @param propertyDic 域名列表
 @example : NSDictionary *propertyDic = @{@"用户属性1":@"属性值1",@"用户属性2":@"属性值2"};
 */
+ (void)setUserProperty:(NSDictionary *)propertyDic;

/**
 @param key 参数的key
 @param v 没取到参数时返回的默认值
 @return 参数的值或者默认值
 */
+ (NSString *)getCustomProperty:(NSString *)key default:(NSString *)v;
@end
