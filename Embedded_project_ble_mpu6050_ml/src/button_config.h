#include <drivers/gpio.h>

#define SW1_NODE		DT_ALIAS(sw0)
#define SW1_GPIO_LABEL	DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW1_GPIO_PIN	DT_GPIO_PIN(SW0_NODE, gpios)
#define SW1_GPIO_FLAGS	(GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
#define BUTTON_DEBOUNCE_DELAY_MS 	100
/* Variables used for button debouncing */
static volatile uint32_t time_1, last_time_1, time_2, last_time_2;
static const struct gpio_dt_spec button_1 = GPIO_DT_SPEC_GET_OR(SW1_NODE, gpios,
							      {0});
static struct gpio_callback button_cb_data_1;

#define SW2_NODE		DT_ALIAS(sw1)
#define SW2_GPIO_LABEL	DT_GPIO_LABEL(SW1_NODE, gpios)
#define SW2_GPIO_PIN	DT_GPIO_PIN(SW1_NODE, gpios)
#define SW2_GPIO_FLAGS	(GPIO_INPUT | DT_GPIO_FLAGS(SW1_NODE, gpios))
static const struct gpio_dt_spec button_2 = GPIO_DT_SPEC_GET_OR(SW2_NODE, gpios,
							      {0});
static struct gpio_callback button_cb_data_2;

extern int button_press;
extern int current_menu;
void button_pressed_1(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	/* Debounce the button */
	time_1 = k_uptime_get_32();	
	if (time_1 < last_time_1 + BUTTON_DEBOUNCE_DELAY_MS) 
	{
		last_time_1 = time_1;
		return;
	}
	printf("Button pressed %s\n", dev->name);
	time_1 = last_time_1;
	button_press = 1;
}
void button_pressed_2(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	/* Debounce the button */
	time_2 = k_uptime_get_32();
	if (time_2 < last_time_2 + BUTTON_DEBOUNCE_DELAY_MS) 
	{
		last_time_2 = time_2;
		return;
	}
	printf("Button pressed %s\n", dev->name);
	time_2 = last_time_2;
	button_press = 2;
	current_menu = 0;
}

void button_init(void)
{
    int ret;
    // Button 1
	ret = gpio_pin_configure_dt(&button_1, GPIO_INPUT);
	ret = gpio_pin_interrupt_configure_dt(&button_1,
					      GPIO_INT_EDGE_TO_ACTIVE);
	gpio_init_callback(&button_cb_data_1, button_pressed_1, BIT(button_1.pin));
	gpio_add_callback(button_1.port, &button_cb_data_1);
	printk("Set up button at %s pin %d\n", button_1.port->name, button_1.pin);

	// Button 2
	ret = gpio_pin_configure_dt(&button_2, GPIO_INPUT);
	ret = gpio_pin_interrupt_configure_dt(&button_2,
					      GPIO_INT_EDGE_TO_ACTIVE);
	gpio_init_callback(&button_cb_data_2, button_pressed_2, BIT(button_2.pin));
	gpio_add_callback(button_2.port, &button_cb_data_2);
	printk("Set up button at %s pin %d\n", button_2.port->name, button_2.pin);
}