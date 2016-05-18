//
//  @file SCLFlicButtonSimulator.h
//  @framework fliclib
//
//  Created by Anton Meier on 2016-06-17.
//  Copyright (c) 2016 Shortcut Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
@class UIColor;

typedef NS_ENUM(NSInteger, SCLFlicButtonConnectionState) {
    SCLFlicButtonConnectionStateConnected = 0,
    SCLFlicButtonConnectionStateConnecting,
    SCLFlicButtonConnectionStateDisconnected,
    SCLFlicButtonConnectionStateDisconnecting,
};

typedef NS_ENUM(NSInteger, SCLFlicButtonLEDIndicateCount) {
    SCLFlicButtonLEDIndicateCount1 = 1,
    SCLFlicButtonLEDIndicateCount2,
    SCLFlicButtonLEDIndicateCount3,
    SCLFlicButtonLEDIndicateCount4,
    SCLFlicButtonLEDIndicateCount5,
};

typedef NS_ENUM(NSInteger, SCLFlicButtonTriggerBehavior) {
    SCLFlicButtonTriggerBehaviorClickAndHold = 0,
    SCLFlicButtonTriggerBehaviorClickAndDoubleClick,
    SCLFlicButtonTriggerBehaviorClickAndDoubleClickAndHold,
};

typedef NS_ENUM(NSInteger, SCLFlicError) {
    SCLFlicErrorUnknown = 0,
    SCLFlicErrorCouldNotCompleteTask = 1,
    SCLFlicErrorConnectionFailed = 2,
    SCLFlicErrorCouldNotUpdateRSSI = 3,
    SCLFlicErrorButtonIsPrivate = 10,
    SCLFlicErrorCryptographicFailure = 11,
    SCLFlicErrorMissingData = 13,
    SCLFlicErrorInvalidSignature = 14,
    SCLFlicErrorButtonAlreadyGrabbed = 15,
    SCLFlicErrorBluetoothErrorUnknown = 100,
    SCLFlicErrorBluetoothErrorInvalidParameters = 101,
    SCLFlicErrorBluetoothErrorInvalidHandle = 102,
    SCLFlicErrorBluetoothErrorNotConnected = 103,
    SCLFlicErrorBluetoothErrorOutOfSpace = 104,
    SCLFlicErrorBluetoothErrorOperationCancelled = 105,
    SCLFlicErrorBluetoothErrorConnectionLost = 106,
    SCLFlicErrorBluetoothErrorPeripheralDisconnected = 107,
    SCLFlicErrorBluetoothErrorUUIDNotAllowed = 108,
    SCLFlicErrorBluetoothErrorAlreadyAdvertising = 109,
    SCLFlicErrorBluetoothErrorConnectionFailed = 110,
    SCLFlicErrorBluetoothErrorConnectionLimitReached = 111,
    SCLFlicErrorFlicRefusedConnection = 200,
};

@protocol SCLFlicButtonDelegate;

@interface SCLFlicButton : NSObject {
    
}

@property(weak, nonatomic, nullable) id<SCLFlicButtonDelegate> delegate;
@property (readonly, nonatomic, strong, nonnull) NSUUID *buttonIdentifier;
@property (readonly, nonatomic, strong, nonnull) NSString *buttonPublicKey;
@property (atomic, readonly, strong, nonnull) NSString *name;
@property (atomic, readonly, strong, nonnull) UIColor *color;
@property (atomic, readonly, strong, nonnull) NSString *userAssignedName;
@property (atomic, readonly) SCLFlicButtonConnectionState connectionState;
@property (nonatomic, readwrite) BOOL lowLatency;
@property (nonatomic, readwrite) SCLFlicButtonTriggerBehavior triggerBehavior;
@property (nonatomic, readonly) int pressCount;
@property (readonly) BOOL isReady;


- (void) connect;
- (void) disconnect;
- (void) indicateLED: (SCLFlicButtonLEDIndicateCount) count;
- (void) readRSSI;

@end

@protocol SCLFlicButtonDelegate <NSObject>

@required

@optional

- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonDown:(BOOL) queued age: (NSInteger) age;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonUp:(BOOL) queued age: (NSInteger) age;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonClick:(BOOL) queued age: (NSInteger) age;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonDoubleClick:(BOOL) queued age: (NSInteger) age;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonHold:(BOOL) queued age: (NSInteger) age;
- (void) flicButtonDidConnect:(SCLFlicButton * _Nonnull) button;
- (void) flicButtonIsReady:(SCLFlicButton * _Nonnull) button;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didDisconnectWithError:(NSError * _Nullable) error;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didFailToConnectWithError:(NSError * _Nullable) error;
- (void) flicButton:(SCLFlicButton * _Nonnull) button didUpdateRSSI:(NSNumber * _Nonnull) RSSI error:(NSError * _Nullable) error;

@end

