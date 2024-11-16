from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class Vacio(_message.Message):
    __slots__ = ()
    def __init__(self) -> None: ...

class Distancia(_message.Message):
    __slots__ = ("distancia",)
    DISTANCIA_FIELD_NUMBER: _ClassVar[int]
    distancia: float
    def __init__(self, distancia: _Optional[float] = ...) -> None: ...

class InfoDisparo(_message.Message):
    __slots__ = ("usuario", "angulo", "velocidad")
    USUARIO_FIELD_NUMBER: _ClassVar[int]
    ANGULO_FIELD_NUMBER: _ClassVar[int]
    VELOCIDAD_FIELD_NUMBER: _ClassVar[int]
    usuario: str
    angulo: float
    velocidad: float
    def __init__(self, usuario: _Optional[str] = ..., angulo: _Optional[float] = ..., velocidad: _Optional[float] = ...) -> None: ...

class Usuario(_message.Message):
    __slots__ = ("usuario",)
    USUARIO_FIELD_NUMBER: _ClassVar[int]
    usuario: str
    def __init__(self, usuario: _Optional[str] = ...) -> None: ...
