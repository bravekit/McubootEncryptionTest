.. _NRF CONNECT SDK FOTA-sample:


######

Overview
********

This sample allows to perform FOTA via Bluetooth for NRF5340-DK with purpose to figure out how to encrypt firmware image updates

Building and Running
********************
To enable encryption it's possible to edit  v1.7.1\\nrf\\modules\\mcuboot\\CMakeLists.txt file -  add "--encrypt {path to key}/enc-rsa2048-pub.pem" after row #109
  
Unfortunatelly it doesn't help, and after downloading signed encrypted image to NRF5340 it starts attemting to update net core (without success)

Another easier method - just use command line signing, like this 

C:/NordicNrf/v1.7.1/bootloader/mcuboot/scripts/imgtool.py sign --key C:/NordicNrf/v1.7.1/bootloader/mcuboot/root-rsa-2048.pem --header-size 0x200 --align 4 --version 5.6.9+8 --pad-header --slot-size 0x74000  --encrypt C:/NordicNrf/v1.7.1/bootloader/mcuboot/enc-rsa2048-pub.pem C:/MyWorkC/TenniRoboAll/Firmware/NRF52/McubootEncryptionTest/build/zephyr/app_to_sign.bin C:/MyWorkC/TenniRoboAll/Firmware/NRF52/McubootEncryptionTest/build/zephyr/app_update_encrypted.bin 

