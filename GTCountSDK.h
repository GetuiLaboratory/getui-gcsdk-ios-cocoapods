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

+ (void)startSDKWithAppId:(NSString *)appId withChannelId:(NSString *)channelId;

+ (void)trackCustomKeyValueEventBegin:(NSString *)eventId withArgs:(NSDictionary *)args;
+ (void)trackCustomKeyValueEventEnd:(NSString *)eventId withArgs:(NSDictionary *)args;
+ (void)trackActiveBegin;
+ (void)trackActiveEnd;
+ (void)trackCountEvent:(NSString *)eventId withArgs:(NSDictionary *)args;

/**
 版本
 */
+(NSString *)sdkVersion;

/**
 设置上报策略
 */
+ (void)setReportStrategy:(GeShuStatReportStrategyType) reportStrategy;

/**
 获取上报策略
 */
+ (GeShuStatReportStrategyType)getReportStrategy;

/**
 上报策略为 PERIOD 时发送间隔，单位分钟，默认一天（60分钟）
 */
+ (void)setPeriodMinutes:(NSUInteger) periodMinutes;

/**
 统计上报策略为 BATCH 时，触发上报时最小缓存消息数，默认32条
 */
+ (void)setMinBatchReportNumber:(NSUInteger) batchNum;

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
