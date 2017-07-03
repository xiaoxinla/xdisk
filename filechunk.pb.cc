// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: filechunk.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "filechunk.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
class FileChunkDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<FileChunk> {
} _FileChunk_default_instance_;

namespace protobuf_filechunk_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FileChunk, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FileChunk, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FileChunk, chunkid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FileChunk, total_),
  ~0u,
  0,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(FileChunk)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_FileChunk_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "filechunk.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _FileChunk_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _FileChunk_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\017filechunk.proto\"+\n\tFileChunk\022\017\n\007chunki"
      "d\030\001 \003(\t\022\r\n\005total\030\002 \002(\005"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 62);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "filechunk.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_filechunk_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int FileChunk::kChunkidFieldNumber;
const int FileChunk::kTotalFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

FileChunk::FileChunk()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_filechunk_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:FileChunk)
}
FileChunk::FileChunk(const FileChunk& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      chunkid_(from.chunkid_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  total_ = from.total_;
  // @@protoc_insertion_point(copy_constructor:FileChunk)
}

void FileChunk::SharedCtor() {
  _cached_size_ = 0;
  total_ = 0;
}

FileChunk::~FileChunk() {
  // @@protoc_insertion_point(destructor:FileChunk)
  SharedDtor();
}

void FileChunk::SharedDtor() {
}

void FileChunk::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FileChunk::descriptor() {
  protobuf_filechunk_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_filechunk_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const FileChunk& FileChunk::default_instance() {
  protobuf_filechunk_2eproto::InitDefaults();
  return *internal_default_instance();
}

FileChunk* FileChunk::New(::google::protobuf::Arena* arena) const {
  FileChunk* n = new FileChunk;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void FileChunk::Clear() {
// @@protoc_insertion_point(message_clear_start:FileChunk)
  chunkid_.Clear();
  total_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool FileChunk::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:FileChunk)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated string chunkid = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_chunkid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->chunkid(this->chunkid_size() - 1).data(),
            this->chunkid(this->chunkid_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "FileChunk.chunkid");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 total = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u)) {
          set_has_total();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &total_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:FileChunk)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:FileChunk)
  return false;
#undef DO_
}

void FileChunk::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:FileChunk)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated string chunkid = 1;
  for (int i = 0, n = this->chunkid_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->chunkid(i).data(), this->chunkid(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "FileChunk.chunkid");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->chunkid(i), output);
  }

  cached_has_bits = _has_bits_[0];
  // required int32 total = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->total(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:FileChunk)
}

::google::protobuf::uint8* FileChunk::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:FileChunk)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated string chunkid = 1;
  for (int i = 0, n = this->chunkid_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->chunkid(i).data(), this->chunkid(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "FileChunk.chunkid");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(1, this->chunkid(i), target);
  }

  cached_has_bits = _has_bits_[0];
  // required int32 total = 2;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->total(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:FileChunk)
  return target;
}

size_t FileChunk::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:FileChunk)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // required int32 total = 2;
  if (has_total()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->total());
  }
  // repeated string chunkid = 1;
  total_size += 1 *
      ::google::protobuf::internal::FromIntSize(this->chunkid_size());
  for (int i = 0, n = this->chunkid_size(); i < n; i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->chunkid(i));
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FileChunk::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:FileChunk)
  GOOGLE_DCHECK_NE(&from, this);
  const FileChunk* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const FileChunk>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:FileChunk)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:FileChunk)
    MergeFrom(*source);
  }
}

void FileChunk::MergeFrom(const FileChunk& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:FileChunk)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  chunkid_.MergeFrom(from.chunkid_);
  if (from.has_total()) {
    set_total(from.total());
  }
}

void FileChunk::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:FileChunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FileChunk::CopyFrom(const FileChunk& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:FileChunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FileChunk::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  return true;
}

void FileChunk::Swap(FileChunk* other) {
  if (other == this) return;
  InternalSwap(other);
}
void FileChunk::InternalSwap(FileChunk* other) {
  chunkid_.InternalSwap(&other->chunkid_);
  std::swap(total_, other->total_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata FileChunk::GetMetadata() const {
  protobuf_filechunk_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_filechunk_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// FileChunk

// repeated string chunkid = 1;
int FileChunk::chunkid_size() const {
  return chunkid_.size();
}
void FileChunk::clear_chunkid() {
  chunkid_.Clear();
}
const ::std::string& FileChunk::chunkid(int index) const {
  // @@protoc_insertion_point(field_get:FileChunk.chunkid)
  return chunkid_.Get(index);
}
::std::string* FileChunk::mutable_chunkid(int index) {
  // @@protoc_insertion_point(field_mutable:FileChunk.chunkid)
  return chunkid_.Mutable(index);
}
void FileChunk::set_chunkid(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:FileChunk.chunkid)
  chunkid_.Mutable(index)->assign(value);
}
#if LANG_CXX11
void FileChunk::set_chunkid(int index, ::std::string&& value) {
  // @@protoc_insertion_point(field_set:FileChunk.chunkid)
  chunkid_.Mutable(index)->assign(std::move(value));
}
#endif
void FileChunk::set_chunkid(int index, const char* value) {
  GOOGLE_DCHECK(value != NULL);
  chunkid_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:FileChunk.chunkid)
}
void FileChunk::set_chunkid(int index, const char* value, size_t size) {
  chunkid_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:FileChunk.chunkid)
}
::std::string* FileChunk::add_chunkid() {
  // @@protoc_insertion_point(field_add_mutable:FileChunk.chunkid)
  return chunkid_.Add();
}
void FileChunk::add_chunkid(const ::std::string& value) {
  chunkid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:FileChunk.chunkid)
}
#if LANG_CXX11
void FileChunk::add_chunkid(::std::string&& value) {
  chunkid_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:FileChunk.chunkid)
}
#endif
void FileChunk::add_chunkid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  chunkid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:FileChunk.chunkid)
}
void FileChunk::add_chunkid(const char* value, size_t size) {
  chunkid_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:FileChunk.chunkid)
}
const ::google::protobuf::RepeatedPtrField< ::std::string>&
FileChunk::chunkid() const {
  // @@protoc_insertion_point(field_list:FileChunk.chunkid)
  return chunkid_;
}
::google::protobuf::RepeatedPtrField< ::std::string>*
FileChunk::mutable_chunkid() {
  // @@protoc_insertion_point(field_mutable_list:FileChunk.chunkid)
  return &chunkid_;
}

// required int32 total = 2;
bool FileChunk::has_total() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void FileChunk::set_has_total() {
  _has_bits_[0] |= 0x00000001u;
}
void FileChunk::clear_has_total() {
  _has_bits_[0] &= ~0x00000001u;
}
void FileChunk::clear_total() {
  total_ = 0;
  clear_has_total();
}
::google::protobuf::int32 FileChunk::total() const {
  // @@protoc_insertion_point(field_get:FileChunk.total)
  return total_;
}
void FileChunk::set_total(::google::protobuf::int32 value) {
  set_has_total();
  total_ = value;
  // @@protoc_insertion_point(field_set:FileChunk.total)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
