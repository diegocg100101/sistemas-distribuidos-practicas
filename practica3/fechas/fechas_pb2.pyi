from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Fecha(_message.Message):
    __slots__ = ("dia", "mes", "anio")
    DIA_FIELD_NUMBER: _ClassVar[int]
    MES_FIELD_NUMBER: _ClassVar[int]
    ANIO_FIELD_NUMBER: _ClassVar[int]
    dia: int
    mes: int
    anio: int
    def __init__(self, dia: _Optional[int] = ..., mes: _Optional[int] = ..., anio: _Optional[int] = ...) -> None: ...

class FechaNumeroDias(_message.Message):
    __slots__ = ("fecha", "numero")
    FECHA_FIELD_NUMBER: _ClassVar[int]
    NUMERO_FIELD_NUMBER: _ClassVar[int]
    fecha: Fecha
    numero: int
    def __init__(self, fecha: _Optional[_Union[Fecha, _Mapping]] = ..., numero: _Optional[int] = ...) -> None: ...
