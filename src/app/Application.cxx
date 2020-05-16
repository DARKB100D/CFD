#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLStereoWidget.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include "..\gui\startupWindow.h"
 
int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLStereoWidget::defaultFormat());

  // QT Stuff
  QApplication app( argc, argv );
 
  StartupWindow MainWindow;
  MainWindow.show();
 
  return app.exec();
}
