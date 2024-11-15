#include <stdio.h>
#include <stdbool.h>

void printMatrix(int matrix[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculateNeedMatrix(int need[][10], int max[][10], int alloc[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafeState(int n, int m, int alloc[][10], int need[][10], int avail[], int safeSeq[]) {
    int work[10], finish[10] = {0};
    for (int i = 0; i < m; i++) work[i] = avail[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found) return false; // No safe sequence
    }
    return true;
}

bool canGrantRequest(int p, int m, int request[], int alloc[][10], int need[][10], int avail[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[p][i] || request[i] > avail[i])
            return false;
    }
    return true;
}

void grantRequest(int p, int m, int request[], int alloc[][10], int need[][10], int avail[]) {
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[p][i] += request[i];
        need[p][i] -= request[i];
    }
}

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], avail[10];
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int need[10][10];
    calculateNeedMatrix(need, max, alloc, n, m);
    printf("Need matrix is:\n");
    printMatrix(need, n, m);

    int safeSeq[10];
    if (isSafeState(n, m, alloc, need, avail, safeSeq)) {
        printf("System is in a safe state. Safe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    int request1[10];
    printf("Enter request for process P1: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request1[i]);
    }

    if (canGrantRequest(1, m, request1, alloc, need, avail)) {
        grantRequest(1, m, request1, alloc, need, avail);
        if (isSafeState(n, m, alloc, need, avail, safeSeq)) {
            printf("Request can be granted. System is in a safe state. Final available resources:\n");
            for (int i = 0; i < m; i++) printf("%d ", avail[i]);
            printf("\n");
        } else {
            printf("Request would lead to an unsafe state.\n");
        }
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    int request2[10];
    printf("Enter request for process P2: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request2[i]);
    }

    if (canGrantRequest(2, m, request2, alloc, need, avail)) {
        grantRequest(2, m, request2, alloc, need, avail);
        if (isSafeState(n, m, alloc, need, avail, safeSeq)) {
            printf("Request can be granted. System is in a safe state. Final available resources:\n");
            for (int i = 0; i < m; i++) printf("%d ", avail[i]);
            printf("\n");
        } else {
            printf("Request would lead to an unsafe state.\n");
        }
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    return 0;
}
