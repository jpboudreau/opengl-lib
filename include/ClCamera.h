#ifndef CLCAMERA_H_INCLUS
#define CLCAMERA_H_INCLUS

#include <GLee.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#include "Utilitaire/Vector3.h"

class ClCamera
{
    public:
        ClCamera(int p_width, int p_height,
                   float p_fovy, float p_near, float p_far);
        virtual ~ClCamera();

        void ChangeToPerspective();
        void ChangeToOrtho();
        void Refresh();

        void Up(float p_velocity);
        void Down(float p_velocity);
        void LeftFromLookAt(float p_velocity);
        void RightFromLookAt(float p_velocity);

    private:
        int m_width;
        int m_height;
        float m_fovy;
        float m_near;
        float m_far;
        Vector3 m_position;
        Vector3 m_lookat;

        float m_cameraAngle;
};

#endif // CLCAMERA_H_INCLUS
