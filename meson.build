project('termNote', 'c',
    version: '0.0.1',
    license: ['proprietary'],
    default_options: ['warning_level=3', 'buildtype=debugoptimized', 'c_std=c11']
)

termNote_srcs = []

inc = include_directories('inc')

subdir('inc')
subdir('src')

termNote_bin = executable('termNote',
    termNote_srcs,
    include_directories: inc
)