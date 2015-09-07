#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	struct udev *udev;
	struct udev_device *dev;
	struct udev_monitor *mon;

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

	while (1) {
		dev = udev_monitor_receive_device(mon);
		if (dev) {
			printf("\n[INFO] Got Device\n");
			printf("   [INFO] Device Name: %s\n", udev_device_get_sysname(dev));
						
			if (udev_device_get_sysname(dev) == "ADP1") {
				if (udev_device_get_sysattr_value(dev, "online") == "1") {
					printf("\n    [INFO] AC Adapter State: Online");
				}
				else if (udev_device_get_sysattr_value(dev, "online") == "0") {
					printf("\n    [INFO] AC Adapter State: Offline");
				}
			}

			udev_device_unref(dev);
		}
	}

	udev_unref(udev);
}