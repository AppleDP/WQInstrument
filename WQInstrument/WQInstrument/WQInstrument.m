//
//  WQGeneralMacro.m
//  WQGeneralMacro
//
//  Created by iOS on 17/11/14.
//  Copyright © 2017年 shenbao. All rights reserved.
//

#import "WQInstrument.h"

@implementation WQInstrument
#pragma mark -- 公有方法
+ (CGSize)calculateSizeWithText:(NSString *)text
                constrainedSize:(CGSize)size
                           font:(UIFont *)font {
    CGSize result = [text boundingRectWithSize:size
                                       options:NSStringDrawingUsesLineFragmentOrigin
                                    attributes:@{NSFontAttributeName : font}
                                       context:nil].size;
    return result;
}

+ (UIViewController *)currentViewController {
    UIViewController *result = nil; UIWindow * window = [[UIApplication sharedApplication] keyWindow];
    if (window.windowLevel != UIWindowLevelNormal) {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(UIWindow * tmpWin in windows) {
            if (tmpWin.windowLevel == UIWindowLevelNormal) {
                window = tmpWin; break;
            }
        }
    }
    id nextResponder = nil;
    UIViewController *appRootVC=window.rootViewController;
    if (appRootVC.presentedViewController) {
        nextResponder = appRootVC.presentedViewController;
    }else{
        UIView *frontView = [[window subviews] objectAtIndex:0];
        nextResponder = [frontView nextResponder];
    }
    if ([nextResponder isKindOfClass:[UITabBarController class]]){
        UITabBarController * tabbar = (UITabBarController *)nextResponder;
        UINavigationController * nav = (UINavigationController *)tabbar.viewControllers[tabbar.selectedIndex];
        result=nav.childViewControllers.lastObject;
    }else if ([nextResponder isKindOfClass:[UINavigationController class]]){
        UIViewController * nav = (UIViewController *)nextResponder;
        result = nav.childViewControllers.lastObject;
    }else{
        result = nextResponder;
    }
    return result;
}

+ (NSDate *)currentTimes {
    NSDate *date = [NSDate date];
    //设置源日期时区
    NSTimeZone* sourceTimeZone = [NSTimeZone timeZoneWithAbbreviation:@"UTC"];
    //或GMT
    //设置转换后的目标日期时区
    NSTimeZone* destinationTimeZone = [NSTimeZone localTimeZone];
    //得到源日期与世界标准时间的偏移量
    NSInteger sourceGMTOffset = [sourceTimeZone secondsFromGMTForDate:date];
    //目标日期与本地时区的偏移量
    NSInteger destinationGMTOffset = [destinationTimeZone secondsFromGMTForDate:date];
    //得到时间偏移量的差值
    NSTimeInterval interval = destinationGMTOffset - sourceGMTOffset;
    //转为现在时间
    NSDate* destinationDateNow = [[NSDate alloc] initWithTimeInterval:interval sinceDate:date];
    return destinationDateNow;
}

+ (NSTimeInterval)currentTimeTimestamp {
    return [self timestampWithDate:[self currentTimes]];
}

+ (NSTimeInterval)timestampWithDate:(NSDate *)date {
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init] ;
    [formatter setDateStyle:NSDateFormatterMediumStyle];
    [formatter setTimeStyle:NSDateFormatterShortStyle];
    [formatter setDateFormat:@"yyyy-MM-dd hh:mm:ss"];
    NSTimeZone *zone = [NSTimeZone systemTimeZone];
    [formatter setTimeZone:zone];
    NSTimeInterval timestamp = [date timeIntervalSince1970];
    return timestamp;
}

+ (NSComparisonResult)date:(NSDate *)oneDay
                   compare:(NSDate *)anotherDay {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd hh:mm:ss"];
    NSString *oneDayStr = [dateFormatter stringFromDate:oneDay];
    NSString *anotherDayStr = [dateFormatter stringFromDate:anotherDay];
    NSDate *dateA = [dateFormatter dateFromString:oneDayStr];
    NSDate *dateB = [dateFormatter dateFromString:anotherDayStr];
    NSComparisonResult result = [dateA compare:dateB];
    return result;
}

+ (UIImage *)image:(UIImage *)image
     withTintColor:(UIColor *)tintColor {
    return [self image:image
         withTintColor:tintColor
             blendMode:kCGBlendModeDestinationIn];
}

+ (UIImage *)image:(UIImage *)image
withGradientTintColor:(UIColor *)tintColor {
    return [self image:image
         withTintColor:tintColor
             blendMode:kCGBlendModeOverlay];
}

+ (UIImage *)imageWithColor:(UIColor *)color
                       size:(CGSize)size {
    CGRect rect = CGRectMake(0.0f, 0.0f, size.width, size.height);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

+ (UIImage *)baseMap:(UIImage *)baseMap
            baseSize:(CGSize)baseSize
           addSubMap:(UIImage *)subMap
            withRect:(CGRect)subMapRect {
    UIGraphicsBeginImageContext(baseSize);
    [baseMap drawInRect:CGRectMake(0, 0, baseSize.width, baseSize.height)];
    [subMap drawInRect:subMapRect];
    UIImage *result = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return result;
}

+ (void)analysisColor:(UIColor *)color
                  red:(int *)r
                green:(int *)g
                 blue:(int *)b
                alpha:(CGFloat *)a {
    const CGFloat *components = CGColorGetComponents(color.CGColor);
    *r = components[0]*255;
    *g = components[1]*255;
    *b = components[2]*255;
    *a = components[3];
}


#pragma mark -- 私有方法
+ (UIImage *)image:(UIImage *)image
     withTintColor:(UIColor *)tintColor
         blendMode:(CGBlendMode)blendMode{
    UIGraphicsBeginImageContextWithOptions(image.size, NO, 0.0f);
    [tintColor setFill];
    CGRect bounds = CGRectMake(0, 0, image.size.width, image.size.height);
    UIRectFill(bounds);
    [image drawInRect:bounds blendMode:blendMode alpha:1.0f];
    if (blendMode != kCGBlendModeDestinationIn) {
        [image drawInRect:bounds
                blendMode:kCGBlendModeDestinationIn alpha:1.0f];
    }
    UIImage *tintedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return tintedImage;
}
@end
