#include <QtTest>
#include "../src/mediator.h" // или другой заголовок из src, если нужно

class ExampleTest : public QObject {
    Q_OBJECT
private slots:
    void testSomething() {
        QVERIFY(true);
    }
};

QTEST_MAIN(ExampleTest)
#include "example_test.moc"
