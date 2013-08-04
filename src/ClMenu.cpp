#include "../include/ClMenu.h"

ClMenu::ClMenu()
{
}

ClMenu::~ClMenu()
{
}

void ClMenu::Draw(ClOpenGl&) const
{
    glColor3f(0.1f, 0.5f, 0.1f);

    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(-400.0f, -4.0f, 400.0f);
        glVertex3f(-400.0f, -10.0f, -400.0f);
        glVertex3f(400.0f, -10.0f, -400.0f);
        glVertex3f(400.0f, -4.0f, 400.0f);
    glEnd();

}

void ClMenu::Update()
{
}

void ClMenu::Initialize()
{
}
