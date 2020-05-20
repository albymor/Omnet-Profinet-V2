//
// Generated file, do not edit! Created by nedtool 5.6 from ProfinetFrame.msg.
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
#include "ProfinetFrame_m.h"

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

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(ProfinetFrame)

ProfinetFrame::ProfinetFrame() : ::inet::FieldsChunk()
{
}

ProfinetFrame::ProfinetFrame(const ProfinetFrame& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ProfinetFrame::~ProfinetFrame()
{
}

ProfinetFrame& ProfinetFrame::operator=(const ProfinetFrame& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ProfinetFrame::copy(const ProfinetFrame& other)
{
    this->Vlan = other.Vlan;
    this->EtherType = other.EtherType;
    this->FrameId = other.FrameId;
    for (size_t i = 0; i < 40; i++) {
        this->Data[i] = other.Data[i];
    }
    this->CycleCounter = other.CycleCounter;
    this->DataStatus = other.DataStatus;
    this->TransferStatus = other.TransferStatus;
}

void ProfinetFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->Vlan);
    doParsimPacking(b,this->EtherType);
    doParsimPacking(b,this->FrameId);
    doParsimArrayPacking(b,this->Data,40);
    doParsimPacking(b,this->CycleCounter);
    doParsimPacking(b,this->DataStatus);
    doParsimPacking(b,this->TransferStatus);
}

void ProfinetFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->Vlan);
    doParsimUnpacking(b,this->EtherType);
    doParsimUnpacking(b,this->FrameId);
    doParsimArrayUnpacking(b,this->Data,40);
    doParsimUnpacking(b,this->CycleCounter);
    doParsimUnpacking(b,this->DataStatus);
    doParsimUnpacking(b,this->TransferStatus);
}

uint16_t ProfinetFrame::getVlan() const
{
    return this->Vlan;
}

void ProfinetFrame::setVlan(uint16_t Vlan)
{
    handleChange();
    this->Vlan = Vlan;
}

uint16_t ProfinetFrame::getEtherType() const
{
    return this->EtherType;
}

void ProfinetFrame::setEtherType(uint16_t EtherType)
{
    handleChange();
    this->EtherType = EtherType;
}

uint16_t ProfinetFrame::getFrameId() const
{
    return this->FrameId;
}

void ProfinetFrame::setFrameId(uint16_t FrameId)
{
    handleChange();
    this->FrameId = FrameId;
}

size_t ProfinetFrame::getDataArraySize() const
{
    return 40;
}

uint8_t ProfinetFrame::getData(size_t k) const
{
    if (k >= 40) throw omnetpp::cRuntimeError("Array of size 40 indexed by %lu", (unsigned long)k);
    return this->Data[k];
}

void ProfinetFrame::setData(size_t k, uint8_t Data)
{
    if (k >= 40) throw omnetpp::cRuntimeError("Array of size 40 indexed by %lu", (unsigned long)k);
    handleChange();
    this->Data[k] = Data;
}

uint16_t ProfinetFrame::getCycleCounter() const
{
    return this->CycleCounter;
}

void ProfinetFrame::setCycleCounter(uint16_t CycleCounter)
{
    handleChange();
    this->CycleCounter = CycleCounter;
}

uint8_t ProfinetFrame::getDataStatus() const
{
    return this->DataStatus;
}

void ProfinetFrame::setDataStatus(uint8_t DataStatus)
{
    handleChange();
    this->DataStatus = DataStatus;
}

uint8_t ProfinetFrame::getTransferStatus() const
{
    return this->TransferStatus;
}

void ProfinetFrame::setTransferStatus(uint8_t TransferStatus)
{
    handleChange();
    this->TransferStatus = TransferStatus;
}

class ProfinetFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_Vlan,
        FIELD_EtherType,
        FIELD_FrameId,
        FIELD_Data,
        FIELD_CycleCounter,
        FIELD_DataStatus,
        FIELD_TransferStatus,
    };
  public:
    ProfinetFrameDescriptor();
    virtual ~ProfinetFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ProfinetFrameDescriptor)

ProfinetFrameDescriptor::ProfinetFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ProfinetFrame)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

ProfinetFrameDescriptor::~ProfinetFrameDescriptor()
{
    delete[] propertynames;
}

bool ProfinetFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ProfinetFrame *>(obj)!=nullptr;
}

const char **ProfinetFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ProfinetFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ProfinetFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int ProfinetFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_Vlan
        FD_ISEDITABLE,    // FIELD_EtherType
        FD_ISEDITABLE,    // FIELD_FrameId
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_Data
        FD_ISEDITABLE,    // FIELD_CycleCounter
        FD_ISEDITABLE,    // FIELD_DataStatus
        FD_ISEDITABLE,    // FIELD_TransferStatus
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ProfinetFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Vlan",
        "EtherType",
        "FrameId",
        "Data",
        "CycleCounter",
        "DataStatus",
        "TransferStatus",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ProfinetFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'V' && strcmp(fieldName, "Vlan") == 0) return base+0;
    if (fieldName[0] == 'E' && strcmp(fieldName, "EtherType") == 0) return base+1;
    if (fieldName[0] == 'F' && strcmp(fieldName, "FrameId") == 0) return base+2;
    if (fieldName[0] == 'D' && strcmp(fieldName, "Data") == 0) return base+3;
    if (fieldName[0] == 'C' && strcmp(fieldName, "CycleCounter") == 0) return base+4;
    if (fieldName[0] == 'D' && strcmp(fieldName, "DataStatus") == 0) return base+5;
    if (fieldName[0] == 'T' && strcmp(fieldName, "TransferStatus") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ProfinetFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_Vlan
        "uint16_t",    // FIELD_EtherType
        "uint16_t",    // FIELD_FrameId
        "uint8_t",    // FIELD_Data
        "uint16_t",    // FIELD_CycleCounter
        "uint8_t",    // FIELD_DataStatus
        "uint8_t",    // FIELD_TransferStatus
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ProfinetFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ProfinetFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ProfinetFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ProfinetFrame *pp = (ProfinetFrame *)object; (void)pp;
    switch (field) {
        case FIELD_Data: return 40;
        default: return 0;
    }
}

const char *ProfinetFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProfinetFrame *pp = (ProfinetFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ProfinetFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProfinetFrame *pp = (ProfinetFrame *)object; (void)pp;
    switch (field) {
        case FIELD_Vlan: return ulong2string(pp->getVlan());
        case FIELD_EtherType: return ulong2string(pp->getEtherType());
        case FIELD_FrameId: return ulong2string(pp->getFrameId());
        case FIELD_Data: return ulong2string(pp->getData(i));
        case FIELD_CycleCounter: return ulong2string(pp->getCycleCounter());
        case FIELD_DataStatus: return ulong2string(pp->getDataStatus());
        case FIELD_TransferStatus: return ulong2string(pp->getTransferStatus());
        default: return "";
    }
}

bool ProfinetFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ProfinetFrame *pp = (ProfinetFrame *)object; (void)pp;
    switch (field) {
        case FIELD_Vlan: pp->setVlan(string2ulong(value)); return true;
        case FIELD_EtherType: pp->setEtherType(string2ulong(value)); return true;
        case FIELD_FrameId: pp->setFrameId(string2ulong(value)); return true;
        case FIELD_Data: pp->setData(i,string2ulong(value)); return true;
        case FIELD_CycleCounter: pp->setCycleCounter(string2ulong(value)); return true;
        case FIELD_DataStatus: pp->setDataStatus(string2ulong(value)); return true;
        case FIELD_TransferStatus: pp->setTransferStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ProfinetFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ProfinetFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ProfinetFrame *pp = (ProfinetFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

