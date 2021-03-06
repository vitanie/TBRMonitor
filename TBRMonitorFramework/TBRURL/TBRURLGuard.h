//
//  TBRURLGuard.h
//
//  负责请求数据的收集并统计
//
//  Created by huanwh on 16/4/13.
//  Copyright © 2016年 huanwh. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^TBRURLChangeHandle)(NSDictionary * badUrl);

/**
 *  ## 统计URL 业务。包含 流量计算、请求成功次数、失败请求列表，收到失败的URL是通知观察者
 */
@interface TBRURLGuard : NSObject
{
    double recieveLength;//网络消耗
}
/**
 *  收到 失败URL时，通知实现 errorUrlChangeBlock 的观察者
 */
@property(nonatomic, copy)TBRURLChangeHandle errorUrlChangeBlock;

///失败URL汇总列表，只读
@property(nonatomic, strong, readonly) NSMutableArray * errorUrlList;

@property(nonatomic, assign, readonly) NSInteger coutnOfSucessRequest;
@property(nonatomic, assign, readonly) NSInteger countOfTotalRequest;
/**
 *  创建唯一 URL统计类
 *
 *  @return 唯一URL统计类 TBRURLGuard 实例
 */
+(instancetype)sharInstance;
/**
 *  添加网络异常的  dictionary Of BadUrl
 *
 *  @param key 异常URL dictionay
 */
+(void)addErrorUrlDictionay:(NSDictionary *)dictionaryOfBadUrl;
/** 添加监听网络失败 监听者
 *
 *
 *  @param errorUrlChangeBlock 网络失败回调
 */
+(void)observerErrorUrlChange:(TBRURLChangeHandle)errorUrlChangeBlock;
#pragma mark -  成功率
/**
 *  消耗流量递增
 */
+(void)increaseTotalRequestCount;
/**
 *  返回 URL 总请求量
 *
 *  @return URL总请求量
 */
+(NSInteger)countOfTotalRequest;
#pragma mark -  流量
/**
 *  记录网络消耗
 *
 *  @param length 当次网络消耗长度
 */
+(void)appendRecieveLength:(double)length;
/**
 *  获取 统计网络消耗总流量
 */
+(double)networkRecieveDataLenght;
/**
 *  重新计算网络消耗
 */
+(void)reset;
@end

/**
 *  URL 失败后 发送通知，和 observerErrorUrlChange 同时触发
 */
extern NSString * const TBRURLErrorStateChangedNotification;