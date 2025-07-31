#include <iostream>
#include <windows.h>
#include <math.h>
#include <string.h>

void gotoxy(SHORT x, SHORT y) {
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

int main() {
    std::ios::sync_with_stdio(false);
    float A = 0, B = 0;
    float i, j;
    char b[1760];
    float z[1760];
    std::cout << "\x1b[2J";  // Clear screen at start

    while (true) {
        memset(b, 32, 1760);   // Fill buffer with spaces
        memset(z, 0, 1760 * sizeof(float));  // Reset z-buffer

        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                float c = sin(i), d = cos(j), e = sin(A), f = sin(j),
                      g = cos(A), h = d + 2, D = 1 / (c * h * e + f * g + 5),
                      l = cos(i), m = cos(B), n = sin(B),
                      t = c * h * g - f * e;

                int x = (int)(40 + 30 * D * (l * h * m - t * n));
                int y = (int)(12 + 15 * D * (l * h * n + t * m));
                int o = x + 80 * y;
                int N = (int)(8 * ((f * e - c * d * g) * m - c * d * e - f * g + l * d * n));

                if (y >= 0 && y < 22 && x >= 0 && x < 80 && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        gotoxy(0, 0);
        for (int k = 0; k < 1760; k++) {
            putchar(k % 80 ? b[k] : '\n');
        }

        A += 0.04;
        B += 0.08;
        Sleep(8);  // ~120 FPS
    }

    return 0;
}
