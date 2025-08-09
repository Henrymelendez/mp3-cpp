# 🎵 Qt Music Player

A modern, feature-rich music player application built with C++ and Qt6, featuring a sleek dark theme interface and comprehensive audio playback capabilities.

## 🚀 Features

### Core Functionality
- **Multi-format Audio Support**: MP3, WAV, OGG, FLAC
- **Playlist Management**: Add, remove, and organize tracks
- **Full Playback Controls**: Play, pause, stop, and track selection
- **Real-time Audio Feedback**: Live position tracking and duration display
- **Volume Control**: Integrated audio level adjustment

### User Interface
- **Modern Dark Theme**: Professional gradient-based design
- **Responsive Layout**: Intuitive button placement and visual hierarchy
- **Real-time Updates**: Live current position and total duration timers
- **Visual Feedback**: Hover effects, selection highlighting, and status indicators
- **Accessibility**: Clear iconography and readable typography

### Technical Features
- **Signal-Slot Architecture**: Efficient event-driven programming
- **Memory Management**: Proper resource handling and cleanup
- **Cross-platform Compatibility**: Native Qt implementation
- **Modular Design**: Clean separation of concerns and reusable components

## 🛠️ Technical Stack

- **Language**: C++17
- **Framework**: Qt6 (Core, Widgets, Multimedia)
- **Build System**: CMake
- **Audio Backend**: Qt Multimedia framework
- **Styling**: Qt Style Sheets (QSS)

## 📋 Prerequisites

- Qt6 (Core, Widgets, Multimedia modules)
- CMake 3.16+
- C++17 compatible compiler
- Audio codec libraries (system dependent)

## 🔧 Installation & Build

### Clone Repository
```bash
git clone [repository-url]
cd qt-music-player
```

### Build with CMake
```bash
mkdir build
cd build
cmake ..
make
```

### Run Application
```bash
./APP
```

## 🎯 Usage

1. **Add Music**: Click "➕ Add Files" to import audio files
2. **Select Track**: Double-click any song in the playlist
3. **Control Playback**: Use play/pause/stop buttons
4. **Monitor Progress**: View real-time position and total duration
5. **Adjust Volume**: Use the horizontal slider
6. **Manage Playlist**: Select and remove unwanted tracks

## 🏗️ Architecture Overview

### Core Components
- **Media Engine**: Qt Multimedia for audio processing
- **UI Framework**: Qt Widgets for native interface
- **Event System**: Signal-slot pattern for component communication
- **Styling System**: QSS for modern visual design

### Key Classes & Functions
```cpp
// Core audio functionality
QMediaPlayer *player;           // Audio playback engine
QAudioOutput *audioOutput;      // Audio output management

// Time formatting and display
QString formatTime(qint64 ms);  // Converts milliseconds to MM:SS
void updatePosition();          // Real-time position updates
void updateDuration();          // Total track duration display

// Playlist management
QList<QString> playlist;        // Track storage
void openFile();               // File selection dialog
void changeTrack();            // Track switching logic
```

### Signal-Slot Connections
- `positionChanged(qint64)` → Real-time timer updates
- `durationChanged(qint64)` → Total duration display
- `clicked()` signals → User interaction handling

## 🎨 Design Patterns

- **Event-Driven Programming**: Qt's signal-slot mechanism
- **Separation of Concerns**: UI, logic, and data handling
- **Observer Pattern**: Real-time updates through Qt signals
- **Resource Management**: RAII principles with Qt objects

## 📊 Performance Features

- **Efficient Memory Usage**: Smart pointer management with Qt
- **Optimized Updates**: Configurable timer intervals
- **Responsive UI**: Non-blocking audio operations
- **Scalable Architecture**: Modular component design

## 🔮 Future Enhancements

- [ ] Shuffle and repeat modes
- [ ] Equalizer integration
- [ ] Playlist save/load functionality
- [ ] Keyboard shortcuts
- [ ] Album artwork display
- [ ] Search and filter capabilities

## 📄 License

This project is available for portfolio demonstration and educational purposes.

---
