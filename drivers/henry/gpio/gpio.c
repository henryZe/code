/*
	reference to drivers/input/keyboard/gpio_keys.c
*/
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#include "gpio.h"

struct gpio_button_data {
	const struct gpio_key_button *button;
	struct input_dev *input;
	struct timer_list timer;
	struct work_struct work;
	unsigned int timer_debounce;		/* in msecs */
	unsigned int irq;
	spinlock_t lock;
	bool disabled;
	bool key_pressed;
};

static irqreturn_t gpio_keys_gpio_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;

	BUG_ON(irq != bdata->irq);

	if (bdata->button->wakeup)
		pm_stay_awake(bdata->input->dev.parent);

	if (bdata->timer_debounce)
		mod_timer(&bdata->timer,
			jiffies + msecs_to_jiffies(bdata->timer_debounce));
	else
		schedule_work(&bdata->work);

	return IRQ_HANDLED;
}

static void gpio_keys_gpio_work_func(struct work_struct *work)
{
	struct gpio_button_data *bdata = container_of(work, struct gpio_button_data, work);

	gpio_keys_gpio_report_event(bdata);

	if (bdata->button->wakeup)
		pm_relax(bdata->input->dev.parent);
}

static int gpio_keys_setup_key(struct platform_device *pdev,
					struct input_dev *input,
					struct gpio_button_data *bdata,
					const struct gpio_keys_button *button)
{
	int error;

	error = request_any_context_irq(bdata->irq, isr, irqflags, desc, bdata);
	if (error < 0) {
		printk("Unable to claim irq %d; error %d\n", bdata->irq, error);
		goto fail;
	}

fail:
	return
}

static void gpio_remove_key(struct gpio_button_data *bdata)
{
	free_irq(bdata->irq, bdata);

	if (bdata->timer_debounce)
		/* wait timer work over */
		del_timer_sync(&bdata->timer);

	cancel_work_sync(&bdata->work);

	if (gpio_is_valid(bdata->button->gpio))
		gpio_free(bdata->button->gpio);
}

MODULE_AUTHOR("Henry.Zeng");
MODULE_DESCRIPTION("gpio");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0.0");
