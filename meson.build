project(
  'GLSnake', 'c',
  version : '1.0.0',
  default_options: [
    'default_library=static',
    'c_std=c99',
  ],
)

resource_dir = get_option('resource_dir')
add_project_arguments(
  '-DRESOURCE_DIR="@0@"'.format(resource_dir),
  language : 'c',
)

# Provides 'sources' and 'dependencies' variables.
subdir('src')

executable(
  'snake',
  sources,
  dependencies: dependencies,
  include_directories: include_directories('include'),
)
