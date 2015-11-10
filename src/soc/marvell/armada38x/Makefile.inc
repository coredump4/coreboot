ifeq ($(CONFIG_SOC_MARVELL_ARMADA38X),y)

bootblock-y += bootblock.c
bootblock-y += bootblock_asm.S
bootblock-y += monotonic_timer.c
ifeq ($(CONFIG_BOOTBLOCK_CONSOLE),y)
bootblock-$(CONFIG_DRIVERS_UART) += uart.c
endif

verstage-$(CONFIG_DRIVERS_UART) += uart.c
verstage-y += monotonic_timer.c

romstage-y += cbmem.c
romstage-y += monotonic_timer.c
romstage-$(CONFIG_DRIVERS_UART) += uart.c

ramstage-y += cbmem.c
ramstage-y += monotonic_timer.c
ramstage-y += soc.c
ramstage-$(CONFIG_DRIVERS_UART) += uart.c

CPPFLAGS_common += -Isrc/soc/marvell/armada38x/include/

BIN_HDR = 3rdparty/blobs/cpu/marvell/armada38x/bin_hdr.bin
DOIMAGE = 3rdparty/blobs/cpu/marvell/armada38x/doimage

$(objcbfs)/bootblock.bin: $(objcbfs)/bootblock.raw.bin
	@chmod a+x $(DOIMAGE)
	$(DOIMAGE) -T flash -D 0 -E 0 -G $(BIN_HDR) $< $@
	rm $<
endif