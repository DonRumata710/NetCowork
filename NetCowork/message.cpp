#include "message.h"

#include <QBuffer>


Message::Message() : stream(&data, QIODevice::ReadWrite)
{}

Message::Message(const QByteArray& _data) :
    data(_data),
    stream(&data, QIODevice::ReadWrite)
{
    stream.setVersion(QDataStream::Qt_5_6);

    stream >> class_id;
    stream >> object_id;
    stream >> func_id;

    data = data.mid(stream.device()->pos());
    stream.device()->seek(0);
}

Message::Message(QByteArray&& _data) :
    data(std::move(_data)),
    stream(&data, QIODevice::ReadWrite)
{
    stream.setVersion(QDataStream::Qt_5_6);

    stream >> class_id;
    stream >> object_id;
    stream >> func_id;

    data = data.mid(stream.device()->pos());
    stream.device()->seek(0);
}

Message::Message(Message&& msg) :
    class_id(msg.class_id),
    object_id(msg.object_id),
    func_id(msg.func_id),
    data(std::move(msg.data)),
    stream(&data, QIODevice::ReadWrite)
{
    stream.setVersion(QDataStream::Qt_5_6);
}

Message& Message::operator=(Message&& msg)
{
    class_id = msg.class_id;
    object_id = msg.object_id;
    func_id = msg.func_id;
    data = std::move(msg.data);
    stream.setDevice(msg.stream.device());
    stream.setVersion(QDataStream::Qt_5_6);

    return *this;
}

Message Message::get_message(QIODevice* device)
{
    QDataStream stream(device);
    stream.setVersion(QDataStream::Qt_5_6);
    uint16_t size;
    stream >> size;

    QByteArray data(size, '\0');
    stream.readRawData(data.data(), size);

    return Message(std::move(data));
}

size_t Message::get_size() const
{
    return static_cast<size_t>(data.size() - stream.device()->pos());
}

std::string Message::get_string()
{
    QString str;
    stream >> str;
    return str.toStdString();
}

uint32_t Message::get_class_id() const
{
    return class_id;
}

void Message::set_class_id(uint32_t new_class_id)
{
    class_id = new_class_id;
}

uint32_t Message::get_object_id()
{
    return object_id;
}

void Message::set_metadata(uint32_t new_class_id, uint32_t new_object_id, uint32_t new_func_id)
{
    class_id = new_class_id;
    object_id = new_object_id;

    if (new_func_id != UINT32_MAX)
        func_id = new_func_id;
}

void Message::set_object_id(uint32_t new_object_id)
{
    object_id = new_object_id;
}

uint32_t Message::get_func_id()
{
    return func_id;
}

void Message::set_func_id(uint32_t new_func_id)
{
    func_id = new_func_id;
}

QByteArray Message::get_data() const
{
    QByteArray msg = data;

    int metadata_size(sizeof(class_id) + sizeof(object_id) + sizeof(func_id));
    uint16_t size (metadata_size + msg.size());
    msg.prepend(sizeof(size) + metadata_size, '\0');

    QDataStream tmp(&msg, QIODevice::WriteOnly);
    tmp.setVersion(QDataStream::Qt_5_6);

    tmp << size;
    tmp << class_id;
    tmp << object_id;
    tmp << func_id;

    return msg;
}
