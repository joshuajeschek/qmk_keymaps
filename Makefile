MARGS=-e CONVERT_TO=promicro_rp2040 -e BUILD_DIR=$(shell pwd)/.build

default: indil

setup:
	ln -s $(shell pwd)/indil ${HOME}/qmk_firmware/keyboards/splitkb/aurora/lily58/keymaps/indil

.PHONY: indil
indil:
	qmk compile ${MARGS} -kb splitkb/aurora/lily58/rev1 -km indil
	sudo ./autoflash.sh

lily58:
	qmk compile ${MARGS} -kb splitkb/aurora/lily58/rev1 -km default
	sudo ./autoflash.sh

clean:
	rm .build -r

