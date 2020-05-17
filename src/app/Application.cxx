#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLStereoWidget.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include "..\gui\startupWindow.h"
 
int main(int argc, char** argv)
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLStereoWidget::defaultFormat());

  QApplication app(argc, argv);
 
  QApplication::setStyle("fusion");

  StartupWindow window;
  window.show();
 
  return app.exec();
}