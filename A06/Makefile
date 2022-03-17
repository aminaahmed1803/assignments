CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@

encode : encode.c read_ppm.c
	$(CC) -g -Wall -Wvla -Werror encode.c read_ppm.c -o $@

decode : decode.c read_ppm.c
	$(CC) -g -Wall -Wvla -Werror decode.c read_ppm_api.c -o $@

decode-api : decode-api.c read_ppm.c
	$(CC) -g -Wall -Wvla -Werror decode-api.c read_ppm_api.c -o $@
