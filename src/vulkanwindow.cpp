#include "vulkanwindow.h"

#include <QMouseEvent>

#include "vulkanrenderer.h"

QVulkanWindowRenderer *VulkanWindow::createRenderer()
{
    qDebug("Creating renderer");

    renderer = new VulkanRenderer(this);

    return renderer;
}

VulkanRenderer* VulkanWindow::getRenderer()
{
    return renderer;
}

void VulkanWindow::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    lastPos = e->pos();
}

void VulkanWindow::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void VulkanWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (!pressed)
        return;

    float dx        = e->pos().x() - lastPos.x();
    float dy        = e->pos().y() - lastPos.y();
    float magnitude = std::max(abs(dx),abs(dy));
    //float trigger   = 3.0f;

    if (  magnitude > 0.0f )
    {
        //Lock here if you want only 1 axis
        /*
        if ( trigger * abs(dx) > abs(dy))
        {
            m_renderer->translate(dx, 0);
        }
        else if (  abs(dx) < trigger * abs(dy) )
        {
            m_renderer->translate(0, dy);
        }
        else
        {
            //small movements filter out
        }
        */

        renderer->translate(dx, dy);
    }

    lastPos = e->pos();
}

void VulkanWindow::wheelEvent(QWheelEvent *e)
{
    e->delta() > 0 ? scale += scale*0.1f : scale -= scale*0.1f;


    //Limit the scale,
    scale = scale > 0.1f ? scale : 0.1f;
    scale = scale < 5.0f ? scale : 5.0f;
    renderer->scale(scale);
}

