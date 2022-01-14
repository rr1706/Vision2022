debug:
	[ -d builddir/ ] && meson builddir || meson builddir --reconfigure
	ninja -C builddir

release: clean
	[ -d builddir/ ] && meson builddir || meson builddir --reconfigure
	ninja -C builddir

deploy: release
	python3 scripts/deploy.py

setup:
	pip install -r requirements.txt

clean:
	rm -rf $(shell cat .gitignore)