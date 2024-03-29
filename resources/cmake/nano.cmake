[host_machine]
system = 'linux'
cpu_family = 'arm'
cpu = 'armv8'
endian = 'little'

[constants]
arch = 'aarch64-linux-gnu'
toolchain = '/usr/bin/' + arch

[binaries]
c = toolchain + '-gcc'
cpp = toolchain + '-g++'
ld = toolchain + '-ld'
ar = toolchain + '-ar'
strip = toolchain + '-strip'
pkgconfig = toolchain + '-pkg-config'

[built-in options]
#c_args = ['']
#cpp_args = ['']
#ld_args = ['']

[built-in paths]
prefix = '/usr'
libdir = '/usr/lib/' + arch

[properties]
root = '/usr/' + arch
pkg_config_libdir = 'builddir/conan'
skip_sanity_check = true

