# nRF52 Dongle RGB

This is a very simple sample using PWM to fade the RGB LED on the nRF52 Dongle

# Building

Follow the Zephyr project [Getting Started](https://docs.zephyrproject.org/latest/getting_started/index.html) guide first.

Also, install nrfutil (see [here](https://docs.zephyrproject.org/latest/boards/arm/nrf52840_pca10059/doc/index.html)).

Clone the repo, go to the cloned folder and run:

```
$ west build -b nrf52840_pca10059
$ cd build
$ nrfutil pkg generate --hw-version 52 --sd-req=0x00 --application zephyr/zephyr.hex --application-version 1 pkg.zip
```

# Flashing

Insert the dongle, press the reset button to enable DFU mode and write:

```
nrfutil dfu serial -pkg pkg.zip -p /dev/ttyACM0
```