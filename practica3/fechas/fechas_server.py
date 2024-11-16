from concurrent import futures
import logging

import grpc
import fechas_pb2
import fechas_pb2_grpc
import datetime


class Fechas(fechas_pb2_grpc.FechasServicer):    
    def siguienteFecha(self, request, context):
        dia = request.dia
        mes = request.mes
        anio = request.anio
        
        fecha = datetime.date(anio, mes, dia)
        
        siguienteDia = fecha + datetime.timedelta(days=1)
         
        return fechas_pb2.Fecha(dia=siguienteDia.day, mes=siguienteDia.month, anio=siguienteDia.year)

    def sumaDiasFecha(self, request, context):
        dia = request.fecha.dia
        mes = request.fecha.mes
        anio = request.fecha.anio
        
        fecha = datetime.date(anio, mes, dia)
        
        sumaDias = fecha + datetime.timedelta(days=request.numero)
        
        return fechas_pb2.Fecha(dia=sumaDias.day, mes=sumaDias.month, anio=sumaDias.year)

def serve():
    port = "50051"
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    fechas_pb2_grpc.add_FechasServicer_to_server(Fechas(), server)
    server.add_insecure_port("[::]:" + port)
    server.start()
    print("Server started, listening on " + port)
    server.wait_for_termination()


if __name__ == "__main__":
    logging.basicConfig()
    serve()
