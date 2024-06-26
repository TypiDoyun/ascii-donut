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
#define TORUS_POSITION 5
#define SCREEN_POSITION 10

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 22
#define DISPLAY_SCALE 4
#define DISPLAY_FPS 60

using namespace std;

Vector3 lightDirection(0, 1, 2);
const double lightDirectionLength = lightDirection.length();
double zBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH] = { 0 };
int displayBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH] = { 0 };

void getModel(int, int);

int main(void) {

    double angleX = 0;
    double angleY = 0;
    double angleZ = 0;
    double phiStep = toRadians(3);
    double thetaStep = toRadians(10);

    while (true) {
        SetConsoleCursorPosition(0, { 0, 0 });

        for (double phi = 0; phi < M_TAU; phi += phiStep) {
            for (double theta = 0; theta < M_TAU; theta += thetaStep) {
                Vector3 vector3(cos(theta) * TORUS_WIDTH, sin(theta) * TORUS_WIDTH, 0);
                Vector3 luminanceVector(vector3);

                vector3.x += TORUS_SCALE;
                vector3.rotateY(phi);
                luminanceVector.rotateY(phi);

                vector3.rotateX(toRadians(angleX));
                vector3.rotateZ(toRadians(angleZ));
                luminanceVector.rotateX(toRadians(angleX));
                luminanceVector.rotateZ(toRadians(angleZ));

                int luminance = -round(lightDirection.dotProduct(luminanceVector) / lightDirectionLength * 11);

                if (luminance < 0) continue;

                vector3.z += SCREEN_POSITION + TORUS_POSITION;

                if (vector3.z <= SCREEN_POSITION) continue;

                double oneOverZ = 1 / vector3.z;
                double ratio = SCREEN_POSITION * oneOverZ;
                int xp = DISPLAY_WIDTH / 2.0 + (vector3.x * ratio * DISPLAY_SCALE * 1.8);
                int yp = DISPLAY_HEIGHT / 2.0 + (vector3.y * ratio * DISPLAY_SCALE);

                if (xp < 0 || yp < 0 || xp >= DISPLAY_WIDTH || yp >= DISPLAY_HEIGHT) continue;
                if (zBuffer[yp][xp] >= oneOverZ) continue;

                zBuffer[yp][xp] = oneOverZ;
                displayBuffer[yp][xp] = luminance + 1;
            }
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

        angleX += 5;
        angleZ += 3;

        Sleep(33);
    }


    return 0;
}

