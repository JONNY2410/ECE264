#include <stdio.h>
#include <stdlib.h>

int my_atoi(char* s) {
	int n = 0;
	int sign = 1;
	if(s[0] == '-') {
		sign = -1;
		s = &s[1];
	}
	while(s[0] != '\0') {
		n *= 10;
		n += s[0] - '0';
		s = &s[1];
	}
	n *= sign;
	return n;
}
int main(int argc, char* argv[]) {
	char* test_strings[] = {"123", "1", "15", "-15", "-23"};
	// WRONG
	//     // int num_test_strings = sizeof(test_strings);
	//
	//         // RIGHT
	int num_test_strings = sizeof(test_strings) / sizeof(test_strings[0]);

	printf("There are %d test strings.\n", num_test_strings);
	for(int i = 0; i < num_test_strings; i++) {
		int n = my_atoi(test_strings[i]);
		printf("%s ==> %d\n", test_strings[i], n);
	}
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
