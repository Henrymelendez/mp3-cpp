#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QFileInfo>
#include <QTime>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>


QList<QString> playlist;
QMediaPlayer *player;
QAudioOutput *audioOutput;
int currentIndex = -1;
bool isPaused = false;

void play(){
    if(currentIndex >= 0 && currentIndex < playlist.size()){
        player->setSource(QUrl::fromLocalFile(playlist[currentIndex]));
        player->play();
    }
}

void stop(){
    player->stop();
    isPaused = false;
}

void pause(QPushButton *pauseButton){
    if(isPaused){
        player->play();
        pauseButton->setText("Pause");
        isPaused = false;
    }
    else {
        player->pause();
        pauseButton->setText("Unpause");
        isPaused = true;
    }
}

void changeTrack(QListWidget *listWidget){
    currentIndex = listWidget->currentRow();
    play();
}

void openFile(QListWidget *listWidget){
    QStringList fileNames = QFileDialog::getOpenFileNames(nullptr, "Open Audio Files", "", "Audio Files (*.mp3 *.wav *.ogg *.flac)");

    foreach (QString filename, fileNames) {
        if(!filename.isEmpty()){
            playlist.append(filename);
            listWidget->addItem(QFileInfo(filename).fileName());
        }
    }
}

QString formatTime(qint64 milliseconds){
    int totalSeconds = milliseconds/1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}


void updatePosition(qint64 position, QLabel *currentTimeLabel){
    QString timeText = "⏱️ Current: " + formatTime(position);
    currentTimeLabel->setText(timeText);
}

void updateDuration(qint64 duration, QLabel *totalTimeLabel) {
    QString timeText = "⏰ Duration: " + formatTime(duration);
    totalTimeLabel->setText(timeText);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Music Player");
    window.resize(600, 700);

    // Modern stylesheet
    app.setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #2C3E50, stop:1 #34495E);
            color: #ECF0F1;
            font-family: "SF Pro Display", "Helvetica Neue", Arial, sans-serif;
            font-size: 13px;
        }

        QLabel {
            color: #BDC3C7;
            font-weight: 500;
            padding: 8px;
            background: rgba(52, 73, 94, 0.3);
            border-radius: 6px;
            margin: 3px;
        }

        QListWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #34495E, stop:1 #2C3E50);
            border: 2px solid #3498DB;
            border-radius: 12px;
            padding: 8px;
            selection-background-color: #3498DB;
            selection-color: white;
            outline: none;
        }

        QListWidget::item {
            padding: 10px;
            margin: 2px;
            border-radius: 8px;
            background: rgba(52, 152, 219, 0.1);
            border-left: 3px solid transparent;
        }

        QListWidget::item:hover {
            background: rgba(52, 152, 219, 0.2);
            border-left: 3px solid #3498DB;
        }

        QListWidget::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #3498DB, stop:1 #2980B9);
            border-left: 3px solid #E74C3C;
            font-weight: bold;
        }

        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #3498DB, stop:1 #2980B9);
            border: none;
            border-radius: 12px;
            padding: 12px 20px;
            color: white;
            font-weight: bold;
            font-size: 14px;
            min-width: 80px;
            margin: 4px;
        }

        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #5DADE2, stop:1 #3498DB);
        }

        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #2980B9, stop:1 #21618C);
        }

        QPushButton#playButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #27AE60, stop:1 #229954);
            min-width: 100px;
        }

        QPushButton#playButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #58D68D, stop:1 #27AE60);
        }

        QPushButton#stopButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #E74C3C, stop:1 #C0392B);
            min-width: 100px;
        }

        QPushButton#stopButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #F1948A, stop:1 #E74C3C);
        }

        QPushButton#pauseButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #F39C12, stop:1 #E67E22);
            min-width: 100px;
        }

        QPushButton#pauseButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #F8C471, stop:1 #F39C12);
        }

        QPushButton#addButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #8E44AD, stop:1 #7D3C98);
            min-width: 120px;
        }

        QPushButton#addButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #BB8FCE, stop:1 #8E44AD);
        }

        QPushButton#deleteButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #95A5A6, stop:1 #7F8C8D);
            min-width: 120px;
        }

        QPushButton#deleteButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #E74C3C, stop:1 #C0392B);
        }

        QSlider::groove:horizontal {
            background: #34495E;
            height: 8px;
            border-radius: 4px;
            border: 1px solid #2C3E50;
        }

        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #3498DB, stop:1 #2980B9);
            border: 2px solid #ECF0F1;
            width: 20px;
            height: 20px;
            border-radius: 12px;
            margin: -7px 0;
        }

        QSlider::handle:horizontal:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #5DADE2, stop:1 #3498DB);
            border: 2px solid #E74C3C;
        }

        QSlider::sub-page:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #3498DB, stop:1 #2980B9);
            border-radius: 4px;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title with enhanced styling
    QLabel *titleLabel = new QLabel("🎵 Music Player", &window);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(R"(
        color: #E74C3C;
        font-size: 32px;
        font-weight: bold;
        padding: 20px;
        background: transparent;
        border-bottom: 3px solid #E74C3C;
        margin-bottom: 15px;
        border-radius: 0px;
    )");
    mainLayout->addWidget(titleLabel);

    // Playlist
    QListWidget *listWidget = new QListWidget(&window);
    listWidget->setMinimumHeight(200);
    mainLayout->addWidget(listWidget);

    // Add/Delete buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *addButton = new QPushButton("➕ Add Files", &window);
    QPushButton *deleteButton = new QPushButton("🗑️ Remove", &window);

    // Set object names for CSS targeting
    addButton->setObjectName("addButton");
    deleteButton->setObjectName("deleteButton");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    mainLayout->addLayout(buttonLayout);

    // Time labels
    QLabel *currentTimeLabel = new QLabel("⏱️ Current: 00:00", &window);
    QLabel *totalTimeLabel = new QLabel("⏰ Duration: 00:00", &window);



    mainLayout->addWidget(currentTimeLabel);
    mainLayout->addWidget(totalTimeLabel);

    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout;
    QPushButton *playButton = new QPushButton("▶️ Play", &window);
    QPushButton *stopButton = new QPushButton("⏹️ Stop", &window);
    QPushButton *pauseButton = new QPushButton("⏸️ Pause", &window);

    // Set object names for CSS targeting
    playButton->setObjectName("playButton");
    stopButton->setObjectName("stopButton");
    pauseButton->setObjectName("pauseButton");

    controlLayout->addWidget(playButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(pauseButton);
    mainLayout->addLayout(controlLayout);

    // Volume and rewind
    QHBoxLayout *rewindVolumeLayout = new QHBoxLayout;
    QPushButton *rewindButton = new QPushButton("⏪ Rewind", &window);
    QSlider *volumeSlider = new QSlider(Qt::Horizontal, &window);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setMinimumWidth(200);

    rewindVolumeLayout->addWidget(rewindButton);
    rewindVolumeLayout->addWidget(new QLabel("🔊 Volume:"));
    rewindVolumeLayout->addWidget(volumeSlider);
    mainLayout->addLayout(rewindVolumeLayout);

    window.setLayout(mainLayout);

    // Initialize media player
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    // Connect signals
    QObject::connect(playButton, &QPushButton::clicked, [=](){
        changeTrack(listWidget);
    });
    QObject::connect(stopButton, &QPushButton::clicked, stop);
    QObject::connect(pauseButton, &QPushButton::clicked, [=](){
        pause(pauseButton);
    });
    QObject::connect(addButton, &QPushButton::clicked, [=](){
        openFile(listWidget);
    });
    QObject::connect(deleteButton, &QPushButton::clicked, [=](){
        int row = listWidget->currentRow();
        if(row >= 0 && row < playlist.size()){
            playlist.removeAt(row);
            delete listWidget->takeItem(row);
        }
    });

    QObject::connect(player, &QMediaPlayer::positionChanged, [=](qint64 position){
        updatePosition(position, currentTimeLabel);
    });

    QObject::connect(player, &QMediaPlayer::durationChanged, [=](qint64 duration){
        updateDuration(duration, totalTimeLabel);
    });

    window.show();
    return app.exec();
}
