project('dvdinfo', 'cpp', version : '0.9.2git', meson_version : '>=0.53.0', license : 'gpl-2.0+')

# add something to limit build only to linux

add_project_arguments('-D__STDC_LIMIT_MACROS', language : 'cpp')

qt5_mod = import('qt5')
qt5widgets = dependency('qt5', modules : 'Widgets')

# dvdread_dep = dependency('dvdread', method : 'system')
# how do I force soversion = 3 ?
dvdread_dep = meson.get_compiler('cpp').find_library('dvdread')
dvdcss_dep = dependency('libdvdcss', method : 'pkg-config')

dvdinfo_headers = [
       'src/dvdtitleinfoview.h',
       'src/dvdinfoview.h',
       'src/mainwindow.h'
       ]

dvdinfo_sources = [
       'src/dvdtitleinfoview.cpp',
       'src/dvdinfoview.cpp',
       'src/dvdinfocore.cpp',
       'src/mainwindow.cpp',
       'src/main.cpp',
       ]

moc_processed = qt5_mod.preprocess(
       moc_headers : dvdinfo_headers
       )

executable(
       'dvdinfo',
       sources: [dvdinfo_sources, moc_processed],
       dependencies: [qt5widgets, dvdread_dep, dvdcss_dep],
       )
