JETSON_IP=jetson
JETSON_USER=frc

OUTDIR=builddir/
JUNK=$(shell cat .gitignore)

configure: $(OUTDIR)
	[ -d builddir/ ] && meson builddir || meson builddir --reconfigure

native: configure
	ninja -C builddir

deploy: clean configure
	ninja -C builddir/ deploy

setup: configure
	ninja -C builddir/ setup

clean:
	rm -rf $(shell cat .gitignore)

$(OUTDIR):
	mkdir $(OUTDIR)