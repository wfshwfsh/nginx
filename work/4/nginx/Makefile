include config.mk

all:
	@echo "all"
    
	@for dir in $(BUILD_DIR); \
	do \
		#echo $$dir; \
        make -C $$dir; \
	done
    
clean: 
	@echo "clean"
	@for dir in $(BUILD_DIR); \
	do \
		#echo $$dir; \
        make clean -C $$dir; \
	done

help:
	@echo $(BUILD_DIR)
	@for dir in $(BUILD_DIR); \
	do \
        make help -C $$dir; \
	done