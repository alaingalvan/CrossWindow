## Prior Art

### [Winit](https://github.com/tomaka/winit)

Winit is by far the most well designed and robust of the libraries featured here. It features:

- Cross platform operating system support (Windows / Mac / Linux / iOS / Android / WebAssembly )
- a simple and easy to use interface.
- connecting libraries for graphics APIs to interface with.

Winit's API surface area and decoupled design was a big inspiration for CrossWindow.

### [Vulkan-WSIWindow](https://github.com/renelindsay/Vulkan-WSIWindow)

Vulkan WSIWindow is a cross platform windowing API that targets all Vulkan 1.0 operating system targets. While the library is easy to use and robust, it was coupled to Vulkan and lacked important features like resizing. There was a need for either improving on the library to add those features or to fork it. 

At the same time, the library had great ideas like wrappers to Vulkan data structures to automatically attach critical extensions needed for Vulkan to work with Operating System windows. Some of those ideas were integrated into [CrossWindow-Graphics](https://github.com/alaingalvan/crosswindow-graphics).

### [GLFW](https://github.com/glfw/glfw)

GLFW was popular among indie developers working on greenfield projects with OpenGL/Vulkan, but was coupled to those graphics libraries and was written in C, which makes programming with it slightly harder.

### [SFML](https://github.com/SFML/SFML)

SFML is a fully featured open source windowing library, though the library is quite large since it tries to cover multiple cross platform use cases such as audio, networking, etc. While one can see the benefit of having one place to get all those features, it's important for libraries to follow the unix philosophy, "Do one thing and do it well". 

CrossWindow only tries to be a cross platform windowing API, other features such as sound and graphics APIs can be done by other people who specialize in those areas.

### [Qt](https://qt.io)

The De Factor Operating system Windowing library. Qt is amazing but its licensing and large surface area leaves a lot to be desired. 