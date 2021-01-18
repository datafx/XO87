# XO87 Community Source Project
Information and community source code for Monstargear XO87 Hot-Swap PCB

There are open PRs with both QMK and VIA to offically add support for this PCB.  Regardless of acceptance, this repo will stay active to provide information, prebuilt firmware hex files, and the latest testing source code.

***WARNING***

This firmware is not compatible with the old factory firmware.  If you are using the old factory firmware you will require an ISP reflash of your board.   If you are unsure which firmware your board is using, please stop by Monstargear's [Discord](https://discord.gg/YhKJ5k2AVC) before attempting to flash your board.  Suggestions and PRs are welcome.

You must download QMK from https://github.com/qmk/qmk_firmware to compiile this firmware.  Simply drop the xo87 folder into the qmk keyboards folder and run make xo87/rgb:production.  Alternatively, you can use the prebuilt firmware provided here if you do not with to build your own or customize the keyamps.  You can then use an ISP flasher to send the production firmware to the board.  After you are running this firmware, you can rebuild and flash via bootloader like normal.  DO NOT FLASH THE STOCK FIRMARE!  Flashing the stock firmware will cause your keyboard to become unresponsive and require you to reflash with ISP again.

To do.

* Clean up and organize LED layout/pattern strangeness
* Update documentation
* Find a way to flash from factory firmware without ISP flashing
* Support for controlling individual LEDs
