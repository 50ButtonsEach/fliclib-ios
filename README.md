# fliclib-ios
The fliclib framework for iOS.
This framework works in collaboration with the Flic app so please make sure that you have it installed before you begin.

Notice: The instructions and documentation available at our website have not been updated to work with the latest release of the framework. This will be done soon.
For instructions on how to implement this go to https://partners.flic.io/partners/developers/ios-tutorial, or take a look at one of our example projects here on github.

**Simulator Support**

The framework itself does not contain slices for x86 and i386 (iOS Simulator). The reason for this is that if we were to add those slices to the framework then
they would have to be removed before App Store submission, which is not a very straightforward thing to do. So, for those who want to run the framework in the simulator
we instead provide a wrapper that adds a fake fliclib implementation when building for x86 and i386.

To use this wrapper follow these steps:

1. Include the files inside the `simulator-wrapper` folder to your project.
2. On all the places in your code where you need to import fliclib you should import the wrapper instead. In other words, replace `#import <fliclib/fliclib.h>` with `#import "fliclibWrapper.h"`. Of course, the file path will depend on how you have configured your project. For example, if you have the *fliclib-ios* repository as a git submodule in your project root then it might look like this `#import "../fliclib-ios/simulator-wrapper/fliclibWrapper.h"`.
3. Make sure that both `SCLFlicManagerSimulator.m` and `SCLFlicButtonSimulator.m` are added to *Compile Sources* in your project *Build Phases*.