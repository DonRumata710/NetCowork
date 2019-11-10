#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>


class Message
{
public:
    Message();
    explicit Message(const QByteArray& _data);
    explicit Message(QByteArray&& _data);
    Message(Message&& msg);

    static Message get_message(QIODevice* device);

    size_t get_size() const;

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

    std::string get_string();

    void set_metadata(uint32_t new_class_id, uint32_t new_object_id, uint32_t new_func_id = UINT32_MAX);

    uint32_t get_class_id() const;

    void set_class_id(uint32_t new_class_id);

    uint32_t get_object_id();

    void set_object_id(uint32_t new_object_id);

    uint32_t get_func_id();

    void set_func_id(uint32_t new_func_id);

    QByteArray get_data() const;

private:
    uint32_t class_id = UINT32_MAX;
    uint32_t object_id = UINT32_MAX;
    uint32_t func_id = UINT32_MAX;
    QByteArray data;
    QDataStream stream;
};


#endif // MESSAGE_H
