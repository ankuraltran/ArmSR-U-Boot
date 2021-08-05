// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Capgemini Engineering
 */

#include <common.h>
#include <dm.h>
#include <init.h>
#include <log.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/periph.h>
#include <asm/arch-rockchip/grf_rk3399.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/misc.h>

#define GRF_BASE        0xff770000
int board_early_init_f(void)
{
	struct rk3399_grf_regs *grf = (void *)GRF_BASE;

	rk_setreg(&grf->io_vsel, BIT(0));
	return 0;
}
