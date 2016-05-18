//
//  @file SCLFlicManagerSimulator.m
//  @framework fliclib
//
//  Created by Anton Meier on 2016-05-17.
//  Copyright (c) 2016 Shortcut Labs. All rights reserved.
//

#import "SCLFlicManagerSimulator.h"
#if TARGET_OS_SIMULATOR

@interface SCLFlicManager ()

@property (nonatomic, strong) NSMutableDictionary<NSUUID *, SCLFlicButton *> *buttonDictionary;

@end

@interface SCLFlicButton ()

- (instancetype) init;

@end

@implementation SCLFlicManager

static SCLFlicManager *_sharedManager = nil;

+ (SCLFlicManager *) sharedManager; {
    return _sharedManager;
}

+ (instancetype _Nullable) configureWithDelegate:(id<SCLFlicManagerDelegate> _Nullable) delegate defaultButtonDelegate: (id<SCLFlicButtonDelegate> _Nullable) buttonDelegate appID: (NSString * _Nonnull) appID appSecret: (NSString * _Nonnull) appSecret backgroundExecution: (BOOL) bExecution; {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedManager = [[SCLFlicManager alloc] initWithDelegate:delegate buttonDelegate:buttonDelegate];
        if ([SCLFlicManager sharedManager].delegate && [[SCLFlicManager sharedManager].delegate respondsToSelector:@selector(flicManagerDidRestoreState:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{ [[SCLFlicManager sharedManager].delegate flicManagerDidRestoreState:[SCLFlicManager sharedManager]]; });
        }
        if ([SCLFlicManager sharedManager].delegate && [[SCLFlicManager sharedManager].delegate respondsToSelector:@selector(flicManager:didChangeBluetoothState:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{ [[SCLFlicManager sharedManager].delegate flicManager:[SCLFlicManager sharedManager] didChangeBluetoothState:[SCLFlicManager sharedManager].bluetoothState]; });
        }
    });
    
    return _sharedManager;
}

- (instancetype) initWithDelegate: (id<SCLFlicManagerDelegate> _Nullable) delegate buttonDelegate: (id<SCLFlicButtonDelegate> _Nullable) buttonDelegate {
    self = [super init];
    if ( self != nil ) {
        NSLog(@"SCLFlicManagerSimulator init");
        _enabled = YES;
        _delegate = delegate;
        _buttonDictionary = [NSMutableDictionary dictionary];
        _defaultButtonDelegate = buttonDelegate;
        _bluetoothState = SCLFlicManagerBluetoothStatePoweredOn;
        return self;
    }
    return nil;
}

- (void) forgetButton:(SCLFlicButton *) button {
    if ([self.buttonDictionary objectForKey:button.buttonIdentifier]) {
        [self.buttonDictionary removeObjectForKey:button.buttonIdentifier];
        if (self.delegate && [self.delegate respondsToSelector:@selector(flicManager:didForgetButton:error:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicManager:self didForgetButton:button.buttonIdentifier error:nil]; });
        }
    }
}

- (void) disable {
    _enabled = NO;
}

- (void) enable {
    _enabled = YES;
}

- (NSDictionary*) knownButtons {
    return [self.buttonDictionary copy];
}

- (void) onLocationChange {
    
}

- (BOOL) handleOpenURL: (NSURL * _Nonnull) url; {
    return YES;
}

- (void) grabFlicFromFlicAppWithCallbackUrlScheme: (NSString *) scheme {
    SCLFlicButton *button = [[SCLFlicButton alloc] init];
    button.delegate = self.defaultButtonDelegate;
    [self.buttonDictionary setObject:button forKey:button.buttonIdentifier];
    if (self.delegate && [self.delegate respondsToSelector:@selector(flicManager:didGrabFlicButton:withError:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicManager:self didGrabFlicButton:button withError:nil]; });
    }
}

@end

#endif
