project('libmsikeyboard', 
        'c',
        'cpp',
        version : '0.2.2',
        meson_version : '>= 0.47.0',
        default_options : [
            'warning_level=1',
            'c_std=gnu89'
        ]
)

hiddep = ''
if ['darwin'].contains(build_machine.system())
    hiddep = 'hidapi'
else
    hiddep = 'hidapi-libusb'
endif

mainlib = shared_library('msikeyboard', 'msikeyboard.c', version: '0.2.2', dependencies: dependency(hiddep), install: true)

install_headers('msikeyboard.h', subdir: 'msikeyboard')

e = executable('test-msikeyboard', 'test-msikeyboard.c', link_with: mainlib)
test('Test MSI keyboard LED', e)

pkg = import('pkgconfig')
pkg.generate(libraries: mainlib,
             subdirs: 'libmsikeyboard',
             version: '0.2.2',
             name: 'libmsikeyboard',
             filebase: 'msikeyboard',
             description: 'C Library for change color, modes, intensity on MSI keyboards.')
