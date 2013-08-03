#include "../include/ClCamera.h"

ClCamera::ClCamera(int p_width, int p_height,
                   float p_fovy, float p_near, float p_far)
    : m_width(p_width), m_height(p_height), m_fovy(p_fovy), m_near(p_near), m_far(p_far),
        m_position(0.0f, 0.0f, 15.0f), m_lookat(0,0,0),
        m_cameraAngle(0.0f) // Start with an angle of 90 degree
{
    ChangeToPerspective();
}

ClCamera::~ClCamera()
{
}

void ClCamera::ChangeToPerspective()
{
    GLfloat aspectRatio;

    if (m_height == 0)
        m_height = 1;

    aspectRatio = static_cast<GLfloat>(m_width)/static_cast<GLfloat>(m_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(m_fovy, aspectRatio, m_near, m_far);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ClCamera::Refresh()
{
    // Camera Immobile
    gluLookAt(m_position.X, m_position.Y, m_position.Z,  // position caméra
              m_lookat.X, m_lookat.Y, m_lookat.Z, // "look at"
              0, 1, 0);// Normale
    glRotatef(m_cameraAngle, 0.f, 1.f, 0.f);
}

void ClCamera::ChangeToOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, m_width, m_height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ClCamera::Up(float p_velocity)
{
    m_position.Y += p_velocity;
}

void ClCamera::Down(float p_velocity)
{
    m_position.Y -= p_velocity;
}

void ClCamera::LeftFromLookAt(float p_velocity)
{
    m_cameraAngle += p_velocity;
}

void ClCamera::RightFromLookAt(float p_velocity)
{
    m_cameraAngle -= p_velocity;
}
