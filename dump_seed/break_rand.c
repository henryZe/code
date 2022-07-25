#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
        int now = time(NULL);
        int key, key1, key_out, key1_out;
        char buff[100];
        int seed;

        scanf("%s", buff);
        key = atoi(buff);
        scanf("%s", buff);
        key1 = atoi(buff);
        printf("key:%d key1:%d\n", key, key1);

        for (seed = now - 60; seed < now; seed++) {
                srand(seed);
                key_out = rand();
                for (int i = 0; i < 100; i++) {
                        key1_out = rand();
                        if (key == key_out && key1 == key1_out) {
                                printf("found! seed is %d, key3 is %d\n", seed, rand());
                                goto end;
                        }
                }
                key_out = key1_out;
        }
end:
        printf("Done");
        return 0;
}