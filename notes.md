# MiniLibX On WSL2

Resource: [Getting a screen on Windows 10 (WSL2)](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#getting-a-screen-on-windows-10-wsl2)

1. Run XLaunch
2. Type `export DISPLAY=localhost:0.0`
3. Run `./fdf`

## Full command

```bash
export DISPLAY=localhost:0.0 && make && ./fdf maps/42.fdf
```

## Check leaks

```bash
leaks --atExit -- ./fdf maps/42.fdf
```

## Features

- [x] Isometric view
- [x] Perspective view
- [x] Other views (top, sides)
- [x] Rotate
- [x] Scale
- [x] Scale Z
- [x] Translate
- [x] Map colors
- [x] Help
- [x] Solid rendering
- [x] Navigate with mouse

Issues to fix:

- [x] Perspective with solid rendering
- [x] Help blinking
- [x] Help to update (usage, controls)
- [ ] Zoom crash
- [ ] Zoom with scroll
- [x] Disable color gradient by default
- [ ] Last check: Norminette, Leaks, Sanitize
