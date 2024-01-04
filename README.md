# gd_fastnoise2
Extension for the [Godot engine](https://github.com/godotengine/godot) that wraps the [FastNoise2](https://github.com/Auburn/FastNoise2) library and exposes functionality to GDScript.

## Building
For the most part, the module gets built along with godot. However, you will need to build the FastNoise2 library first. 
It is on the road map to have it built as part of godot's build process, but at this point it still needs to be manually built.

### Pre-requisites
- [Scons](https://scons.org/)

### Building FastNoise.lib
```bash
git checkout git@github.com:zak-grumbles/gd_fastnoise2.git
cd gd_fastnoise2
git submodule update --init
cd FastNoise2
scons
```

#### Options
Along with the built-in scons options, these additional options 
- `use_llvm=yes` - Compile using llvm/clang

## Including in Godot
As long as this repo is cloned into either the `godot/modules` directory or in a custom_modules directory it will be picked up along with the built-in modules when `godot` is built.