#/bin/bash
VENDOR_ID="8d1d"
PRODUCT_ID="b4c2"
BOOT_LABEL="RPI-RP2"
PWD=$(pwd)
MOUNT_TO="$PWD/.mount"
FWF=$(ls -t $PWD/.build/*.uf2 | head -1)
i=1
sp="/-\|"

mount_indil() {
  while true; do
    if [[ -n $(lsblk -ro LABEL | grep $BOOT_LABEL) ]]; then
      break
    fi
    printf "\b${sp:i++%${#sp}:1}";
    sleep 0.25;
  done
  echo -e "\r\e[K"

  DEV_PATH=$(lsblk -ro NAME,LABEL | grep $BOOT_LABEL | awk '{print "/dev/"$1}');
  MOUNT_POINT=$(lsblk -no MOUNTPOINT $DEV_PATH)

  if [[ -z $MOUNT_POINT ]]; then
    MOUNT_POINT=$MOUNT_TO
    echo "Mounting on $MOUNT_POINT..."
    mkdir -p $MOUNT_POINT
    mount $DEV_PATH $MOUNT_POINT
  else
    echo "Already mounted on $MOUNT_POINT"
  fi
}

flash() {
  cp $FWF $MOUNT_POINT
  while true; do
    if [[ -n $(lsusb | grep -i $VENDOR_ID:$PRODUCT_ID) ]]; then
      break
    fi
    printf "\b${sp:i++%${#sp}:1}";
    sleep 0.25;
  done
  echo -e "\r\e[K"
}

echo "Please enter flashing mode on left side..."
mount_indil
echo "Flashing left side..."
flash
echo "Please enter flashing mode on right side..."
mount_indil
echo "Flashing right side..."
flash
echo "Done!"

