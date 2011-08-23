/*************************************************************************

	Copyright 2011 Ibrahim Sha'ath

	This file is part of KeyFinder.

	KeyFinder is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	KeyFinder is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with KeyFinder.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

#ifndef BATCHWINDOW_H
#define BATCHWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QThread>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QFuture>
#include <QFutureWatcher>
#include <QClipboard>
#include <QMessageBox>
#include <QLabel>

#include <vector>

#include "guidetail.h"
#include "preferences.h"
#include "guivisuals.h"
#include "keyfinderworkerthread.h"
#include "metadatataglib.h"

namespace Ui {
	class BatchWindow;
}

class BatchWindow : public QMainWindow{
	Q_OBJECT
public:
	explicit BatchWindow(QWidget *parent = 0);
	~BatchWindow();
private:
	// analysis
	Preferences prefs;
	KeyFinderWorkerThread* modelThread;
	// batch processing
	bool allowDrops;
	void dragEnterEvent(QDragEnterEvent*);
	void dropEvent(QDropEvent*);
	QFutureWatcher<void> fileDropWatcher;
	void filesDropped(QList<QUrl>&);
	QStringList getDirectoryContents(QDir);
	void addNewRow(QString);
	void getMetadata();
	int currentFile;
	void processCurrentFile();
	void cleanUpAfterRun();
	// UI
	Ui::BatchWindow* ui;
	Visuals* vis;
	QLabel* initialHelpLabel;
private slots:
	void fileFailed();
	void fileFinished(int);
	void fileDropFinished();
	void on_runBatchButton_clicked();
	void copySelectedFromTableWidget();
	void writeDetectedToGrouping();
	void clearDetected();
	void runDetailedAnalysis();
};

#endif
