all:
	make dbg_cnn cnn

SOURCES = utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c

dbg_cnn: $(SOURCES)
	gcc -Wall -Wextra -O0 -g -fsanitize=address -I../Headers $(SOURCES) -lm -o dbg_cnn

cnn: $(SOURCES)
	gcc -O3 -I../Headers $(SOURCES) -lm -o cnn

clean :
	rm -f dbg_cnn cnn
