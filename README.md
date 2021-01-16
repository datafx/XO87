# XO87
Information and community source for Monstargear XO87 Hot-Swap PCB

***WARNING***

This firmware is not compatible with the default factory firmware.  Using this firmware is unsupported and will require an ISP reflash of your board.  The original source has not been made available by the manufacturer and there is no known way to restore the factory firmware at this time.  This code is a work in progress, but is being released so that anyone with a bricked board can restore most of the default functionality.  Suggestions and PRs are welcome.  Use at your own risk.

You must download QMK from https://github.com/mechmerlin/qmk_firmware to compiile this firmware.  Simply drop the xo87 folder into the qmk keyboards folder and run make xo87/rgb:production.  Alternatively, you can use the prebuilt firmware provided here if you do not with to build your own or customize the keyamps.  You can then use an ISP flasher to send the production firmware to the board.  After you are running this firmware, you can rebuild and flash via bootloader like normal.  DO NOT FLASH THE STOCK FIRMARE!  Flashing the stock firmware will cause your keyboard to become unresponsive and require you to reflash with ISP again.
