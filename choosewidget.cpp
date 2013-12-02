#include "choosewidget.h"
#include "ui_choosewidget.h"

ChooseWidget::ChooseWidget(QWidget *parent) :
    Panel(parent),
    ui(new Ui::ChooseWidget)
{
    ui->setupUi(this);
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextTrack()));
    connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousTrack()));
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(launchGame()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backToMenu()));

    m_trackList = new TrackList();
    m_trackList->load();

    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());

}

ChooseWidget::~ChooseWidget()
{
    delete ui;
    delete m_trackList;
}

void ChooseWidget::nextTrack()
{
    m_trackList->next();
    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
}

void ChooseWidget::previousTrack()
{
    m_trackList->previous();
    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
}

void ChooseWidget::launchGame()
{
     emit startGame(m_trackList->currentTrack(), "Car");
}

void ChooseWidget::backToMenu()
{
    emit showPanel("Menu");
}
