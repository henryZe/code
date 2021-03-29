#
# Makefile for the HENRY driver
#

LINUXINCLUDE += \
	-Idrivers/alidrivers/include \
	-Idrivers/alidrivers/include/alirpcng

obj-$(CONFIG_ALI_HENRY) += alihenry_drv.o
alihenry_drv-y := ali_henry_drv.o ali_henry_drv_dbgfs.o ali_henry_drv_sys.o
alihenry_drv-$(CONFIG_MEM_TEST) += ali_henry_molloc_test.o

obj-$(CONFIG_HENRY_FIFO) += kfifo.o
kfifo-y := kernel_fifo.o
