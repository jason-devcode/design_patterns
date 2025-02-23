/**
 * Dynamic Record - Experiment to create data records with dynamic field types and dynamic searching.
 */

#include <iostream>
#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <any>

template <typename ValueType>
class Field {
public:
    Field() = default;
    Field(const ValueType &value, const std::string &name)
        : m_value(value), m_name(name) {}
    ~Field() = default;

    ValueType getValue() const { return m_value; }
    std::string getName() const { return m_name; }

    void setValue(const ValueType &value) { m_value = value; }
    void setName(const std::string &name) { m_name = name; }

private:
    ValueType m_value;
    std::string m_name;
};

using ByteField   = Field<unsigned char>;
using ShortField  = Field<short int>;
using IntField    = Field<int>;
using BigIntField = Field<long long int>;
using FloatField  = Field<float>;
using DoubleField = Field<double>;
using StringField = Field<std::string>;

template <typename... FieldTypes>
class Record {
private:
    // Helper function to search in the tuple
    template <typename Tuple, std::size_t... I, typename T>
    std::any findInTupleImpl(const Tuple &t, const T &target, std::index_sequence<I...>) {
        std::any result;
        // Expands the fold with an initializer list, evaluating an if for each index.
        (void)std::initializer_list<int>{
            (std::get<I>(t).getName() == target ? (result = std::get<I>(t).getValue(), 0) : 0)...
        };
        return result;
    }

    template <typename T, typename... Args>
    std::any findInTuple(const std::tuple<Args...> &t, const T &target) {
        return findInTupleImpl(t, target, std::make_index_sequence<sizeof...(Args)>{});
    }

public:
    // Constructor that receives fields by value (or const reference to avoid copies)
    Record(const FieldTypes &...fieldsValues) : fields(fieldsValues...) {}

    std::any getFieldValue(const std::string &name) {
        return findInTuple(fields, name);
    }

private:
    std::tuple<FieldTypes...> fields;
};

int main() {
    IntField intField(1, "id");
    StringField stringField("user123", "name");

    Record<IntField, StringField> r(intField, stringField);

    std::any valueId = r.getFieldValue("id");
    std::any valueName = r.getFieldValue("name");

    if (valueId.has_value()) {
        std::cout << "id: " << std::any_cast<int>(valueId) << std::endl;
    } else {
        std::cout << "Field 'id' not found" << std::endl;
    }

    if (valueName.has_value()) {
        std::cout << "name: " << std::any_cast<std::string>(valueName) << std::endl;
    } else {
        std::cout << "Field 'name' not found" << std::endl;
    }

    return 0;
}
