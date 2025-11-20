# 3D Engine

## General features:

- Phong lighting model implemented (Ambient, Diffuse, Specular components).
- Cube Map Skybox for an immersive space environment.
- 2D Texture Mapping.
- Primitive mesh generation (Sphere, Cube, etc.).
- External .obj model and .mtl material loading (via tinyobjloader).
- Frame rate independent physics.
- Modular code structure with clear separation of concerns using dedicated classes: Camera, Scene, Skybox, TextureManager, etc.
- ImGui Integration for UI/Controls and FPS display.

## Run:

Distribution pakacges with pre-compiled executables / binaries are available at: 

Linux: `dist/linux/app`

Windows: `dist/win/app.exe`

## Install / Build:

### Linux:

The latest pre-compiled executable is available in `dist/linux` 

Build:
```
$ make linux
```

Run (Directly):
```
$ ./build/linux/app
```

Run (Using default target):
```
$ make run
```

Create Distribution Package:
```
$ make dist-linux
```

### Windows (Cross-Compilation):

You have to be on Linux in order to cros-compile this to Windows.   

The latest pre-compiled executable is available in `dist/win` along with the required dlls.

Build:
```
$ make win
```

Create Distribution Package:
```
$ make dist-win
```
