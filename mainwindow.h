#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <trayglobal.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void Update_Tray_Event_Swap(int);
  void Update_Tray_Event_Here();
  void Update_Tray_Event_Visible();
signals:


private:
     void createMenuTray();
     QWidget *w;
     QLabel *StatusApp;
     QToolBar *topbar;
     QSystemTrayIcon *trayIcon;
     QMenu    *trayIconMenu;
     QMenu    *BaseAppMenu;
     QLineEdit *titleEdit;
     QTextEdit *messageEdit;
     QComboBox *typeCombo;
     QTextEdit *infoDisplay;
     QComboBox *iconCombo;
     QAction *toggleVisibilityAction;
     QCheckBox *toggleIconCheckBox;
     QIcon masterico;

};

#endif // MAINWINDOW_H
