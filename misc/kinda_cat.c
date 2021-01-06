#include <stdio.h>
#include <malloc.h>

inline void seek_beg(FILE *f) {
	fseek(f, 0, SEEK_SET);
}

inline void seek_end(FILE *f) {
	fseek(f, 0, SEEK_END);
}

inline long file_size(FILE *f) {
	seek_end(f);
	long size = ftell(f);
	seek_beg(f);
	return size;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "%s compile_flags.txt\n", argv[0]);
		return 1;
	}

	argv++;

	FILE *txt;
	errno_t err = fopen_s(&txt, argv[0], "r");
	if (err) {
		fprintf(stderr, "Unable to open %s\n", argv[0]);
		return err;
	}

	long size = file_size(txt);
	char *buf = (char *) malloc(size);

	if (buf == NULL) {
		// well fuck
		perror("Allocation failure!");
		return 1;
	}

	_fread_nolock(buf, sizeof(char), size, txt);

	for (size_t i = 0; i < size; ++i) {
		if (buf[i] == '\n') {
			buf[i] = ' ';
		}
	}

	_fwrite_nolock(buf, sizeof(char), size, stdout);
}
