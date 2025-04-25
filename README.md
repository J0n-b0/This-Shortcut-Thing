# This-Shortcut-Thing

Boot Firms with a CIA shortcut

Requires [FastBoot3ds](https://github.com/derrekr/fastboot3DS) with FCRAM enabled or [GodMode9](https://github.com/d0k3/GodMode9) as Firm0 instead of B9S 
  
Building instructions:
  Needs [bannertool](https://github.com/diasurgical/bannertool) and [makerom](https://github.com/3DSGuy/Project_CTR/tree/master/makerom) set in environment

  1. Put the icon, banner image and banner sound in the assets folder
  2. Change `APP_TITLE`, `APP_DESCRIPTION`, `APP_AUTHOR`, `APP_PRODUCT_CODE` and `APP_UNIQUE_ID` to your needs 
  3. Drop the payload and the splash screen (use the same method as you would for Luma3ds splashes) in the romfs folder
  4. Run `make`
  5. Have fun!
