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
