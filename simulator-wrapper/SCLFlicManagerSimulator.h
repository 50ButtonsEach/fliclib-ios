//
//  @file SCLFlicManagerSimulator.h
//  @framework fliclib
//
//  Created by Anton Meier on 2016-05-17.
//  Copyright (c) 2016 Shortcut Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCLFlicButtonSimulator.h"

typedef NS_ENUM(NSInteger, SCLFlicManagerBluetoothState) {
    SCLFlicManagerBluetoothStatePoweredOn = 0,
    SCLFlicManagerBluetoothStatePoweredOff,
    SCLFlicManagerBluetoothStateResetting,
    SCLFlicManagerBluetoothStateUnsupported,
    SCLFlicManagerBluetoothStateUnauthorized,
    SCLFlicManagerBluetoothStateUnknown,
};

@protocol SCLFlicManagerDelegate;

@interface SCLFlicManager : NSObject {
    
}

@property(weak, nonatomic, nullable) id<SCLFlicManagerDelegate> delegate;
@property(weak, nonatomic, nullable) id<SCLFlicButtonDelegate> defaultButtonDelegate;
@property (nonatomic, readonly) SCLFlicManagerBluetoothState bluetoothState;
@property (readonly, getter=isEnabled) BOOL enabled;

+ (instancetype _Nullable) sharedManager;
+ (instancetype _Nullable) configureWithDelegate:(id<SCLFlicManagerDelegate> _Nullable) delegate defaultButtonDelegate: (id<SCLFlicButtonDelegate> _Nullable) buttonDelegate appID: (NSString * _Nonnull) appID appSecret: (NSString * _Nonnull) appSecret backgroundExecution: (BOOL) bExecution;
- (NSDictionary<NSUUID *, SCLFlicButton *> * _Nonnull) knownButtons;
- (void) forgetButton:(SCLFlicButton * _Nonnull) button;
- (void) disable;
- (void) enable;
- (void) grabFlicFromFlicAppWithCallbackUrlScheme: (NSString * _Nonnull) scheme;
- (BOOL) handleOpenURL: (NSURL * _Nonnull) url;
- (void) onLocationChange;

@end


@protocol SCLFlicManagerDelegate <NSObject>

@required

- (void) flicManager:(SCLFlicManager * _Nonnull) manager didGrabFlicButton:(SCLFlicButton * _Nullable) button withError: (NSError * _Nullable) error;

@optional

- (void) flicManager:(SCLFlicManager * _Nonnull) manager didChangeBluetoothState: (SCLFlicManagerBluetoothState) state;
- (void) flicManagerDidRestoreState:(SCLFlicManager * _Nonnull) manager;
- (void) flicManager:(SCLFlicManager * _Nonnull) manager didForgetButton:(NSUUID * _Nonnull) buttonIdentifier error:(NSError * _Nullable)error;

@end
