sources = files([
  'gameover.c',
  'gui.c',
  'highscores.c',
  'ingame.c',
  'main.c',
  'mainmenu.c',
  'paused.c',
  'targa.c',
  'ttfonts.c',
])

sdl2_mixer_dep = dependency('sdl2_mixer', required: false)
if not sdl2_mixer_dep.found()
  sdl2_mixer_dep = dependency('SDL2_mixer')
endif

sdl2_ttf_dep = dependency('sdl2_ttf', required: false)
if not sdl2_ttf_dep.found()
  sdl2_ttf_dep = dependency('SDL2_ttf')
endif

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

dependencies = [
  dependency('gl', method: 'system'),
  dependency('sdl2'),
  sdl2_mixer_dep,
  sdl2_ttf_dep,
]
if m_dep.found()
  dependencies += m_dep
endif
