ifeq ($(DEBUG),true)
#-g是生成调试信息。GNU调试器可以利用该信息
CC = g++ -g
VERSION = debug
else
CC = g++
VERSION = release
endif


SRCS = $(wildcard *.cxx)
OBJS = $(SRCS:.cxx=.o)
DEPS = $(SRCS:.cxx=.d)

BIN := $(addprefix $(BUILD_ROOT)/, $(BIN))

LINK_OBJ_DIR = $(BUILD_ROOT)/app/link_obj
DEP_DIR = $(BUILD_ROOT)/app/dep

#create folder DEPS, OBJS, BIN
$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))

OBJS := $(addprefix $(LINK_OBJ_DIR)/, $(OBJS))
DEPS := $(addprefix $(DEP_DIR)/, $(DEPS))

ALL_LINK_OBJ = $(wildcard $(LINK_OBJ_DIR)/*.o)
#因为构建依赖关系时app目录下这个.o文件还没构建出来
ALL_LINK_OBJ += $(OBJS)


all: $(DEPS) $(OBJS) $(BIN)

#build rules for DEPS
#gcc -MM 輸出編譯所有用到的對應關聯文件
$(DEP_DIR)/%.d:%.cxx
	@echo -n $(LINK_OBJ_DIR)/ > $@
	$(CC) -I$(INCLUDE_PATH) -MM $^ >> $@

#build rules for OBJS
$(LINK_OBJ_DIR)/%.o:%.cxx
	$(CC) -I$(INCLUDE_PATH) -o $@ -c $(filter %.cxx,$^)

#link all objs
$(BIN): $(ALL_LINK_OBJ)
	$(CC) -o $@ $^

clean: 
	@echo "sub-folder clean"
	rm -rf $(LINK_OBJ_DIR)
	rm -rf $(DEP_DIR)

help:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(ALL_LINK_OBJ)
	@echo $(INCLUDE_PATH)
	@echo $(BIN)


