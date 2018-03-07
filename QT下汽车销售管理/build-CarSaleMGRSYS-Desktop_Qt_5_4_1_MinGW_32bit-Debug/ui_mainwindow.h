/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionM;
    QAction *actionS;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *carM;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBoxFac;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *comboBoxBra;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QLineEdit *lineEditPri;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QSpinBox *spinBox;
    QLabel *label_21;
    QLabel *labelLas;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_29;
    QLineEdit *lineEditTol;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButtonSur;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButtonCan;
    QWidget *page_2;
    QTextEdit *textEdit;
    QWidget *carC;
    QMenuBar *menuBar;
    QMenu *menuA;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(556, 378);
        actionM = new QAction(MainWindow);
        actionM->setObjectName(QStringLiteral("actionM"));
        actionS = new QAction(MainWindow);
        actionS->setObjectName(QStringLiteral("actionS"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(150, 0));
        carM = new QWidget();
        carM->setObjectName(QStringLiteral("carM"));
        splitter = new QSplitter(carM);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 20, 493, 192));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setMinimumSize(QSize(200, 0));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, -43, 220, 183));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBoxFac = new QComboBox(page);
        comboBoxFac->setObjectName(QStringLiteral("comboBoxFac"));

        horizontalLayout->addWidget(comboBoxFac);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        comboBoxBra = new QComboBox(page);
        comboBoxBra->setObjectName(QStringLiteral("comboBoxBra"));

        horizontalLayout_4->addWidget(comboBoxBra);

        horizontalSpacer_6 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_11->addWidget(label_6);

        lineEditPri = new QLineEdit(page);
        lineEditPri->setObjectName(QStringLiteral("lineEditPri"));

        horizontalLayout_11->addWidget(lineEditPri);

        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_15 = new QLabel(page);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_13->addWidget(label_15);

        spinBox = new QSpinBox(page);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_13->addWidget(spinBox);

        label_21 = new QLabel(page);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_13->addWidget(label_21);

        labelLas = new QLabel(page);
        labelLas->setObjectName(QStringLiteral("labelLas"));

        horizontalLayout_13->addWidget(labelLas);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_29 = new QLabel(page);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_19->addWidget(label_29);

        lineEditTol = new QLineEdit(page);
        lineEditTol->setObjectName(QStringLiteral("lineEditTol"));

        horizontalLayout_19->addWidget(lineEditTol);

        label_28 = new QLabel(page);
        label_28->setObjectName(QStringLiteral("label_28"));

        horizontalLayout_19->addWidget(label_28);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        pushButtonSur = new QPushButton(page);
        pushButtonSur->setObjectName(QStringLiteral("pushButtonSur"));

        horizontalLayout_12->addWidget(pushButtonSur);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_13);

        pushButtonCan = new QPushButton(page);
        pushButtonCan->setObjectName(QStringLiteral("pushButtonCan"));

        horizontalLayout_12->addWidget(pushButtonCan);


        verticalLayout->addLayout(horizontalLayout_12);

        toolBox->addItem(page, QString::fromUtf8("\350\275\246\350\276\206\347\256\241\347\220\206"));
        label_2->raise();
        comboBoxFac->raise();
        comboBoxBra->raise();
        label_5->raise();
        label_6->raise();
        lineEditPri->raise();
        label_10->raise();
        label_15->raise();
        spinBox->raise();
        label_21->raise();
        labelLas->raise();
        spinBox->raise();
        labelLas->raise();
        label_15->raise();
        label_21->raise();
        label_10->raise();
        lineEditPri->raise();
        label_6->raise();
        label_28->raise();
        lineEditTol->raise();
        label_29->raise();
        labelLas->raise();
        spinBox->raise();
        label_15->raise();
        label_21->raise();
        pushButtonSur->raise();
        pushButtonCan->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 237, 140));
        toolBox->addItem(page_2, QString::fromUtf8("\350\275\246\350\276\206\347\273\237\350\256\241"));
        splitter->addWidget(toolBox);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        splitter->addWidget(textEdit);
        stackedWidget->addWidget(carM);
        carC = new QWidget();
        carC->setObjectName(QStringLiteral("carC"));
        stackedWidget->addWidget(carC);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 23));
        menuA = new QMenu(menuBar);
        menuA->setObjectName(QStringLiteral("menuA"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuA->menuAction());
        menuA->addAction(actionM);
        menuA->addAction(actionS);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionM->setText(QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\256\241\347\220\206", 0));
        actionS->setText(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\273\237\350\256\241", 0));
        label->setText(QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\256\241\347\220\206", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\216\202\345\256\266\357\274\232", 0));
        label_5->setText(QApplication::translate("MainWindow", "\345\223\201\347\211\214\357\274\232", 0));
        label_6->setText(QApplication::translate("MainWindow", "\346\212\245\344\273\267\357\274\232", 0));
        label_10->setText(QApplication::translate("MainWindow", "\344\270\207", 0));
        label_15->setText(QApplication::translate("MainWindow", "\346\225\260\351\207\217\357\274\232", 0));
        label_21->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\346\225\260\351\207\217\357\274\232", 0));
        labelLas->setText(QApplication::translate("MainWindow", "20", 0));
        label_29->setText(QApplication::translate("MainWindow", "\346\200\273\344\273\267\357\274\232", 0));
        label_28->setText(QApplication::translate("MainWindow", "\344\270\207", 0));
        pushButtonSur->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0));
        pushButtonCan->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\256\241\347\220\206", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\273\237\350\256\241", 0));
        menuA->setTitle(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\256\241\347\220\206", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
