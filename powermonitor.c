#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{
	struct udev *udev;
	struct udev_device *dev;
	struct udev_monitor *mon;
	int fd;

	/* Create the udev object */
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		exit(1);
	}

	/* Set up a monitor to monitor power_supply devices */
	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "power_supply", NULL);
	udev_monitor_enable_receiving(mon);
	printf("[INFO] Monitoring...\n");

	while (1) {
		dev = udev_monitor_receive_device(mon);
			if (dev) {
				
				if(strcmp(udev_device_get_sysname(dev), "ADP1") == 0) {
					printf("\n  [DEBUG] Found ADP1\n");
					
					if(strcmp(udev_device_get_sysattr_value(dev, "online"), "1") == 0) {
						printf("\n  [INFO] AC Adapter State: Online\n");
						changeBrightness(937);
					}
					
					else if (strcmp(udev_device_get_sysattr_value(dev, "online"), "1") < 0) {
						printf("\n  [INFO] AC Adapter State: Offline\n");
						changeBrightness(92);
					}
				}
			}
		udev_device_unref(dev);
		}
	udev_unref(udev);
	return 0;
}

int changeBrightness(int v) {

	int val = v;

	/* FILE structure pointers, for the return value of fopen() */
	FILE* f_write;

	f_write = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
	if (!f_write) { /* open operation failed. */
	    perror("Failed opening file '/sys/class/backlight/intel_backlight/brightness' for reading:");
	    exit(1);
	}
	fprintf(f_write, "%i", val);
	fclose(f_write);

	return;
}
