#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cJSON.h"

long long convertBaseToDecimal(const char *value, int base) {
    long long decimalValue = 0;
    long long basePower = 1;

    int len = strlen(value);
    for (int i = len - 1; i >= 0; i--) {
        int digit = (value[i] >= '0' && value[i] <= '9') ? (value[i] - '0') : (value[i] - 'a' + 10);
        decimalValue += digit * basePower;
        basePower *= base;
    }
    return decimalValue;
}

double lagrangeInterpolation(int *x, double *y, int n) {
    double secret = 0;
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - x[j]) / (x[i] - x[j]);
            }
        }
        secret += term;
    }
    return secret;
}

int main() {
    FILE *file = fopen("input.json", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char *buffer = malloc(fileSize + 1);
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);
    if (!json) {
        fprintf(stderr, "JSON parse error\n");
        return 1;
    }

    cJSON *keys = cJSON_GetObjectItem(json, "keys");
    int n = 3; 
    int k = 2; 

    int *x = malloc(k * sizeof(int));
    double *y = malloc(k * sizeof(double));

    int count = 0;
    for (cJSON *point = json->child; point != NULL && count < k; point = point->next) {
        if (cJSON_IsObject(point)) {
            int base = 10; 
            const char *value = point->value.valuestring; 

            x[count] = count + 1; 
            y[count] = convertBaseToDecimal(value, base); 
            count++;
        }
    }

    double secret = lagrangeInterpolation(x, y, k);
    printf("The constant term (secret) is: %.0f\n", secret);

    free(x);
    free(y);
    cJSON_Delete(json);

    return 0;
}
