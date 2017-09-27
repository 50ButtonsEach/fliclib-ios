//
//  @file SCLFlicButton.h
//  @framework fliclib
//
//  Created by Anton Meier on 2014-06-18.
//  Copyright (c) 2017 Shortcut Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
@class UIColor;

/*!
 *  @enum SCLFlicButtonConnectionState
 *
 *  @discussion Represents the diffrent connection states that a flic can be in at any given time.
 *
 */
typedef NS_ENUM(NSInteger, SCLFlicButtonConnectionState) {
    /**
     * The flic is currently connected. This means that the iOS device has an active link with the flic and that data can be sent in both
     * directions provided that it has also been verified, notified by the <code>flicButtonIsReady:</code> callback.
     */
    SCLFlicButtonConnectionStateConnected = 0,
    /**
     * The flic is currently connecting. This means that the iOS device is either in the process of establishing a link with flic or
     * that it is waiting for flic to come within proximity so that such process can be initiated.
     */
    SCLFlicButtonConnectionStateConnecting,
    /**
     * The flic is currently disconnected.
     */
    SCLFlicButtonConnectionStateDisconnected,
    /**
     * The flic is currently disconnecting.
     */
    SCLFlicButtonConnectionStateDisconnecting,
};

/*!
 *  @enum SCLFlicButtonLEDIndicateCount
 *
 *  @discussion Represents the indication count, meaning how many times the LED will fade when using the <code>indicateLED:</code> method.
 *              Please be mindful of battery usage.
 *
 */
typedef NS_ENUM(NSInteger, SCLFlicButtonLEDIndicateCount) {
    /**
     * The LED will fade 1 time.
     */
    SCLFlicButtonLEDIndicateCount1 = 1,
    /**
     * The LED will fade 2 times.
     */
    SCLFlicButtonLEDIndicateCount2,
    /**
     * The LED will fade 3 times.
     */
    SCLFlicButtonLEDIndicateCount3,
    /**
     * The LED will fade 4 times.
     */
    SCLFlicButtonLEDIndicateCount4,
    /**
     * The LED will fade 5 times.
     */
    SCLFlicButtonLEDIndicateCount5,
};

/*!
 *  @enum SCLFlicButtonTriggerBehavior
 *
 *  @discussion Represents the different trigger event behaviors that can be configured on the flic.
 *              The buttonUp and buttonDown events will be active no matter which of these alternatives you choose.
 *
 */
typedef NS_ENUM(NSInteger, SCLFlicButtonTriggerBehavior) {
    /**
     * Used to distinguish between only click and hold.
     * <br/><br/>
     * Click will be fired when the button is released if it was pressed for maximum 1 second.
     * Otherwise, hold will be fired 1 second after the button was pressed. Click will then not be fired upon release.
     * Since this option will only distinguish between click and hold it does not have to take double click into consideration.
     * This means that the click event can be sent immediately on button release rather than to wait for a possible double click.
     * <br/><br/>
     * Note: this will be the default behavior.
     */
    SCLFlicButtonTriggerBehaviorClickAndHold = 0,
    /**
     * Used to distinguish between only single click and double click.
     * <br/><br/>
     * Double click will be registered if the time between two button down events was at most 0.5 seconds.
     * The double click event will then be fired upon button release.
     * If the time was more than 0.5 seconds, a single click event will be fired;
     * either directly upon button release if the button was down for more than 0.5 seconds, or after 0.5 seconds
     * if the button was down for less than 0.5 seconds.
     * <br/><br/>
     * To summarize this, a small delay will be added to the click event (if it was released within 0.5 s) in order to see if a
     * double click will happen next. This ensures that a click event will not be sent prior to the double click.
     */
    SCLFlicButtonTriggerBehaviorClickAndDoubleClick,
    /**
     * Used to distinguish between single click, double click and hold.
     * <br/><br/>
     * If the time between the first button down and button up event was more than 1 second, a hold event will be fired.
     * <br/><br/>
     * Else, double click will be fired if the time between two button down events was at most 0.5 seconds.
     * The double click event will then be fired upon button release.
     * If the time was more than 0.5 seconds, a single click event will be fired;
     * either directly upon button release if the button was down for more than 0.5 seconds,
     * or after 0.5 seconds if the button was down for less than 0.5 seconds.
     * <br/><br/>
     * Note: Three fast consecutive clicks means one double click and then one single click.
     * Four fast consecutive clicks means two double clicks.
     */
    SCLFlicButtonTriggerBehaviorClickAndDoubleClickAndHold,
    /**
     * This mode will only send click and the event will be sent directly on buttonDown. This will be the same as listening for
     * buttonDown. This click mode can be used if you wish to have the lowes possible latency on the click event.
     */
    SCLFlicButtonTriggerBehaviorClick,
};

/*!
 *  @enum SCLFlicError
 *
 *  @discussion These enums represents the different error codes that can be sent on both the SCLFlicButton and SCLFlicManager classes.
 *
 */
typedef NS_ENUM(NSInteger, SCLFlicError) {
    /**
     * An error has occurred.
     */
    SCLFlicErrorUnknown = 0,
    /**
     * General error code that can be sent to let you know that a started task did not complete.
     */
    SCLFlicErrorCouldNotCompleteTask = 1,
    /**
     * If a connection to a button failed for unknown reasons. This could for example be if it is brought out of range during a connection sequense.
     */
    SCLFlicErrorConnectionFailed = 2,
    /**
     * The RSSI value could not be read.
     */
    SCLFlicErrorCouldNotUpdateRSSI = 3,
    /**
     * If you try to access a button that is currently being used with another device, or another app on the same iOS device.
     */
    SCLFlicErrorButtonIsPrivate = 10,
    /**
     * A crypthographic error has occurred.
     */
    SCLFlicErrorCryptographicFailure = 11,
    /**
     * The request did not contain enough data to be completed.
     */
    SCLFlicErrorMissingData = 13,
    /**
     * The signature over the data is not valid. The data might be corrupt.
     */
    SCLFlicErrorInvalidSignature = 14,
    /**
     * You are trying to grab a Flic button that you have already grabbed before.
     */
    SCLFlicErrorButtonAlreadyGrabbed = 15,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorUnknown = 100,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorInvalidParameters = 101,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorInvalidHandle = 102,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorNotConnected = 103,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorOutOfSpace = 104,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorOperationCancelled = 105,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorConnectionLost = 106,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorPeripheralDisconnected = 107,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorUUIDNotAllowed = 108,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorAlreadyAdvertising = 109,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorConnectionFailed = 110,
    /**
     * Bluetooth specific error
     */
    SCLFlicErrorBluetoothErrorConnectionLimitReached = 111,
    /**
     * Connection was refused by Flic
     */
    SCLFlicErrorFlicRefusedConnection = 200,
};

@protocol SCLFlicButtonDelegate;

/*!
 *  @class SCLFlicButton
 *
 *  @discussion An instance of this class represents a physical flic.
 *              All commands will be directly passed to the physical flic and any events occurring on the flic will be passed along
 *              using the specified delegate methods.
 *
 */
@interface SCLFlicButton : NSObject {
    
}

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive events related to this particular flic.
 *
 */
@property(weak, nonatomic, nullable) id<SCLFlicButtonDelegate> delegate;

/*!
 *  @property buttonIdentifier
 *
 *  @discussion The virtual ID of the flic.
 *
 */
@property (readonly, nonatomic, strong, nonnull) NSUUID *buttonIdentifier;

/*!
 *  @property buttonPublicKey
 *
 *  @discussion The public key of the flic. This in the key that is used to identify the flic on our backend.
 *
 */
@property (readonly, nonatomic, strong, nonnull) NSString *buttonPublicKey;

/*!
 *  @property name
 *
 *  @discussion The Bluetooth device name of the flic button.
 *
 */
@property (atomic, readonly, strong, nonnull) NSString *name;

/*!
 *  @property color
 *
 *  @discussion The actual color of the grabbed Flic button. If for some reason the real color is not available, such as if the button
 *              was already grabbed with an earlier version of fliclib, then the color will default to white.
 *
 */
@property (atomic, readonly, strong, nonnull) UIColor *color;

/*!
 *  @property userAssignedName
 *
 *  @discussion This is the user assigned name of the Flic button that is assigned and displayed in the Flic App.
 *
 */
@property (atomic, readonly, strong, nonnull) NSString *userAssignedName;

/*!
 *  @property state
 *
 *  @discussion The current state of the flic.
 *
 */
@property (atomic, readonly) SCLFlicButtonConnectionState connectionState;

/*!
 *  @property lowLatency
 *
 *  @discussion The latency setting for this button. If you set this to YES then you will get lower latency on the click events when your
 *              app is in the foreground. As soon as the app leaves the foreground it will be set back to the regular latency setting.
 *              Please only use this if you have a very good reason for it, such as if you are designing a foreground game that requires it.
 *              Battery consumption will increase with this activated.
 *
 */
@property (nonatomic, readwrite) BOOL lowLatency;

/*!
 *  @property triggerBehavior
 *
 *  @discussion This property specifies how the flic press events should be handled. You are allowed to change this property any time you want.
 *              Take a look at SCLFlicButtonTriggerBehavior to see the options available.
 *
 */
@property (nonatomic, readwrite) SCLFlicButtonTriggerBehavior triggerBehavior;

/*!
 *  @property pressCount
 *
 *  @discussion This property specifies how many times the flic has been toggled at any given time. This will register all down events
 *              as well as the up events, which means that if you want to know how many times it has been clicked then you have to divide
 *              this number by two. Also, this property will always contain the last known registered value, meaning that if the flic
 *              has been pressed while not being within proximity then the property will of course not be up to date. It will be updated
 *              as soon as the flic connects the next time. Important notice: Even though this value is represented by an int the internal
 *              counter only consists of 3 bytes meaning that the counter will rollover at 0xffffff (16777215). However, it is highly unlikely
 *              that anyone will ever reach those numbers. The presscounter will be reset if a factory reset is done on the physical flic button.
 *
 */
@property (nonatomic, readonly) int pressCount;

/*!
 *  @property isReady
 *
 *  @discussion This property lets you know wether the Flic is ready or not.
 *
 */
@property (readonly) BOOL isReady;

/*!
 *  @method connect:
 *
 *  @discussion		Attempts to connect the flic. If the flic is not available, due to either being out of range or not advertising,
 *                  then the flic will be connected once it becomes available since this call will not time out, also called a
 *                  pending connection. It can be canceled by calling the <code>disconnect</code> method.
 *
 */
- (void) connect;

/*!
 *  @method disconnect:
 *
 *  @discussion		Disconnect a currently connected flic or cancel a pending connection.
 *
 */
- (void) disconnect;

/*!
 *  @method indicateLED:
 *
 *  @discussion     Use this method when you want to indicate something to the user by fading the LED. Be mindful with battery usage.
 *                  This will only work if the Flic is connected. To prevent unnecessary battery wase the maximum fade count is five.
 *
 *  @param count    Decides how many times the LED will indicate (fade)
 */
- (void) indicateLED: (SCLFlicButtonLEDIndicateCount) count;

/*!
 *  @method readRSSI
 *
 *  @discussion         A call to this method will read the RSSI (received signal strength indication) of the flic while it is currently connected.
 *                      A callback will be sent to the SCLFlicButton delegate once the value has been updated. This value is represented
 *                      in decibels and has an effective range from -100 to 0.
 *
 */
- (void) readRSSI;

@end

/*!
 *  @protocol SCLFlicButtonDelegate
 *
 *  @discussion         The delegate of a SCLFlicButton object must adopt the <code>SCLFlicButtonDelegate</code> protocol. There are not
 *                      any required delegate methods, but all are recommended for proper use of the Flic.
 *
 */
@protocol SCLFlicButtonDelegate <NSObject>

@required

@optional

/*!
 *  @method flicButton:didReceiveButtonDown:age:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param queued       This lets you know if the event is a queued event that happened before the flic connected or if it is a real time
 *                      event.
 *  @param age          The age of the trigger event in seconds. This is particularily important when receiving events that might have been
 *                      queued up on flic while it was out of range. The units is in seconds and will be rounded to the nearest second.
 *
 *  @discussion         The flic registered a button down event.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonDown:(BOOL) queued age: (NSInteger) age;

/*!
 *  @method flicButton:didReceiveButtonUp:age:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param queued       This lets you know if the event is a queued event that happened before the flic connected or if it is a real time
 *                      event.
 *  @param age          The age of the trigger event in seconds. This is particularily important when receiving events that might have been
 *                      queued up on flic while it was out of range. The units is in seconds and will be rounded to the nearest second.
 *
 *  @discussion         The flic registered a button up event.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonUp:(BOOL) queued age: (NSInteger) age;

/*!
 *  @method flicButton:didReceiveButtonClick:age:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param queued       This lets you know if the event is a queued event that happened before the flic connected or if it is a real time
 *                      event.
 *  @param age          The age of the trigger event in seconds. This is particularily important when receiving events that might have been
 *                      queued up on flic while it was out of range. The units is in seconds and will be rounded to the nearest second.
 *
 *  @discussion         The flic registered a button click event.
 *                      The behavior of this event depends on what SCLFlicButtonTriggerBehavior the triggerBehavior property is set to.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonClick:(BOOL) queued age: (NSInteger) age;

/*!
 *  @method flicButton:didReceiveButtonDoubleClick:age:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param queued       This lets you know if the event is a queued event that happened before the flic connected or if it is a real time
 *                      event.
 *  @param age          The age of the trigger event in seconds. This is particularily important when receiving events that might have been
 *                      queued up on flic while it was out of range. The units is in seconds and will be rounded to the nearest second.
 *
 *  @discussion         The flic registered a button double click event.
 *                      The behavior of this event depends on what SCLFlicButtonTriggerBehavior the triggerBehavior property is set to.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonDoubleClick:(BOOL) queued age: (NSInteger) age;

/*!
 *  @method flicButton:didReceiveButtonHold:age:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param queued       This lets you know if the event is a queued event that happened before the flic connected or if it is a real time
 *                      event.
 *  @param age          The age of the trigger event in seconds. This is particularily important when receiving events that might have been
 *                      queued up on flic while it was out of range. The units is in seconds and will be rounded to the nearest second.
 *
 *  @discussion         The flic registered a button hold event.
 *                      The behavior of this event depends on what SCLFlicButtonTriggerBehavior the triggerBehavior property is set to.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didReceiveButtonHold:(BOOL) queued age: (NSInteger) age;

/*!
 *  @method flicButtonDidConnect:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *
 *  @discussion         This delegate method is called every time the flic physically connected to the iOS device, regardless of the reason for it.
 *                      Keep in mind that you also have to wait for the <code>flicButtonIsReady:</code> before the flic is ready for use.
 *                      The <code>connectionState</code> is not guaranteed to switch to <code>SCLFlicButtonConnectionStateConnected</code> until
 *                      after the <code>flicButtonIsReady:</code> callback has arrived.
 *
 */
- (void) flicButtonDidConnect:(SCLFlicButton * _Nonnull) button;

/*!
 *  @method flicButtonIsReady:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *
 *  @discussion         This delegate method is called every time the flic has sucessfully connected and the autheticity has been verified.
 *                      You will not receive any press events from the flic before this callback has been sent. Typically this event will be sent
 *                      immediately after the <code>flicButtonDidConnect:</code> event.
 *
 */
- (void) flicButtonIsReady:(SCLFlicButton * _Nonnull) button;

/*!
 *  @method flicButton:didDisconnectWithError:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param error        The error that caused the disconnect. If the disconnect was intentional, then the parameter will be nil.
 *
 *  @discussion         This delegate method is called every time the flic has disconnected, regardless of the reason for it.
 *                      This can sometimes be called during a connection event that failed before the user was notified of the connection.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didDisconnectWithError:(NSError * _Nullable) error;

/*!
 *  @method flicButton:didFailToConnectWithError:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param error        The error that caused the flic to fail to connect.
 *
 *  @discussion         The requested connection failed. Please note that depending on at what point in the connection process the connection
 *                      failed you might also receive a regular flicButtonDidDisconnect: as well. If the connection fails and this callback is
 *                      made then the flic will always cancel the pending connection, regardless of what state the flic happens to be in.
 *                      This means that if you get a <code>flicButton:didFailToConnectWithError:</code> then you
 *                      need to call the <code>connect:</code> yourself to activate the pending connection once again.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didFailToConnectWithError:(NSError * _Nullable) error;

/*!
 *  @method flicButton:didUpdateRSSI:error:
 *
 *  @param button       The SCLFlicButton object that the event came from.
 *  @param RSSI         The RSSI value represented in decibels.
 *  @param error        In case there was a problem with updating the RSSI value then this parameter will describe the error.
 *                      This will in all other cases be nil.
 *
 *  @discussion         This callback verifies (unless an error occurred) that the RSSI value was updated.
 *
 */
- (void) flicButton:(SCLFlicButton * _Nonnull) button didUpdateRSSI:(NSNumber * _Nonnull) RSSI error:(NSError * _Nullable) error;

@end
