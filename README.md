# Merry christmas and a happy new year!

Just a little bit of code I threw together christmas morning 2018. Give it a shot, and spread the Christmas cheer!

## Dependencies

### Ubuntu:
`libncurses5-dev`

`libncursesw5-dev`

### Arch:
`ncurses`

## Compiling

Run following: `gcc -o christmas christmas.c -lncurses`, or just use the makefile.

## Usage
```bash
christmas [options]
```
#### options:
```
-t --time <time>     time in milliseconds between each tick of the program. Default 150

-h --help            display help message
```
