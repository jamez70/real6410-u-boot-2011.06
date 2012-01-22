/*
 * drivers/usb/gadget/s3c_udc_otg_xfer_slave.c
 * Samsung S3C on-chip full/high speed USB OTG 2.0 device controllers
 *
 * Copyright (C) 2009 for Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#define S3C_VA_OTG 0x7c000000
#define S3C_VA_OTGSFR 0x7c100000

#define S3C_USBOTG_PHYREG(x)		((x) + S3C_VA_OTGSFR)

#define S3C_USBOTG_PHYPWR		S3C_USBOTG_PHYREG(0x0)
#define S3C_USBOTG_PHYCLK		S3C_USBOTG_PHYREG(0x4)
#define S3C_USBOTG_RSTCON		S3C_USBOTG_PHYREG(0x8)


/* USB2.0 OTG Controller register */
#define S3C_USBOTGREG(x) ((x) + S3C_VA_OTG)

//==============================================================================================
// Core Global Registers
#define S3C_UDC_OTG_GOTGCTL			S3C_USBOTGREG(0x000)		// OTG Control & Status
#define S3C_UDC_OTG_GOTGINT			S3C_USBOTGREG(0x004)		// OTG Interrupt
#define S3C_UDC_OTG_GAHBCFG			S3C_USBOTGREG(0x008)		// Core AHB Configuration
#define S3C_UDC_OTG_GUSBCFG			S3C_USBOTGREG(0x00C)		// Core USB Configuration
#define S3C_UDC_OTG_GRSTCTL			S3C_USBOTGREG(0x010)		// Core Reset
#define S3C_UDC_OTG_GINTSTS			S3C_USBOTGREG(0x014)		// Core Interrupt
#define S3C_UDC_OTG_GINTMSK			S3C_USBOTGREG(0x018)		// Core Interrupt Mask
#define S3C_UDC_OTG_GRXSTSR			S3C_USBOTGREG(0x01C)		// Receive Status Debug Read/Status Read
#define S3C_UDC_OTG_GRXSTSP			S3C_USBOTGREG(0x020)		// Receive Status Debug Pop/Status Pop
#define S3C_UDC_OTG_GRXFSIZ			S3C_USBOTGREG(0x024)		// Receive FIFO Size
#define S3C_UDC_OTG_GNPTXFSIZ		S3C_USBOTGREG(0x028)		// Non-Periodic Transmit FIFO Size
#define S3C_UDC_OTG_GNPTXSTS		S3C_USBOTGREG(0x02C)		// Non-Periodic Transmit FIFO/Queue Status

#define S3C_UDC_OTG_HPTXFSIZ		S3C_USBOTGREG(0x100)		// Host Periodic Transmit FIFO Size
#define S3C_UDC_OTG_DPTXFSIZ1		S3C_USBOTGREG(0x104)		// Device Periodic Transmit FIFO-1 Size
#define S3C_UDC_OTG_DPTXFSIZ2		S3C_USBOTGREG(0x108)		// Device Periodic Transmit FIFO-2 Size
#define S3C_UDC_OTG_DPTXFSIZ3		S3C_USBOTGREG(0x10C)		// Device Periodic Transmit FIFO-3 Size
#define S3C_UDC_OTG_DPTXFSIZ4		S3C_USBOTGREG(0x110)		// Device Periodic Transmit FIFO-4 Size
#define S3C_UDC_OTG_DPTXFSIZ5		S3C_USBOTGREG(0x114)		// Device Periodic Transmit FIFO-5 Size
#define S3C_UDC_OTG_DPTXFSIZ6		S3C_USBOTGREG(0x118)		// Device Periodic Transmit FIFO-6 Size
#define S3C_UDC_OTG_DPTXFSIZ7		S3C_USBOTGREG(0x11C)		// Device Periodic Transmit FIFO-7 Size
#define S3C_UDC_OTG_DPTXFSIZ8		S3C_USBOTGREG(0x120)		// Device Periodic Transmit FIFO-8 Size
#define S3C_UDC_OTG_DPTXFSIZ9		S3C_USBOTGREG(0x124)		// Device Periodic Transmit FIFO-9 Size
#define S3C_UDC_OTG_DPTXFSIZ10		S3C_USBOTGREG(0x128)		// Device Periodic Transmit FIFO-10 Size
#define S3C_UDC_OTG_DPTXFSIZ11		S3C_USBOTGREG(0x12C)		// Device Periodic Transmit FIFO-11 Size
#define S3C_UDC_OTG_DPTXFSIZ12		S3C_USBOTGREG(0x130)		// Device Periodic Transmit FIFO-12 Size
#define S3C_UDC_OTG_DPTXFSIZ13		S3C_USBOTGREG(0x134)		// Device Periodic Transmit FIFO-13 Size
#define S3C_UDC_OTG_DPTXFSIZ14		S3C_USBOTGREG(0x138)		// Device Periodic Transmit FIFO-14 Size
#define S3C_UDC_OTG_DPTXFSIZ15		S3C_USBOTGREG(0x13C)		// Device Periodic Transmit FIFO-15 Size

//==============================================================================================
// Host Mode Registers
//------------------------------------------------
// Host Global Registers
#define S3C_UDC_OTG_HCFG		S3C_USBOTGREG(0x400)		// Host Configuration
#define S3C_UDC_OTG_HFIR		S3C_USBOTGREG(0x404)		// Host Frame Interval
#define S3C_UDC_OTG_HFNUM		S3C_USBOTGREG(0x408)		// Host Frame Number/Frame Time Remaining
#define S3C_UDC_OTG_HPTXSTS		S3C_USBOTGREG(0x410)		// Host Periodic Transmit FIFO/Queue Status
#define S3C_UDC_OTG_HAINT		S3C_USBOTGREG(0x414)		// Host All Channels Interrupt
#define S3C_UDC_OTG_HAINTMSK	S3C_USBOTGREG(0x418)		// Host All Channels Interrupt Mask

//------------------------------------------------
// Host Port Control & Status Registers
#define S3C_UDC_OTG_HPRT		S3C_USBOTGREG(0x440)		// Host Port Control & Status

//------------------------------------------------
// Host Channel-Specific Registers
#define S3C_UDC_OTG_HCCHAR0		S3C_USBOTGREG(0x500)		// Host Channel-0 Characteristics
#define S3C_UDC_OTG_HCSPLT0		S3C_USBOTGREG(0x504)		// Host Channel-0 Split Control
#define S3C_UDC_OTG_HCINT0		S3C_USBOTGREG(0x508)		// Host Channel-0 Interrupt
#define S3C_UDC_OTG_HCINTMSK0	S3C_USBOTGREG(0x50C)		// Host Channel-0 Interrupt Mask
#define S3C_UDC_OTG_HCTSIZ0		S3C_USBOTGREG(0x510)		// Host Channel-0 Transfer Size
#define S3C_UDC_OTG_HCDMA0		S3C_USBOTGREG(0x514)		// Host Channel-0 DMA Address


//==============================================================================================
// Device Mode Registers
//------------------------------------------------
// Device Global Registers
#define S3C_UDC_OTG_DCFG		S3C_USBOTGREG(0x800)		// Device Configuration
#define S3C_UDC_OTG_DCTL		S3C_USBOTGREG(0x804)		// Device Control
#define S3C_UDC_OTG_DSTS		S3C_USBOTGREG(0x808)		// Device Status
#define S3C_UDC_OTG_DIEPMSK		S3C_USBOTGREG(0x810)		// Device IN Endpoint Common Interrupt Mask
#define S3C_UDC_OTG_DOEPMSK		S3C_USBOTGREG(0x814)		// Device OUT Endpoint Common Interrupt Mask
#define S3C_UDC_OTG_DAINT		S3C_USBOTGREG(0x818)		// Device All Endpoints Interrupt
#define S3C_UDC_OTG_DAINTMSK	S3C_USBOTGREG(0x81C)		// Device All Endpoints Interrupt Mask
#define S3C_UDC_OTG_DTKNQR1		S3C_USBOTGREG(0x820)		// Device IN Token Sequence Learning Queue Read 1
#define S3C_UDC_OTG_DTKNQR2		S3C_USBOTGREG(0x824)		// Device IN Token Sequence Learning Queue Read 2
#define S3C_UDC_OTG_DVBUSDIS	S3C_USBOTGREG(0x828)		// Device VBUS Discharge Time
#define S3C_UDC_OTG_DVBUSPULSE	S3C_USBOTGREG(0x82C)		// Device VBUS Pulsing Time
#define S3C_UDC_OTG_DTKNQR3		S3C_USBOTGREG(0x830)		// Device IN Token Sequence Learning Queue Read 3
#define S3C_UDC_OTG_DTKNQR4		S3C_USBOTGREG(0x834)		// Device IN Token Sequence Learning Queue Read 4

//------------------------------------------------
// Device Logical IN Endpoint-Specific Registers
#define S3C_UDC_OTG_DIEPCTL0		S3C_USBOTGREG(0x900)		// Device IN Endpoint 0 Control
#define S3C_UDC_OTG_DIEPINT0		S3C_USBOTGREG(0x908)		// Device IN Endpoint 0 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ0		S3C_USBOTGREG(0x910)		// Device IN Endpoint 0 Transfer Size
#define S3C_UDC_OTG_DIEPDMA0		S3C_USBOTGREG(0x914)		// Device IN Endpoint 0 DMA Address

#define S3C_UDC_OTG_DIEPCTL1		S3C_USBOTGREG(0x920)		// Device IN Endpoint 2 Control
#define S3C_UDC_OTG_DIEPINT1		S3C_USBOTGREG(0x928)		// Device IN Endpoint 2 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ1		S3C_USBOTGREG(0x930)		// Device IN Endpoint 2 Transfer Size
#define S3C_UDC_OTG_DIEPDMA1		S3C_USBOTGREG(0x934)		// Device IN Endpoint 2 DMA Address

#define S3C_UDC_OTG_DIEPCTL2		S3C_USBOTGREG(0x940)		// Device IN Endpoint 2 Control
#define S3C_UDC_OTG_DIEPINT2		S3C_USBOTGREG(0x948)		// Device IN Endpoint 2 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ2		S3C_USBOTGREG(0x950)		// Device IN Endpoint 2 Transfer Size
#define S3C_UDC_OTG_DIEPDMA2		S3C_USBOTGREG(0x954)		// Device IN Endpoint 2 DMA Address

#define S3C_UDC_OTG_DIEPCTL3		S3C_USBOTGREG(0x960)		// Device IN Endpoint 3 Control
#define S3C_UDC_OTG_DIEPINT3		S3C_USBOTGREG(0x968)		// Device IN Endpoint 3 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ3		S3C_USBOTGREG(0x970)		// Device IN Endpoint 3 Transfer Size
#define S3C_UDC_OTG_DIEPDMA3		S3C_USBOTGREG(0x974)		// Device IN Endpoint 3 DMA Address

#define S3C_UDC_OTG_DIEPCTL4		S3C_USBOTGREG(0x980)		// Device IN Endpoint 4 Control
#define S3C_UDC_OTG_DIEPINT4		S3C_USBOTGREG(0x988)		// Device IN Endpoint 4 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ4		S3C_USBOTGREG(0x990)		// Device IN Endpoint 4 Transfer Size
#define S3C_UDC_OTG_DIEPDMA4		S3C_USBOTGREG(0x994)		// Device IN Endpoint 4 DMA Address

#define S3C_UDC_OTG_DIEPCTL5		S3C_USBOTGREG(0x9a0)		// Device IN Endpoint 5 Control
#define S3C_UDC_OTG_DIEPINT5		S3C_USBOTGREG(0x9a8)		// Device IN Endpoint 5 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ5		S3C_USBOTGREG(0x9b0)		// Device IN Endpoint 5 Transfer Size
#define S3C_UDC_OTG_DIEPDMA5		S3C_USBOTGREG(0x9b4)		// Device IN Endpoint 5 DMA Address

#define S3C_UDC_OTG_DIEPCTL6		S3C_USBOTGREG(0x9c0)		// Device IN Endpoint 6 Control
#define S3C_UDC_OTG_DIEPINT6		S3C_USBOTGREG(0x9c8)		// Device IN Endpoint 6 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ6		S3C_USBOTGREG(0x9d0)		// Device IN Endpoint 6 Transfer Size
#define S3C_UDC_OTG_DIEPDMA6		S3C_USBOTGREG(0x9d4)		// Device IN Endpoint 6 DMA Address

#define S3C_UDC_OTG_DIEPCTL7		S3C_USBOTGREG(0x9e0)		// Device IN Endpoint 7 Control
#define S3C_UDC_OTG_DIEPINT7		S3C_USBOTGREG(0x9e8)		// Device IN Endpoint 7 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ7		S3C_USBOTGREG(0x9f0)		// Device IN Endpoint 7 Transfer Size
#define S3C_UDC_OTG_DIEPDMA7		S3C_USBOTGREG(0x9f4)		// Device IN Endpoint 7 DMA Address

#define S3C_UDC_OTG_DIEPCTL8		S3C_USBOTGREG(0xa00)		// Device IN Endpoint 8 Control
#define S3C_UDC_OTG_DIEPINT8		S3C_USBOTGREG(0xa08)		// Device IN Endpoint 8 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ8		S3C_USBOTGREG(0xa10)		// Device IN Endpoint 8 Transfer Size
#define S3C_UDC_OTG_DIEPDMA8		S3C_USBOTGREG(0xa14)		// Device IN Endpoint 8 DMA Address

#define S3C_UDC_OTG_DIEPCTL9		S3C_USBOTGREG(0xa20)		// Device IN Endpoint 9 Control
#define S3C_UDC_OTG_DIEPINT9		S3C_USBOTGREG(0xa28)		// Device IN Endpoint 9 Interrupt
#define S3C_UDC_OTG_DIEPTSIZ9		S3C_USBOTGREG(0xa30)		// Device IN Endpoint 9 Transfer Size
#define S3C_UDC_OTG_DIEPDMA9		S3C_USBOTGREG(0xa34)		// Device IN Endpoint 9 DMA Address

//------------------------------------------------
// Device Logical OUT Endpoint-Specific Registers
#define S3C_UDC_OTG_DOEPCTL0		S3C_USBOTGREG(0xB00)		// Device OUT Endpoint 0 Control
#define S3C_UDC_OTG_DOEPINT0		S3C_USBOTGREG(0xB08)		// Device OUT Endpoint 0 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ0		S3C_USBOTGREG(0xB10)		// Device OUT Endpoint 0 Transfer Size
#define S3C_UDC_OTG_DOEPDMA0		S3C_USBOTGREG(0xB14)		// Device OUT Endpoint 0 DMA Address

#define S3C_UDC_OTG_DOEPCTL1		S3C_USBOTGREG(0xB20)		// Device OUT Endpoint 1 Control
#define S3C_UDC_OTG_DOEPINT1		S3C_USBOTGREG(0xB28)		// Device OUT Endpoint 1 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ1		S3C_USBOTGREG(0xB30)		// Device OUT Endpoint 1 Transfer Size
#define S3C_UDC_OTG_DOEPDMA1		S3C_USBOTGREG(0xB34)		// Device OUT Endpoint 1 DMA Address

#define S3C_UDC_OTG_DOEPCTL2		S3C_USBOTGREG(0xB40)		// Device OUT Endpoint 2 Control
#define S3C_UDC_OTG_DOEPINT2		S3C_USBOTGREG(0xB48)		// Device OUT Endpoint 2 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ2		S3C_USBOTGREG(0xB50)		// Device OUT Endpoint 2 Transfer Size
#define S3C_UDC_OTG_DOEPDMA2		S3C_USBOTGREG(0xB54)		// Device OUT Endpoint 2 DMA Address

#define S3C_UDC_OTG_DOEPCTL3		S3C_USBOTGREG(0xB60)		// Device OUT Endpoint 3 Control
#define S3C_UDC_OTG_DOEPINT3		S3C_USBOTGREG(0xB68)		// Device OUT Endpoint 3 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ3		S3C_USBOTGREG(0xB70)		// Device OUT Endpoint 3 Transfer Size
#define S3C_UDC_OTG_DOEPDMA3		S3C_USBOTGREG(0xB74)		// Device OUT Endpoint 3 DMA Address

#define S3C_UDC_OTG_DOEPCTL4		S3C_USBOTGREG(0xB80)		// Device OUT Endpoint 4 Control
#define S3C_UDC_OTG_DOEPINT4		S3C_USBOTGREG(0xB88)		// Device OUT Endpoint 4 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ4		S3C_USBOTGREG(0xB90)		// Device OUT Endpoint 4 Transfer Size
#define S3C_UDC_OTG_DOEPDMA4		S3C_USBOTGREG(0xB94)		// Device OUT Endpoint 4 DMA Address

#define S3C_UDC_OTG_DOEPCTL5		S3C_USBOTGREG(0xBa0)		// Device OUT Endpoint 5 Control
#define S3C_UDC_OTG_DOEPINT5		S3C_USBOTGREG(0xBa8)		// Device OUT Endpoint 5 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ5		S3C_USBOTGREG(0xBb0)		// Device OUT Endpoint 5 Transfer Size
#define S3C_UDC_OTG_DOEPDMA5		S3C_USBOTGREG(0xBb4)		// Device OUT Endpoint 5 DMA Address

#define S3C_UDC_OTG_DOEPCTL6		S3C_USBOTGREG(0xBc0)		// Device OUT Endpoint 6 Control
#define S3C_UDC_OTG_DOEPINT6		S3C_USBOTGREG(0xBc8)		// Device OUT Endpoint 6 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ6		S3C_USBOTGREG(0xBd0)		// Device OUT Endpoint 6 Transfer Size
#define S3C_UDC_OTG_DOEPDMA6		S3C_USBOTGREG(0xBd4)		// Device OUT Endpoint 6 DMA Address

#define S3C_UDC_OTG_DOEPCTL7		S3C_USBOTGREG(0xBe0)		// Device OUT Endpoint 7 Control
#define S3C_UDC_OTG_DOEPINT7		S3C_USBOTGREG(0xBe8)		// Device OUT Endpoint 7 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ7		S3C_USBOTGREG(0xBf0)		// Device OUT Endpoint 7 Transfer Size
#define S3C_UDC_OTG_DOEPDMA7		S3C_USBOTGREG(0xBf4)		// Device OUT Endpoint 7 DMA Address

#define S3C_UDC_OTG_DOEPCTL8		S3C_USBOTGREG(0xc00)		// Device OUT Endpoint 8 Control
#define S3C_UDC_OTG_DOEPINT8		S3C_USBOTGREG(0xc08)		// Device OUT Endpoint 8 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ8		S3C_USBOTGREG(0xc10)		// Device OUT Endpoint 8 Transfer Size
#define S3C_UDC_OTG_DOEPDMA8		S3C_USBOTGREG(0xc14)		// Device OUT Endpoint 8 DMA Address

#define S3C_UDC_OTG_DOEPCTL9		S3C_USBOTGREG(0xc20)		// Device OUT Endpoint 9 Control
#define S3C_UDC_OTG_DOEPINT9		S3C_USBOTGREG(0xc28)		// Device OUT Endpoint 9 Interrupt
#define S3C_UDC_OTG_DOEPTSIZ9		S3C_USBOTGREG(0xc30)		// Device OUT Endpoint 9 Transfer Size
#define S3C_UDC_OTG_DOEPDMA9		S3C_USBOTGREG(0xc34)		// Device OUT Endpoint 9 DMA Address

//------------------------------------------------
// Endpoint FIFO address
#define S3C_UDC_OTG_EP0_FIFO		S3C_USBOTGREG(0x1000)
#define S3C_UDC_OTG_EP1_FIFO		S3C_USBOTGREG(0x2000)
#define S3C_UDC_OTG_EP2_FIFO		S3C_USBOTGREG(0x3000)
#define S3C_UDC_OTG_EP3_FIFO		S3C_USBOTGREG(0x4000)
#define S3C_UDC_OTG_EP4_FIFO		S3C_USBOTGREG(0x5000)
#define S3C_UDC_OTG_EP5_FIFO		S3C_USBOTGREG(0x6000)
#define S3C_UDC_OTG_EP6_FIFO		S3C_USBOTGREG(0x7000)
#define S3C_UDC_OTG_EP7_FIFO		S3C_USBOTGREG(0x8000)
#define S3C_UDC_OTG_EP8_FIFO		S3C_USBOTGREG(0x9000)
#define S3C_UDC_OTG_EP9_FIFO		S3C_USBOTGREG(0xa000)


//==============================================================================================
// Power and Clock Gating Registers
//------------------------------------------------
#define S3C_UDC_OTG_PCGCCTL		S3C_USBOTGREG(0x0E00)

//=====================================================================
//definitions related to CSR setting

// S3C_UDC_OTG_PCGCCTL : Power and Clock Gating Registers
#define STOP_PCLK_BIT		(0)
#define GATE_HCLK_BIT		(1)

// S3C_UDC_OTG_GOTGCTL
#define B_SESSION_VALID				(0x1<<19)
#define A_SESSION_VALID				(0x1<<18)

//S3C_UDC_OTG_DSTS: Device Status
#define	SUSPEND_STS		(0)

// S3C_UDC_OTG_GAHBCFG
#define PTXFE_HALF				(0<<8)
#define PTXFE_ZERO				(1<<8)
#define NPTXFE_HALF				(0<<7)
#define NPTXFE_ZERO				(1<<7)
#define MODE_SLAVE				(0<<5)
#define MODE_DMA				(1<<5)
#define BURST_SINGLE			(0<<1)
#define BURST_INCR				(1<<1)
#define BURST_INCR4				(3<<1)
#define BURST_INCR8				(5<<1)
#define BURST_INCR16			(7<<1)
#define GBL_INT_UNMASK			(1<<0)
#define GBL_INT_MASK			(0<<0)

// S3C_UDC_OTG_GRSTCTL
//#define AHB_MASTER_IDLE			(0x1<<31)
#define CORE_SOFT_RESET			(0x1<<0)

// S3C_UDC_OTG_GINTSTS/S3C_UDC_OTG_GINTMSK core interrupt register
//#define INT_RESUME				(0x1<<31)
#define INT_DISCONN				(0x1<<29)
#define INT_CONN_ID_STS_CNG		(0x1<<28)
#define INT_OUT_EP				(0x1<<19)
#define INT_IN_EP				(0x1<<18)
#define INT_ENUMDONE			(0x1<<13)
#define INT_RESET				(0x1<<12)
#define INT_SUSPEND				(0x1<<11)
#define INT_EARLY_SUSPEND		(0x1<<10)
//#define	INT_GOUTNakEff			(0x1<<7)
//#define	INT_GINNakEff			(0x1<<6)
#define INT_NP_TX_FIFO_EMPTY	(0x1<<5)
#define INT_RX_FIFO_NOT_EMPTY	(0x1<<4)
#define INT_SOF					(0x1<<3)
#define INT_OTG					(0x1<<2)
#define INT_MODE_MIS			(0x1<<1)
#define INT_CUR_MOD				(0x1<<0)

//#define FULL_SPEED_CONTROL_PKT_SIZE		(8)
//#define FULL_SPEED_BULK_PKT_SIZE		(64)

//#define HIGH_SPEED_CONTROL_PKT_SIZE		(64)
//#define HIGH_SPEED_BULK_PKT_SIZE		(512)

//#define RX_FIFO_SIZE				(2048)
//#define NPTX_FIFO_START_ADDR		RX_FIFO_SIZE
//#define NPTX_FIFO_SIZE				(2048)
//#define PTX_FIFO_SIZE				(2048)

#define DEPCTL_TXFNUM_0			(0x0<<22)
#define DEPCTL_TXFNUM_1			(0x1<<22)
#define DEPCTL_TXFNUM_2			(0x2<<22)
#define DEPCTL_TXFNUM_3			(0x3<<22)
#define DEPCTL_TXFNUM_4			(0x4<<22)


// Enumeration speed
#define USB_HIGH_30_60MHZ			(0x0<<1)
#define USB_FULL_30_60MHZ			(0x1<<1)
#define USB_LOW_6MHZ				(0x2<<1)
#define USB_FULL_48MHZ				(0x3<<1)

// S3C_UDC_OTG_GRXSTSP STATUS
#define OUT_PKT_RECEIVED			(0x2<<17)
#define OUT_TRANSFER_COMPLELTED		(0x3<<17)
#define SETUP_TRANSACTION_COMPLETED	(0x4<<17)
#define SETUP_PKT_RECEIVED			(0x6<<17)
#define GLOBAL_OUT_NAK				(0x1<<17)


// S3C_UDC_OTG_DCTL device control register
#define NORMAL_OPERATION			(0x1<<0)
#define SOFT_DISCONNECT				(0x1<<1)

// S3C_UDC_OTG_DIEPCTL0/DOEPCTL0 device control IN/OUT endpoint 0 control register
#define DEPCTL_EPENA				(0x1<<31)
#define DEPCTL_EPDIS				(0x1<<30)
#define DEPCTL_SNAK					(0x1<<27)
#define DEPCTL_CNAK					(0x1<<26)
#define DEPCTL_CTRL_TYPE			(0x0<<18)
#define DEPCTL_ISO_TYPE				(0x1<<18)
#define DEPCTL_BULK_TYPE			(0x2<<18)
#define DEPCTL_INTR_TYPE			(0x3<<18)
#define DEPCTL_USBACTEP				(0x1<<15)
#define DEPCTL0_MPS_64				(0x0<<0)
#define DEPCTL0_MPS_32				(0x1<<0)
#define DEPCTL0_MPS_16				(0x2<<0)
#define DEPCTL0_MPS_8				(0x3<<0)
#define DEPCTL_MPS_BULK_512			(512<<0)
#define DEPCTL_MPS_INT_MPS_16		(16<<0)
#define DIEPCTL_NEXT_EP_BIT			(11)


// S3C_UDC_OTG_DIEPMSK/DOEPMSK device IN/OUT endpoint common interrupt mask register
// S3C_UDC_OTG_DIEPINTn/DOEPINTn device IN/OUT endpoint interrupt register
#define BACK2BACK_SETUP_RECEIVED		(0x1<<6)
#define INTKNEPMIS						(0x1<<5)
#define INTKN_TXFEMP					(0x1<<4)
#define NON_ISO_IN_EP_TIMEOUT			(0x1<<3)
#define CTRL_OUT_EP_SETUP_PHASE_DONE	(0x1<<3)
#define AHB_ERROR						(0x1<<2)
#define EPDISBLD						(0x1<<1)
#define TRANSFER_DONE					(0x1<<0)

//DIEPTSIZ0 / DOEPTSIZ0

// DEPTSIZ common bit
#define DEPTSIZ_PKT_CNT_BIT 	(19)
#define DEPTSIZ_XFER_SIZE_BIT	(0)

#define	DEPTSIZ_SETUP_PKCNT_1	(1<<29)
#define	DEPTSIZ_SETUP_PKCNT_2	(2<<29)
#define	DEPTSIZ_SETUP_PKCNT_3	(3<<29)



#define GINTMSK_INIT	(INT_RESUME|INT_ENUMDONE|INT_RESET|INT_SUSPEND|INT_RX_FIFO_NOT_EMPTY)
#define DOEPMSK_INIT	(AHB_ERROR)
#define DIEPMSK_INIT	(NON_ISO_IN_EP_TIMEOUT|AHB_ERROR)
#define GAHBCFG_INIT	(PTXFE_HALF|NPTXFE_HALF|MODE_SLAVE|BURST_SINGLE|GBL_INT_UNMASK)

#define EP2_IN 2
#define EP3_IN 3
#define EP1_OUT 1
u32 tx_ep_num = 2;

static int set_interface_first = 0;

/*-------------------------------------------------------------------------*/

/** Read to request from FIFO (max read == bytes in fifo)
 *  Return:  0 = still running, 1 = completed, negative = errno
 */
static int read_fifo(struct s3c_ep *ep, struct s3c_request *req)
{
	u32 csr, gintmsk;
	u32 *buf;
	u32 bufferspace, count, count_bytes, is_short = 0;
	u32 fifo = ep->fifo_num;

	csr = readl(S3C_UDC_OTG_GRXSTSP);
	count_bytes = (csr & 0x7ff0)>>4;

	gintmsk = readl(S3C_UDC_OTG_GINTMSK);

	if(!count_bytes) {
		DEBUG_OUT_EP("%s: count_bytes %d bytes\n", __FUNCTION__, count_bytes);

		// Unmask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
		writel(gintmsk | INT_RX_FIFO_NOT_EMPTY, S3C_UDC_OTG_GINTMSK);
		return 0;
	}

	buf = req->req.buf + req->req.actual;
//	prefetchw(buf);
	bufferspace = req->req.length - req->req.actual;

	count = count_bytes / 4;
	if(count_bytes%4) count = count + 1;

	req->req.actual += min(count_bytes, bufferspace);

	is_short = (count_bytes < ep->ep.maxpacket);
	DEBUG_OUT_EP("%s: read %s, %d bytes%s req %p %d/%d GRXSTSP:0x%x\n",
		__FUNCTION__,
		ep->ep.name, count_bytes,
		is_short ? "/S" : "", req, req->req.actual, req->req.length, csr);

	while (likely(count-- != 0)) {
		u32 byte = (u32) readl(fifo);

		if (unlikely(bufferspace == 0)) {
			/* this happens when the driver's buffer
		 	* is smaller than what the host sent.
		 	* discard the extra data.
		 	*/
			if (req->req.status != -EOVERFLOW)
				printk("%s overflow %d\n", ep->ep.name, count);
			req->req.status = -EOVERFLOW;
		} else {
			*buf++ = byte;
			bufferspace-=4;
		}
 	 }

	// Unmask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
	writel(gintmsk | INT_RX_FIFO_NOT_EMPTY, S3C_UDC_OTG_GINTMSK);

	/* completion */
	if (is_short || req->req.actual == req->req.length) {
		done(ep, req, 0);
		return 1;
	}

	/* finished that packet.  the next one may be waiting... */
	return 0;
}

/* Inline code */
static __inline__ int write_packet(struct s3c_ep *ep,
				   struct s3c_request *req, int max)
{
	u32 *buf;
	int length, count;
	u32 fifo = ep->fifo_num, in_ctrl;

	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	length = req->req.length - req->req.actual;
	length = min(length, max);
	req->req.actual += length;

	DEBUG("%s: Write %d (max %d), fifo=0x%x\n",
		__FUNCTION__, length, max, fifo);

	if(ep_index(ep) == EP0_CON) {
		writel((1<<19)|(length<<0), (u32) S3C_UDC_OTG_DIEPTSIZ0);

		in_ctrl =  readl(S3C_UDC_OTG_DIEPCTL0);
		writel(DEPCTL_EPENA|DEPCTL_CNAK|(EP2_IN<<11)| in_ctrl, (u32) S3C_UDC_OTG_DIEPCTL0);

		DEBUG_EP0("%s:(DIEPTSIZ0):0x%x, (DIEPCTL0):0x%x, (GNPTXSTS):0x%x\n", __FUNCTION__,
			readl(S3C_UDC_OTG_DIEPTSIZ0),readl(S3C_UDC_OTG_DIEPCTL0),
			readl(S3C_UDC_OTG_GNPTXSTS));

		udelay(30);

	} else if ((ep_index(ep) == EP2_IN)) {
		writel((1<<19)|(length<<0), S3C_UDC_OTG_DIEPTSIZ2);

		in_ctrl =  readl(S3C_UDC_OTG_DIEPCTL2);
		writel(DEPCTL_EPENA|DEPCTL_CNAK|(EP2_IN<<11)| in_ctrl, (u32) S3C_UDC_OTG_DIEPCTL2);

		DEBUG_IN_EP("%s:(DIEPTSIZ2):0x%x, (DIEPCTL2):0x%x, (GNPTXSTS):0x%x\n", __FUNCTION__,
			readl(S3C_UDC_OTG_DIEPTSIZ2),readl(S3C_UDC_OTG_DIEPCTL2),
			readl(S3C_UDC_OTG_GNPTXSTS));

		udelay(30);

	} else if ((ep_index(ep) == EP3_IN)) {

		if (set_interface_first == 1) {
			DEBUG_IN_EP("%s: first packet write skipped after set_interface\n", __FUNCTION__);
			set_interface_first = 0;
			return length;
		}

		writel((1<<19)|(length<<0), S3C_UDC_OTG_DIEPTSIZ3);

		in_ctrl =  readl(S3C_UDC_OTG_DIEPCTL3);
		writel(DEPCTL_EPENA|DEPCTL_CNAK|(EP2_IN<<11)| in_ctrl, (u32) S3C_UDC_OTG_DIEPCTL3);

		DEBUG_IN_EP("%s:(DIEPTSIZ3):0x%x, (DIEPCTL3):0x%x, (GNPTXSTS):0x%x\n", __FUNCTION__,
			readl(S3C_UDC_OTG_DIEPTSIZ3),readl(S3C_UDC_OTG_DIEPCTL3),
			readl(S3C_UDC_OTG_GNPTXSTS));

		udelay(30);

	} else {
		printk("%s: --> Error Unused Endpoint!!\n",
			__FUNCTION__);
		BUG();
	}

	for (count=0;count<length;count+=4) {
	  	writel(*buf++, fifo);
	}
	return length;
}

/** Write request to FIFO (max write == maxp size)
 *  Return:  0 = still running, 1 = completed, negative = errno
 */
static int write_fifo(struct s3c_ep *ep, struct s3c_request *req)
{
	u32 max, gintmsk;
	unsigned count;
	int is_last = 0, is_short = 0;

	gintmsk = readl(S3C_UDC_OTG_GINTMSK);

	max = le16_to_cpu(ep->desc->wMaxPacketSize);
	count = write_packet(ep, req, max);

	/* last packet is usually short (or a zlp) */
	if (unlikely(count != max))
		is_last = is_short = 1;
	else {
		if (likely(req->req.length != req->req.actual)
		    || req->req.zero)
			is_last = 0;
		else
			is_last = 1;
		/* interrupt/iso maxpacket may not fill the fifo */
		is_short = unlikely(max < ep_maxpacket(ep));
	}

	DEBUG_IN_EP("%s: wrote %s %d bytes%s%s req %p %d/%d\n",
			__FUNCTION__,
      			ep->ep.name, count,
     	 		is_last ? "/L" : "", is_short ? "/S" : "",
      			req, req->req.actual, req->req.length);

	/* requests complete when all IN data is in the FIFO */
	if (is_last) {
		if(!ep_index(ep)){
			printk("%s: --> Error EP0 must not come here!\n",
				__FUNCTION__);
			BUG();
		}
		writel(gintmsk&(~INT_NP_TX_FIFO_EMPTY), S3C_UDC_OTG_GINTMSK);
		done(ep, req, 0);
		return 1;
	}

	// Unmask USB OTG 2.0 interrupt source : INT_NP_TX_FIFO_EMPTY
	writel(gintmsk | INT_NP_TX_FIFO_EMPTY, S3C_UDC_OTG_GINTMSK);
	return 0;
}

/* ********************************************************************************************* */
/* Bulk OUT (recv)
 */

static void s3c_out_epn(struct s3c_udc *dev, u32 ep_idx)
{
	struct s3c_ep *ep = &dev->ep[ep_idx];
	struct s3c_request *req;

	if (unlikely(!(ep->desc))) {
		/* Throw packet away.. */
		printk("%s: No descriptor?!?\n", __FUNCTION__);
		return;
	}

	if (list_empty(&ep->queue))
		req = 0;
	else
		req = list_entry(ep->queue.next,
				struct s3c_request, queue);

	if (unlikely(!req)) {
		DEBUG_OUT_EP("%s: NULL REQ on OUT EP-%d\n", __FUNCTION__, ep_idx);
		return;

	} else {
		read_fifo(ep, req);
	}

}

/**
 * s3c_in_epn - handle IN interrupt
 */
static void s3c_in_epn(struct s3c_udc *dev, u32 ep_idx)
{
	struct s3c_ep *ep = &dev->ep[ep_idx];
	struct s3c_request *req;

	if (list_empty(&ep->queue))
		req = 0;
	else
		req = list_entry(ep->queue.next, struct s3c_request, queue);

	if (unlikely(!req)) {
		DEBUG_IN_EP("%s: NULL REQ on IN EP-%d\n", __FUNCTION__, ep_idx);
		return;
	}
	else {
		write_fifo(ep, req);
	}

}

/*
 *	elfin usb client interrupt handler.
 */
static irqreturn_t s3c_udc_irq(int irq, void *_dev)
{
	struct s3c_udc *dev = _dev;
	u32 intr_status;
	u32 usb_status, ep_ctrl, gintmsk;

	spin_lock(&dev->lock);

	intr_status = readl(S3C_UDC_OTG_GINTSTS);
	gintmsk = readl(S3C_UDC_OTG_GINTMSK);

	DEBUG_ISR("\n**** %s : GINTSTS=0x%x(on state %s), GINTMSK : 0x%x\n",
			__FUNCTION__, intr_status, state_names[dev->ep0state], gintmsk);

	if (!intr_status) {
		spin_unlock(&dev->lock);
		return IRQ_HANDLED;
	}

	if (intr_status & INT_ENUMDONE) {
		DEBUG_SETUP("####################################\n");
		DEBUG_SETUP("    %s: Speed Detection interrupt\n",
				__FUNCTION__);
		writel(INT_ENUMDONE, S3C_UDC_OTG_GINTSTS);

		usb_status = (readl(S3C_UDC_OTG_DSTS) & 0x6);

		if (usb_status & (USB_FULL_30_60MHZ | USB_FULL_48MHZ)) {
			DEBUG_SETUP("    %s: Full Speed Detection\n",__FUNCTION__);
			set_max_pktsize(dev, USB_SPEED_FULL);

		} else {
			DEBUG_SETUP("    %s: High Speed Detection : 0x%x\n", __FUNCTION__, usb_status);
			set_max_pktsize(dev, USB_SPEED_HIGH);
		}
	}

	if (intr_status & INT_EARLY_SUSPEND) {
		DEBUG_SETUP("####################################\n");
		DEBUG_SETUP("    %s:Early suspend interrupt\n", __FUNCTION__);
		writel(INT_EARLY_SUSPEND, S3C_UDC_OTG_GINTSTS);
	}

	if (intr_status & INT_SUSPEND) {
		usb_status = readl(S3C_UDC_OTG_DSTS);
		DEBUG_SETUP("####################################\n");
		DEBUG_SETUP("    %s:Suspend interrupt :(DSTS):0x%x\n", __FUNCTION__, usb_status);
		writel(INT_SUSPEND, S3C_UDC_OTG_GINTSTS);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
		    && dev->driver
		    && dev->driver->suspend) {

			dev->driver->suspend(&dev->gadget);
		}
	}

	if (intr_status & INT_RESUME) {
		DEBUG_SETUP("####################################\n");
		DEBUG_SETUP("    %s: Resume interrupt\n", __FUNCTION__);
		writel(INT_RESUME, S3C_UDC_OTG_GINTSTS);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
		    && dev->driver
		    && dev->driver->resume) {

			dev->driver->resume(&dev->gadget);
		}
	}

	if (intr_status & INT_RESET) {
		usb_status = readl(S3C_UDC_OTG_GOTGCTL);
		DEBUG_SETUP("####################################\n");
		DEBUG_SETUP("    %s: Reset interrupt - (GOTGCTL):0x%x\n", __FUNCTION__, usb_status);
		writel(INT_RESET, S3C_UDC_OTG_GINTSTS);

		if((usb_status & 0xc0000) == (0x3 << 18)) {
			if(reset_available) {
				DEBUG_SETUP("     ===> OTG core got reset (%d)!! \n", reset_available);
				reconfig_usbd();
				dev->ep0state = WAIT_FOR_SETUP;
				reset_available = 0;
			}
		} else {
			reset_available = 1;
			DEBUG_SETUP("      RESET handling skipped : reset_available : %d\n", reset_available);
		}
	}

	if (intr_status & INT_RX_FIFO_NOT_EMPTY) {
		u32 grx_status, packet_status, ep_num, fifoCntByte = 0;

		// Mask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
		gintmsk &= ~INT_RX_FIFO_NOT_EMPTY;
		writel(gintmsk, S3C_UDC_OTG_GINTMSK);

		grx_status = readl(S3C_UDC_OTG_GRXSTSR);
		DEBUG_ISR("    INT_RX_FIFO_NOT_EMPTY(GRXSTSR):0x%x, GINTMSK:0x%x\n", grx_status, gintmsk);

		packet_status = grx_status & 0x1E0000;
		fifoCntByte = (grx_status & 0x7ff0)>>4;
		ep_num = grx_status & EP_MASK;

		if (fifoCntByte) {

			if (packet_status == SETUP_PKT_RECEIVED)  {
				DEBUG_EP0("      => A SETUP data packet received : %d bytes\n", fifoCntByte);
				s3c_handle_ep0(dev);

				// Unmask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
				gintmsk |= INT_RX_FIFO_NOT_EMPTY;

			} else if (packet_status == OUT_PKT_RECEIVED) {

				if(ep_num == EP1_OUT) {
					ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL1);
					DEBUG_ISR("      => A Bulk OUT data packet received : %d bytes, (DOEPCTL1):0x%x\n",
						fifoCntByte, ep_ctrl);
					s3c_out_epn(dev, 1);
					gintmsk = readl(S3C_UDC_OTG_GINTMSK);
					writel(ep_ctrl | DEPCTL_CNAK, S3C_UDC_OTG_DOEPCTL1);
				} else if (ep_num == EP0_CON) {
					ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL0);
					DEBUG_EP0("      => A CONTROL OUT data packet received : %d bytes, (DOEPCTL0):0x%x\n",
						fifoCntByte, ep_ctrl);
					dev->ep0state = DATA_STATE_RECV;
					s3c_ep0_read(dev);
					gintmsk |= INT_RX_FIFO_NOT_EMPTY;
				} else {
					DEBUG_ISR("      => Unused EP: %d bytes, (GRXSTSR):0x%x\n", fifoCntByte, grx_status);
				}
			} else {
				grx_status = readl(S3C_UDC_OTG_GRXSTSP);

				// Unmask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
				gintmsk |= INT_RX_FIFO_NOT_EMPTY;

				DEBUG_ISR("      => A reserved packet received : %d bytes\n", fifoCntByte);
			}
		} else {
			if (dev->ep0state == DATA_STATE_XMIT) {
				ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL0);
				DEBUG_EP0("      => Write ep0 continue... (DOEPCTL0):0x%x\n", ep_ctrl);
				s3c_ep0_write(dev);
			}

			if (packet_status == SETUP_TRANSACTION_COMPLETED) {
				ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL0);
				DEBUG_EP0("      => A SETUP transaction completed (DOEPCTL0):0x%x\n", ep_ctrl);
				writel(ep_ctrl | DEPCTL_CNAK, S3C_UDC_OTG_DOEPCTL0);

			} else if (packet_status == OUT_TRANSFER_COMPLELTED) {
				if (ep_num == EP1_OUT) {
					ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL1);
					DEBUG_ISR("      => An OUT transaction completed (DOEPCTL1):0x%x\n", ep_ctrl);
					writel(ep_ctrl | DEPCTL_CNAK, S3C_UDC_OTG_DOEPCTL1);
				} else if (ep_num == EP0_CON) {
					ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL0);
					DEBUG_ISR("      => An OUT transaction completed (DOEPCTL0):0x%x\n", ep_ctrl);
					writel(ep_ctrl | DEPCTL_CNAK, S3C_UDC_OTG_DOEPCTL0);
				} else {
					DEBUG_ISR("      => Unused EP: %d bytes, (GRXSTSR):0x%x\n", fifoCntByte, grx_status);
				}
			} else if (packet_status == OUT_PKT_RECEIVED) {
				DEBUG_ISR("      => A  OUT PACKET RECEIVED (NO FIFO CNT BYTE)...(GRXSTSR):0x%x\n", grx_status);
			} else {
				DEBUG_ISR("      => A RESERVED PACKET RECEIVED (NO FIFO CNT BYTE)...(GRXSTSR):0x%x\n", grx_status);
			}

			grx_status = readl(S3C_UDC_OTG_GRXSTSP);

			// Unmask USB OTG 2.0 interrupt source : INT_RX_FIFO_NOT_EMPTY
			gintmsk |= INT_RX_FIFO_NOT_EMPTY;

		}

		// Un/Mask USB OTG 2.0 interrupt sources
		writel(gintmsk, S3C_UDC_OTG_GINTMSK);

		spin_unlock(&dev->lock);
		return IRQ_HANDLED;
	}


	if (intr_status & INT_NP_TX_FIFO_EMPTY) {
		DEBUG_ISR("    INT_NP_TX_FIFO_EMPTY (GNPTXSTS):0x%x, (GINTMSK):0x%x, ep_num=%d\n",
				readl(S3C_UDC_OTG_GNPTXSTS),
				readl(S3C_UDC_OTG_GINTMSK),
				tx_ep_num);

		s3c_in_epn(dev, tx_ep_num);
	}

	spin_unlock(&dev->lock);

	return IRQ_HANDLED;
}

/** Queue one request
 *  Kickstart transfer if needed
 */
static int s3c_queue(struct usb_ep *_ep, struct usb_request *_req,
			 gfp_t gfp_flags)
{
	struct s3c_request *req;
	struct s3c_ep *ep;
	struct s3c_udc *dev;
	unsigned long flags;

	req = container_of(_req, struct s3c_request, req);
	if (unlikely(!_req || !_req->complete || !_req->buf
			|| !list_empty(&req->queue)))
	{
		DEBUG("%s: bad params\n", __FUNCTION__);
		return -EINVAL;
	}

	ep = container_of(_ep, struct s3c_ep, ep);
	if (unlikely(!_ep || (!ep->desc && ep->ep.name != ep0name))) {
		DEBUG("%s: bad ep\n", __FUNCTION__);
		return -EINVAL;
	}

	dev = ep->dev;
	if (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)) {
		DEBUG("%s: bogus device state %p\n", __FUNCTION__, dev->driver);
		return -ESHUTDOWN;
	}

	DEBUG("\n%s: %s queue req %p, len %d buf %p\n",
		__FUNCTION__, _ep->name, _req, _req->length, _req->buf);

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* kickstart this i/o queue? */
	DEBUG("%s: Add to ep=%d, Q empty=%d, stopped=%d\n",
		__FUNCTION__, ep_index(ep), list_empty(&ep->queue), ep->stopped);

	if (list_empty(&ep->queue) && likely(!ep->stopped)) {
		u32 csr;

		if (unlikely(ep_index(ep) == 0)) {
			/* EP0 */
			list_add_tail(&req->queue, &ep->queue);
			s3c_ep0_kick(dev, ep);
			req = 0;

		} else if (ep_is_in(ep)) {
			csr = readl((u32) S3C_UDC_OTG_GINTSTS);
			DEBUG_IN_EP("%s: ep_is_in, S3C_UDC_OTG_GINTSTS=0x%x\n",
				__FUNCTION__, csr);

			if((csr & INT_NP_TX_FIFO_EMPTY) &&
			   (write_fifo(ep, req) == 1)) {
				req = 0;
			} else {
				DEBUG("++++ IN-list_add_taill::req=%p, ep=%d\n",
					req, ep_index(ep));
				tx_ep_num = ep_index(ep);
			}
		} else {
			csr = readl((u32) S3C_UDC_OTG_GINTSTS);
			DEBUG_OUT_EP("%s: ep_is_out, S3C_UDC_OTG_GINTSTS=0x%x\n",
				__FUNCTION__, csr);

			if((csr & INT_RX_FIFO_NOT_EMPTY) &&
			   (read_fifo(ep, req) == 1))
				req = 0;
			else
				DEBUG("++++ OUT-list_add_taill::req=%p, DOEPCTL1:0x%x\n",
					req, readl(S3C_UDC_OTG_DOEPCTL1));
		}
	}

	/* pio or dma irq handler advances the queue. */
	if (likely(req != 0))
		list_add_tail(&req->queue, &ep->queue);

	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}

/****************************************************************/
/* End Point 0 related functions                                */
/****************************************************************/

/* return:  0 = still running, 1 = completed, negative = errno */
static int write_fifo_ep0(struct s3c_ep *ep, struct s3c_request *req)
{
	u32 max;
	unsigned count;
	int is_last;

	max = ep_maxpacket(ep);

	DEBUG_EP0("%s: max = %d\n", __FUNCTION__, max);

	count = write_packet(ep, req, max);

	/* last packet is usually short (or a zlp) */
	if (likely(count != max))
		is_last = 1;
	else {
		if (likely(req->req.length != req->req.actual) || req->req.zero)
			is_last = 0;
		else
			is_last = 1;
	}

	DEBUG_EP0("%s: wrote %s %d bytes%s %d left %p\n", __FUNCTION__,
		  ep->ep.name, count,
		  is_last ? "/L" : "", req->req.length - req->req.actual, req);

	/* requests complete when all IN data is in the FIFO */
	if (is_last) {
		return 1;
	}

	return 0;
}

static __inline__ int s3c_fifo_read(struct s3c_ep *ep, u32 *cp, int max)
{
	int bytes;
	int count;
	u32 grx_status = readl(S3C_UDC_OTG_GRXSTSP);
	bytes = (grx_status & 0x7ff0)>>4;

	DEBUG_EP0("%s: GRXSTSP=0x%x, bytes=%d, ep_index=%d, fifo=0x%x\n",
			__FUNCTION__, grx_status, bytes, ep_index(ep), ep->fifo_num);

	// 32 bits interface
	count = bytes / 4;

	while (count--) {
		*cp++ = (u32) readl(S3C_UDC_OTG_EP0_FIFO);
	}

	return bytes;
}

static int read_fifo_ep0(struct s3c_ep *ep, struct s3c_request *req)
{
	u32 csr;
	u32 *buf;
	unsigned bufferspace, count, is_short, bytes;
	u32 fifo = ep->fifo_num;

	DEBUG_EP0("%s\n", __FUNCTION__);

	csr = readl(S3C_UDC_OTG_GRXSTSP);
	bytes = (csr & 0x7ff0)>>4;

	buf = req->req.buf + req->req.actual;
//	prefetchw(buf);
	bufferspace = req->req.length - req->req.actual;

	/* read all bytes from this packet */
	if (likely((csr & EP_MASK) == EP0_CON)) {
		count = bytes / 4;
		req->req.actual += min(bytes, bufferspace);

	} else	{		// zlp
		count = 0;
		bytes = 0;
	}

	is_short = (bytes < ep->ep.maxpacket);
	DEBUG_EP0("%s: read %s %02x, %d bytes%s req %p %d/%d\n",
		  __FUNCTION__,
		  ep->ep.name, csr, bytes,
		  is_short ? "/S" : "", req, req->req.actual, req->req.length);

	while (likely(count-- != 0)) {
		u32 byte = (u32) readl(fifo);

		if (unlikely(bufferspace == 0)) {
			/* this happens when the driver's buffer
			 * is smaller than what the host sent.
			 * discard the extra data.
			 */
			if (req->req.status != -EOVERFLOW)
				DEBUG_EP0("%s overflow %d\n", ep->ep.name,
					  count);
			req->req.status = -EOVERFLOW;
		} else {
			*buf++ = byte;
			bufferspace = bufferspace - 4;
		}
	}

	/* completion */
	if (is_short || req->req.actual == req->req.length) {
		return 1;
	}

	return 0;
}

/**
 * udc_set_address - set the USB address for this device
 * @address:
 *
 * Called from control endpoint function
 * after it decodes a set address setup packet.
 */
static void udc_set_address(struct s3c_udc *dev, unsigned char address)
{
	u32 ctrl = readl(S3C_UDC_OTG_DCFG);
	writel(address << 4 | ctrl, S3C_UDC_OTG_DCFG);

	ctrl = readl(S3C_UDC_OTG_DIEPCTL0);
	writel(DEPCTL_EPENA|DEPCTL_CNAK|ctrl, S3C_UDC_OTG_DIEPCTL0); /* EP0: Control IN */

	DEBUG_EP0("%s: USB OTG 2.0 Device address=%d, DCFG=0x%x\n",
		__FUNCTION__, address, readl(S3C_UDC_OTG_DCFG));

	dev->usb_address = address;
}



static int first_time = 1;

static void s3c_ep0_read(struct s3c_udc *dev)
{
	struct s3c_request *req;
	struct s3c_ep *ep = &dev->ep[0];
	int ret;

	if (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next, struct s3c_request, queue);
	else {
		printk("%s: ---> BUG\n", __FUNCTION__);
		BUG();	//logic ensures		-jassi
		return;
	}

	DEBUG_EP0("%s: req.length = 0x%x, req.actual = 0x%x\n",
		__FUNCTION__, req->req.length, req->req.actual);

	if(req->req.length == 0) {
		dev->ep0state = WAIT_FOR_SETUP;
		first_time = 1;
		done(ep, req, 0);
		return;
	}

	if(!req->req.actual && first_time){	//for SetUp packet
		first_time = 0;
		return;
	}

	ret = read_fifo_ep0(ep, req);
	if (ret) {
		dev->ep0state = WAIT_FOR_SETUP;
		first_time = 1;
		done(ep, req, 0);
		return;
	}

}

/*
 * DATA_STATE_XMIT
 */
static int s3c_ep0_write(struct s3c_udc *dev)
{
	struct s3c_request *req;
	struct s3c_ep *ep = &dev->ep[0];
	int ret, need_zlp = 0;

	DEBUG_EP0("%s: ep0 write\n", __FUNCTION__);

	if (list_empty(&ep->queue))
		req = 0;
	else
		req = list_entry(ep->queue.next, struct s3c_request, queue);

	if (!req) {
		DEBUG_EP0("%s: NULL REQ\n", __FUNCTION__);
		return 0;
	}

	DEBUG_EP0("%s: req.length = 0x%x, req.actual = 0x%x\n",
		__FUNCTION__, req->req.length, req->req.actual);

	if (req->req.length == 0) {
		dev->ep0state = WAIT_FOR_SETUP;
	   	done(ep, req, 0);
		return 1;
	}

	if (req->req.length - req->req.actual == ep0_fifo_size) {
		/* Next write will end with the packet size, */
		/* so we need Zero-length-packet */
		need_zlp = 1;
	}

	ret = write_fifo_ep0(ep, req);

	if ((ret == 1) && !need_zlp) {
		/* Last packet */
		DEBUG_EP0("%s: finished, waiting for status\n", __FUNCTION__);
		dev->ep0state = WAIT_FOR_SETUP;
	} else {
		DEBUG_EP0("%s: not finished\n", __FUNCTION__);
	}

	if (need_zlp) {
		DEBUG_EP0("%s: Need ZLP!\n", __FUNCTION__);
		dev->ep0state = DATA_STATE_NEED_ZLP;
	}

	if(ret)
	   done(ep, req, 0);

	return 1;
}

static int s3c_udc_set_halt(struct usb_ep *_ep, int value)
{
	struct s3c_ep	*ep;
	u32 ep_num;
	ep = container_of(_ep, struct s3c_ep, ep);
	ep_num =ep_index(ep);

	DEBUG("%s: ep_num = %d, value = %d\n", __FUNCTION__, ep_num, value);
	/* TODO */
	return 0;
}

void s3c_udc_ep_activate(struct s3c_ep *ep)
{
	/* TODO */
}

/*
 * WAIT_FOR_SETUP (OUT_PKT_RDY)
 */
static void s3c_ep0_setup(struct s3c_udc *dev)
{
	struct s3c_ep *ep = &dev->ep[0];
	int i, bytes, is_in;
	u32 ep_ctrl;

	/* Nuke all previous transfers */
	nuke(ep, -EPROTO);

	/* read control req from fifo (8 bytes) */
	bytes = s3c_fifo_read(ep, (u32 *)&usb_ctrl, 8);

	DEBUG_SETUP("Read CTRL REQ %d bytes\n", bytes);
	DEBUG_SETUP("  CTRL.bRequestType = 0x%x (is_in %d)\n", usb_ctrl->bRequestType,
		    usb_ctrl->bRequestType & USB_DIR_IN);
	DEBUG_SETUP("  CTRL.bRequest = 0x%x\n", usb_ctrl->bRequest);
	DEBUG_SETUP("  CTRL.wLength = 0x%x\n", usb_ctrl->wLength);
	DEBUG_SETUP("  CTRL.wValue = 0x%x (%d)\n", usb_ctrl.wValue, usb_ctrl.wValue >> 8);
	DEBUG_SETUP("  CTRL.wIndex = 0x%x\n", usb_ctrl.wIndex);

	/* Set direction of EP0 */
#if 0
	if (likely(usb_ctrl.bRequestType & USB_DIR_IN)) {
		ep->bEndpointAddress |= USB_DIR_IN;
		is_in = 1;
	} else {
		ep->bEndpointAddress &= ~USB_DIR_IN;
		is_in = 0;
	}
#endif
	dev->req_pending = 1;

	/* Handle some SETUP packets ourselves */
	switch (usb_ctrl->bRequest) {
		case USB_REQ_SET_ADDRESS:
			if (usb_ctrl->bRequestType
				!= (USB_TYPE_STANDARD | USB_RECIP_DEVICE))
				break;

			DEBUG_SETUP("%s: *** USB_REQ_SET_ADDRESS (%d)\n",
					__FUNCTION__, usb_ctrl->wValue);
			udc_set_address(dev, usb_ctrl->wValue);
			return;

		case USB_REQ_SET_CONFIGURATION :
			DEBUG_SETUP("============================================\n");
			DEBUG_SETUP("%s: USB_REQ_SET_CONFIGURATION (%d)\n",
					__FUNCTION__, usb_ctrl->wValue);
config_change:
			// Just to send ZLP(Zero length Packet) to HOST in response to SET CONFIGURATION
			ep_ctrl = readl(S3C_UDC_OTG_DIEPCTL0);
			writel(DEPCTL_EPENA|DEPCTL_CNAK|ep_ctrl, S3C_UDC_OTG_DIEPCTL0); /* EP0: Control IN */

			// For Startng EP1 on this new configuration
			ep_ctrl = readl(S3C_UDC_OTG_DOEPCTL1);
			writel(DEPCTL_EPDIS|DEPCTL_CNAK|DEPCTL_BULK_TYPE|DEPCTL_USBACTEP|ep_ctrl, S3C_UDC_OTG_DOEPCTL1); /* EP1: Bulk OUT */

			// For starting EP2 on this new configuration
			ep_ctrl = readl(S3C_UDC_OTG_DIEPCTL2);
			writel(DEPCTL_BULK_TYPE|DEPCTL_USBACTEP|ep_ctrl, S3C_UDC_OTG_DIEPCTL2); /* EP2: Bulk IN */

			// For starting EP3 on this new configuration
			ep_ctrl = readl(S3C_UDC_OTG_DIEPCTL3);
			writel(DEPCTL_BULK_TYPE|DEPCTL_USBACTEP|ep_ctrl, S3C_UDC_OTG_DIEPCTL3); /* EP3: INTR IN */

			DEBUG_SETUP("%s:(DOEPCTL1):0x%x, (DIEPCTL2):0x%x, (DIEPCTL3):0x%x\n",
				__FUNCTION__,
				readl(S3C_UDC_OTG_DOEPCTL1),
				readl(S3C_UDC_OTG_DIEPCTL2),
				readl(S3C_UDC_OTG_DIEPCTL3));

			DEBUG_SETUP("============================================\n");

			reset_available = 1;
			dev->req_config = 1;
			break;

		case USB_REQ_GET_DESCRIPTOR:
			DEBUG_SETUP("%s: *** USB_REQ_GET_DESCRIPTOR  \n",__FUNCTION__);
			break;

		case USB_REQ_SET_INTERFACE:
			DEBUG_SETUP("%s: *** USB_REQ_SET_INTERFACE (%d)\n",
					__FUNCTION__, usb_ctrl->wValue);

			set_interface_first = 1;
			goto config_change;
			break;

		case USB_REQ_GET_CONFIGURATION:
			DEBUG_SETUP("%s: *** USB_REQ_GET_CONFIGURATION  \n",__FUNCTION__);
			break;

		case USB_REQ_GET_STATUS:
			DEBUG_SETUP("%s: *** USB_REQ_GET_STATUS  \n",__FUNCTION__);
			break;

		default:
			DEBUG_SETUP("%s: *** Default of usb_ctrl.bRequest=0x%x happened.\n",
					__FUNCTION__, usb_ctrl->bRequest);
			break;
	}

	if (likely(dev->driver)) {
		/* device-2-host (IN) or no data setup command,
		 * process immediately */
		spin_unlock(&dev->lock);
		DEBUG_SETUP("%s: ctrlrequest will be passed to fsg_setup()\n", __FUNCTION__);
		i = dev->driver->setup(&dev->gadget, (struct usb_ctrlrequest *)&usb_ctrl);
		spin_lock(&dev->lock);

		if (i < 0) {
			/* setup processing failed, force stall */
			DEBUG_SETUP("%s: gadget setup FAILED (stalling), setup returned %d\n",
				__FUNCTION__, i);
			/* ep->stopped = 1; */
			dev->ep0state = WAIT_FOR_SETUP;
		}
	}
}

/*
 * handle ep0 interrupt
 */
static void s3c_handle_ep0(struct s3c_udc *dev)
{
	if (dev->ep0state == WAIT_FOR_SETUP) {
		DEBUG_EP0("%s: WAIT_FOR_SETUP\n", __FUNCTION__);
		s3c_ep0_setup(dev);

	} else {
		DEBUG_EP0("%s: strange state!!(state = %s)\n",
			__FUNCTION__, state_names[dev->ep0state]);
	}
}

static void s3c_ep0_kick(struct s3c_udc *dev, struct s3c_ep *ep)
{
	DEBUG_EP0("%s: ep_is_in = %d\n", __FUNCTION__, ep_is_in(ep));
	if (ep_is_in(ep)) {
		dev->ep0state = DATA_STATE_XMIT;
		s3c_ep0_write(dev);
	} else {
		dev->ep0state = DATA_STATE_RECV;
		s3c_ep0_read(dev);
	}
}
