// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: filechunk.proto

#ifndef PROTOBUF_filechunk_2eproto__INCLUDED
#define PROTOBUF_filechunk_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
class FileChunk;
class FileChunkDefaultTypeInternal;
extern FileChunkDefaultTypeInternal _FileChunk_default_instance_;

namespace protobuf_filechunk_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_filechunk_2eproto

// ===================================================================

class FileChunk : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:FileChunk) */ {
 public:
  FileChunk();
  virtual ~FileChunk();

  FileChunk(const FileChunk& from);

  inline FileChunk& operator=(const FileChunk& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FileChunk& default_instance();

  static inline const FileChunk* internal_default_instance() {
    return reinterpret_cast<const FileChunk*>(
               &_FileChunk_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(FileChunk* other);

  // implements Message ----------------------------------------------

  inline FileChunk* New() const PROTOBUF_FINAL { return New(NULL); }

  FileChunk* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const FileChunk& from);
  void MergeFrom(const FileChunk& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(FileChunk* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string chunkid = 1;
  int chunkid_size() const;
  void clear_chunkid();
  static const int kChunkidFieldNumber = 1;
  const ::std::string& chunkid(int index) const;
  ::std::string* mutable_chunkid(int index);
  void set_chunkid(int index, const ::std::string& value);
  #if LANG_CXX11
  void set_chunkid(int index, ::std::string&& value);
  #endif
  void set_chunkid(int index, const char* value);
  void set_chunkid(int index, const char* value, size_t size);
  ::std::string* add_chunkid();
  void add_chunkid(const ::std::string& value);
  #if LANG_CXX11
  void add_chunkid(::std::string&& value);
  #endif
  void add_chunkid(const char* value);
  void add_chunkid(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& chunkid() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_chunkid();

  // required int32 total = 2;
  bool has_total() const;
  void clear_total();
  static const int kTotalFieldNumber = 2;
  ::google::protobuf::int32 total() const;
  void set_total(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:FileChunk)
 private:
  void set_has_total();
  void clear_has_total();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> chunkid_;
  ::google::protobuf::int32 total_;
  friend struct protobuf_filechunk_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// FileChunk

// repeated string chunkid = 1;
inline int FileChunk::chunkid_size() const {
  return chunkid_.size();
}
inline void FileChunk::clear_chunkid() {
  chunkid_.Clear();
}
inline const ::std::string& FileChunk::chunkid(int index) const {
  // @@protoc_insertion_point(field_get:FileChunk.chunkid)
  return chunkid_.Get(index);
}
inline ::std::string* FileChunk::mutable_chunkid(int index) {
  // @@protoc_insertion_point(field_mutable:FileChunk.chunkid)
  return chunkid_.Mutable(index);
}
inline void FileChunk::set_chunkid(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:FileChunk.chunkid)
  chunkid_.Mutable(index)->assign(value);
}
#if LANG_CXX11
inline void FileChunk::set_chunkid(int index, ::std::string&& value) {
  // @@protoc_insertion_point(field_set:FileChunk.chunkid)
  chunkid_.Mutable(index)->assign(std::move(value));
}
#endif
inline void FileChunk::set_chunkid(int index, const char* value) {
  GOOGLE_DCHECK(value != NULL);
  chunkid_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:FileChunk.chunkid)
}
inline void FileChunk::set_chunkid(int index, const char* value, size_t size) {
  chunkid_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:FileChunk.chunkid)
}
inline ::std::string* FileChunk::add_chunkid() {
  // @@protoc_insertion_point(field_add_mutable:FileChunk.chunkid)
  return chunkid_.Add();
}
inline void FileChunk::add_chunkid(const ::std::string& value) {
  chunkid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:FileChunk.chunkid)
}
#if LANG_CXX11
inline void FileChunk::add_chunkid(::std::string&& value) {
  chunkid_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:FileChunk.chunkid)
}
#endif
inline void FileChunk::add_chunkid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  chunkid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:FileChunk.chunkid)
}
inline void FileChunk::add_chunkid(const char* value, size_t size) {
  chunkid_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:FileChunk.chunkid)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
FileChunk::chunkid() const {
  // @@protoc_insertion_point(field_list:FileChunk.chunkid)
  return chunkid_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
FileChunk::mutable_chunkid() {
  // @@protoc_insertion_point(field_mutable_list:FileChunk.chunkid)
  return &chunkid_;
}

// required int32 total = 2;
inline bool FileChunk::has_total() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FileChunk::set_has_total() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FileChunk::clear_has_total() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FileChunk::clear_total() {
  total_ = 0;
  clear_has_total();
}
inline ::google::protobuf::int32 FileChunk::total() const {
  // @@protoc_insertion_point(field_get:FileChunk.total)
  return total_;
}
inline void FileChunk::set_total(::google::protobuf::int32 value) {
  set_has_total();
  total_ = value;
  // @@protoc_insertion_point(field_set:FileChunk.total)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_filechunk_2eproto__INCLUDED
