//
//  @file SCLFlicButtonSimulator.m
//  @framework fliclib
//
//  Created by Anton Meier on 2016-06-17.
//  Copyright (c) 2016 Shortcut Labs. All rights reserved.
//

#import "SCLFlicButtonSimulator.h"
#if TARGET_OS_SIMULATOR

#import <UIKit/UIKit.h>

@implementation SCLFlicButton

- (instancetype) init {
    self = [super init];
    if ( self != nil ) {
        NSLog(@"SCLFlicButtonSimulator init");
        _isReady = YES;
        _lowLatency = NO;
        _buttonIdentifier = [NSUUID UUID];
        _name=[NSString stringWithFormat:@"FLIC: %@", _buttonIdentifier.UUIDString ];
        _connectionState=SCLFlicButtonConnectionStateConnected;
        _triggerBehavior = SCLFlicButtonTriggerBehaviorClickAndHold;
        _pressCount = 0;
        _buttonPublicKey = _buttonIdentifier.UUIDString;
        _userAssignedName = @"My Flic";
        _color = [UIColor whiteColor];
        
        // Uncomment to recieve a button down 2 seconds after grab.
        /*
        __weak SCLFlicButton *flicButton = self;
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            if ([flicButton.delegate respondsToSelector:@selector(flicButton:didReceiveButtonDown:age:)]) {
                dispatch_async(dispatch_get_main_queue(), ^{ [flicButton.delegate flicButton:self didReceiveButtonDown:NO age:0]; });
            }
        });
        */
        return self;
    }
    return nil;
}

- (void) connect {
    _connectionState = SCLFlicButtonConnectionStateConnected;
    if ([self.delegate respondsToSelector:@selector(flicButtonDidConnect:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicButtonDidConnect:self]; });
    }
    _isReady = YES;
    if ([self.delegate respondsToSelector:@selector(flicButtonIsReady:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicButtonIsReady:self]; });
    }
}

- (void) disconnect {
    _connectionState = SCLFlicButtonConnectionStateConnected;
    _isReady = NO;
    if ([self.delegate respondsToSelector:@selector(flicButton:didDisconnectWithError:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicButton:self didDisconnectWithError:nil]; });
    }
}

- (void) indicateLED: (SCLFlicButtonLEDIndicateCount) count {
    
}

- (void) readRSSI {
    if ([self.delegate respondsToSelector:@selector(flicButton:didUpdateRSSI:error:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{ [self.delegate flicButton:self didUpdateRSSI:[NSNumber numberWithInt: -1] error:nil]; });
    }
}

@end

#endif
