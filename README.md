# This-Shortcut-Thing
A fork of the abandoned [That-Shortcut-Thingy](https://github.com/SUOlivia/That-Shortcut-Thingy). 
Boot Firms with a CIA shortcut

Usage instructions:
  Needs [FastBoot3ds](https://github.com/derrekr/fastboot3DS) or [GodMode9](https://github.com/d0k3/GodMode9) as Firm0 instead of B9S  
  1. Install the CIA
  2. Launch the shortcut
  3. ???
  4. Profit
  
  (Note that if you are using FastBoot3ds, FCRAM Boot needs to be enabled. It is located under Boot Setup)

Building instructions:
  Needs [bannertool](https://github.com/Steveice10/bannertool) and [makerom](https://github.com/3DSGuy/Project_CTR/tree/master/makerom) set in environment
  1. Put the icon, banner image and banner sound in the assets folder
  2. Change `APP_TITLE`, `APP_DESCRIPTION`, `APP_AUTHOR`, `APP_PRODUCT_CODE` and `APP_UNIQUE_ID` to your needs 
  3. Drop the payload and the splash screen (using the same method as Luma3ds splashes) in the romfs folder
  4. Run `make`
  5. Have fun!

  When finished, remember to run `clean` to reset and get rid of old files before making another shortcut :3


Note: 
When building, two errors will be produced ending in `[-Wint-conversion]`. It works fine even with this error, and I'm hoping to fix it eventually.
