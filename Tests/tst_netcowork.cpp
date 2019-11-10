#include <QtTest>

#include <Message.h>


class NetCowork : public QObject
{
    Q_OBJECT

public:
    NetCowork();
    ~NetCowork();

private slots:
    void test_message();

};

NetCowork::NetCowork()
{

}

NetCowork::~NetCowork()
{

}

void NetCowork::test_message()
{
    Message data1;
    data1.set_metadata(1, 2, 3);
    data1.add_value<uint32_t>(4);

    Message data2(data1.get_data().mid(2));
    QVERIFY(data2.get_data() == data1.get_data());

    data2.set_func_id(10);

    Message data3;
    data3.set_metadata(1, 2, 10);

    uint32_t val;
    val = data2.get_value<uint32_t>();
    data3.add_value(val);

    QVERIFY(data2.get_data() == data3.get_data());

    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    buffer.write(data3.get_data());
    buffer.seek(0);

    Message data4(Message::get_message(&buffer));
    QVERIFY(data3.get_data() == data4.get_data());
}

QTEST_APPLESS_MAIN(NetCowork)

#include "tst_netcowork.moc"
