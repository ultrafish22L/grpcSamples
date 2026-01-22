// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_BINARY_FILE_H_
#define _OCTANE_WRAP_BINARY_FILE_H_ 1

// system includes
#include <string>
// API includes
#include "octanetypes.h"
#include "octanevectypes.h"


namespace Octane { class ApiBinaryGroup; }
namespace Octane { class ApiBinaryTable; }


namespace OctaneWrap
{

class BinaryGroup;

//--------------------------------------------------------------------------------------------------
/// Wraps ApiBinaryTable.
class BinaryTable
{
    OCTANEAPI_NO_COPY(BinaryTable);

    friend class BinaryGroup;

public:

    /// Create a new binary table.
    BinaryTable();

    /// Destructor.
    ~BinaryTable();

    /// Returns TRUE if this table doesn't have any entries.
    bool isEmpty() const;

    /// Returns the number of entries in this table.
    size_t size() const;

    /// Erases the entry with the passed in id. No operation if the entry doen not exist.
    void erase(
        const int32_t id);

    /// Returns TRUE if there is an entry with the passed in id.
    bool has(
        const int32_t id) const;

    /// Returns TRUE if the 2 objects refer to the same group internally.
    bool operator==(
        const BinaryTable &other) const;

    //-- element access --

    bool get(const int32_t id,  bool             &value) const;
    bool get(const int32_t id,  int8_t           &value) const;
    bool get(const int32_t id,  Octane::int8_2   &value) const;
    bool get(const int32_t id,  Octane::int8_3   &value) const;
    bool get(const int32_t id,  Octane::int8_4   &value) const;
    bool get(const int32_t id,  uint8_t          &value) const;
    bool get(const int32_t id,  Octane::uint8_2  &value) const;
    bool get(const int32_t id,  Octane::uint8_3  &value) const;
    bool get(const int32_t id,  Octane::uint8_4  &value) const;
    bool get(const int32_t id,  int16_t          &value) const;
    bool get(const int32_t id,  Octane::int16_2  &value) const;
    bool get(const int32_t id,  Octane::int16_3  &value) const;
    bool get(const int32_t id,  Octane::int16_4  &value) const;
    bool get(const int32_t id,  uint16_t         &value) const;
    bool get(const int32_t id,  Octane::uint16_2 &value) const;
    bool get(const int32_t id,  Octane::uint16_3 &value) const;
    bool get(const int32_t id,  Octane::uint16_4 &value) const;
    bool get(const int32_t id,  int32_t          &value) const;
    bool get(const int32_t id,  Octane::int32_2  &value) const;
    bool get(const int32_t id,  Octane::int32_3  &value) const;
    bool get(const int32_t id,  Octane::int32_4  &value) const;
    bool get(const int32_t id,  uint32_t         &value) const;
    bool get(const int32_t id,  Octane::uint32_2 &value) const;
    bool get(const int32_t id,  Octane::uint32_3 &value) const;
    bool get(const int32_t id,  Octane::uint32_4 &value) const;
    bool get(const int32_t id,  int64_t          &value) const;
    bool get(const int32_t id,  Octane::int64_2  &value) const;
    bool get(const int32_t id,  Octane::int64_3  &value) const;
    bool get(const int32_t id,  Octane::int64_4  &value) const;
    bool get(const int32_t id,  uint64_t         &value) const;
    bool get(const int32_t id,  Octane::uint64_2 &value) const;
    bool get(const int32_t id,  Octane::uint64_3 &value) const;
    bool get(const int32_t id,  Octane::uint64_4 &value) const;
    bool get(const int32_t id,  float            &value) const;
    bool get(const int32_t id,  Octane::float_2  &value) const;
    bool get(const int32_t id,  Octane::float_3  &value) const;
    bool get(const int32_t id,  Octane::float_4  &value) const;
    bool get(const int32_t id,  double           &value) const;
    bool get(const int32_t id,  Octane::double_2 &value) const;
    bool get(const int32_t id,  Octane::double_3 &value) const;
    bool get(const int32_t id,  Octane::double_4 &value) const;
    bool get(const int32_t id,  std::string      &value) const;

    /// Return values should be deleted by the caller.
    bool getGroup(const int32_t id, BinaryGroup &group) const;
    bool getTable(const int32_t id, BinaryTable &table) const;

    //-- element modifiers --

    void set(const int32_t id,  const bool             value);
    void set(const int32_t id,  const int8_t           value);
    void set(const int32_t id,  const Octane::int8_2   value);
    void set(const int32_t id,  const Octane::int8_3   value);
    void set(const int32_t id,  const Octane::int8_4   value);
    void set(const int32_t id,  const uint8_t          value);
    void set(const int32_t id,  const Octane::uint8_2  value);
    void set(const int32_t id,  const Octane::uint8_3  value);
    void set(const int32_t id,  const Octane::uint8_4  value);
    void set(const int32_t id,  const int16_t          value);
    void set(const int32_t id,  const Octane::int16_2  value);
    void set(const int32_t id,  const Octane::int16_3  value);
    void set(const int32_t id,  const Octane::int16_4  value);
    void set(const int32_t id,  const uint16_t         value);
    void set(const int32_t id,  const Octane::uint16_2 value);
    void set(const int32_t id,  const Octane::uint16_3 value);
    void set(const int32_t id,  const Octane::uint16_4 value);
    void set(const int32_t id,  const int32_t          value);
    void set(const int32_t id,  const Octane::int32_2  value);
    void set(const int32_t id,  const Octane::int32_3  value);
    void set(const int32_t id,  const Octane::int32_4  value);
    void set(const int32_t id,  const uint32_t         value);
    void set(const int32_t id,  const Octane::uint32_2 value);
    void set(const int32_t id,  const Octane::uint32_3 value);
    void set(const int32_t id,  const Octane::uint32_4 value);
    void set(const int32_t id,  const int64_t          value);
    void set(const int32_t id,  const Octane::int64_2  value);
    void set(const int32_t id,  const Octane::int64_3  value);
    void set(const int32_t id,  const Octane::int64_4  value);
    void set(const int32_t id,  const uint64_t         value);
    void set(const int32_t id,  const Octane::uint64_2 value);
    void set(const int32_t id,  const Octane::uint64_3 value);
    void set(const int32_t id,  const Octane::uint64_4 value);
    void set(const int32_t id,  const float            value);
    void set(const int32_t id,  const Octane::float_2  value);
    void set(const int32_t id,  const Octane::float_3  value);
    void set(const int32_t id,  const Octane::float_4  value);
    void set(const int32_t id,  const double           value);
    void set(const int32_t id,  const Octane::double_2 value);
    void set(const int32_t id,  const Octane::double_3 value);
    void set(const int32_t id,  const Octane::double_4 value);
    void set(const int32_t id,  const std::string&     value);

    void setGroup(const int32_t id, const BinaryGroup &group);
    void setTable(const int32_t id, const BinaryTable &table);

    //-- io operations --

    /// Writes this ApiBinaryTable into a file.
    ///
    /// @param[in]  path
    ///     Full path to the output file.
    /// @return
    ///     TRUE if the operation was successful, FALSE if not.
    bool write(
        const std::string &path);

    /// Reads an ApiBinaryTable from a file.
    ///
    /// @param[in]  path
    ///     Full path to the input file.
    /// @param[out] octaneVersion 
    ///     Octane version number used to write the input file.
    /// @return
    ///     Pointer to the binary table. Should be disposed of via delete.
    static BinaryTable* read(
        const std::string &path,
        uint32_t          &octaneVersion);

    /// Dumps the table into the log (use for debugging only).
    void dump(
        const uint32_t indent) const;

private:

    /// wrapped binary table
    Octane::ApiBinaryTable *mApiBinaryTable;

    BinaryTable(
        Octane::ApiBinaryTable *ptr);
};



//--------------------------------------------------------------------------------------------------
/// Wraps ApiBinaryGroup.
class BinaryGroup 
{
    OCTANEAPI_NO_COPY(BinaryGroup);

    friend class BinaryTable;

public:

    /// Creates a new binary group.
    BinaryGroup();

    /// Destructor.
    ~BinaryGroup();

    /// Returns TRUE if this group doesn't have any entries.
    bool isEmpty() const;

    /// Returns the number of entries in this group.
    size_t size() const;

    /// Removes the first entry.
    void popFront();

    /// Removes the last entry.
    void popBack();

    /// Returns the id of the element stored at ix.
    int32_t getId(
        const size_t ix) const;

    /// Returns TRUE if the 2 objects refer to the same group internally.
    bool operator==(
        const BinaryGroup &other) const;

    //-- element access --

    bool get(const size_t ix,  bool             &value) const;
    bool get(const size_t ix,  int8_t           &value) const;
    bool get(const size_t ix,  Octane::int8_2   &value) const;
    bool get(const size_t ix,  Octane::int8_3   &value) const;
    bool get(const size_t ix,  Octane::int8_4   &value) const;
    bool get(const size_t ix,  uint8_t          &value) const;
    bool get(const size_t ix,  Octane::uint8_2  &value) const;
    bool get(const size_t ix,  Octane::uint8_3  &value) const;
    bool get(const size_t ix,  Octane::uint8_4  &value) const;
    bool get(const size_t ix,  int16_t          &value) const;
    bool get(const size_t ix,  Octane::int16_2  &value) const;
    bool get(const size_t ix,  Octane::int16_3  &value) const;
    bool get(const size_t ix,  Octane::int16_4  &value) const;
    bool get(const size_t ix,  uint16_t         &value) const;
    bool get(const size_t ix,  Octane::uint16_2 &value) const;
    bool get(const size_t ix,  Octane::uint16_3 &value) const;
    bool get(const size_t ix,  Octane::uint16_4 &value) const;
    bool get(const size_t ix,  int32_t          &value) const;
    bool get(const size_t ix,  Octane::int32_2  &value) const;
    bool get(const size_t ix,  Octane::int32_3  &value) const;
    bool get(const size_t ix,  Octane::int32_4  &value) const;
    bool get(const size_t ix,  uint32_t         &value) const;
    bool get(const size_t ix,  Octane::uint32_2 &value) const;
    bool get(const size_t ix,  Octane::uint32_3 &value) const;
    bool get(const size_t ix,  Octane::uint32_4 &value) const;
    bool get(const size_t ix,  int64_t          &value) const;
    bool get(const size_t ix,  Octane::int64_2  &value) const;
    bool get(const size_t ix,  Octane::int64_3  &value) const;
    bool get(const size_t ix,  Octane::int64_4  &value) const;
    bool get(const size_t ix,  uint64_t         &value) const;
    bool get(const size_t ix,  Octane::uint64_2 &value) const;
    bool get(const size_t ix,  Octane::uint64_3 &value) const;
    bool get(const size_t ix,  Octane::uint64_4 &value) const;
    bool get(const size_t ix,  float            &value) const;
    bool get(const size_t ix,  Octane::float_2  &value) const;
    bool get(const size_t ix,  Octane::float_3  &value) const;
    bool get(const size_t ix,  Octane::float_4  &value) const;
    bool get(const size_t ix,  double           &value) const;
    bool get(const size_t ix,  Octane::double_2 &value) const;
    bool get(const size_t ix,  Octane::double_3 &value) const;
    bool get(const size_t ix,  Octane::double_4 &value) const;
    bool get(const size_t ix,  std::string      &value) const;

    /// Return values should be deleted by the caller.
    bool getGroup(const size_t ix, BinaryGroup &group) const;
    bool getTable(const size_t ix, BinaryTable &table) const;

    //-- element modifiers, elements are added to the back --
 
    void add(const int32_t id,  const bool             value);
    void add(const int32_t id,  const int8_t           value);
    void add(const int32_t id,  const Octane::int8_2   value);
    void add(const int32_t id,  const Octane::int8_3   value);
    void add(const int32_t id,  const Octane::int8_4   value);
    void add(const int32_t id,  const uint8_t          value);
    void add(const int32_t id,  const Octane::uint8_2  value);
    void add(const int32_t id,  const Octane::uint8_3  value);
    void add(const int32_t id,  const Octane::uint8_4  value);
    void add(const int32_t id,  const int16_t          value);
    void add(const int32_t id,  const Octane::int16_2  value);
    void add(const int32_t id,  const Octane::int16_3  value);
    void add(const int32_t id,  const Octane::int16_4  value);
    void add(const int32_t id,  const uint16_t         value);
    void add(const int32_t id,  const Octane::uint16_2 value);
    void add(const int32_t id,  const Octane::uint16_3 value);
    void add(const int32_t id,  const Octane::uint16_4 value);
    void add(const int32_t id,  const int32_t          value);
    void add(const int32_t id,  const Octane::int32_2  value);
    void add(const int32_t id,  const Octane::int32_3  value);
    void add(const int32_t id,  const Octane::int32_4  value);
    void add(const int32_t id,  const uint32_t         value);
    void add(const int32_t id,  const Octane::uint32_2 value);
    void add(const int32_t id,  const Octane::uint32_3 value);
    void add(const int32_t id,  const Octane::uint32_4 value);
    void add(const int32_t id,  const int64_t          value);
    void add(const int32_t id,  const Octane::int64_2  value);
    void add(const int32_t id,  const Octane::int64_3  value);
    void add(const int32_t id,  const Octane::int64_4  value);
    void add(const int32_t id,  const uint64_t         value);
    void add(const int32_t id,  const Octane::uint64_2 value);
    void add(const int32_t id,  const Octane::uint64_3 value);
    void add(const int32_t id,  const Octane::uint64_4 value);
    void add(const int32_t id,  const float            value);
    void add(const int32_t id,  const Octane::float_2  value);
    void add(const int32_t id,  const Octane::float_3  value);
    void add(const int32_t id,  const Octane::float_4  value);
    void add(const int32_t id,  const double           value);
    void add(const int32_t id,  const Octane::double_2 value);
    void add(const int32_t id,  const Octane::double_3 value);
    void add(const int32_t id,  const Octane::double_4 value);
    void add(const int32_t id,  const char*            value);

    void addGroup(const int32_t id, const BinaryGroup &group);
    void addTable(const int32_t id, const BinaryTable &table);

    /// Dumps the group into the log (use for debugging only).
    void dump(
        const uint32_t indent) const;

private:

    /// wrapped binary group
    Octane::ApiBinaryGroup *mApiBinaryGroup;

    BinaryGroup(
        Octane::ApiBinaryGroup *ptr);
};



} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_BINARY_FILE_H_
