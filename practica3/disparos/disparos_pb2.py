# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: disparos.proto
# Protobuf Python Version: 5.28.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import runtime_version as _runtime_version
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
_runtime_version.ValidateProtobufRuntimeVersion(
    _runtime_version.Domain.PUBLIC,
    5,
    28,
    1,
    '',
    'disparos.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0e\x64isparos.proto\x12\x08\x64isparos\"\x07\n\x05Vacio\"\x1e\n\tDistancia\x12\x11\n\tdistancia\x18\x01 \x01(\x02\"A\n\x0bInfoDisparo\x12\x0f\n\x07usuario\x18\x01 \x01(\t\x12\x0e\n\x06\x61ngulo\x18\x02 \x01(\x02\x12\x11\n\tvelocidad\x18\x03 \x01(\x02\"\x1a\n\x07Usuario\x12\x0f\n\x07usuario\x18\x02 \x01(\t2\xbb\x01\n\x07\x44isparo\x12:\n\x10\x64imeCentroDianna\x12\x0f.disparos.Vacio\x1a\x13.disparos.Distancia\"\x00\x12>\n\x0e\x64ispararCannon\x12\x15.disparos.InfoDisparo\x1a\x13.disparos.Distancia\"\x00\x12\x34\n\x0cmejorDisparo\x12\x0f.disparos.Vacio\x1a\x11.disparos.Usuario\"\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'disparos_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_VACIO']._serialized_start=28
  _globals['_VACIO']._serialized_end=35
  _globals['_DISTANCIA']._serialized_start=37
  _globals['_DISTANCIA']._serialized_end=67
  _globals['_INFODISPARO']._serialized_start=69
  _globals['_INFODISPARO']._serialized_end=134
  _globals['_USUARIO']._serialized_start=136
  _globals['_USUARIO']._serialized_end=162
  _globals['_DISPARO']._serialized_start=165
  _globals['_DISPARO']._serialized_end=352
# @@protoc_insertion_point(module_scope)