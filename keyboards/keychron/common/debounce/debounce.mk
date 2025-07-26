DEBOUNCE_DIR = common/debounce
SRC += \
     $(DEBOUNCE_DIR)/sym_defer_g.c \
     $(DEBOUNCE_DIR)/sym_defer_pr.c \
     $(DEBOUNCE_DIR)/sym_defer_pk.c \
     $(DEBOUNCE_DIR)/sym_eager_pr.c \
     $(DEBOUNCE_DIR)/sym_eager_pk.c \
     $(DEBOUNCE_DIR)/asym_eager_defer_pk.c \
     $(DEBOUNCE_DIR)/none.c \
     $(DEBOUNCE_DIR)/keychron_debounce.c

VPATH += $(TOP_DIR)/keyboards/keychron/$(DEBOUNCE_DIR)

OPT_DEFS += -DDYNAMIC_DEBOUNCE_ENABLE
