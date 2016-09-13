#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// This program takes max jump height from input and prints
// jump height for every time point with step 0.1 seconds.
// Program should print all time points when height is min and max.
//
// TODO: Fix all warnings on high warning level (/W4, -Wall -Wextra).
// TODO: Rename variables and split to several functions,
// see also https://ps-group.github.io/sfml/coding_conventions.html
// TODO: fix negative height values, fix heigh values higher than max height.
int main(int, char *[])
{
    const float g = 9.8f;
    float T;
    float Vn;
    int S;
    int M;
    printf("S: ");
    if (0 == scanf("%d", &S))
    {
        printf("\n" "expected floating-point number" "\n");
        exit(1);
    }
    // T - time point when height is at maximum.
    // t - current time point
    // v(t) == v0 - g * t
    // v0 = g * T
    // s(t) == v0 * t - 0.5 * g * t * t
    T = sqrt(S * 2 / g);
    printf("T=%f\n", T);
    bool flag = false;
    for (float t = 0; t < T * 2; t += 0.1f)
    {
if (t > T && !flag)
{
flag = true;
float V0 = g * T;
float s = V0 * T - 0.5 * g * T * T;
printf("t=%f, s=%f\n", T, s);
}
float V0 = g * T;
float s = V0 * t - 0.5 * g * t * t;
printf("t=%f, s=%f\n", t, s);
}

float V0 = g * T;
float s = V0 * (T*2) - 0.5 * g * (T * 2) * (T * 2);
printf("t=%f, s=%f\n", T * 2, s);

// TODO: remove system("pause") and never use it again.
system("pause");

return 0;
}