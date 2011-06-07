
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QList>
#include <QMainWindow>
#include "preview.h"

class GraffitiArea;
//class SideDock;
class QScrollArea;
//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QHBoxLayout   *quteBoardHBox;
    //bool pen;
protected:
    void closeEvent(QCloseEvent *event);
    void updateColorBox(QColor color);
    void updatePenWidth(int newWidth);
    void updateEraserWidth(int newWidth);

private slots:
    void open();
    void save();
    void changeColor();
    void colorChanged();
    //void rgbSliderChanged(int newValue);
    void redSliderChanged(int newValue);
    void greenSliderChanged(int newValue);
    void blueSliderChanged(int newValue);
    void changeColorBlack();
    void changeColorRed();
    void changeColorGreen();
    void changeColorBlue();
    void changeColorWhite();
    void changeColorGray();
    void changeColorMagenta();
    void changeColorDarkRed();
    void changeColorDarkGreen();
    void changeColorDarkBlue();
    void changeColorYellow();
    void changeColorCyan();
    void penWidth();
    void penSliderChanged(int newWidth);
    void eraserWidth();
    void eraserSliderChanged(int newWidth);
    void updatePreviewScroll();
    void fillColor();
    void about();

public slots:
    void updatePreviewImage();

private:
    void initToolBox();
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    

    QFrame *mainFrame;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *eraserWidthAct;
    QAction *fillColorAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    
    
    QGroupBox     *toolGBox;
    QVBoxLayout   *verticalLayout;
    GraffitiArea  *graffitiArea;
    QScrollArea   *scrollArea;
    QGridLayout   *toolGrid;
    
    QPushButton   *eraserTool;
    QPushButton   *pencilTool;
    QPushButton   *colorSelectionTool;
    QPushButton   *clearTool;
    QPushButton   *textTool;
    QPushButton   *lineTool;
    QPushButton   *rectangleTool;
    QPushButton   *ellipseTool;
    QPushButton   *fillTool;
    QPushButton   *zoomTool;
    QSpacerItem   *verticalSpacer;


    QDockWidget *utilityDock;

   // QFrame *dockContent;
    QFrame *dockContent;

    QVBoxLayout     *dockLayout;
    QGroupBox       *widthGroupBox;
    QGridLayout    *widthBoxLayout;
    QSpinBox             *spinPenWidth;
    QSpinBox             *spinEraserWidth;
    QGroupBox       *colorGroupBox;
    QVBoxLayout     *colorBoxLayout;
    QGridLayout        * sliderLayout;
    QSlider *sliderRed;
    QSlider *sliderGreen;
    QSlider *sliderBlue;
    QLabel* labelRedValue;
    QLabel* labelGreenValue;
    QLabel* labelBlueValue;

    QHBoxLayout    *swatchLayout;
    QPushButton     *colorSwatch;
    QGridLayout    *smallSwatchLayout;
    QPushButton *blackColorSwatch;
    QPushButton *grayColorSwatch;
    QPushButton *redColorSwatch;
    QPushButton *darkRedColorSwatch;
    QPushButton *magentaColorSwatch;
    QPushButton *yellowColorSwatch;
    QPushButton *greenColorSwatch;
    QPushButton *darkGreenColorSwatch;
    QPushButton *blueColorSwatch;
    QPushButton *darkBlueColorSwatch;
    QPushButton *cyanColorSwatch;
    QPushButton *whiteColorSwatch;

    QGroupBox        *imageGroupBox;
    QHBoxLayout     *imageBoxLayout;
    QScrollArea *previewScrollArea;
    Preview              *previewArea;
    QSpacerItem     *spacerUtilityPane;

    int penWidthValue;
    int eraserWidthValue;
    int valueRed;
    int valueGreen;
    int valueBlue;
};
//! [0]

#endif
