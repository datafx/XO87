# XO87 Community Source Project
Information and community source code for Monstargear XO87 Hot-Swap and Solderable PCBs

The Hot-Swap board has been officially added to QMK, but this repo will stay active to provide information, prebuilt firmware hex files, and the latest testing source code.  The Soldered board firmware is only in beta.

***WARNING***

This firmware is not compatible with the old factory firmware.  If you are using the old factory firmware you will require an ISP reflash of your board.   If you are unsure which firmware your board is using, please check [here](https://www.monstargears.com/75/?bmode=view&idx=5748773&back_url=&t=board&page=1) or stop by Monstargear's [Discord](https://discord.gg/YhKJ5k2AVC) before attempting to flash your board.  The maintainers of this firmware and Monstargear will not be responsible for issues caused by incorrect flashes.  Please ask if you are unsure!  Suggestions and PRs are welcome.

If you wish to compile your own firmware instead of using one of the provided hex files, you must download QMK from https://github.com/qmk/qmk_firmware.  Simply drop the monstargear folder into the qmk keyboards folder and run make monstargear/xo87/rgb:production.  Alternatively, you can use the prebuilt firmware provided here if you do not with to build your own or customize the keyamps.  You can then use an ISP flasher to send the production firmware to the board.  After you are running this firmware, you can rebuild and flash via bootloader like normal.  DO NOT FLASH THE OLD FIRMWARE ONCE YOU ARE USING THE NEW FIRMWARE!  Flashing the old firmware over the new firmware will cause your keyboard to become unresponsive and require you to reflash with ISP again.

If you are on the old firmware and using an ISP flasher, please flash the file "monstargear_xo87_rgb_via_production.hex".  This file contains both the firmware and bootloader.

If you are already on the newer firmware please use the file name "monstargear_xo87_rgb_via.hex".  This file is able to be used through QMK toolbox.

To do.

* ~~Clean up and organize LED layout/pattern strangeness~~
* ~~Update documentation~~
* Find a way to flash from factory firmware without ISP flashing
* Support for controlling individual LEDs
* ~~Support for soldered version of PCB~~ - Partial
* Full support for LED matrix on soldered board
