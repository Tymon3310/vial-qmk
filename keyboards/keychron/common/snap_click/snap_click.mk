SNAP_CLICK_DIR = common/snap_click
SRC += \
     $(SNAP_CLICK_DIR)/snap_click.c \

VPATH += $(TOP_DIR)/keyboards/keychron/$(SNAP_CLICK_DIR)

OPT_DEFS += -DSNAP_CLICK_ENABLE
