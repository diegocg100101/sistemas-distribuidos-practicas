from __future__ import print_function

import logging

import grpc
import fechas_pb2
import fechas_pb2_grpc


def run():
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = fechas_pb2_grpc.FechasStub(channel)
        fecha = fechas_pb2.Fecha(dia=15, mes=11, anio=2024)
        numero = 50
        request = fechas_pb2.FechaNumeroDias(fecha=fecha, numero=numero)
        response = stub.sumaDiasFecha(request)
    print(f"Fecha sumando {numero} días: {response.dia}/{response.mes}/{response.anio}")


if __name__ == "__main__":
    logging.basicConfig()
    run()
