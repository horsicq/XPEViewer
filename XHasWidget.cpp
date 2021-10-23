@@ -113,7 +113,7 @@ void XHashWidget::reload()
        ui->tableWidgetRegions->setHorizontalHeaderLabels(slHeader);
        ui->tableWidgetRegions->horizontalHeader()->setVisible(true);

        for(int i=0;i<nNumberOfMemoryRecords;i++)
        for(qint32 i=0;i<nNumberOfMemoryRecords;i++)
        {
            QTableWidgetItem *pItemName=new QTableWidgetItem;
