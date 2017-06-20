#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/string.h>
#include <linux/ctype.h>

#include "acsmx.h"
#include "acsmx.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SQ");
MODULE_DESCRIPTION("AC");
MODULE_VERSION("1.0");

unsigned char text[MAXLEN];
extern int nline;

int nocase = 0;
ACSM_STRUCT * acsm;

int add_pattern(char *p)
{
	acsmAddPattern(acsm, p, strlen (p), nocase);
	/* Generate GtoTo Table and Fail Table */

	return 0;
}

int end_add_pattern(void)
{
    acsmCompile(acsm);
	return 0;
}

int AC_match(char *t) {
	acsmSearch(acsm, t, strlen(t), PrintMatch);
	return 0;
}

// 模块加载
static int init_hook_module(void)
{
    printk(KERN_ALERT "kernel_AC: insmod\n");
    char *t = kmalloc(sizeof(char)*40, GFP_ATOMIC);
    //添加模式集
    acsm = acsmNew();

	return 0;
}

// 模块卸载
static void cleanup_hook_module(void)
{
    acsmFree(acsm);
	printk(KERN_ALERT "kernel_AC: rmmod\n");
}

module_init(init_hook_module);
module_exit(cleanup_hook_module);
EXPORT_SYMBOL(AC_match);
EXPORT_SYMBOL(add_pattern);
EXPORT_SYMBOL(end_add_pattern);
