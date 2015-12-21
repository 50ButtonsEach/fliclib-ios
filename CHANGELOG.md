#fliclib-ios 0.9.5

**Changes**

* Overall stabilify implovements.
* Bluetooth rework to improve connectivity.
* Flilib now has a check to see if Flic app exists before a button is grabbed. If it is not existitng then the user will be forwarded to the App Store. This requires that the developer adds "flic" as an item under LSApplicationQueriesSchemes.
* SCLFlicButtonMode has been changed. We now only have one foreground mode and one background mode. Please see documentation for more information about that.
* Bitcode support added.
* refreshPendingConnections: method added to SCLFlicManager. This method is important when using the background mode for Flic in order to keep the pending connections in a proper state. Please see documentation for more information about that.

#fliclib-ios 0.8.2

**Changes**

* Stability improvements.
* Added error handling to generateButtonFromURL:error:. Possible errors are: SCLFlicErrorButtonAlreadyExisting, SCLFlicErrorMissingData, SCLFlicErrorInvalidSignature, SCLFlicErrorUnknown
* Added isReady property.


#fliclib-ios 0.7.1

**Changes**

* Stability improvements.
* Passive mode removed, use ActiveKeepAlive for those use-cases instead.
* Updated Documentation.

#fliclib-ios 0.6.7

**Changes**

* Added a flag for background execution in the manager initializing method.
* Swift compatibillity verified.
* Added Nullability Annotations.
* Updated documentation.

**Issues fixed**

* Fixed an issue that resulted in the flicButtonIsReady: not being sent on every connect.
* Fixed an issue with the outgoing packet signing that caused the Flic to drop indicateLED: calls.

Please note that these fixes requires the firmware version R11 on the Flic to work properly.

# fliclib-ios 0.6.6
Initial commit
