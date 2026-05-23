/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QPushButton *loadDataButton;
    QWidget *configureRenderUI;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *currStepLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *minStepLabel;
    QSlider *stepSlider;
    QLabel *maxStepLabel;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *minSpinBox;
    QLabel *label_4;
    QSpinBox *maxSpinBox;
    QPushButton *renderButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 666);
        MainWindow->setMinimumSize(QSize(1024, 512));
        MainWindow->setDocumentMode(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1024, 512));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");

        horizontalLayout_4->addWidget(widget_2);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::Box);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 283, 650));
        scrollAreaWidgetContents->setMinimumSize(QSize(90, 0));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setObjectName("verticalLayout_4");
        loadDataButton = new QPushButton(scrollAreaWidgetContents);
        loadDataButton->setObjectName("loadDataButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loadDataButton->sizePolicy().hasHeightForWidth());
        loadDataButton->setSizePolicy(sizePolicy);
        loadDataButton->setMinimumSize(QSize(0, 80));

        verticalLayout_4->addWidget(loadDataButton);

        configureRenderUI = new QWidget(scrollAreaWidgetContents);
        configureRenderUI->setObjectName("configureRenderUI");
        verticalLayout = new QVBoxLayout(configureRenderUI);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(configureRenderUI);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        currStepLabel = new QLabel(configureRenderUI);
        currStepLabel->setObjectName("currStepLabel");
        currStepLabel->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(currStepLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        minStepLabel = new QLabel(configureRenderUI);
        minStepLabel->setObjectName("minStepLabel");
        minStepLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(minStepLabel);

        stepSlider = new QSlider(configureRenderUI);
        stepSlider->setObjectName("stepSlider");
        stepSlider->setMinimumSize(QSize(0, 30));
        stepSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(stepSlider);

        maxStepLabel = new QLabel(configureRenderUI);
        maxStepLabel->setObjectName("maxStepLabel");
        maxStepLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(maxStepLabel);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(configureRenderUI);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(configureRenderUI);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        minSpinBox = new QSpinBox(configureRenderUI);
        minSpinBox->setObjectName("minSpinBox");

        horizontalLayout_2->addWidget(minSpinBox);

        label_4 = new QLabel(configureRenderUI);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        maxSpinBox = new QSpinBox(configureRenderUI);
        maxSpinBox->setObjectName("maxSpinBox");

        horizontalLayout_2->addWidget(maxSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        renderButton = new QPushButton(configureRenderUI);
        renderButton->setObjectName("renderButton");
        sizePolicy.setHeightForWidth(renderButton->sizePolicy().hasHeightForWidth());
        renderButton->setSizePolicy(sizePolicy);
        renderButton->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(renderButton);


        verticalLayout_4->addWidget(configureRenderUI);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_4->addWidget(scrollArea);

        horizontalLayout_4->setStretch(0, 5);
        horizontalLayout_4->setStretch(1, 2);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        loadDataButton->setText(QCoreApplication::translate("MainWindow", "Load Data", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Select step:</p></body></html>", nullptr));
        currStepLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>0</p></body></html>", nullptr));
        minStepLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">0</p></body></html>", nullptr));
        maxStepLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">0</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select function normalization range(including):", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "From:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "To:", nullptr));
        renderButton->setText(QCoreApplication::translate("MainWindow", "Render", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
