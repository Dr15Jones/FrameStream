
# --------------------------------------------------
# Purify
# --------------------------------------------------
ifneq (,$(findstring $(PURIFY),yY))
#  PURIFY_PATH  := /opt/rational/purify-4.5.1-solaris2
#  PURIFY_PATH  := /opt/rational/releases/DeveloperTools.5.2/sun4_solaris2/bin
  PURIFY_PATH  := /nfs/opt/rational/releases/DeveloperTools.2001a.04.00/sun4_solaris2/bin
  PURIFY_CACHEDIR := /nfs/c3off/Offline/cache

  PURIFY_FLAGS := -messages=first 
  PURIFY_FLAGS += -leaks-at-exit=yes 
  PURIFY_FLAGS += -static-checking=no
#  PURIFY_FLAGS += -best-effort

#  PURIFY_FLAGS += -always-use-cache-dir=yes 
  PURIFY_FLAGS += -cache-dir=$(PURIFY_CACHEDIR)

  PURIFY_EXE   := $(PURIFY_PATH)/purify
  PURIFY_CLEAN := $(PURIFY_PATH)/pure_remove_old_files

  DO_PURIFY    := $(PURIFY_CLEAN) $(PURIFY_CACHEDIR) 31; \
		  $(PURIFY_EXE) $(PURIFY_FLAGS)

#  PURIFY_DIR   := `$(PURIFY_EXE) -print-home-dir`
#  PURIFY_STUBS := $(PURIFY_DIR)/purify_stubs.a
endif

# --------------------------------------------------
# Quantify
# --------------------------------------------------
ifneq (,$(findstring $(QUANTIFY),yY))
#  QUANTIFY_PATH  := /opt/rational/quantify-4.5.1-solaris2
#  QUANTIFY_PATH  := /opt/rational/releases/DeveloperTools.5.2/sun4_solaris2/bin
  QUANTIFY_PATH  := /nfs/opt/rational/releases/DeveloperTools.2001a.04.00/sun4_solaris2/bin
  QUANTIFY_CACHEDIR := /nfs/c3off/Offline/cache

  QUANTIFY_FLAGS :=
  QUANTIFY_FLAGS += -cache-dir=$(QUANTIFY_CACHEDIR)
#  QUANTIFY_FLAGS += -best-effort

  QUANTIFY_EXE   := $(QUANTIFY_PATH)/quantify
  QUANTIFY_CLEAN := $(QUANTIFY_PATH)/pure_remove_old_files

  DO_QUANTIFY    := $(QUANTIFY_CLEAN) $(QUANTIFY_CACHEDIR) 31; \
	            $(QUANTIFY_EXE) $(QUANTIFY_FLAGS)

#  QUANTIFY_DIR   := `$(QUANTIFY_EXE) -print_home_dir`
#  QUANTIFY_STUBS := $(QUANTIFY_DIR)/quantify_stubs.a
endif
