#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    QFont font ("Courier");

    QPushButton button;
    button.setText("Fox");
    button.setToolTip("Ahhhh.....FoX");
    button.setFont(font);
    button.setIcon(QIcon::fromTheme("face-smile"));
    button.show();

    return app.exec();
}
