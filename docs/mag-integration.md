```cpp
// Initialize Mag Window with main function args
mwin::init(MainArgs);

// Initialize Window Description
mwin::WindowDesc desc();

// Create Window Object
mwin::Window window(desc);

// Initialize Mag
mag::Instance instance = mag::createInstance();
mag::Surface surface = window.getSurface(instance);

```