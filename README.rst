.. _NRF CONNECT SDK FOTA-sample:


######

Overview
********

This sample allows to perform FOTA via Bluetooth for NRF5340-DK with purpose to figure out how to encrypt firmware image updates


Building and Running
********************
To enable encryption it's possible to edit  v1.7.1\nrf\modules\mcuboot\CMakeLists.txt file -  add "--encrypt path to key/enc-rsa2048-pub.pem" after row #109
  
Unfortunatelly it doesn't help, and after downloading signed encrypted image to NRF5340 it starts attemting to update net core (without success)

