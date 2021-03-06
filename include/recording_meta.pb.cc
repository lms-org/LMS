// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: recording_meta.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "recording_meta.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace lms {

namespace {

const ::google::protobuf::Descriptor* MetaFile_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MetaFile_reflection_ = NULL;
const ::google::protobuf::Descriptor* MetaFile_Channel_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MetaFile_Channel_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_recording_5fmeta_2eproto() {
  protobuf_AddDesc_recording_5fmeta_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "recording_meta.proto");
  GOOGLE_CHECK(file != NULL);
  MetaFile_descriptor_ = file->message_type(0);
  static const int MetaFile_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile, channels_),
  };
  MetaFile_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MetaFile_descriptor_,
      MetaFile::default_instance_,
      MetaFile_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MetaFile));
  MetaFile_Channel_descriptor_ = MetaFile_descriptor_->nested_type(0);
  static const int MetaFile_Channel_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile_Channel, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile_Channel, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile_Channel, writing_modules_),
  };
  MetaFile_Channel_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MetaFile_Channel_descriptor_,
      MetaFile_Channel::default_instance_,
      MetaFile_Channel_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile_Channel, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MetaFile_Channel, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MetaFile_Channel));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_recording_5fmeta_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MetaFile_descriptor_, &MetaFile::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MetaFile_Channel_descriptor_, &MetaFile_Channel::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_recording_5fmeta_2eproto() {
  delete MetaFile::default_instance_;
  delete MetaFile_reflection_;
  delete MetaFile_Channel::default_instance_;
  delete MetaFile_Channel_reflection_;
}

void protobuf_AddDesc_recording_5fmeta_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024recording_meta.proto\022\003lms\"s\n\010MetaFile\022"
    "\'\n\010channels\030\001 \003(\0132\025.lms.MetaFile.Channel"
    "\032>\n\007Channel\022\014\n\004name\030\001 \001(\t\022\014\n\004type\030\002 \001(\t\022"
    "\027\n\017writing_modules\030\003 \003(\t", 144);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "recording_meta.proto", &protobuf_RegisterTypes);
  MetaFile::default_instance_ = new MetaFile();
  MetaFile_Channel::default_instance_ = new MetaFile_Channel();
  MetaFile::default_instance_->InitAsDefaultInstance();
  MetaFile_Channel::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_recording_5fmeta_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_recording_5fmeta_2eproto {
  StaticDescriptorInitializer_recording_5fmeta_2eproto() {
    protobuf_AddDesc_recording_5fmeta_2eproto();
  }
} static_descriptor_initializer_recording_5fmeta_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MetaFile_Channel::kNameFieldNumber;
const int MetaFile_Channel::kTypeFieldNumber;
const int MetaFile_Channel::kWritingModulesFieldNumber;
#endif  // !_MSC_VER

MetaFile_Channel::MetaFile_Channel()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:lms.MetaFile.Channel)
}

void MetaFile_Channel::InitAsDefaultInstance() {
}

MetaFile_Channel::MetaFile_Channel(const MetaFile_Channel& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:lms.MetaFile.Channel)
}

void MetaFile_Channel::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  type_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MetaFile_Channel::~MetaFile_Channel() {
  // @@protoc_insertion_point(destructor:lms.MetaFile.Channel)
  SharedDtor();
}

void MetaFile_Channel::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (type_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete type_;
  }
  if (this != default_instance_) {
  }
}

void MetaFile_Channel::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MetaFile_Channel::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MetaFile_Channel_descriptor_;
}

const MetaFile_Channel& MetaFile_Channel::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_recording_5fmeta_2eproto();
  return *default_instance_;
}

MetaFile_Channel* MetaFile_Channel::default_instance_ = NULL;

MetaFile_Channel* MetaFile_Channel::New() const {
  return new MetaFile_Channel;
}

void MetaFile_Channel::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
    if (has_type()) {
      if (type_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        type_->clear();
      }
    }
  }
  writing_modules_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MetaFile_Channel::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:lms.MetaFile.Channel)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_type;
        break;
      }

      // optional string type = 2;
      case 2: {
        if (tag == 18) {
         parse_type:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->type().data(), this->type().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "type");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_writing_modules;
        break;
      }

      // repeated string writing_modules = 3;
      case 3: {
        if (tag == 26) {
         parse_writing_modules:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_writing_modules()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->writing_modules(this->writing_modules_size() - 1).data(),
            this->writing_modules(this->writing_modules_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "writing_modules");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_writing_modules;
        if (input->ExpectAtEnd()) goto success;
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
  // @@protoc_insertion_point(parse_success:lms.MetaFile.Channel)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:lms.MetaFile.Channel)
  return false;
#undef DO_
}

void MetaFile_Channel::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:lms.MetaFile.Channel)
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // optional string type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "type");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->type(), output);
  }

  // repeated string writing_modules = 3;
  for (int i = 0; i < this->writing_modules_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
    this->writing_modules(i).data(), this->writing_modules(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE,
    "writing_modules");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->writing_modules(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:lms.MetaFile.Channel)
}

::google::protobuf::uint8* MetaFile_Channel::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:lms.MetaFile.Channel)
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // optional string type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "type");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->type(), target);
  }

  // repeated string writing_modules = 3;
  for (int i = 0; i < this->writing_modules_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->writing_modules(i).data(), this->writing_modules(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "writing_modules");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(3, this->writing_modules(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lms.MetaFile.Channel)
  return target;
}

int MetaFile_Channel::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional string type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->type());
    }

  }
  // repeated string writing_modules = 3;
  total_size += 1 * this->writing_modules_size();
  for (int i = 0; i < this->writing_modules_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->writing_modules(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MetaFile_Channel::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MetaFile_Channel* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MetaFile_Channel*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MetaFile_Channel::MergeFrom(const MetaFile_Channel& from) {
  GOOGLE_CHECK_NE(&from, this);
  writing_modules_.MergeFrom(from.writing_modules_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MetaFile_Channel::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MetaFile_Channel::CopyFrom(const MetaFile_Channel& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MetaFile_Channel::IsInitialized() const {

  return true;
}

void MetaFile_Channel::Swap(MetaFile_Channel* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(type_, other->type_);
    writing_modules_.Swap(&other->writing_modules_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MetaFile_Channel::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MetaFile_Channel_descriptor_;
  metadata.reflection = MetaFile_Channel_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int MetaFile::kChannelsFieldNumber;
#endif  // !_MSC_VER

MetaFile::MetaFile()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:lms.MetaFile)
}

void MetaFile::InitAsDefaultInstance() {
}

MetaFile::MetaFile(const MetaFile& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:lms.MetaFile)
}

void MetaFile::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MetaFile::~MetaFile() {
  // @@protoc_insertion_point(destructor:lms.MetaFile)
  SharedDtor();
}

void MetaFile::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MetaFile::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MetaFile::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MetaFile_descriptor_;
}

const MetaFile& MetaFile::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_recording_5fmeta_2eproto();
  return *default_instance_;
}

MetaFile* MetaFile::default_instance_ = NULL;

MetaFile* MetaFile::New() const {
  return new MetaFile;
}

void MetaFile::Clear() {
  channels_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MetaFile::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:lms.MetaFile)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .lms.MetaFile.Channel channels = 1;
      case 1: {
        if (tag == 10) {
         parse_channels:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_channels()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_channels;
        if (input->ExpectAtEnd()) goto success;
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
  // @@protoc_insertion_point(parse_success:lms.MetaFile)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:lms.MetaFile)
  return false;
#undef DO_
}

void MetaFile::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:lms.MetaFile)
  // repeated .lms.MetaFile.Channel channels = 1;
  for (int i = 0; i < this->channels_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->channels(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:lms.MetaFile)
}

::google::protobuf::uint8* MetaFile::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:lms.MetaFile)
  // repeated .lms.MetaFile.Channel channels = 1;
  for (int i = 0; i < this->channels_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->channels(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lms.MetaFile)
  return target;
}

int MetaFile::ByteSize() const {
  int total_size = 0;

  // repeated .lms.MetaFile.Channel channels = 1;
  total_size += 1 * this->channels_size();
  for (int i = 0; i < this->channels_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->channels(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MetaFile::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MetaFile* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MetaFile*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MetaFile::MergeFrom(const MetaFile& from) {
  GOOGLE_CHECK_NE(&from, this);
  channels_.MergeFrom(from.channels_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MetaFile::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MetaFile::CopyFrom(const MetaFile& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MetaFile::IsInitialized() const {

  return true;
}

void MetaFile::Swap(MetaFile* other) {
  if (other != this) {
    channels_.Swap(&other->channels_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MetaFile::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MetaFile_descriptor_;
  metadata.reflection = MetaFile_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace lms

// @@protoc_insertion_point(global_scope)
