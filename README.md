![Flic Logo Black](https://user-images.githubusercontent.com/2717016/70526105-1bbaa200-1b49-11ea-9aa0-49e7959300c3.png)

# fliclib-ios

This is the official iOS framework for the original **Flic 1**. If you are looking to integrate the new **Flic 2**, please see [https://github.com/50ButtonsEach/flic2lib-ios](https://github.com/50ButtonsEach/flic2lib-ios)

**Note:** As of `April 7th, 2020`, this framework is distributed as an XCFramework bundle instead of a regular framework bundle.

## Getting Started

This framework works in collaboration with the Flic app so please make sure that you have it installed before you begin. The app is free and you can find it in the [App Store](https://itunes.apple.com/us/app/flic-app/id977593793?ls=1&mt=8).

Either follow the quick tutorial below, or take a look at one of our example projects here on GitHub for [Swift](https://github.com/50ButtonsEach/ios-boilerplate-swift) or [Objective-C](https://github.com/50ButtonsEach/ios-boilerplate-objc).

## Set up Xcode

Please note that steps 5-6 are optional and only needed if you are building an app that needs to run in the background.

1. Place the downloaded `fliclib.xcframework` folder somewhere on you computer, preferably in your project's folder structure.

2. Drag-and-drop the whole `fliclib.xcframework` folder from your finder window to the `Frameworks, Libraries, and Embedded Content` section under
the `General` tab of your application's target setting. 
	
	Ensure that `fliclib.xcframework` is listed as *Embed & Sign*:
	
	<img width="480" alt="Frameworks, Libraries and Embedded Content" src="https://user-images.githubusercontent.com/2717016/78569793-682a9b80-7824-11ea-98f9-ca0ee03ae0f3.png">
	
	Doing this should automatically add the xcframework to `Link Binary With Libraries` under the Build Phases tab.

3. Under `Project Settings` -&gt; `Build Settings`, set the flag `Allow Non-modular includes in Framework Modules` to **Yes**:
	
	![Allow non Modular](https://user-images.githubusercontent.com/2717016/70518151-26216f80-1b3a-11ea-8b05-4f61a58e5ce1.png)
	
4. In your project plist file, you need to register your app to handle URL scheme calls. This is needed when you fetch a Flic object from the Flic App. You also need to add the Flic app to the list of **Application Query Schemes**. Don't worry, we will explain this in greater detail later on. Make sure that your plist file contains something like this:

	![Plist](https://user-images.githubusercontent.com/2717016/84664531-f60abd00-af1e-11ea-83b6-cea1c7bcc744.png)

	Of course, make sure that you select a URL that is unique to your specific app. That's it! Xcode is now properly set up to integrate Flic and we can start coding.

5. In your project settings, check the `Uses Bluetooth LE accessories` option under `Background Modes` in the `Signing & Capabilities` tab.
	
	*Note:* If you can't see the options for `Background Modes` then you need to add that capability by pressing **+** in the top left corner of that view.
	
	Checking this option will let iOS know that we want permission to communicate with Flic buttons while the application is in the background.
	
	![Background Modes](https://user-images.githubusercontent.com/2717016/70518152-26ba0600-1b3a-11ea-9379-00d4638d3f35.png)

6. It the project's Info.plist file we must now add two keys:
	
	* Privacy - Bluetooth Peripheral Usage Description
	* Privacy - Bluetooth Always Usage Description
	
	The first one specifies that we wish to connect with Bluetooth Peripherals and the second one specifies that we will do so in the background. The values that you add here will be displayed to the user when iOS shows its bluetooth permission dialogs.
	
	![Plist Values](https://user-images.githubusercontent.com/2717016/70518156-27529c80-1b3a-11ea-86b1-65f75c705d66.png)

## Objective-C Code

1. Import the xcframework module by adding `@ import fliclib;` wherever it suits your application the best. If you are using Swift, then type `@import fliclib` instead. In this case we will just add it to the view controller implementation file. We also went ahead and added both of the Button and Manager delegate protocols.
	
	```objc
	@ import flic2lib;
	
	@interface ViewController () <SCLFlicButtonDelegate, SCLFlicManagerDelegate>
	
	@end
	```

2. The first thing we need to do before we can start using the Flic Manager is to configure its singleton. This needs to be done on every application launch.
	
	In this case we will do so in the `viewDidLoad` method. The background execution flag specifies whether or not you intend to use the buttons in the background. For this simple example we will set it to **YES**. The *appID* and *appSecret* parameters are unique for every application and can be generated on our developer portal.
	
	```obj-c
	- (void)viewDidLoad
	{
		[super viewDidLoad];
		[SCLFlicManager configureWithDelegate:self defaultButtonDelegate:self appID:appID appSecret:appSecret backgroundExecution:YES];
	}
	```

3. We now have a manager that we can use to grab a button from the Flic app, but before we do that we need to properly set up our URL scheme so that the callback works properly. To accomplish this we have to add a method `application:openURL:sourceApplication:annotation:` to our AppDelegate.m that will receive the URL callback. In this callback we can just forward it to the manager singleton.
	
	```objc
	- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options;
	{
		return [[SCLFlicManager sharedManager] handleOpenURL:url];
	}
	```

4. We are now all set to grab our first Flic button. To do this we need to call the `grabFlicFromFlicAppWithCallbackUrlScheme:` method on the manager singleton. What this call will do is open up the Flic app and present the user with a view where they can choose one of their connected Flics. Once the user has chosen one Flic, it will redirect back to the specified callback URL. We decided to put this feature in an *IBAction* and hook that up to a *UIButton* to be displayed in the UI.

	```objc
	- (IBAction)grab:(id)sender;
	{
		[[SCLFlicManager sharedManager] grabFlicFromFlicAppWithCallbackUrlScheme:@"yourAppURL"];
	}
	```

5. We now need to implement the `flicManager:didGrabFlicButton:withError:` callback in order to get notified when a button has been grabbed. If no error occurred, a new *SCLFlicButton* instance that is tied to the selected physical Flic has been created. The first thing that we should remember to do is to set the delegate here, unless you have not already set the default delegate on the manager (which we have already done in this example). This would also be a good place do all of your custom button settings in case you need any behavior that is different from the default.
	
	```objc
	- (void)flicManager:(SCLFlicManager *)manager didGrabFlicButton:(SCLFlicButton *)button withError:(NSError *)error;
	{
		if (error)
		{
			NSLog(@"Could not grab a Flic: %@", error);
		}
	}
	```

6. That's it! You now have a Flic button tied to your app, and you can start using it however you like. For example, lets implement the `flicButton:didReceiveButtonDown:age:` delegate method to make sure that things are working as they should. Remember that it might take a second or two to connect to the Flic. If you want to be notified of when the Flic is properly connected and ready to use, you can also implement the flicButtonIsReady: method.

	```objc
	- (void) flicButton:(SCLFlicButton *) button didReceiveButtonDown:(BOOL) queued age: (NSInteger) age;
	{
		NSLog(@"Yey, it works");
	}
	```

That's it!

## Background Execution

This step is optional and only required if you intend to use the Flic buttons while the app is in the background.

1. Set the backgroundExecution flag to **YES** when configuring the manager singleton.

2. When a Flic related event happens while your app is completely terminated the iOS device will re-launch your app to the background. However, since this can now be considered as a brand new launch of the application, we also need to re-initialize fliclib. To do this just initialize the manager as normal when the app boots. When doing this you will after a short time get a callback on the manager delegate, `flicManagerDidRestoreState:`, where you can collect all Flic buttons again and reset their delegates if needed.

	```objc
	- (void) flicManagerDidRestoreState:(SCLFlicManager *)manager;
	{
		// Set the delegate on all buttons if you have not set the default button delegate on the manager.
	}
	```

	If you have your own classes that depend on the button instances then this would also be the safe place to collect the buttons using the *knownButtons* method. If you have manny buttons and need to distinguish between them then the *buttonIdentifier* can be used for this purpose.

## Simulator Support

The XCFramework bundle will run in the simulator by default, no configuration needed.

## Licence

Any documentation or source code contained in this repository is released under [CC0](LICENCE%20(for%20the%20documentation%20and%20source%20code).txt). The fliclib binary is released under a [separate license](LICENCE%20(for%20the%20fliclib%20binary).txt) which allows you to use it almost without restrictions.
