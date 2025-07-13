#include <QApplication>
#include "menu.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Menu menu;
    MainWindow ventana;

    QObject::connect(&menu, &Menu::nivelSeleccionado, [&ventana](int nivel){
        ventana.iniciarNivel(nivel);
        ventana.show();
    });

    menu.show();  // Mostrar el menú al iniciar

    return a.exec();
}
