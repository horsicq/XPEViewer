/* Copyright (c) 2020-2024 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "guimainwindow.h"

#include "ui_guimainwindow.h"

GuiMainWindow::GuiMainWindow(QWidget *pParent) : QMainWindow(pParent), ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);
#ifdef USE_YARA
    XYara::initialize();
#endif
    g_pFile = nullptr;
    g_pXInfo = nullptr;

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME, X_APPLICATIONVERSION));

    setAcceptDrops(true);

    g_xOptions.setName(X_OPTIONSFILE);

    g_xOptions.addID(XOptions::ID_VIEW_STYLE, "Fusion");
    g_xOptions.addID(XOptions::ID_VIEW_QSS, "");
    g_xOptions.addID(XOptions::ID_VIEW_LANG, "System");
    g_xOptions.addID(XOptions::ID_VIEW_FONT_CONTROLS, XOptions::getDefaultFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TABLEVIEWS, XOptions::getMonoFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TREEVIEWS, XOptions::getDefaultFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TEXTEDITS, XOptions::getMonoFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_STAYONTOP, false);
    g_xOptions.addID(XOptions::ID_VIEW_SHOWLOGO, false);
    g_xOptions.addID(XOptions::ID_FILE_SAVELASTDIRECTORY, true);
    g_xOptions.addID(XOptions::ID_FILE_SAVEBACKUP, true);
    g_xOptions.addID(XOptions::ID_FILE_SAVERECENTFILES, true);

#ifdef Q_OS_WIN
    g_xOptions.addID(XOptions::ID_FILE_CONTEXT, "*");
#endif

    DIEOptionsWidget::setDefaultValues(&g_xOptions);
    SearchSignaturesOptionsWidget::setDefaultValues(&g_xOptions);
    XHexViewOptionsWidget::setDefaultValues(&g_xOptions);
    XDisasmViewOptionsWidget::setDefaultValues(&g_xOptions);
    XOnlineToolsOptionsWidget::setDefaultValues(&g_xOptions);
    XInfoDBOptionsWidget::setDefaultValues(&g_xOptions);
#ifdef USE_YARA
    g_xOptions.addID(XOptions::ID_SCAN_YARARULESPATH, "$data/yara_rules");
#endif
    g_xOptions.load();

    g_xShortcuts.setName(X_SHORTCUTSFILE);
    g_xShortcuts.setNative(g_xOptions.isNative(), g_xOptions.getApplicationDataPath());

    g_xShortcuts.addId(X_ID_FILE_OPEN);
    g_xShortcuts.addId(X_ID_FILE_CLOSE);
    g_xShortcuts.addId(X_ID_FILE_EXIT);

    g_xShortcuts.addGroup(XShortcuts::GROUPID_STRINGS);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_SIGNATURES);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_HEX);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_DISASM);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_FIND);

    g_xShortcuts.load();

    ui->widgetViewer->setGlobal(&g_xShortcuts, &g_xOptions);

    connect(&g_xOptions, SIGNAL(openFile(QString)), this, SLOT(processFile(QString)));
    connect(&g_xOptions, SIGNAL(errorMessage(QString)), this, SLOT(errorMessageSlot(QString)));

    createMenus();
    updateShortcuts();

    adjustView();

    if (QCoreApplication::arguments().count() > 1) {
        QString sFileName = QCoreApplication::arguments().at(1);

        processFile(sFileName);
    }
}

GuiMainWindow::~GuiMainWindow()
{
    closeCurrentFile();
    g_xOptions.save();
    g_xShortcuts.save();

    // DialogXInfoDBTransferProcess::saveDatabase(g_pXInfo);

    delete ui;
#ifdef USE_YARA
    XYara::finalize();
#endif
}

void GuiMainWindow::createMenus()
{
    g_pMenuFile = new QMenu(tr("File"), ui->menubar);
    g_pMenuTools = new QMenu(tr("Tools"), ui->menubar);
    g_pMenuHelp = new QMenu(tr("Help"), ui->menubar);

    g_pActionOpen = new QAction(tr("Open"), this);
    g_pActionClose = new QAction(tr("Close"), this);
    g_pActionExit = new QAction(tr("Exit"), this);
    g_pActionOptions = new QAction(tr("Options"), this);
    g_pActionAbout = new QAction(tr("About"), this);
    g_pActionShortcuts = new QAction(tr("Shortcuts"), this);
    g_pActionDemangle = new QAction(tr("Demangle"), this);

    ui->menubar->addAction(g_pMenuFile->menuAction());
    ui->menubar->addAction(g_pMenuTools->menuAction());
    ui->menubar->addAction(g_pMenuHelp->menuAction());

    g_pMenuFile->addAction(g_pActionOpen);
    g_pMenuFile->addMenu(g_xOptions.createRecentFilesMenu(this));
    g_pMenuFile->addAction(g_pActionClose);
    g_pMenuFile->addAction(g_pActionExit);
    g_pMenuTools->addAction(g_pActionDemangle);
    g_pMenuTools->addAction(g_pActionShortcuts);
    g_pMenuTools->addAction(g_pActionOptions);
    g_pMenuHelp->addAction(g_pActionAbout);

    connect(g_pActionOpen, SIGNAL(triggered()), this, SLOT(actionOpenSlot()));
    connect(g_pActionClose, SIGNAL(triggered()), this, SLOT(actionCloseSlot()));
    connect(g_pActionExit, SIGNAL(triggered()), this, SLOT(actionExitSlot()));
    connect(g_pActionOptions, SIGNAL(triggered()), this, SLOT(actionOptionsSlot()));
    connect(g_pActionAbout, SIGNAL(triggered()), this, SLOT(actionAboutSlot()));
    connect(g_pActionShortcuts, SIGNAL(triggered()), this, SLOT(actionShortcutsSlot()));
    connect(g_pActionDemangle, SIGNAL(triggered()), this, SLOT(actionDemangleSlot()));
}

void GuiMainWindow::actionOpenSlot()
{
    QString sDirectory = g_xOptions.getLastDirectory();

    QString sFileName = QFileDialog::getOpenFileName(this, tr("Open file") + QString("..."), sDirectory, tr("All files") + QString(" (*)"));

    if (!sFileName.isEmpty()) {
        processFile(sFileName);
    }
}

void GuiMainWindow::actionCloseSlot()
{
    closeCurrentFile();
}

void GuiMainWindow::actionExitSlot()
{
    this->close();
}

void GuiMainWindow::actionOptionsSlot()
{
    DialogOptions dialogOptions(this, &g_xOptions, XOptions::GROUPID_FILE);
    dialogOptions.setGlobal(&g_xShortcuts, &g_xOptions);
    dialogOptions.exec();

    adjustView();
}

void GuiMainWindow::actionAboutSlot()
{
    DialogAbout dialogAbout(this);
    dialogAbout.exec();
}

void GuiMainWindow::adjustView()
{
    g_xOptions.adjustStayOnTop(this);
    g_xOptions.adjustWidget(this, XOptions::ID_VIEW_FONT_CONTROLS);

    ui->widgetViewer->adjustView();

    if (g_xOptions.isShowLogo()) {
        ui->labelLogo->show();
    } else {
        ui->labelLogo->hide();
    }
}

void GuiMainWindow::processFile(const QString &sFileName)
{
    if ((sFileName != "") && (QFileInfo(sFileName).isFile())) {
        g_xOptions.setLastFileName(sFileName);

        closeCurrentFile();

        g_pFile = new QFile;
        g_pXInfo = new XInfoDB;

        g_pFile->setFileName(sFileName);

        if (!g_pFile->open(QIODevice::ReadWrite)) {
            if (!g_pFile->open(QIODevice::ReadOnly)) {
                closeCurrentFile();
            }
        }

        if (g_pFile) {
            XPE pe(g_pFile);
            if (pe.isValid()) {
                g_pXInfo->setData(g_pFile, pe.getFileType());

                ui->stackedWidgetMain->setCurrentIndex(1);
                g_formatOptions.bIsImage = false;
                g_formatOptions.nImageBase = -1;
                g_formatOptions.nStartType = SPE::TYPE_INFO;
                ui->widgetViewer->setData(g_pFile, g_formatOptions, 0, 0, 0);
                ui->widgetViewer->setXInfoDB(g_pXInfo);

                ui->widgetViewer->reload();

                adjustView();

                setWindowTitle(sFileName);
            } else {
                QMessageBox::critical(this, tr("Error"), tr("It is not a valid file"));
            }
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Cannot open file"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open file"));
    }
}

void GuiMainWindow::errorMessageSlot(const QString &sText)
{
    QMessageBox::critical(this, tr("Error"), sText);
}

void GuiMainWindow::closeCurrentFile()
{
    if (g_pXInfo) {
        delete g_pXInfo;
        g_pXInfo = nullptr;
    }

    if (g_pFile) {
        g_pFile->close();
        delete g_pFile;
        g_pFile = nullptr;
    }

    ui->stackedWidgetMain->setCurrentIndex(0);
    ui->widgetViewer->cleanup();

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME, X_APPLICATIONVERSION));
}

void GuiMainWindow::updateShortcuts()
{
    g_pActionOpen->setShortcut(g_xShortcuts.getShortcut(X_ID_FILE_OPEN));
    g_pActionClose->setShortcut(g_xShortcuts.getShortcut(X_ID_FILE_CLOSE));
    g_pActionExit->setShortcut(g_xShortcuts.getShortcut(X_ID_FILE_EXIT));
}

void GuiMainWindow::dragEnterEvent(QDragEnterEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dragMoveEvent(QDragMoveEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dropEvent(QDropEvent *pEvent)
{
    const QMimeData *pMimeData = pEvent->mimeData();

    if (pMimeData->hasUrls()) {
        QList<QUrl> urlList = pMimeData->urls();

        if (urlList.count()) {
            QString sFileName = urlList.at(0).toLocalFile();

            sFileName = XBinary::convertFileName(sFileName);

            processFile(sFileName);
        }
    }
}

void GuiMainWindow::actionShortcutsSlot()
{
    DialogShortcuts dialogShortcuts(this);

    dialogShortcuts.setData(&g_xShortcuts);

    dialogShortcuts.exec();

    adjustView();

    updateShortcuts();
}

void GuiMainWindow::actionDemangleSlot()
{
    DialogDemangle dialogDemangle(this);

    dialogDemangle.exec();
}
