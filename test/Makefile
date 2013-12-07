include config.mk

APP_NAME := $(LOCAL_MODULE)
APP_ARCH := armeabi

NDK_FILE := android-ndk-r9-linux-x86_64.tar.bz2
NDK_PATH_DEFAULT := ~/Development/android-ndk-r9
NDK_BUILD_DEFAULT_PATH := $(NDK_PATH_DEFAULT)/ndk-build
SDK_FILE := android-sdk_r22.0.5-linux.tgz
SDK_PATH := ~/Development/android-sdk-linux
ADB_DEFAULT_PATH := $(SDK_PATH)/platform-tools/adb

.PHONY: all build test uninstall ndk clean sdk

all: build

$(NDK_FILE):
	@echo === Grabbing NDK ===
	@wget http://dl.google.com/android/ndk/$(NDK_FILE)

$(NDK_BUILD_DEFAULT_PATH): | $(NDK_FILE)
	@echo === Extracting NDK ===
	@tar -xvf $(NDK_FILE)

ndk: $(NDK_BUILD_DEFAULT_PATH)

$(SDK_FILE):
	@echo === Grabbing SDK ===
	@wget http://dl.google.com/android/$(SDK_FILE)

$(ADB_DEFAULT_PATH): | $(SDK_FILE)
	@echo === Extracting SDK ===
	@tar -xvf $(SDK_FILE)
	@echo y | $(SDK_PATH)/tools/android update sdk -t platform-tool --no-ui

sdk: $(ADB_DEFAULT_PATH)

-include paths.mk

paths.mk:
	@if [ -e $(NDK_BUILD_DEFAULT_PATH) ]; then \
		echo ==== Using grabbed NDK ====; \
		echo "NDK_BUILD := $(NDK_BUILD_DEFAULT_PATH)" > paths.mk; \
	else \
		if command -v ndk-build >/dev/null 2>/dev/null; then \
			echo ==== Using NDK from PATH ====; \
			echo "NDK_BUILD := ndk-build" > paths.mk; \
		else \
			echo ==== NDK not found in PATH ====; \
			touch paths.mk; \
			make ndk; \
			echo "NDK_BUILD := $(NDK_BUILD_DEFAULT_PATH)" > paths.mk; \
		fi; \
	fi
	@if [ -e $(ADB_DEFAULT_PATH) ]; then \
		echo ==== Using grabbed SDK ====; \
		echo "ADB := $(ADB_DEFAULT_PATH)" >> paths.mk; \
	else \
		if command -v adb >/dev/null 2>/dev/null; then \
			echo ==== Using SDK from PATH ====; \
			echo "ADB := adb" >> paths.mk; \
		else \
			echo ==== SDK not found in PATH ====; \
			make sdk; \
			echo "ADB := $(ADB_DEFAULT_PATH)" >> paths.mk; \
		fi; \
	fi

build:
	@echo === Building application ===
	@$(NDK_BUILD_DEFAULT_PATH) NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk; \

test: build
	@echo === Pushing application to the device ===
	@$(ADB) push libs/$(APP_ARCH)/$(APP_NAME) /data/local/tmp
	@$(ADB) shell touch /data/local/tmp/test
	@$(ADB) shell chmod 777 /data/local/tmp/$(APP_NAME)
	@$(ADB) shell chmod 777 /data/local/tmp/test
	@echo === Running application ===
	@$(ADB) shell /data/local/tmp/hw5_test

uninstall:
	@echo === Removing application ===
	@$(ADB) shell rm -r /data/local/tmp/hw5_test
	@$(ADB) shell rm -r /data/local/tmp/test_file
	@$(ADB) shell rm -r /data/local/tmp/test


clean:
	rm -rf libs obj

clean-ndk:
	rm -rf $(NDK_PATH_DEFAULT)
	rm -rf $(NDK_FILE)
