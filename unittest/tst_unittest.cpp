#include <QtTest>
#include "statistics.hh"

class unittest : public QObject
{
    Q_OBJECT

public:
    unittest();

private Q_SLOTS:
    /**
     * @brief Tests if the total poin calculation is correct.
     */
    void test_statistics();
};

unittest::unittest()
{

}

void unittest::test_statistics()
{
    Aaro::statistics stat;
    QCOMPARE(stat.getPoints(), stat.getBuses() * 10 + stat.getPlanes() * 25);
}

QTEST_APPLESS_MAIN(unittest)

#include "tst_unittest.moc"
