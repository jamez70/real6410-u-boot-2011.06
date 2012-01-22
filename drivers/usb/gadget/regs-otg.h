/* linux/arch/arm/plat-s3c/include/plat/regs-otg.h
 *
 * Copyright (C) 2004 Herbert Poetzl <herbert at 13thfloor.at>
 *
 * Registers remapping:
 * Lukasz Majewski <l.majewski at samsumg.com>
 *
 * This include file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef __ASM_ARCH_REGS_USB_OTG_HS_H
#define __ASM_ARCH_REGS_USB_OTG_HS_H

/* USB2.0 OTG Controller register */
struct s3c_usbotg_phy {
	u32 phypwr;
	u32 phyclk;
	u32 rstcon;
};

/* Device Logical IN Endpoint-Specific Registers */
struct s3c_dev_in_endp {
	u32 diepctl;
	u8  res1[4];
	u32 diepint;
	u8  res2[4];
	u32 dieptsiz;
	u32 diepdma;
	u8  res3[4];
	u32 diepdmab;
};

/* Device Logical OUT Endpoint-Specific Registers */
struct s3c_dev_out_endp {
	u32 doepctl;
	u8  res1[4];
	u32 doepint;
	u8  res2[4];
	u32 doeptsiz;
	u32 doepdma;
	u8  res3[4];
	u32 doepdmab;
};

struct ep_fifo {
	u32 fifo;
	u8  res[4092];
};

/* USB2.0 OTG Controller register */
struct s3c_usbotg_reg {
	/* Core Global Registers */
	u32 gotgctl; /* OTG Control & Status */
	u32 gotgint; /* OTG Interrupt */
	u32 gahbcfg; /* Core AHB Configuration */
	u32 gusbcfg; /* Core USB Configuration */
	u32 grstctl; /* Core Reset */
	u32 gintsts; /* Core Interrupt */
	u32 gintmsk; /* Core Interrupt Mask */
	u32 grxstsr; /* Receive Status Debug Read/Status Read */
	u32 grxstsp; /* Receive Status Debug Pop/Status Pop */
	u32 grxfsiz; /* Receive FIFO Size */
	u32 gnptxfsiz; /* Non-Periodic Transmit FIFO Size */
	u8  res1[216];
	u32 dieptxf[15]; /* Device Periodic Transmit FIFO size register */
	u8  res2[1728];
	/* Device Configuration */
	u32 dcfg; /* Device Configuration Register */
	u32 dctl; /* Device Control */
	u32 dsts; /* Device Status */
	u8  res3[4];
	u32 diepmsk; /* Device IN Endpoint Common Interrupt Mask */
	u32 doepmsk; /* Device OUT Endpoint Common Interrupt Mask */
	u32 daint; /* Device All Endpoints Interrupt */
	u32 daintmsk; /* Device All Endpoints Interrupt Mask */
	u8  res4[224];
	struct s3c_dev_in_endp in_endp[16];
	struct s3c_dev_out_endp out_endp[16];
	u8  res5[768];
	struct ep_fifo ep[16];
};

/*===================================================================== */
/*definitions related to CSR setting */

/* S3C_UDC_OTG_GOTGCTL */
#define B_SESSION_VALID		(0x1<<19)
#define A_SESSION_VALID		(0x1<<18)

/* S3C_UDC_OTG_GAHBCFG */
#define PTXFE_HALF			(0<<8)
#define PTXFE_ZERO			(1<<8)
#define NPTXFE_HALF			(0<<7)
#define NPTXFE_ZERO			(1<<7)
#define MODE_SLAVE			(0<<5)
#define MODE_DMA			(1<<5)
#define BURST_SINGLE			(0<<1)
#define BURST_INCR			(1<<1)
#define BURST_INCR4			(3<<1)
#define BURST_INCR8			(5<<1)
#define BURST_INCR16			(7<<1)
#define GBL_INT_UNMASK			(1<<0)
#define GBL_INT_MASK			(0<<0)

/* S3C_UDC_OTG_GRSTCTL */
#define AHB_MASTER_IDLE		(1u<<31)
#define CORE_SOFT_RESET		(0x1<<0)

/* S3C_UDC_OTG_GINTSTS/S3C_UDC_OTG_GINTMSK core interrupt register */
#define INT_RESUME			(1u<<31)
#define INT_DISCONN			(0x1<<29)
#define INT_CONN_ID_STS_CNG		(0x1<<28)
#define INT_OUT_EP			(0x1<<19)
#define INT_IN_EP			(0x1<<18)
#define INT_ENUMDONE			(0x1<<13)
#define INT_RESET			(0x1<<12)
#define INT_SUSPEND			(0x1<<11)
#define INT_EARLY_SUSPEND		(0x1<<10)
#define INT_NP_TX_FIFO_EMPTY		(0x1<<5)
#define INT_RX_FIFO_NOT_EMPTY		(0x1<<4)
#define INT_SOF			(0x1<<3)
#define INT_DEV_MODE			(0x0<<0)
#define INT_HOST_MODE			(0x1<<1)
#define INT_GOUTNakEff			(0x01<<7)
#define INT_GINNakEff			(0x01<<6)

#define FULL_SPEED_CONTROL_PKT_SIZE	8
#define FULL_SPEED_BULK_PKT_SIZE	64

#define HIGH_SPEED_CONTROL_PKT_SIZE	64
#define HIGH_SPEED_BULK_PKT_SIZE	512

#define RX_FIFO_SIZE			(1024*2)
#define NPTX_FIFO_SIZE			(1024*2)
#define PTX_FIFO_SIZE			(1024*2)

#define DEPCTL_TXFNUM_0		(0x0<<22)
#define DEPCTL_TXFNUM_1		(0x1<<22)
#define DEPCTL_TXFNUM_2		(0x2<<22)
#define DEPCTL_TXFNUM_3		(0x3<<22)
#define DEPCTL_TXFNUM_4		(0x4<<22)

/* Enumeration speed */
#define USB_HIGH_30_60MHZ		(0x0<<1)
#define USB_FULL_30_60MHZ		(0x1<<1)
#define USB_LOW_6MHZ			(0x2<<1)
#define USB_FULL_48MHZ			(0x3<<1)

/* S3C_UDC_OTG_GRXSTSP STATUS */
#define OUT_PKT_RECEIVED		(0x2<<17)
#define OUT_TRANSFER_COMPLELTED	(0x3<<17)
#define SETUP_TRANSACTION_COMPLETED	(0x4<<17)
#define SETUP_PKT_RECEIVED		(0x6<<17)
#define GLOBAL_OUT_NAK			(0x1<<17)

/* S3C_UDC_OTG_DCTL device control register */
#define NORMAL_OPERATION		(0x1<<0)
#define SOFT_DISCONNECT		(0x1<<1)

/* S3C_UDC_OTG_DAINT device all endpoint interrupt register */
#define DAINT_OUT_BIT			(16)
#define DAINT_MASK			(0xFFFF)

/* S3C_UDC_OTG_DIEPCTL0/DOEPCTL0 device
   control IN/OUT endpoint 0 control register */
#define DEPCTL_EPENA			(0x1<<31)
#define DEPCTL_EPDIS			(0x1<<30)
#define DEPCTL_SETD1PID		(0x1<<29)
#define DEPCTL_SETD0PID		(0x1<<28)
#define DEPCTL_SNAK			(0x1<<27)
#define DEPCTL_CNAK			(0x1<<26)
#define DEPCTL_STALL			(0x1<<21)
#define DEPCTL_TYPE_BIT		(18)
#define DEPCTL_TYPE_MASK		(0x3<<18)
#define DEPCTL_CTRL_TYPE		(0x0<<18)
#define DEPCTL_ISO_TYPE		(0x1<<18)
#define DEPCTL_BULK_TYPE		(0x2<<18)
#define DEPCTL_INTR_TYPE		(0x3<<18)
#define DEPCTL_USBACTEP		(0x1<<15)
#define DEPCTL_NEXT_EP_BIT		(11)
#define DEPCTL_MPS_BIT			(0)
#define DEPCTL_MPS_MASK		(0x7FF)

#define DEPCTL0_MPS_64			(0x0<<0)
#define DEPCTL0_MPS_32			(0x1<<0)
#define DEPCTL0_MPS_16			(0x2<<0)
#define DEPCTL0_MPS_8			(0x3<<0)
#define DEPCTL_MPS_BULK_512		(512<<0)
#define DEPCTL_MPS_INT_MPS_16		(16<<0)

#define DIEPCTL0_NEXT_EP_BIT		(11)


/* S3C_UDC_OTG_DIEPMSK/DOEPMSK device IN/OUT endpoint
   common interrupt mask register */
/* S3C_UDC_OTG_DIEPINTn/DOEPINTn device IN/OUT endpoint interrupt register */
#define BACK2BACK_SETUP_RECEIVED	(0x1<<6)
#define INTKNEPMIS			(0x1<<5)
#define INTKN_TXFEMP			(0x1<<4)
#define NON_ISO_IN_EP_TIMEOUT		(0x1<<3)
#define CTRL_OUT_EP_SETUP_PHASE_DONE	(0x1<<3)
#define AHB_ERROR			(0x1<<2)
#define EPDISBLD			(0x1<<1)
#define TRANSFER_DONE			(0x1<<0)

#endif
