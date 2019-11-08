#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>


class Message
{
public:
    Message() : stream(&data, QIODevice::ReadWrite) {}
    Message(const QByteArray& _data) :
        data(_data),
        stream(&data, QIODevice::ReadWrite)
    {
        stream.readRawData((char*)&class_id, sizeof(class_id));
        stream.readRawData((char*)&object_id, sizeof(object_id));
        stream.readRawData((char*)&func_id, sizeof(func_id));
    }

    Message(Message&& msg) :
        class_id(msg.class_id),
        object_id(msg.object_id),
        data(std::move(msg.data)),
        stream(&data, QIODevice::ReadOnly)
    {}

    size_t get_size() const
    {
        return static_cast<size_t>(data.size() - stream.device()->pos());
    }

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

    void set_metadata(uint32_t new_class_id, uint32_t new_object_id, uint32_t new_func_id = UINT32_MAX)
    {
        class_id = new_class_id;
        object_id = new_object_id;

        if (new_func_id != UINT32_MAX)
            func_id = new_func_id;
    }

    uint32_t get_class_id() const
    {
        return class_id;
    }

    void set_class_id(uint32_t new_class_id)
    {
        class_id = new_class_id;
    }

    uint32_t get_object_id()
    {
        return object_id;
    }

    void set_object_id(uint32_t new_object_id)
    {
        object_id = new_object_id;
    }

    uint32_t get_func_id()
    {
        return object_id;
    }

    void set_func_id(uint32_t new_func_id)
    {
        func_id = new_func_id;
    }

    QByteArray get_data() const
    {
        QByteArray msg = data;

        msg.prepend(reinterpret_cast<const char*>(&func_id), sizeof(func_id));
        msg.prepend(reinterpret_cast<const char*>(&object_id), sizeof(object_id));
        msg.prepend(reinterpret_cast<const char*>(&class_id), sizeof(class_id));

        uint16_t size (msg.size());
        msg.prepend(reinterpret_cast<char*>(&size), sizeof(size));
        return msg;
    }

private:
    uint32_t class_id = UINT32_MAX;
    uint32_t object_id = UINT32_MAX;
    uint32_t func_id = UINT32_MAX;
    QByteArray data;
    QDataStream stream;
};


#endif // MESSAGE_H
