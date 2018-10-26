# 3DRaycast
A 3D Raycasting Engine (fork of https://github.com/name-here/3DRaycast)

## TODO
[ ]Work on [TODO](TODO.md)


## How to install
* Need SDL2 library, [download either runtime or development SDL2](https://www.libsdl.org/download-2.0.php) and put it into /Library/Frameworks. (Installer says it will work in ~/Library/Frameworks, too. We didn't have such a folder on our osX 10.13.6 machine, so we made one. Using ```make``` unfortunately gave us errors:
    ```
    g++ -c -o 3DRaycast.o 3DRaycast.cpp -g -Og -Wall -Wextra -pedantic -std=c++11 `sdl2-config --cflags`
    /bin/sh: sdl2-config: command not found
    3DRaycast.cpp:34:10: fatal error: 'SDL2/SDL.h' file not found
    #include <SDL2/SDL.h>
    ```


## How to compile and run:
* ```cd``` to code's directory, type ```make``` into terminal. Stand back!
* ```./3DRaycast```


## References
* [SDL library](https://wiki.libsdl.org/) including ["how to compile"](https://wiki.libsdl.org/Installation). Note: "Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D."
* [Screencast tutorials for getting started with OpenSceneGraph/Mac OS X](	http://www.openscenegraph.org/projects/osg/wiki/Support/Tutorials/MacOSXTips). 
"Though these are OpenSceneGraph centric, the same exact concepts apply to	SDL, thus the videos are recommended for everybody getting started with	developing on Mac OS X. (You can skim over the PlugIns stuff since SDLdoesn't have any PlugIns to worry about.)"
* Testing, see ["closed"](https://stackoverflow.com/questions/91384/unit-testing-for-c-code-tools-and-methodology) and and ["not constructive"](https://stackoverflow.com/questions/242926/comparison-of-c-unit-test-frameworks)
* Re-factoring (see Malcolm Fowler)
* [Markdown](https://daringfireball.net/projects/markdown/) how to edit “markdown” text, and especially see [Github Flavored Markdown](github.github.com/gfm) and [live preview of gfm](jbt.github.io/markdown-editor).
Also see [Editing in Github in general](https://help.github.com/articles/about-writing-and-formatting-on-github/), 
and [how to create/highlight code blocks](https://help.github.com/articles/creating-and-highlighting-code-blocks/).


## Related Articles
* [desc](uri)
