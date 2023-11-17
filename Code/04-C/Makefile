all:
	make dbg_cnn cnn

SOURCES = utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c
INCLUDE_DIR = ../03-Headers

dbg_cnn: $(SOURCES) $(wildcard $(INCLUDE_DIR)/*.h)
	gcc -Wall -Wextra -O0 -g -fsanitize=address -I$(INCLUDE_DIR) $(SOURCES) -lm -o dbg_cnn

cnn: $(SOURCES) $(wildcard $(INCLUDE_DIR)/*.h)
	gcc -O3 -I$(INCLUDE_DIR) $(SOURCES) -lm -o cnn

clean:
	rm -f dbg_cnn cnn
