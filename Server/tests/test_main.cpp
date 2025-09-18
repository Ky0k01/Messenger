#include <QtTest>
#include "../src/WebSocketManager/server.h"

class ServerTest : public QObject {
    Q_OBJECT
private slots:
    void test_example() {
        // Пример теста
        QVERIFY(true);
    }
};

QTEST_MAIN(ServerTest)
#include "test_main.moc"
