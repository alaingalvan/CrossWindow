```cpp
// Initialize Mag Window with main function args
xwin::init(MainArgs);

// Initialize Window Description
xwin::WindowDesc desc();

// Create Window Object
xwin::Window window(desc);

// Initialize Mag
mag::Instance instance = mag::createInstance();
mag::Surface surface = window.getSurface(instance);

```