/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.
 */

#ifndef _SOC_PM_H_
#define _SOC_PM_H_

#include <arch/io.h>
#include <soc/pmc.h>

/* ACPI_BASE_ADDRESS / PMBASE */

#define PM1_STS			0x00
#define  WAK_STS		(1 << 15)
#define  PCIEXPWAK_STS		(1 << 14)
#define  PRBTNOR_STS		(1 << 11)
#define  RTC_STS		(1 << 10)
#define  PWRBTN_STS		(1 << 8)
#define  GBL_STS		(1 << 5)
#define  BM_STS			(1 << 4)
#define  TMROF_STS		(1 << 0)
#define PM1_EN			0x02
#define  PCIEXPWAK_DIS		(1 << 14)
#define  RTC_EN			(1 << 10)
#define  PWRBTN_EN		(1 << 8)
#define  GBL_EN			(1 << 5)
#define  TMROF_EN		(1 << 0)
#define PM1_CNT			0x04
#define  SLP_EN			(1 << 13)
#define  SLP_TYP		(7 << 10)
#define   SLP_TYP_SHIFT         10
#define   SLP_TYP_S0		0
#define   SLP_TYP_S1		1
#define   SLP_TYP_S3		5
#define   SLP_TYP_S4		6
#define   SLP_TYP_S5		7
#define  GBL_RLS		(1 << 2)
#define  BM_RLD			(1 << 1)
#define  SCI_EN			(1 << 0)
#define PM1_TMR			0x08
#define SMI_EN			0x30
#define  XHCI_SMI_EN		(1 << 31)
#define  ME_SMI_EN		(1 << 30)
#define  GPIO_UNLOCK_SMI_EN	(1 << 27)
#define  INTEL_USB2_EN		(1 << 18)
#define  LEGACY_USB2_EN		(1 << 17)
#define  PERIODIC_EN		(1 << 14)
#define  TCO_EN			(1 << 13)
#define  MCSMI_EN		(1 << 11)
#define  BIOS_RLS		(1 <<  7)
#define  SWSMI_TMR_EN		(1 <<  6)
#define  APMC_EN		(1 <<  5)
#define  SLP_SMI_EN		(1 <<  4)
#define  LEGACY_USB_EN		(1 <<  3)
#define  BIOS_EN		(1 <<  2)
#define  EOS			(1 <<  1)
#define  GBL_SMI_EN		(1 <<  0)
#define SMI_STS			0x34
#define UPWRC			0x3c
#define  UPWRC_WS		(1 << 8)
#define  UPWRC_WE		(1 << 1)
#define  UPWRC_SMI		(1 << 0)
#define GPE_CNTL		0x42
#define  SWGPE_CTRL		(1 << 1)
#define DEVACT_STS		0x44
#define PM2_CNT			0x50

#define GPE0_REG_MAX		4
#define GPE0_REG_SIZE		32
#define GPE0_STS(x)		(0x80 + (x * 4))
#define  GPE_31_0		0	/* 0x80/0x90 = GPE[31:0] */
#define  GPE_63_32		1	/* 0x84/0x94 = GPE[63:32] */
#define  GPE_95_64		2	/* 0x88/0x98 = GPE[95:64] */
#define  GPE_STD		3	/* 0x8c/0x9c = Standard GPE */
#define   WADT_STS		(1 << 18)
#define   LAN_WAK_STS		(1 << 16)
#define   GPIO_T2_STS		(1 << 15)
#define   ESPI_STS		(1 << 14)
#define   PME_B0_STS		(1 << 13)
#define   ME_SCI_STS		(1 << 12)
#define   PME_STS		(1 << 11)
#define   BATLOW_STS		(1 << 10)
#define   PCI_EXP_STS		(1 << 9)
#define   SMB_WAK_STS		(1 << 7)
#define   TCOSCI_STS		(1 << 6)
#define   SWGPE_STS		(1 << 2)
#define   HOT_PLUG_STS		(1 << 1)
#define GPE0_EN(x)		(0x90 + (x * 4))
#define   WADT_EN		(1 << 18)
#define   LAN_WAK_EN		(1 << 16)
#define   GPIO_T2_EN		(1 << 15)
#define   ESPI_EN		(1 << 14)
#define   PME_B0_EN		(1 << 13)
#define   ME_SCI_EN		(1 << 12)
#define   PME_EN		(1 << 11)
#define   BATLOW_EN		(1 << 10)
#define   PCI_EXP_EN		(1 << 9)
#define   TCOSCI_EN		(1 << 6)
#define   SWGPE_EN		(1 << 2)
#define   HOT_PLUG_EN		(1 << 1)

#define MAINBOARD_POWER_OFF	0
#define MAINBOARD_POWER_ON	1
#define MAINBOARD_POWER_KEEP	2

#define SLEEP_STATE_S0		0
#define SLEEP_STATE_S3		3
#define SLEEP_STATE_S5		5

struct chipset_power_state {
	uint16_t pm1_sts;
	uint16_t pm1_en;
	uint32_t pm1_cnt;
	uint16_t tco1_sts;
	uint16_t tco2_sts;
	uint32_t gpe0_sts[4];
	uint32_t gpe0_en[4];
	uint32_t gen_pmcon_a;
	uint32_t gen_pmcon_b;
	uint32_t gblrst_cause[2];
	uint32_t prev_sleep_state;
} __attribute__ ((packed));

/* PM1_CNT */
void enable_pm1_control(uint32_t mask);
void disable_pm1_control(uint32_t mask);

/* PM1 */
uint16_t clear_pm1_status(void);
void enable_pm1(uint16_t events);
uint32_t clear_smi_status(void);

/* SMI */
void enable_smi(uint32_t mask);
void disable_smi(uint32_t mask);

/* ALT_GP_SMI */
uint32_t clear_alt_smi_status(void);
void enable_alt_smi(int gpionum, u32 mask);
void reset_alt_smi_status(void);

/* TCO */
uint32_t clear_tco_status(void);
void enable_tco_sci(void);

/* GPE0 */
uint32_t clear_gpe_status(void);
void clear_gpe_enable(void);
void enable_all_gpe(uint32_t set1, uint32_t set2, uint32_t set3, uint32_t set4);
void disable_all_gpe(void);
void enable_gpe(uint32_t mask);
void disable_gpe(uint32_t mask);

/* Return the selected ACPI SCI IRQ */
int acpi_sci_irq(void);

/* Get base address PMC memory mapped registers. */
uint8_t *pmc_mmio_regs(void);
/* Get base address of TCO I/O registers. */
uint16_t pmc_tco_regs(void);

static inline int deep_s3_enabled(void)
{
	uint32_t deep_s3_pol;

	deep_s3_pol = read32(pmc_mmio_regs() + S3_PWRGATE_POL);
	return !!(deep_s3_pol & (S3DC_GATE_SUS | S3AC_GATE_SUS));
}

#endif