//
// Generated file, do not edit! Created by opp_msgtool 6.0 from tcp/TCPControlInfo.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "TCPControlInfo_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

class inet__IPv4AddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    inet__IPv4AddressDescriptor();
    virtual ~inet__IPv4AddressDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(inet__IPv4AddressDescriptor)

inet__IPv4AddressDescriptor::inet__IPv4AddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IPv4Address)), "")
{
    propertyNames = nullptr;
}

inet__IPv4AddressDescriptor::~inet__IPv4AddressDescriptor()
{
    delete[] propertyNames;
}

bool inet__IPv4AddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<inet::IPv4Address *>(obj)!=nullptr;
}

const char **inet__IPv4AddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *inet__IPv4AddressDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int inet__IPv4AddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int inet__IPv4AddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *inet__IPv4AddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int inet__IPv4AddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *inet__IPv4AddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **inet__IPv4AddressDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *inet__IPv4AddressDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int inet__IPv4AddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void inet__IPv4AddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'inet::IPv4Address'", field);
    }
}

const char *inet__IPv4AddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string inet__IPv4AddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void inet__IPv4AddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv4Address'", field);
    }
}

omnetpp::cValue inet__IPv4AddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'inet::IPv4Address' as cValue -- field index out of range?", field);
    }
}

void inet__IPv4AddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv4Address'", field);
    }
}

const char *inet__IPv4AddressDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr inet__IPv4AddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void inet__IPv4AddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv4Address *pp = omnetpp::fromAnyPtr<inet::IPv4Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv4Address'", field);
    }
}

class inet__IPv6AddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    inet__IPv6AddressDescriptor();
    virtual ~inet__IPv6AddressDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(inet__IPv6AddressDescriptor)

inet__IPv6AddressDescriptor::inet__IPv6AddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IPv6Address)), "")
{
    propertyNames = nullptr;
}

inet__IPv6AddressDescriptor::~inet__IPv6AddressDescriptor()
{
    delete[] propertyNames;
}

bool inet__IPv6AddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<inet::IPv6Address *>(obj)!=nullptr;
}

const char **inet__IPv6AddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *inet__IPv6AddressDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int inet__IPv6AddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int inet__IPv6AddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *inet__IPv6AddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int inet__IPv6AddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *inet__IPv6AddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **inet__IPv6AddressDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *inet__IPv6AddressDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int inet__IPv6AddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void inet__IPv6AddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'inet::IPv6Address'", field);
    }
}

const char *inet__IPv6AddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string inet__IPv6AddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void inet__IPv6AddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv6Address'", field);
    }
}

omnetpp::cValue inet__IPv6AddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'inet::IPv6Address' as cValue -- field index out of range?", field);
    }
}

void inet__IPv6AddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv6Address'", field);
    }
}

const char *inet__IPv6AddressDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr inet__IPv6AddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void inet__IPv6AddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    inet::IPv6Address *pp = omnetpp::fromAnyPtr<inet::IPv6Address>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'inet::IPv6Address'", field);
    }
}

Register_Class(TCPControlInfo)

TCPControlInfo::TCPControlInfo(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TCPControlInfo::TCPControlInfo(const TCPControlInfo& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TCPControlInfo::~TCPControlInfo()
{
}

TCPControlInfo& TCPControlInfo::operator=(const TCPControlInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TCPControlInfo::copy(const TCPControlInfo& other)
{
    this->srcIPv4 = other.srcIPv4;
    this->srcIPv6 = other.srcIPv6;
    this->srcPort = other.srcPort;
    this->destIPv4 = other.destIPv4;
    this->destIPv6 = other.destIPv6;
    this->destPort = other.destPort;
    this->tcpCommand = other.tcpCommand;
    this->tcpStatus = other.tcpStatus;
}

void TCPControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->srcIPv4);
    doParsimPacking(b,this->srcIPv6);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->destIPv4);
    doParsimPacking(b,this->destIPv6);
    doParsimPacking(b,this->destPort);
    doParsimPacking(b,this->tcpCommand);
    doParsimPacking(b,this->tcpStatus);
}

void TCPControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->srcIPv4);
    doParsimUnpacking(b,this->srcIPv6);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->destIPv4);
    doParsimUnpacking(b,this->destIPv6);
    doParsimUnpacking(b,this->destPort);
    doParsimUnpacking(b,this->tcpCommand);
    doParsimUnpacking(b,this->tcpStatus);
}

const inet::IPv4Address& TCPControlInfo::getSrcIPv4() const
{
    return this->srcIPv4;
}

void TCPControlInfo::setSrcIPv4(const inet::IPv4Address& srcIPv4)
{
    this->srcIPv4 = srcIPv4;
}

const inet::IPv6Address& TCPControlInfo::getSrcIPv6() const
{
    return this->srcIPv6;
}

void TCPControlInfo::setSrcIPv6(const inet::IPv6Address& srcIPv6)
{
    this->srcIPv6 = srcIPv6;
}

int TCPControlInfo::getSrcPort() const
{
    return this->srcPort;
}

void TCPControlInfo::setSrcPort(int srcPort)
{
    this->srcPort = srcPort;
}

const inet::IPv4Address& TCPControlInfo::getDestIPv4() const
{
    return this->destIPv4;
}

void TCPControlInfo::setDestIPv4(const inet::IPv4Address& destIPv4)
{
    this->destIPv4 = destIPv4;
}

const inet::IPv6Address& TCPControlInfo::getDestIPv6() const
{
    return this->destIPv6;
}

void TCPControlInfo::setDestIPv6(const inet::IPv6Address& destIPv6)
{
    this->destIPv6 = destIPv6;
}

int TCPControlInfo::getDestPort() const
{
    return this->destPort;
}

void TCPControlInfo::setDestPort(int destPort)
{
    this->destPort = destPort;
}

int TCPControlInfo::getTcpCommand() const
{
    return this->tcpCommand;
}

void TCPControlInfo::setTcpCommand(int tcpCommand)
{
    this->tcpCommand = tcpCommand;
}

int TCPControlInfo::getTcpStatus() const
{
    return this->tcpStatus;
}

void TCPControlInfo::setTcpStatus(int tcpStatus)
{
    this->tcpStatus = tcpStatus;
}

class TCPControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcIPv4,
        FIELD_srcIPv6,
        FIELD_srcPort,
        FIELD_destIPv4,
        FIELD_destIPv6,
        FIELD_destPort,
        FIELD_tcpCommand,
        FIELD_tcpStatus,
    };
  public:
    TCPControlInfoDescriptor();
    virtual ~TCPControlInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TCPControlInfoDescriptor)

TCPControlInfoDescriptor::TCPControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TCPControlInfo)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TCPControlInfoDescriptor::~TCPControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool TCPControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TCPControlInfo *>(obj)!=nullptr;
}

const char **TCPControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TCPControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TCPControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int TCPControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_srcIPv4
        FD_ISCOMPOUND,    // FIELD_srcIPv6
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISCOMPOUND,    // FIELD_destIPv4
        FD_ISCOMPOUND,    // FIELD_destIPv6
        FD_ISEDITABLE,    // FIELD_destPort
        FD_ISEDITABLE,    // FIELD_tcpCommand
        FD_ISEDITABLE,    // FIELD_tcpStatus
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *TCPControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcIPv4",
        "srcIPv6",
        "srcPort",
        "destIPv4",
        "destIPv6",
        "destPort",
        "tcpCommand",
        "tcpStatus",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int TCPControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcIPv4") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "srcIPv6") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "destIPv4") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "destIPv6") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "destPort") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "tcpCommand") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "tcpStatus") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *TCPControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::IPv4Address",    // FIELD_srcIPv4
        "inet::IPv6Address",    // FIELD_srcIPv6
        "int",    // FIELD_srcPort
        "inet::IPv4Address",    // FIELD_destIPv4
        "inet::IPv6Address",    // FIELD_destIPv6
        "int",    // FIELD_destPort
        "int",    // FIELD_tcpCommand
        "int",    // FIELD_tcpStatus
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **TCPControlInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TCPControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TCPControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TCPControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TCPControlInfo'", field);
    }
}

const char *TCPControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TCPControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcIPv4: return "";
        case FIELD_srcIPv6: return "";
        case FIELD_srcPort: return long2string(pp->getSrcPort());
        case FIELD_destIPv4: return "";
        case FIELD_destIPv6: return "";
        case FIELD_destPort: return long2string(pp->getDestPort());
        case FIELD_tcpCommand: return long2string(pp->getTcpCommand());
        case FIELD_tcpStatus: return long2string(pp->getTcpStatus());
        default: return "";
    }
}

void TCPControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(string2long(value)); break;
        case FIELD_destPort: pp->setDestPort(string2long(value)); break;
        case FIELD_tcpCommand: pp->setTcpCommand(string2long(value)); break;
        case FIELD_tcpStatus: pp->setTcpStatus(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TCPControlInfo'", field);
    }
}

omnetpp::cValue TCPControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcIPv4: return omnetpp::toAnyPtr(&pp->getSrcIPv4()); break;
        case FIELD_srcIPv6: return omnetpp::toAnyPtr(&pp->getSrcIPv6()); break;
        case FIELD_srcPort: return pp->getSrcPort();
        case FIELD_destIPv4: return omnetpp::toAnyPtr(&pp->getDestIPv4()); break;
        case FIELD_destIPv6: return omnetpp::toAnyPtr(&pp->getDestIPv6()); break;
        case FIELD_destPort: return pp->getDestPort();
        case FIELD_tcpCommand: return pp->getTcpCommand();
        case FIELD_tcpStatus: return pp->getTcpStatus();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TCPControlInfo' as cValue -- field index out of range?", field);
    }
}

void TCPControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destPort: pp->setDestPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tcpCommand: pp->setTcpCommand(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tcpStatus: pp->setTcpStatus(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TCPControlInfo'", field);
    }
}

const char *TCPControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_srcIPv4: return omnetpp::opp_typename(typeid(inet::IPv4Address));
        case FIELD_srcIPv6: return omnetpp::opp_typename(typeid(inet::IPv6Address));
        case FIELD_destIPv4: return omnetpp::opp_typename(typeid(inet::IPv4Address));
        case FIELD_destIPv6: return omnetpp::opp_typename(typeid(inet::IPv6Address));
        default: return nullptr;
    };
}

omnetpp::any_ptr TCPControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcIPv4: return omnetpp::toAnyPtr(&pp->getSrcIPv4()); break;
        case FIELD_srcIPv6: return omnetpp::toAnyPtr(&pp->getSrcIPv6()); break;
        case FIELD_destIPv4: return omnetpp::toAnyPtr(&pp->getDestIPv4()); break;
        case FIELD_destIPv6: return omnetpp::toAnyPtr(&pp->getDestIPv6()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TCPControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TCPControlInfo *pp = omnetpp::fromAnyPtr<TCPControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TCPControlInfo'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

