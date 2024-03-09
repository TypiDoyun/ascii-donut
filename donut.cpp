#include <stdio.h>
#include <cmath>
#include <vector>
#include "utils/vector3.h"
#include "utils/windows.h"

#define toRadians(degrees) degrees * M_PI / 180
#define toDegrees(radians) radians / M_PI * 180
#define M_TAU M_PI * 2

#define TORUS_SCALE 2
#define TORUS_WIDTH 1
#define TORUS_POSITION 10
#define SCREEN_POSITION 10

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 22
#define DISPLAY_SCALE 4

using namespace std;

Vector3 lightDirection(0, 1, 4);
const int lightDirectionLength = lightDirection.length();
vector<Vector3> model;
double zBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH] = { 0 };
int displayBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH] = { 0 };

void getModel(int, int);

int main(void) {
    getModel(TORUS_SCALE, TORUS_WIDTH);

    // Vector3 vector3 = model[10];
    // printf("{ %.2lf %.2lf %.2lf }\n", vector3.x, vector3.y, vector3.z);

    printf("model length: %zu\n", model.size());

    int angleX = 0;
    int angleY = 0;
    int angleZ = 0;

    while (true) {
        SetConsoleCursorPosition(0, { 0, 0 });
        for (Vector3 vector : model) {

            vector.rotateX(toRadians(angleX));
            vector.rotateY(toRadians(angleY));
            vector.rotateZ(toRadians(angleZ));

            double luminance = -lightDirection.dotProduct(vector) / vector.length() / lightDirectionLength;

            if (luminance <= 0) continue;
            if (luminance > 1) luminance = 1;

            vector.z += SCREEN_POSITION + TORUS_POSITION;

            if (vector.z <= SCREEN_POSITION) continue;

            double oneOverZ = 1 / vector.z;
            double ratio = SCREEN_POSITION * oneOverZ;
            int xp = DISPLAY_WIDTH / 2.0 + (vector.x * ratio * DISPLAY_SCALE * 1.8);
            int yp = DISPLAY_HEIGHT / 2.0 + (vector.y * ratio * DISPLAY_SCALE);

            if (xp < 0 || yp < 0 || xp >= DISPLAY_WIDTH || yp >= DISPLAY_HEIGHT) continue;
            if (zBuffer[yp][xp] >= oneOverZ) continue;

            zBuffer[yp][xp] = oneOverZ;
            displayBuffer[yp][xp] = luminance * 12;
            // printf("%d\n", displayBuffer[yp][xp]);
        }
        
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                int value = displayBuffer[y][x];

                if (value == 0) printf(" ");
                else printf("%c", ".,-~:;=!*#$@"[value - 1]);

                displayBuffer[y][x] = 0;
                zBuffer[y][x] = 0;
            }
            printf("\n");
        }

        angleX += 3;
        // angleY += 5;
        angleZ += 7;

        Sleep(33);
    }


    return 0;
}

void getModel(int torusScale, int torusWidth) {
    double phiStep = toRadians(3);
    double thetaStep = toRadians(10);
    // double phiStep = toRadians(15);
    // double thetaStep = toRadians(10);

    for (double phi = 0; phi < M_TAU; phi += phiStep) {
        for (double theta = 0; theta < M_TAU; theta += thetaStep) {
            // printf("{ phi: %6.2lfdeg, theta: %6.2lfdeg }\n", toDegrees(phi), toDegrees(theta));
            Vector3 vector3(torusScale + cos(theta) * torusWidth, sin(theta) * torusWidth, 0);

            vector3.rotateY(phi);

            model.push_back(vector3);
        }
    }
}

