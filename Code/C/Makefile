debug_hls_cnn :
	gcc -Wall -Wextra -O0 -g -fsanitize=address -I../Headers utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c -lm -o debug_hls_cnn

hls_cnn :
	gcc -O3 -I../Headers utils.c activ_fun.c conv.c pool.c flat.c dense.c cnn.c cnn_tb.c -lm -o hls_cnn
