![Flic Logo Black](https://user-images.githubusercontent.com/2717016/70526105-1bbaa200-1b49-11ea-9aa0-49e7959300c3.png)

# fliclib-ios

This is the official iOS framework for the original **Flic 1**. If you are looking to integrate the new **Flic 2**, please see [https://github.com/50ButtonsEach/flic2lib-ios](https://github.com/50ButtonsEach/flic2lib-ios)

**Note:** As of `April 7th, 2020`, this framework is distributed as an XCFramework bundle instead of a regular framework bundle.

## Getting Started

This framework works in collaboration with the Flic app so please make sure that you have it installed before you begin. For instructions on how to implement this see [https://partners.flic.io/partners/developers/ios-tutorial](https://partners.flic.io/partners/developers/ios-tutorial), or take a look at one of our example projects here on github for [Swift](https://github.com/50ButtonsEach/ios-boilerplate-swift) or [Objective-C](https://github.com/50ButtonsEach/ios-boilerplate-objc).

***

**Note:** As of `April 7th, 2020`, the first 4 steps under the *Set up Xcode* section in the linked tutorial are no longer valid. Instead, replace them with the following 2 steps:

1. Place the downloaded `fliclib.xcframework` folder somewhere on you computer, preferably in your project's folder structure.

2. Drag-and-drop the whole `fliclib.xcframework` folder from your finder window to the `Frameworks, Libraries, and Embedded Content` section under
the `General` tab of your application's target setting. 
	
	Ensure that `fliclib.xcframework` is listed as *Embed & Sign*:
	
	<img width="480" alt="Frameworks, Libraries and Embedded Content" src="https://user-images.githubusercontent.com/2717016/78569793-682a9b80-7824-11ea-98f9-ca0ee03ae0f3.png">
	
	Doing this should automatically add the xcframework to `Link Binary With Libraries` under the Build Phases tab.

## Simulator Support

The XCFramework bundle will run in the simulator by default, no configuration needed.

## Licence

Any documentation or source code contained in this repository is released under [CC0](LICENCE%20(for%20the%20documentation%20and%20source%20code).txt). The fliclib binary is released under a [separate license](LICENCE%20(for%20the%20fliclib%20binary).txt) which allows you to use it almost without restrictions.
