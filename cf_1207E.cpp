#include <cstdio>

int ask(int a[]) {
    printf("?");
    for(int i = 0; i < 100; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
    fflush(stdout);
    int ans;
    scanf("%d", &ans);
    return ans;
}

int arr[100];
int main() {
    for(int i = 0; i < 100; i++) {
        arr[i] = ((i + 1) << 7);
    }
    int ans1 = ask(arr);

    for(int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    int ans2 = ask(arr);

    int mask = (1 << 7) - 1;

    ans1 = (ans1 & mask);
    ans2 = (ans2 & (mask << 7));

    printf("! %d\n", ans1 ^ ans2);
    fflush(stdout);
    return 0;
}
