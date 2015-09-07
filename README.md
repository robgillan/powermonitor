#powermonitor
This is an Ubuntu 15.04 app that monitors changes in the power supply
(AC adapter or battery) and changes screen brightness based on
whether the laptop is plugged in or not. This likely only works
with systems using an Intel onboard graphics set as the brightness
file is located at `/sys/class/backlight/intel_backlight/brightness`
on my system (Dell Inspiron 7000 series).

Currently it is implemented using a loop that will cause blocking;
On my to-do list is to someday update this.

NOTE: sudo/root is required to make changes to the brightness file
that this program operates on.
