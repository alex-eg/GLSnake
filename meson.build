project(
  'GLSnake', 'c',
  version : '1.0.0',
  default_options: [
    'default_library=static',
    'c_std=c99',
  ],
)

add_project_arguments('-DRESOURCE_DIR="./resources"', language: 'c')

# Provides 'sources' and 'dependencies' variables.
subdir('src')

executable(
  'snake',
  sources,
  dependencies: dependencies,
  include_directories: include_directories('include'),
)
