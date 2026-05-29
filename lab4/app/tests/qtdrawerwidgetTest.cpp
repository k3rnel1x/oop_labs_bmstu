#include <QApplication>
#define PATH1 "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/students_exams (вариант 2).csv"
#define PATH2 "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/schools_exams (вариант 1).csv"
#include <surfacedrawer/QtDrawerWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDrawerWidget drawer(std::make_unique<CsvFileReader>());

    drawer.LoadScene(PATH1, NormalizationParameters{0, 100, 1,1});
    drawer.RotateScene(0, 0.002, 0);
    drawer.show();

    return QCoreApplication::exec();
}