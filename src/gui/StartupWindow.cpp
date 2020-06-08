#include "StartupWindow.h"

// This is included here because it is forward declared in
// StartupWindow.h
#include "ui_StartupWindow.h"

#include "MainWindow.h"

StartupWindow::StartupWindow() {
	// Load UI
	this->ui = new Ui_StartupWindow;
	this->ui->setupUi(this);

	// connect signals and slots
	connectObjects();

	// fill last projects list
	fillProjectHistory();
}

StartupWindow::~StartupWindow()
{
	delete ui;
}

void StartupWindow::btnCreateProject_Click()
{
	this->hide();
	MainWindow * window = new MainWindow();
	window->show();
}

void StartupWindow::btnOpenProject_Click()
{
	this->hide();
	
	QString selected_path = QFileDialog::getExistingDirectory(this, tr("Укажите место расположения проекта"), QApplication::applicationDirPath(), QFileDialog::ShowDirsOnly);
	if (selected_path.isNull()) return;

	MainWindow * window = new MainWindow(selected_path);
	window->show();
}

void StartupWindow::projectList_Click(QListWidgetItem *item)
{
	this->hide();

	QVariant data = item->data(Qt::UserRole);
	QString path = data.toString();

	MainWindow * window = new MainWindow(path);
	window->show();
}

void StartupWindow::connectObjects()
{
	connect(ui->btnCreateProject, SIGNAL(clicked()), this, SLOT(btnCreateProject_Click()));
	connect(ui->btnOpenProject, SIGNAL(clicked()), this, SLOT(btnOpenProject_Click()));
	connect(ui->ProjectsListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(projectList_Click(QListWidgetItem*)));
}

void StartupWindow::projectHistory_AddItem(QString name, QString path) {
	QVariant fullFilePathData(path);

	QListWidgetItem * newItem = new QListWidgetItem;
	newItem->setData(Qt::UserRole, fullFilePathData);
	newItem->setText(name + " (" + path + ")");
	newItem->setIcon(QIcon(":/Application/project.png"));
	ui->ProjectsListWidget->addItem(newItem);
}

void StartupWindow::fillProjectHistory()
{
	// load recent projects list

	// add items
	projectHistory_AddItem("Test project", "D:\\Hemodynamics\\TST");
}