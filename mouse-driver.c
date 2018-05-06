#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

// probe function
static int mouse_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "[*] USB Mouse (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0;
}

// disconnect
static void mouse_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] USB Mouse driver removed\n");
}

// usb_device_id
static struct usb_device_id mouse_table[] = {
	// CAMBIAR VENDOR y PRODUCT number
	{ USB_DEVICE(0x0e0f, 0x0003) },
	{}
};

MODULE_DEVICE_TABLE(usb, mouse_table);

// usb_driver
static struct usb_driver mouse_driver =
{
	.name = "USB Mouse Driver",
	.id_table = mouse_table,
	.probe = mouse_probe,
	.disconnect = mouse_disconnect,
};



static int __init mouse_init(void){
	int ret = -1;
	printk(KERN_INFO "[*] USB Mouse Driver init");
	printk(KERN_INFO "\tRegistering Driver with Kernel");
	ret = usb_register(&mouse_driver);
	printk(KERN_INFO "\tRegistration is complete");
	return ret;
}

static void __exit mouse_exit(void){
	printk(KERN_INFO "[*] USB Mouse Driver exit");
	usb_deregister(&mouse_driver);
	printk(KERN_INFO "\tunregistration complete");
}

module_init(mouse_init);
module_exit(mouse_exit);

MODULE_LICENSE("GPL");

