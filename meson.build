project('libmsikeyboard', 'c')
hiddep = dependency('hidapi-libusb')
mainlib = shared_library('msikeyboard', 'msikeyboard.c', version: '0.2.2', dependencies: hiddep, install: true)

install_headers('msikeyboard.h', subdir: 'libmsikeyboard')

e = executable('test-msikeyboard', 'test-msikeyboard.c', link_with: mainlib)
test('Test MSI keyboard LED', e)

pkg = import('pkgconfig')
pkg.generate(libraries: mainlib,
             subdirs: 'libmsikeyboard',
             version: '0.2.2',
             name: 'libmsikeyboard',
             filebase: 'msikeyboard',
             description: 'C Library for change color, modes, intensity on MSI keyboards.')
