// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <init.h>
#include <log.h>
#include <asm/arch-rockchip/periph.h>
#include <power/regulator.h>

#include <blk.h>
#include <dfu.h>
#include <env.h>
#include <memalign.h>
#include <misc.h>
#include <mtd.h>
#include <mtd_node.h>

#ifndef CONFIG_SPL_BUILD
int board_early_init_f(void)
{
	struct udevice *regulator;
	int ret;

	ret = regulator_get_by_platname("vcc5v0_host", &regulator);
	if (ret) {
		debug("%s vcc5v0_host init fail! ret %d\n", __func__, ret);
		goto out;
	}

	ret = regulator_set_enable(regulator, true);
	if (ret)
		debug("%s vcc5v0-host-en set fail! ret %d\n", __func__, ret);

out:
	return 0;
}
#endif



/* ALT_INFO Macro Function below added for DFU_ALT_INFO */

#ifdef CONFIG_SET_DFU_ALT_INFO

#define CONFIG_DFU_ALT_BOOT_SD \
	"mmc 1=idbloader-img raw 0x40 0x2000;u-boot-itb raw 0x4000 0x2000\0"

#define CONFIG_DFU_ALT_BOOT_EMMC \
	"mmc 0=idbloader-img raw 0x40 0x2000;u-boot-itb raw 0x4000 0x2000\0"

char *get_dfu_alt_boot(char *interface, char *devstr)
{
	char *alt_boot;
	struct mmc *mmc;
	int dev_num = 0;

	if (devstr == NULL) {
		devstr = "0";
	}
	alt_boot = env_get("dfu_alt_boot");

	if (alt_boot == NULL) {
		dev_num = simple_strtoul(devstr, NULL, 10);
		mmc = find_mmc_device(dev_num);
		if (!mmc) {
			return NULL;
		}
		if (mmc_init(mmc)) {
			return NULL;
			}
		if (IS_SD(mmc)) {
			alt_boot = CONFIG_DFU_ALT_BOOT_SD;
		} else {
			alt_boot = CONFIG_DFU_ALT_BOOT_EMMC;
		}
	}
	return alt_boot;
}
#endif

#ifdef CONFIG_SET_DFU_ALT_INFO
#define CONFIG_SET_DFU_ALT_BUF_LEN (SZ_1K)
void set_dfu_alt_info(char *interface, char *devstr)
{
	size_t buf_size = CONFIG_SET_DFU_ALT_BUF_LEN;

	ALLOC_CACHE_ALIGN_BUFFER(char, buf, buf_size);
	char *alt_info = "Settings not found!";
	char *status = "error!\n";
	char *alt_setting;

	int offset = 0;

	alt_setting = get_dfu_alt_boot(interface, devstr);
	if (alt_setting) {
		env_set("dfu_alt_boot", alt_setting);
		offset = snprintf(buf, buf_size, "%s", alt_setting);
	}

	if (offset) {
		alt_info = buf;
		status = "done\n";
	}

	env_set("dfu_alt_info", alt_info);
	puts(status);
}

#endif
