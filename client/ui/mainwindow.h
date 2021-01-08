#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "framelesswindow.h"
#include "protocols/vpnprotocol.h"

class Settings;
class VpnConnection;

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class - Main application window
 */
#ifdef Q_OS_WIN
class MainWindow : public CFramelessWindow
#else
class MainWindow : public QMainWindow
#endif

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum class Page {Initialization = 0, NewServer = 1, Vpn = 2, Sites = 3, SomeSettings = 4, Share = 5};

private slots:
    void onBytesChanged(quint64 receivedBytes, quint64 sentBytes);
    void onConnectionStateChanged(VpnProtocol::ConnectionState state);
    void onVpnProtocolError(amnezia::ErrorCode errorCode);

    void onPushButtonBackFromNewServerClicked(bool clicked);
    void onPushButtonBackFromSettingsClicked(bool clicked);
    void onPushButtonBackFromSitesClicked(bool clicked);
    void onPushButtonBlockedListClicked(bool clicked);
    void onPushButtonConnectToggled(bool checked);
    void onPushButtonNewServerConnectWithNewData(bool clicked);
    void onPushButtonNewServerSetup(bool clicked);
    void onPushButtonSettingsClicked(bool clicked);

    void on_pushButton_close_clicked();

private:
    void goToPage(Page page);

    Ui::MainWindow *ui;
    VpnConnection* m_vpnConnection;
    Settings* m_settings;

    bool canMove = false;
    QPoint offset;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // MAINWINDOW_H
