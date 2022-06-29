dbg_cnn :
	gcc -Wall -Wextra -O0 -g -fsanitize=address -I../Headers utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c -lm -o dbg_cnn

cnn :
	gcc -O3 -I../Headers utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c -lm -o cnn
