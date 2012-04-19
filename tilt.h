
#ifndef _IMU_TILT_H_
#define _IMU_TILT_H_ 1

#define DEG_RAD_OP (3.14159265359 / 180.0)
#define RAD_DEG_OP (180.0 / 3.14159265359)

#define IMU_ANGLE_FIX_OFFSET  (-0.25 * DEG_RAD_OP)

typedef struct _tilt tilt;

struct _tilt
{
    // Two states, angle and gyro bias. Unbiased angular rate is a byproduct.
    float bias;
    float rate;
    float angle;

    // Covariance of estimation error matrix.
    float P_00;
    float P_01;
    float P_10;
    float P_11;

    // State constants.
    float dt;
    float R_angle;
    float Q_gyro;
    float Q_angle;

    float angle_dy_offset;
};

void tilt_init(tilt *self, float dt, float R_angle, float Q_gyro, float Q_angle);
void tilt_state_update(tilt *self, float gyro_rate);
void tilt_kalman_update(tilt *self, float angle_measured);

inline static float tilt_get_bias(tilt *self)
// Get the bias.
{
    return self->bias;
}

inline static float tilt_get_rate(tilt *self)
// Get the rate.
{
    return self->rate;
}

inline static float tilt_get_angle(tilt *self)
// Get the angle.
{
    // return (self->angle - IMU_ANGLE_FIX_OFFSET);
    return self->angle - self->angle_dy_offset;
}

#endif // _IMU_TILT_H_
