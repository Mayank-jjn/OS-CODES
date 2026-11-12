#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, r[100], s[100], head, cylinders;
    int i, j, cur, total, done[100];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &r[i]);
        s[i] = r[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter number of cylinders: ");
    scanf("%d", &cylinders);

    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (s[i] > s[j]) {
                int t = s[i];
                s[i] = s[j];
                s[j] = t;
            }

    // SSTF
    for (i = 0; i < n; i++)
        done[i] = 0;

    cur = head;
    total = 0;

    for (i = 0; i < n; i++) {
        int pos = -1, d = 999999;

        for (j = 0; j < n; j++)
            if (!done[j] && abs(r[j] - cur) < d) {
                d = abs(r[j] - cur);
                pos = j;
            }

        done[pos] = 1;
        total += abs(r[pos] - cur);
        cur = r[pos];
    }

    printf("\nSSTF seek movement = %d\n", total);

    // SCAN: move towards higher cylinders first
    cur = head;
    total = 0;

    for (i = 0; i < n; i++)
        if (s[i] >= head) {
            total += abs(s[i] - cur);
            cur = s[i];
        }

    total += abs((cylinders - 1) - cur);
    cur = cylinders - 1;

    for (i = n - 1; i >= 0; i--)
        if (s[i] < head) {
            total += abs(s[i] - cur);
            cur = s[i];
        }

    printf("SCAN seek movement = %d\n", total);

    // C-LOOK
    cur = head;
    total = 0;
    j = 0;

    while (j < n && s[j] < head)
        j++;

    for (i = j; i < n; i++) {
        total += abs(s[i] - cur);
        cur = s[i];
    }

    if (j > 0) {
        total += abs(cur - s[0]);
        cur = s[0];

        for (i = 1; i < j; i++) {
            total += abs(s[i] - cur);
            cur = s[i];
        }
    }

    printf("C-LOOK seek movement = %d\n", total);

    return 0;
}