#ifndef HAVE_PVXS
#include <math.h>

#include <ntndArrayConverterAPI.h>
#include <NDArray.h>
#include <pv/ntndarray.h>

typedef struct NTNDArrayInfo
{
    int ndims;
    size_t dims[ND_ARRAY_MAX_DIMS];
    size_t nElements, totalBytes;
    int bytesPerElement;
    NDColorMode_t colorMode;
    NDDataType_t dataType;
    std::string codec;

    struct
    {
        int dim;
        size_t size, stride;
    }x, y, color;
}NTNDArrayInfo_t;

class NTNDARRAYCONVERTER_API NTNDArrayConverter
{
public:
    NTNDArrayConverter(epics::nt::NTNDArrayPtr array);

    NTNDArrayInfo_t getInfo (void);
    void toArray (NDArray *dest);
    void fromArray (NDArray *src);

private:
    epics::nt::NTNDArrayPtr m_array;

    epics::pvData::ScalarType getValueType (void);
    NDColorMode_t getColorMode (void);

    template <typename arrayType>
    void toValue (NDArray *dest);
    void toValue (NDArray *dest);

    void toDimensions (NDArray *dest);
    void toTimeStamp (NDArray *dest);
    void toDataTimeStamp (NDArray *dest);

    template <typename pvAttrType, typename valueType>
    void toAttribute (NDArray *dest, epics::pvData::PVStructurePtr src);
    void toStringAttribute (NDArray *dest, epics::pvData::PVStructurePtr src);
    void toUndefinedAttribute (NDArray *dest, epics::pvData::PVStructurePtr src);
    void toAttributes (NDArray *dest);

    template <typename arrayType, typename srcDataType>
    void fromValue (NDArray *src);
    void fromValue (NDArray *src);

    void fromDimensions (NDArray *src);
    void fromTimeStamp (NDArray *src);
    void fromDataTimeStamp (NDArray *src);

    template <typename pvAttrType, typename valueType>
    void fromAttribute (epics::pvData::PVStructurePtr dest, NDAttribute *src);
    void fromStringAttribute (epics::pvData::PVStructurePtr dest, NDAttribute *src);
    void fromUndefinedAttribute (epics::pvData::PVStructurePtr dest);
    void fromAttributes (NDArray *src);
};

typedef std::tr1::shared_ptr<NTNDArrayConverter> NTNDArrayConverterPtr;
#else
#include <math.h>

#include <ntndArrayConverterAPI.h>
#include <NDArray.h>
#include <pvxs/data.h>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

typedef struct NTNDArrayInfo
{
    int ndims;
    size_t dims[ND_ARRAY_MAX_DIMS];
    size_t nElements, totalBytes;
    int bytesPerElement;
    NDColorMode_t colorMode;
    NDDataType_t dataType;
    std::string codec;

    struct
    {
        int dim;
        size_t size, stride;
    }x, y, color;
}NTNDArrayInfo_t;

class NTNDARRAYCONVERTER_API NTNDArrayConverter
{
public:
    NTNDArrayConverter(pvxs::Value value);
    NTNDArrayInfo_t getInfo (void);
    void toArray (NDArray *dest);
    void fromArray (NDArray *src);

private:
    pvxs::Value m_value;
    std::unordered_map<std::type_index, NDAttrDataType_t> m_typeMap;
    std::unordered_map<std::type_index, std::string> m_fieldNameMap;
    std::unordered_map<std::type_index, pvxs::ArrayType> m_arrayTypeMap;
    NDColorMode_t getColorMode (void);

    template <typename arrayType>
    void toValue (NDArray *dest);
    void toValue (NDArray *dest);

    void toDimensions (NDArray *dest);
    void toTimeStamp (NDArray *dest);
    void toDataTimeStamp (NDArray *dest);

    template <typename valueType>
    void toAttribute (NDArray *dest, pvxs::Value attribute);
    void toStringAttribute (NDArray *dest, pvxs::Value attribute);
    void toUndefinedAttribute (NDArray *dest, pvxs::Value attribute);
    void toAttributes (NDArray *dest);

    template <typename arrayType>
    void fromValue (NDArray *src);
    void fromValue (NDArray *src);
    
    void fromDimensions (NDArray *src);
    void fromTimeStamp (NDArray *src);
    void fromDataTimeStamp (NDArray *src);

    template <typename valueType>
    void fromAttribute (pvxs::Value dest_value, NDAttribute *src);
    void fromStringAttribute (pvxs::Value dest_value, NDAttribute *src);
    void fromAttributes (NDArray *src);
};

typedef std::shared_ptr<NTNDArrayConverter> NTNDArrayConverterPtr;

#endif
