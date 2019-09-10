#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>


class Message
{
public:
    Message() : stream(&data, QIODevice::ReadWrite) {}
    Message(const QByteArray& _data) : data(_data), stream(&data, QIODevice::ReadWrite) {}

    template<typename T>
    void add_value(const T& value)
    {
        stream << value;
    }

    template<typename val_type>
    val_type get_value()
    {
        val_type val;
        stream >> val;
        return val;
    }

    std::string get_string()
    {
        QString str;
        stream >> str;
        return str.toStdString();
    }

    void set_metadata(uint32_t class_id, uint32_t object_id)
    {
        data.prepend(reinterpret_cast<char*>(&object_id), sizeof(object_id));
        data.prepend(reinterpret_cast<char*>(&class_id), sizeof(class_id));
    }

    QByteArray get_data()
    {
        uint16_t size;
        data.prepend(reinterpret_cast<char*>(&size), sizeof(size));
        return data;
    }

private:
    QByteArray data;
    QDataStream stream;
};


#endif // MESSAGE_H
