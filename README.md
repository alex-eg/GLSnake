Small SDL and Old OpenGL snake game!

# Requirements
- `SDL2`
- `SDL2_ttf`
- `SDL2_mixer` (with Vorbis support for .ogg music)
- Legacy OpenGL 2.1+ (fixed-function pipeline)

# Build
```bash
$ meson setup builddir  # Once, add --wipe if needed to remake builddir.
$ meson compile -C builddir  # Compile and link.
$ builddir/snake  # Run the game!
```
