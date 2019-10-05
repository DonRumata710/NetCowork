#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>


class Message
{
public:
    Message() : stream(&data, QIODevice::ReadWrite) {}
    Message(const QByteArray& _data) : data(_data), stream(&data, QIODevice::ReadWrite) {}

    Message(Message&& msg) :
        class_id(msg.class_id),
        object_id(msg.object_id),
        data(std::move(msg.data)),
        stream(&data, QIODevice::ReadOnly)
    {}

    template<typename T>
    void add_value(const T& value)
    {
        stream << value;
    }

    template<>
    void add_value(const std::string& value)
    {
        stream << QString(value.c_str());
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

    void set_metadata(uint32_t new_class_id, uint32_t new_object_id)
    {
        class_id = new_class_id;
        object_id = new_object_id;
    }

    void set_class_id(uint32_t new_class_id)
    {
        class_id = new_class_id;
    }

    void set_object_id(uint32_t new_object_id)
    {
        object_id = new_object_id;
    }

    QByteArray get_data() const
    {
        QByteArray msg = data;

        msg.prepend(reinterpret_cast<const char*>(&object_id), sizeof(object_id));
        msg.prepend(reinterpret_cast<const char*>(&class_id), sizeof(class_id));

        uint16_t size (msg.size());
        msg.prepend(reinterpret_cast<char*>(&size), sizeof(size));
        return msg;
    }

private:
    uint32_t class_id = UINT32_MAX;
    uint32_t object_id = UINT32_MAX;
    QByteArray data;
    QDataStream stream;
};


#endif // MESSAGE_H
