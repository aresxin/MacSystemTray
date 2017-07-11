#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
      QMenuBar *menuBar = new QMenuBar(this);
      QStatusBar *statusbar = new QStatusBar(this);
      StatusApp = new QLabel("App Loading ..... ");
      statusbar->addWidget(StatusApp);
      this->setMenuBar(menuBar);
      this->setStatusBar(statusbar);
      QPixmap perimage(":/images/mac/quit.png");
      trayIcon = new QSystemTrayIcon(QIcon(perimage),this);
      QGridLayout *layout = new QGridLayout();
      w = new QWidget(this);
      this->setCentralWidget(w);
      w->setLayout(layout);

      //// elements to show
      QLabel *titleLabel = new QLabel(tr("Message Title"));
      titleEdit = new QLineEdit(tr("Message Title"));
      /////  titleEdit  messageEdit
      QLabel *messageLabel = new QLabel(tr("Message Contents"));
      messageEdit = new QTextEdit(tr("Man is more ape than many of the apes"));
      messageEdit->setAcceptRichText(false);


      QPushButton *balloonButton = new QPushButton(tr("Send this message..."));
      balloonButton->setToolTip(tr("Click here to balloon the message"));
      //// connect(balloonButton, SIGNAL(released()), this, SLOT(Update_Tray_Event_Here()));
      connect(balloonButton,&QPushButton::released, this, &MainWindow::Update_Tray_Event_Here );



      infoDisplay = new QTextEdit(tr("Status messages will be visible here.."));
      infoDisplay->setDisabled(true);
      infoDisplay->setMaximumHeight(100);

      toggleIconCheckBox = new QCheckBox(tr("Show system tray icon"));
      toggleIconCheckBox->setChecked(true);
      QObject::connect(toggleIconCheckBox,&QCheckBox::stateChanged, this, &MainWindow::Update_Tray_Event_Visible );


      QLabel *iconLabel = new QLabel("Select color");
      iconCombo = new QComboBox(this);
      const QStringList colorNames = QColor::colorNames();
      int index = 0;
      foreach (const QString &colorName, colorNames) {
              const QString hartname = colorName;
              const QColor qtcolor(hartname);
              QIcon nowid =  createColorIcon(qtcolor);
              iconCombo->addItem(nowid,hartname,qtcolor);
              //// addItem(const QIcon &aicon, const QString &atext,const QVariant &auserData)
      }


              layout->addWidget(titleLabel, 0, 0);
              layout->addWidget(titleEdit, 0, 1);
              layout->addWidget(messageLabel, 1, 0);
              layout->addWidget(messageEdit, 1, 1);
              layout->addWidget(balloonButton, 4, 1);
              layout->addWidget(infoDisplay, 5, 0, 1, 2);
              layout->addWidget(toggleIconCheckBox, 6, 0);
              layout->addWidget(iconLabel, 7, 0);
              layout->addWidget(iconCombo, 7, 1);

      QObject::connect(iconCombo, SIGNAL(activated(int)),this, SLOT(Update_Tray_Event_Swap(int)));

      this->createMenuTray();
      setWindowTitle(tr("System Tray Example"));
      setWindowIcon(QIcon(":/zzzapple.png"));
}

void MainWindow::createMenuTray()
{

  QPixmap perimage(":/images/mac/quit.png");
  if (perimage.isNull()) {
      QMessageBox::warning(this, tr("Image is null by pixmap"),tr("Image is null by icon"));
    }
      perimage.scaled(11,11);
      masterico = QIcon(perimage);  //// QIcon masterico;
      if ( masterico.isNull() ) {
          QMessageBox::warning(this, tr("Image ICON is null by icon"),tr("Image is null by icon"));
        }
      if (!trayIcon->isSystemTrayAvailable()) {
        QMessageBox::warning(this, tr("System tray is unavailable"),tr("System tray unavailable"));
      }

      if (!trayIcon->supportsMessages()) {
        QMessageBox::warning(this, tr("System tray supportsMessages is unavailable"),tr("System tray supportsMessages unavailable"));
      }

      trayIcon->setToolTip(tr("System tray sample "));
      trayIcon->setIcon(masterico);
      trayIcon->setObjectName(tr("SystemTrayHandler"));

      // Create the menu that will be used for the context menu
      BaseAppMenu = new QMenu(0);
      BaseAppMenu->setToolTip("System trayIcon example");
      BaseAppMenu->setIcon(masterico);

      QAction *quitAction = new QAction("&Quit", this); // last
      quitAction->setIcon(masterico);
      quitAction->setShortcut(tr("Ctrl+w"));
      quitAction->setStatusTip(tr("Quit Aplication"));
      connect(quitAction,&QAction::triggered, this, &MainWindow::close);
      BaseAppMenu->addAction(quitAction);

      QAction *maximizeAction = new QAction("Maximize", this);
      maximizeAction->setIcon(masterico);
      connect(maximizeAction,&QAction::triggered, this, &MainWindow::showMaximized );
      topbar = addToolBar(tr("&Tray Sample"));
      topbar->addAction(quitAction);

#if defined Q_OS_MACOS
     BaseAppMenu->setAsDockMenu();  //// only mac osx
#endif

     trayIcon->setContextMenu(BaseAppMenu);
     this->setMinimumSize(400,400);
     BaseAppMenu->addAction(maximizeAction);
     trayIcon->setVisible(true);
     trayIcon->setToolTip(tr("System Tray Example "));
     trayIcon->showMessage(QString("Banana.... "),QString("Le banane sono li ...."),masterico,15000);
     //// this->statusBar()->setToolTip(QString("Le banane sono li ...."));
}

void MainWindow::Update_Tray_Event_Swap( const int hubint )
{
  Q_UNUSED(hubint);
  this->Update_Tray_Event_Here();
}


void MainWindow::Update_Tray_Event_Here()
{
  const QColor qtcolor = iconCombo->currentData().value<QColor>();
  QIcon nowidactive =  createColorIcon(qtcolor);

  ///////// //// display message by SystemTray item mac window ecc..->text();
  QString MS_title = titleEdit->text();
  QString MS_message = messageEdit->document()->toPlainText();
  trayIcon->setVisible(true);
  trayIcon->setToolTip(tr("System Tray Example "));
    if (trayIcon->isSystemTrayAvailable()) {
      trayIcon->showMessage(MS_title,MS_message,QSystemTrayIcon::Warning,15000);
      trayIcon->setIcon(nowidactive);

    }
  infoDisplay->setPlainText(MS_message + QString(" current color:") + qtcolor.name() );
  StatusApp->setText(QString("MainWindow::Update_Tray_Event_Here"));
}

void MainWindow::Update_Tray_Event_Visible()
{
   const bool now = toggleIconCheckBox->isChecked();
   if (trayIcon->isSystemTrayAvailable()) {
        if (now) {
            //// active?
            trayIcon->setVisible(true);
          } else {
            trayIcon->setVisible(false);
          }
   }
   this->statusBar()->setStatusTip(QString("MainWindow::Update_Tray_Event_Visible"));
   StatusApp->setText(QString("MainWindow::Update_Tray_Event_Visible"));
}



MainWindow::~MainWindow()
{

}
