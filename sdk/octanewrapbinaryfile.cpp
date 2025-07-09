// Copyright (C) 2025 OTOY NZ Ltd.

// application includes
#include "apibinaryfile.h"
// myself
#include "octanewrapbinaryfile.h"

using namespace OctaneWrap;


//--------------------------------------------------------------------------------------------------
// Implementation of BinaryTable.

BinaryTable::BinaryTable()
:
    mApiBinaryTable(Octane::ApiBinaryTable::create())
{}


BinaryTable::~BinaryTable()
{
    mApiBinaryTable->destroy();
}


bool BinaryTable::isEmpty() const
{
    return mApiBinaryTable->isEmpty();
}


size_t BinaryTable::size() const
{
    return mApiBinaryTable->size();
}


void BinaryTable::erase(
    const int32_t id)
{
    mApiBinaryTable->erase(id);
}


bool BinaryTable::has(
    const int32_t id) const
{
    return mApiBinaryTable->has(id);
}


bool BinaryTable::operator==(
    const BinaryTable &other) const
{
    return mApiBinaryTable->equals(*other.mApiBinaryTable);
}


bool BinaryTable::get(const int32_t id,  bool             &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  int8_t           &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int8_2   &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int8_3   &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int8_4   &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  uint8_t          &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint8_2  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint8_3  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint8_4  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  int16_t          &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int16_2  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int16_3  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int16_4  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  uint16_t         &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint16_2 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint16_3 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint16_4 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  int32_t          &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int32_2  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int32_3  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int32_4  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  uint32_t         &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint32_2 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint32_3 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint32_4 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  int64_t          &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int64_2  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int64_3  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::int64_4  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  uint64_t         &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint64_2 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint64_3 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::uint64_4 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  float            &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::float_2  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::float_3  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::float_4  &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  double           &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::double_2 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::double_3 &value) const { return mApiBinaryTable->get(id, value); }
bool BinaryTable::get(const int32_t id,  Octane::double_4 &value) const { return mApiBinaryTable->get(id, value); }

bool BinaryTable::get(const int32_t id,
                      std::string   &value) const
{ 
    // get the string in C-style
    const char *cStyleStr = NULL;
    if (!mApiBinaryTable->get(id, cStyleStr))
    {
        return false;
    }

    // copy into a std::string
    value = cStyleStr;
    mApiBinaryTable->cleanupString(cStyleStr);

    return true;
}


bool BinaryTable::getGroup(const int32_t id, BinaryGroup &group) const
{
    Octane::ApiBinaryGroup *apiBinaryGroup = NULL;
    if (!mApiBinaryTable->getGroup(id, apiBinaryGroup))
    {
        return false;
    }

    group.mApiBinaryGroup->destroy();
    group.mApiBinaryGroup = apiBinaryGroup;
    return true;
}


bool BinaryTable::getTable(const int32_t id, BinaryTable &table) const
{
    Octane::ApiBinaryTable *apiBinaryTable = NULL;
    if (!mApiBinaryTable->getTable(id, apiBinaryTable))
    {
        return false;
    }

    table.mApiBinaryTable->destroy();
    table.mApiBinaryTable = apiBinaryTable;
    return true;
}


void BinaryTable::set(const int32_t id,  const bool             value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const int8_t           value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int8_2   value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int8_3   value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int8_4   value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const uint8_t          value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint8_2  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint8_3  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint8_4  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const int16_t          value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int16_2  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int16_3  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int16_4  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const uint16_t         value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint16_2 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint16_3 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint16_4 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const int32_t          value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int32_2  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int32_3  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int32_4  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const uint32_t         value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint32_2 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint32_3 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint32_4 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const int64_t          value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int64_2  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int64_3  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::int64_4  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const uint64_t         value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint64_2 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint64_3 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::uint64_4 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const float            value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::float_2  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::float_3  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::float_4  value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const double           value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::double_2 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::double_3 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const Octane::double_4 value) { mApiBinaryTable->set(id, value); }
void BinaryTable::set(const int32_t id,  const std::string&     value) { mApiBinaryTable->set(id, value.c_str()); }


void BinaryTable::setGroup(const int32_t id, const BinaryGroup &group)
{
    mApiBinaryTable->setGroup(id, *group.mApiBinaryGroup);
}


void BinaryTable::setTable(const int32_t id, const BinaryTable &table)
{
    mApiBinaryTable->setTable(id, *table.mApiBinaryTable);
}


bool BinaryTable::write(
    const std::string &path)
{
    return mApiBinaryTable->write(path.c_str());
}


BinaryTable* BinaryTable::read(
    const std::string &path,
    uint32_t          &octaneVersion)
{
    Octane::ApiBinaryTable *table = Octane::ApiBinaryTable::read(path.c_str(), octaneVersion);
    if (table)
    {
        return new BinaryTable(table);
    }
    return NULL;
}


void BinaryTable::dump(
    const uint32_t indent) const
{
    mApiBinaryTable->dump(indent);
}


BinaryTable::BinaryTable(
    Octane::ApiBinaryTable *ptr)
:
    mApiBinaryTable(ptr)
{}



//--------------------------------------------------------------------------------------------------
// Implementation of BinaryGroup.

BinaryGroup::BinaryGroup()
:
    mApiBinaryGroup(Octane::ApiBinaryGroup::create())
{}


BinaryGroup::~BinaryGroup()
{
    mApiBinaryGroup->destroy();
}


bool BinaryGroup::isEmpty() const
{
    return mApiBinaryGroup->isEmpty();
}


size_t BinaryGroup::size() const
{
    return mApiBinaryGroup->size();
}


void BinaryGroup::popFront()
{
    mApiBinaryGroup->popFront();
}


void BinaryGroup::popBack()
{
    mApiBinaryGroup->popBack();
}


int32_t BinaryGroup::getId(
    const size_t ix) const
{
    return mApiBinaryGroup->getId(ix);
}


bool BinaryGroup::operator==(
    const BinaryGroup &other) const
{
    return mApiBinaryGroup->equals(*other.mApiBinaryGroup);
}


bool BinaryGroup::get(const size_t ix,  bool             &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  int8_t           &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int8_2   &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int8_3   &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int8_4   &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  uint8_t          &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint8_2  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint8_3  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint8_4  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  int16_t          &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int16_2  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int16_3  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int16_4  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  uint16_t         &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint16_2 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint16_3 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint16_4 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  int32_t          &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int32_2  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int32_3  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int32_4  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  uint32_t         &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint32_2 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint32_3 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint32_4 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  int64_t          &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int64_2  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int64_3  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::int64_4  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  uint64_t         &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint64_2 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint64_3 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::uint64_4 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  float            &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::float_2  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::float_3  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::float_4  &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  double           &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::double_2 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::double_3 &value) const { return mApiBinaryGroup->get(ix, value); }
bool BinaryGroup::get(const size_t ix,  Octane::double_4 &value) const { return mApiBinaryGroup->get(ix, value); }

bool BinaryGroup::get(const size_t ix, std::string &value) const
{
    const char *tmp = NULL;
    if (!mApiBinaryGroup->get(ix, tmp))
    {
        return false;
    }

    value = tmp;
    mApiBinaryGroup->cleanupString(tmp);
    return true;
}


bool BinaryGroup::getGroup(const size_t ix, BinaryGroup &group) const
{
    Octane::ApiBinaryGroup *apiBinaryGroup = NULL;
    if (!mApiBinaryGroup->getGroup(ix, apiBinaryGroup))
    {
        return false;
    }

    group.mApiBinaryGroup->destroy();
    group.mApiBinaryGroup = apiBinaryGroup;
    return true;
}


bool BinaryGroup::getTable(const size_t ix, BinaryTable &table) const
{
    Octane::ApiBinaryTable *apiBinaryTable = NULL;
    if (!mApiBinaryGroup->getTable(ix, apiBinaryTable))
    {
        return false;
    }

    table.mApiBinaryTable->destroy();
    table.mApiBinaryTable = apiBinaryTable;
    return true;
}

 
void BinaryGroup::add(const int32_t id,  const bool             value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const int8_t           value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int8_2   value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int8_3   value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int8_4   value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const uint8_t          value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint8_2  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint8_3  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint8_4  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const int16_t          value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int16_2  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int16_3  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int16_4  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const uint16_t         value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint16_2 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint16_3 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint16_4 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const int32_t          value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int32_2  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int32_3  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int32_4  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const uint32_t         value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint32_2 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint32_3 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint32_4 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const int64_t          value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int64_2  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int64_3  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::int64_4  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const uint64_t         value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint64_2 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint64_3 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::uint64_4 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const float            value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::float_2  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::float_3  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::float_4  value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const double           value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::double_2 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::double_3 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const Octane::double_4 value) { mApiBinaryGroup->add(id, value); }
void BinaryGroup::add(const int32_t id,  const char*            value) { mApiBinaryGroup->add(id, value); }

void BinaryGroup::addGroup(const int32_t id, const BinaryGroup &group)
{
    mApiBinaryGroup->addGroup(id, *group.mApiBinaryGroup);
}


void BinaryGroup::addTable(const int32_t id, const BinaryTable &table)
{
    mApiBinaryGroup->addTable(id, *table.mApiBinaryTable);
}


void BinaryGroup::dump(
    const uint32_t indent) const
{
    return mApiBinaryGroup->dump(indent);
}


BinaryGroup::BinaryGroup(
    Octane::ApiBinaryGroup *ptr)
:
    mApiBinaryGroup(ptr)
{}
