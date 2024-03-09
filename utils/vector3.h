#include <cmath>

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
    Vector3(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    void rotateX(double radians) {
        double cosine = cos(radians);
        double sine = sin(radians);
        double y = this->y;
        double z = this->z;

        this->y = cosine * y - sine * z;
        this->z = sine * y + cosine * z;
    }

    void rotateY(double radians) {
        double cosine = cos(radians);
        double sine = sin(radians);
        double x = this->x;
        double z = this->z;

        this->x = cosine * x - sine * z;
        this->z = sine * x + cosine * z;
    }

    void rotateZ(double radians) {
        double cosine = cos(radians);
        double sine = sin(radians);
        double x = this->x;
        double y = this->y;

        this->x = sine * x + cosine * y;
        this->y = cosine * x - sine * y;
    }

    double length() const
    {
        return distance(0, 0, 0);
    }

    void add(double x, double y, double z)
    {
        this->x += x;
        this->y += y;
        this->z += z;
    }
    void add(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    double distance(double x, double y, double z) const
    {
        return powl((powl(this->x - x, 2) + powl(this->y - y, 2) + powl(this->z - z, 2)), 0.5);
    }
    double distance(const Vector3& other) const
    {
        return powl((powl(this->x - other.x, 2) + powl(this->y - other.y, 2) + powl(this->z - other.z, 2)), 0.5);
    }

    double dotProduct(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    double dotProduct(double x, double y, double z) const
    {
        return x * this->x + y * this->y + z * this->z;
    }

    double cosSimilarity(const Vector3& other) const
    {   
        double result = dotProduct(other) / (length() * other.length());
        return isnan(result) ? 0 : result;
    }

};