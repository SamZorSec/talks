#!/bin/sh

# sudo apt install adb zipalign apksigner
# apktool: https://apktool.org/

# generate a keystore
# keytool -genkey -v -keystore my.keystore -keyalg RSA -keysize 2048 -validity 10000 -alias app

# disassemble the APK and perform the modifications (AndroidManifest.xml for example)
# apktool d Original/base.apk -o Rebranded

APP_NAME="Rebranded"
OUT_DIR="${PWD}/${APP_NAME}/dist"
APP_BASE="${OUT_DIR}/base.apk"
APP_ALIGNED="${OUT_DIR}/base_aligned.apk"
APP_SIGNED="${OUT_DIR}/base_signed.apk"

# clean the destination folder
rm "$APP_BASE"
rm "$APP_ZIPPED"
rm "$APP_ALIGNED"

# repack the application
apktool b "$APP_NAME"

# optimize the application
zipalign -p -v 4 "$APP_BASE" "$APP_ALIGNED"

# sign the application
apksigner sign --ks-key-alias app --ks my.keystore --out "$APP_SIGNED" "$APP_ALIGNED"

# install the application
adb install "$APP_SIGNED"