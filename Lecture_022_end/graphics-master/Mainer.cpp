#include <Qt\qapplication.h>
#include <MEGWindow.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    MeGlwindow meWindow;
    meWindow.show();

	return app.exec();
	
}