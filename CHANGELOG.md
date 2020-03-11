![Flic Logo Black](https://user-images.githubusercontent.com/2717016/70526105-1bbaa200-1b49-11ea-9aa0-49e7959300c3.png)

# Changelog

This file documents the changes between different versions of the `fliclib.framework` for the original Flic.

## fliclib-ios 1.3.3

### Changes

### Significant Changes

* Adjustments made to the framework in order to support Core Bluetooth API changes indtroduced in iOS 13.4. Older versions of this framework will still work on iOS 13.4, but we do recommend updating. If you do not update the framework then there is a risk that the button connection will not be re-set properly if connection is lost during the Bluetooth LE encryption exchange/setup process. This is particularily important for applications that uses long-term execution in the background.

### Minor Changes

* Added human readable descriptions to all `SCLFlicError` codes, except the ones prefixed with `SCLFlicErrorBluetoothError`. The description can be read using the `NSLocalizedDescriptionKey` key of the error’s userInfo dictionary.

* All error codes in the framework are now unique and only ever used once each. This is to make troubleshooting easier.

* New error codes:
	* `SCLFlicErrorIllegalVerificationResponse`
	* `SCLFlicErrorCouldNotDiscoverServices`
	* `SCLFlicErrorConnectionRetryLimitReached`

* Renamed error codes:
	* `SCLFlicErrorCouldNotCompleteTask` to `SCLFlicErrorCouldNotForgetButton`

* The framework is no longer code-signed by us. Our signature on the framework is not needed since the end developer (you) will need to re-sign it on build regardless. This is done using the `Embed & Sign` option when importing the framework.

* Changed bluetooth connection parameters (for iOS 12 and above) in order to achieve lower click latency on events that occur while the Flic is connected. This should not affect the Flic battery life.

## fliclib-ios 1.2.3

### Changes

* Fixed a bug that caused click events to be slower than they should have been, particularly when lowLatency mode was used.

## fliclib-ios 1.2.2

### Changes

* Corrected a UIApplication method call that accidentally ran on a background queue.
* State restoration adjusted slightly to better work with iOS11.1/2.

## fliclib-ios 1.2.0

### Changes

* Bluetooth connectivity fixes for iOS11
* fliclib data storage moved from NSDocumentDirectory to NSLibraryDirectory. Any existing old files will be moved over to the new location.

## fliclib-ios 1.1.11

### Changes

* A few iOS 10.2 bluetooth patches
* Added SCLFlicButtonTriggerBehaviorClick which can be used if you only need click and want the lowest possible latency on that event.

## fliclib-ios 1.1.7

### Changes

* iOS 10 compatibility added. This version is a mandatory update if you need iOS 10 support. Apple has unfortunately made API breaking changes to the Bluetooth framework which is why this update is needed. Any apps using older versions of the fliclib framework will stop working properly if a user updates to iOS 10 unless this has been updated.

## fliclib-ios 1.1.5

Bug fix release.

### Issues Fixed

* Added an event ack for every button events unique per app. In certain conditions a race condition could occur where one app could fetch all the queued events from the button before the other app connected. Now both the third party app and the Flic app will get all the events even if one of the apps had the button disconnected while the event happened.
* Corrected HTML tags is header file.

## fliclib-ios 1.1.3

This release has a lot of API breaking changes. We have collected a lot of feedback and decided to make some structural changes in order to make it easier to implement the fliclib framework. This framework will only work together with the Flic 2.0 and above app version and requires that the 'flic20' url scheme is added to the plist file instead of 'flic'.

### Changes

* The manager is now a singleton. This makes sense since we only support one instance per application. It also helps it order to avoid the need to store and pass references across multiple views and classes.
* The manager now has a defaultButtonDelegate that you can set if you know in advance where you want the events. This also removes the need for implementing the managerDidRestoreState since the delegates will also be set on restoration. 
* Foreground/Background modes have been removed. Instead a lowLatency property can be used if you wish to reduce the latency, but both modes functions in the background as regardless. You opt-in for background execution on manager configuration.
* Auto-connect is activated on all modes and can only be turned off by manually disconnecting the button. To turn it on again, simply call connect again.
* handleOpenURL: added that can be called directly from App delegate. When new buttons are grabbed they will be sent through a flicManager:didGrabFlicButton:withError: callback.
* All buttons are now automatically connected on a grab.
* userAssignedName property added that contains the name set by the user in the Flic app.
* color property that contains the color of the actual Flic button grabbed.
* refreshPendingConnections has changed name to onLocationChange, to better display how it should be used.
* The grab method has changed name to grabFlicFromFlicAppWithCallbackUrlScheme: and the scheme should only be the url scheme name that you have registered, meaning not a full URL.
* Cleanup of error codes.

### Issues Fixed

* Fixed issue that caused a manually disconnected button to connect after state restoration.

## fliclib-ios 1.0.3

### Changes

* Changes to BLE reconnection
* Internal rework
* Updated error codes

### Issues Fixed

* Fixed issue that caused connection to fail if you set mode directly before initiating a connection.
* Fixed issue in outgoing packet signing that caused an invalid signature on packets send if the app was crashed and relaunched in the background during an active Flic connection.

## fliclib-ios 0.9.5

### Changes

* Overall stabilify implovements.
* Bluetooth rework to improve connectivity.
* Flilib now has a check to see if Flic app exists before a button is grabbed. If it is not existitng then the user will be forwarded to the App Store. This requires that the developer adds "flic" as an item under LSApplicationQueriesSchemes.
* SCLFlicButtonMode has been changed. We now only have one foreground mode and one background mode. Please see documentation for more information about that.
* Bitcode support added.
* refreshPendingConnections: method added to SCLFlicManager. This method is important when using the background mode for Flic in order to keep the pending connections in a proper state. Please see documentation for more information about that.

## fliclib-ios 0.8.2

### Changes

* Stability improvements.
* Added error handling to generateButtonFromURL:error:. Possible errors are: SCLFlicErrorButtonAlreadyExisting, SCLFlicErrorMissingData, SCLFlicErrorInvalidSignature, SCLFlicErrorUnknown
* Added isReady property.


## fliclib-ios 0.7.1

### Changes

* Stability improvements.
* Passive mode removed, use ActiveKeepAlive for those use-cases instead.
* Updated Documentation.

## fliclib-ios 0.6.7

### Changes

* Added a flag for background execution in the manager initializing method.
* Swift compatibillity verified.
* Added Nullability Annotations.
* Updated documentation.

### Issues fixed

* Fixed an issue that resulted in the flicButtonIsReady: not being sent on every connect.
* Fixed an issue with the outgoing packet signing that caused the Flic to drop indicateLED: calls.

Please note that these fixes requires the firmware version R11 on the Flic to work properly.

## fliclib-ios 0.6.6

Initial commit
