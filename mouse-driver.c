#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

// probe function
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "[*] USB Mouse (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0;
}

// disconnect
static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] USB Mouse driver removed\n");
}

// usb_device_id
static struct usb_device_id pen_table[] = {
	// 0e0f:0003
	{ USB_DEVICE(0x0e0f, 0x0003) },
	{}
};

MODULE_DEVICE_TABLE(usb, pen_table);

// usb_driver
static struct usb_driver pen_driver =
{
	.name = "USB Mouse Driver",
	.id_table = pen_table,
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};



static int __init pen_init(void){
	int ret = -1;
	printk(KERN_INFO "[*] USB Mouse Driver init");
	printk(KERN_INFO "\tRegistering Driver with Kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\tRegistration is complete");
	return ret;
}

static void __exit pen_exit(void){
	printk(KERN_INFO "[*] USB Mouse Driver exit");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "\tunregistration complete");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");

