//
//  WQGeneralMacro.h
//  WQGeneralMacro
//
//  Created by iOS on 17/11/14.
//  Copyright © 2017年 shenbao. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/********************************** 单例宏定义 **********************************/
#pragma mark -- 单例宏定义
#define kWQSingleH() + (instancetype)shareInstance;
#if __has_feature(objc_arc)
#define kWQSingleM() \
static id _instance; \
+ (instancetype)allocWithZone:(struct _NSZone *)zone { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken,^{ \
        _instance = [super allocWithZone:zone]; \
    }); \
    return _instance; \
} \
\
+ (instancetype)shareInstance { \
    return [[self alloc] init]; \
} \
\
- (id)copyWithZone:(NSZone *)zone { \
    return _instance; \
} \
\
- (id)mutableCopyWithZone:(NSZone *)zone { \
    return _instance; \
}
#else
#define kSingleM() \
static id _instance; \
+ (instancetype)allocWithZone:(struct _NSZone *)zone { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        _instance = [super allocWithZone:zone]; \
    }); \
    return _instance; \
} \
\
+ (instancetype)shareInstance { \
    return [[self alloc]init]; \
} \
\
- (id)copyWithZone:(NSZone *)zone { \
    return _instance; \
} \
\
- (id)mutableCopyWithZone:(NSZone *)zone { \
    return _instance; \
} \
-(oneway void)release { \
} \
\
-(instancetype)retain { \
    return _instance; \
} \
\
-(NSUInteger)retainCount { \
    return MAXFLOAT; \
}
#endif

/********************************** 颜色宏定义 **********************************/
#pragma mark -- 颜色宏定义
#define kWQHsb(h, s, b) [UIColor colorWithHue:h/360.0f \
                                   saturation:s/100.0f \
                                   brightness:b/100.0f \
                                        alpha:1.0]
#define kWQRgba(r, g, b, a) [UIColor colorWithRed:(r)/255.0 \
                                            green:(g)/255.0 \
                                             blue:(b)/255.0 \
                                            alpha:(a)]
#define kWQHexColor(c, a) [UIColor colorWithRed:(((c >> 16) & 0xFF) / 255.0) \
                                          green:(((c >> 8) & 0xFF) / 255.0) \
                                           blue:(((c) & 0xFF)/ 255.0) \
                                          alpha:a]

/********************************** 通知宏定义 **********************************/
#pragma mark -- 通知宏定义
#define kWQNotiObserver(observer, SEL, key, anObject) [[NSNotificationCenter defaultCenter] addObserver:observer \
                                                                                               selector:SEL \
                                                                                                   name:key \
                                                                                                 object:anObject]
#define kWQNotiPost(key, anObject, aUserInfo) [[NSNotificationCenter defaultCenter] postNotificationName:key \
                                                                                                  object:anObject \
                                                                                                userInfo:aUserInfo]
#define kWQNotiRemove(observer, key, anObject) [[NSNotificationCenter defaultCenter] removeObserver:observer \
                                                                                               name:key \
                                                                                             object:anObject]

/********************************** 屏幕宽高宏 **********************************/
#pragma mark -- 屏幕宽高宏
#define kWQSWidth [UIScreen mainScreen].bounds.size.width
#define kWQSHeight [UIScreen mainScreen].bounds.size.height

/********************************** 主线程执行 **********************************/
#pragma mark -- 主线程执行
#define kWQExecuteOnMain(block) !block ? : [[NSThread currentThread] isMainThread] ? block() : dispatch_async(dispatch_get_main_queue(), ^{block();})

/********************************** 沙盒路径  **********************************/
#pragma mark -- 沙盒路径
#define kWQLibraryPath NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES)[0]
#define kWQDocumentPath NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0]
#define kWQCachePath NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)[0]
#define kWQTmpPath NSTemporaryDirectory()

/********************************** 弱变量转换 **********************************/
#define WS(sself) __weak __typeof(&*self)sself = self


/********************************** 常用工具类 **********************************/
#pragma mark -- 常用工具类
@interface WQInstrument : NSObject
/**
 计算文字长度
 
 @pragma text 文本
 @pragma size 限定大小
 @pragma font 文本字体
 */
+ (CGSize)calculateSizeWithText:(NSString *)text
                constrainedSize:(CGSize)size
                           font:(UIFont *)font;
/**
 获得当前控制器
 */
+ (UIViewController *)currentViewController;

/**
 获得当前时间 格式为 YYYY-MM-dd HH:mm:ss
 */
+ (NSDate *)currentTimes;

/**
 获得当前时区时间戳,精确到秒
 */
+ (NSTimeInterval)currentTimeTimestamp;

/**
 获取指定时间时间戳
 */
+ (NSTimeInterval)timestampWithDate:(NSDate *)date;

/**
 比较两个时间大小,精确到秒
 @return 比较结果 { NSOrderedAscending = -1L, NSOrderedSame, NSOrderedDescending }
 */
+ (NSComparisonResult)date:(NSDate *)oneDay
                   compare:(NSDate *)anotherDay;
/**
 修改图片颜色
 */
+ (UIImage *)image:(UIImage *)image withTintColor:(UIColor *)tintColor;
+ (UIImage *)image:(UIImage *)image withGradientTintColor:(UIColor *)tintColor;

/**
 生成一张 color 色的 image
 
 @pragma color 生成图片的颜色
 @pragma size 生成图片的大小
 */
+ (UIImage *)imageWithColor:(UIColor *)color
                       size:(CGSize)size;
/**
 两张图片合成一张
 
 @pragma baseMap  底图
 @pragma baseSize 合成后底图大小
 @pragma subMap   子图
 @pragma subMapRect 子图在底图的位置
 */
+ (UIImage *)baseMap:(UIImage *)baseMap
            baseSize:(CGSize)baseSize
           addSubMap:(UIImage *)subMap
            withRect:(CGRect)subMapRect;
/**
 解析颜色 color
 
 @pragma color 解析颜色
 @pragma r 解析后 red
 @pragma g 解析后 green
 @pragma b 解析后 blue
 @pragma a 解析后 alpha
 */
+ (void)analysisColor:(UIColor *)color
                  red:(int *)r
                green:(int *)g
                 blue:(int *)b
                alpha:(CGFloat *)a;
@end
NS_ASSUME_NONNULL_END
