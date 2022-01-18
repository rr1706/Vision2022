JETSON_IP=jetson
JETSON_USER=frc

OUTDIR=builddir/
JUNK=$(shell cat .gitignore)

configure:
	[ -d builddir/ ] && meson builddir || meson builddir --reconfigure

debug: configure
	ninja -C builddir

release: clean configure
	ninja -C builddir

deploy: release
	python3 scripts/deploy.py

setup: configure
	ninja -C builddir/ pip

clean:
	rm -rf $(shell cat .gitignore)