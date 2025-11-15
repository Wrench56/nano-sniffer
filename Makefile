FQBN := arduino:mbed_nano:nano33ble
BUILD_DIR := build
SRC_DIR := embedded
FLAGS := -Wall -Wextra -Wpedantic -Werror -O2

PORT := $(shell arduino-cli board list | grep "$(FQBN)" | awk '{print $$1}' | head -n 1)

ifeq ($(PORT),)
  $(warning No Nano 33 BLE detected! Plug in board or press reset.)
endif

.PHONY: all build upload flash clean install-core install-ble install

all: build

build:
	arduino-cli compile \
		--fqbn $(FQBN) \
		--build-path $(BUILD_DIR) \
		--build-property compiler.cpp.extra_flags="$(FLAGS)" \
		--build-property compiler.c.extra_flags="$(FLAGS)" \
		$(SRC_DIR)

upload:
	@if [ "$(PORT)" = "" ]; then \
		echo "ERROR: No serial port found for Nano 33 BLE."; \
		exit 1; \
	fi; \
	echo "Using port $(PORT)"; \
	arduino-cli upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--input-dir $(BUILD_DIR) \
		--verify \
		$(SRC_DIR)

flash: build upload

install-core:
	arduino-cli core update-index && \
	arduino-cli core install arduino:mbed_nano

install-ble:
	arduino-cli lib install ArduinoBLE

install: install-core install-ble
