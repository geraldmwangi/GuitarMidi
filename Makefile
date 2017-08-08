#!/usr/bin/make -f
# Makefile for StateVariableFilter-DPF Plugin #
# ---------------------------- #
# Created by JimsonDrift, Based on Distrho Plugins by falktx
#

include Makefile.mk

all: libs plugins gen

# --------------------------------------------------------------

libs:
ifeq ($(HAVE_DGL),true)
	$(MAKE) -C DPF/dgl
endif

plugins: libs
	$(MAKE) all -C plugins/BandPass
	$(MAKE) all -C plugins/ChebyshevBandPass



gen: plugins DPF/utils/lv2_ttl_generator
	@$(CURDIR)/DPF/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/DPF/utils/generate-vst-bundles.sh
endif

DPF/utils/lv2_ttl_generator:
	$(MAKE) -C DPF/utils/lv2-ttl-generator

# --------------------------------------------------------------

clean:
ifeq ($(HAVE_DGL),true)
	$(MAKE) clean -C DPF/dgl
endif
	$(MAKE) clean -C DPF/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/BandPass


# --------------------------------------------------------------

.PHONY: plugins
