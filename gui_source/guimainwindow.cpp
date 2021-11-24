/* Copyright (c) 2020-2021 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

GuiMainWindow::GuiMainWindow(QWidget *pParent) :
    QMainWindow(pParent),
    ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    g_pFile=nullptr;

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME,X_APPLICATIONVERSION));

    setAcceptDrops(true);

    g_xOptions.setName(X_OPTIONSFILE);

//    listIDs.append(XOptions::ID_SAVERECENTFILES);
    g_xOptions.addID(XOptions::ID_STYLE);
    g_xOptions.addID(XOptions::ID_QSS);
    g_xOptions.addID(XOptions::ID_LANG);
    g_xOptions.addID(XOptions::ID_STAYONTOP);
    g_xOptions.addID(XOptions::ID_SAVELASTDIRECTORY);
    g_xOptions.addID(XOptions::ID_SAVEBACKUP);
    g_xOptions.addID(XOptions::ID_SEARCHSIGNATURESPATH);
    g_xOptions.addID(XOptions::ID_SHOWLOGO);
    g_xOptions.load();

    g_xShortcuts.setName(X_SHORTCUTSFILE);

    g_xShortcuts.addGroup(XShortcuts::GROUPID_STRINGS);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_SIGNATURES);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_HEX);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_DISASM);

    g_xShortcuts.load();

    adjust();

    if(QCoreApplication::arguments().count()>1)
    {
        QString sFileName=QCoreApplication::arguments().at(1);

        processFile(sFileName);
    }
}

GuiMainWindow::~GuiMainWindow()
{
    closeCurrentFile();
    g_xOptions.save();
    g_xShortcuts.save();

    delete ui;
}

void GuiMainWindow::on_actionOpen_triggered()
{
    QString sDirectory=g_xOptions.getLastDirectory();

    QString sFileName=QFileDialog::getOpenFileName(this,tr("Open file")+QString("..."),sDirectory,tr("All files")+QString(" (*)"));

    if(!sFileName.isEmpty())
    {
        processFile(sFileName);
    }
}

void GuiMainWindow::on_actionClose_triggered()
{
    closeCurrentFile();
}

void GuiMainWindow::on_actionExit_triggered()
{
    this->close();
}

void GuiMainWindow::on_actionOptions_triggered()
{
    DialogOptions dialogOptions(this,&g_xOptions);
    dialogOptions.exec();

    adjust();
}

void GuiMainWindow::on_actionAbout_triggered()
{
    DialogAbout dialogAbout(this);
    dialogAbout.exec();
}

void GuiMainWindow::adjust()
{
    g_xOptions.adjustStayOnTop(this);

    ui->widgetViewer->setOptions(g_formatOptions);
    ui->widgetViewer->setGlobal(&g_xShortcuts,&g_xOptions);

    if(g_xOptions.isShowLogo())
    {
        ui->labelLogo->show();
    }
    else
    {
        ui->labelLogo->hide();
    }
}

void GuiMainWindow::processFile(QString sFileName)
{
    if((sFileName!="")&&(QFileInfo(sFileName).isFile()))
    {
        g_xOptions.setLastFileName(sFileName);

        closeCurrentFile();

        g_pFile=new QFile;

        g_pFile->setFileName(sFileName);

        if(!g_pFile->open(QIODevice::ReadWrite))
        {
            if(!g_pFile->open(QIODevice::ReadOnly))
            {
                closeCurrentFile();
            }
        }

        if(g_pFile)
        {
            XPE pe(g_pFile);
            if(pe.isValid())
            {
                ui->stackedWidgetMain->setCurrentIndex(1);
                g_formatOptions.bIsImage=false;
                g_formatOptions.nImageBase=-1;
                g_formatOptions.nStartType=SPE::TYPE_HEURISTICSCAN;
                ui->widgetViewer->setData(g_pFile,g_formatOptions,0,0,0);

                ui->widgetViewer->reload();

                adjust();

                setWindowTitle(sFileName);
            }
            else
            {
                QMessageBox::critical(this,tr("Error"),tr("It is not a valid file"));
            }
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),tr("Cannot open file"));
        }
    }
}

void GuiMainWindow::closeCurrentFile()
{
    ui->stackedWidgetMain->setCurrentIndex(0);

    if(g_pFile)
    {
        g_pFile->close();
        delete g_pFile;
        g_pFile=nullptr;
    }

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME,X_APPLICATIONVERSION));
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
    const QMimeData *pMimeData=pEvent->mimeData();

    if(pMimeData->hasUrls())
    {
        QList<QUrl> urlList=pMimeData->urls();

        if(urlList.count())
        {
            QString sFileName=urlList.at(0).toLocalFile();

            sFileName=XBinary::convertFileName(sFileName);

            processFile(sFileName);
        }
    }
}

void GuiMainWindow::on_actionShortcuts_triggered()
{
    DialogShortcuts dialogShortcuts(this);

    dialogShortcuts.setData(&g_xShortcuts);

    dialogShortcuts.exec();

    adjust();
}

void GuiMainWindow::on_actionDemangle_triggered()
{
    DialogDemangle dialogDemangle(this);

    dialogDemangle.exec();
}
