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

#define GRF_IO_VSEL_BT565_SHIFT 0
#define GRF_IO_VSEL_ADDR  0xff77e640

int board_early_init_f(void)
{
	/* BT565 is in 1.8v domain */
	rk_setreg(GRF_IO_VSEL_ADDR, 1 << GRF_IO_VSEL_BT565_SHIFT);

	return 0;
}
