![Flic Logo Black](https://user-images.githubusercontent.com/2717016/70526105-1bbaa200-1b49-11ea-9aa0-49e7959300c3.png)

# fliclib-ios

This is the official iOS framework for the original **Flic 1**. If you are looking to integrate the new **Flic 2**, please see [https://github.com/50ButtonsEach/flic2lib-ios](https://github.com/50ButtonsEach/flic2lib-ios)

## Getting Started

This framework works in collaboration with the Flic app so please make sure that you have it installed before you begin. For instructions on how to implement this see [https://partners.flic.io/partners/developers/ios-tutorial](https://partners.flic.io/partners/developers/ios-tutorial), or take a look at one of our example projects here on github for [Swift](https://github.com/50ButtonsEach/ios-boilerplate-swift) or [Objective-C](https://github.com/50ButtonsEach/ios-boilerplate-objc).

## Simulator Support

The framework itself does not contain slices for x86 and i386 (iOS Simulator). The reason for this is that if we were to add those slices to the framework then
they would have to be removed before App Store submission, which is not a very straightforward thing to do. So, for those who want to run the framework in the simulator
we instead provide a wrapper that adds a fake fliclib implementation when building for x86 and i386.

To use this wrapper follow these steps:

1. Include the files inside the `simulator-wrapper` folder to your project.
2. On all the places in your code where you need to import fliclib you should import the wrapper instead. In other words, replace `#import <fliclib/fliclib.h>` with `#import "fliclibWrapper.h"`. Of course, the file path will depend on how you have configured your project. For example, if you have the *fliclib-ios* repository as a git submodule in your project root then it might look like this `#import "../fliclib-ios/simulator-wrapper/fliclibWrapper.h"`.
3. Make sure that both `SCLFlicManagerSimulator.m` and `SCLFlicButtonSimulator.m` are added to *Compile Sources* in your project *Build Phases*.

## Licence

Any documentation or source code contained in this repository is released under [CC0](LICENCE%20(for%20the%20documentation%20and%20source%20code).txt). The fliclib binary is released under a [separate license](LICENCE%20(for%20the%20fliclib%20binary).txt) which allows you to use it almost without restrictions.
