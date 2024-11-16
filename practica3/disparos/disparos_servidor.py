from concurrent import futures
import logging

import grpc
import disparos_pb2
import disparos_pb2_grpc
import datetime
import numpy as np

class Disparo(disparos_pb2_grpc.DisparoServicer):
    def __init__(self):
        # Variables globales para almacenar el mejor disparo
        self.mejor_disparo = np.inf
        self.mejor_usuario = ""

    def calculaDistancia(self, velocidad, angulo):
        g = 9.81
        theta = angulo * np.pi / 180
        distancia = velocidad * velocidad * np.sin(2 * theta) / g
        return distancia
    
    def dimeCentroDianna(self, request, context):
        # Este método no necesita datos del cliente
        return disparos_pb2.Distancia(distancia=137)  # Retorna el centro fijo
    
    def dispararCannon(self, request, context):
        centro = 137  # Posición fija del centro

        # Accede a los valores enviados en el request
        angulo = request.angulo % 90  # Limita el ángulo a 90 grados
        velocidad = request.velocidad
        usuario = request.usuario

        # Calcula la posición de la bala después de lanzar
        bala = self.calculaDistancia(velocidad, angulo)
        
        # Calcula la distancia entre la bala y el centro
        distancia = abs(centro - bala)

        # Verifica si es el mejor disparo
        if distancia < self.mejor_disparo:
            self.mejor_disparo = distancia
            self.mejor_usuario = usuario

        print(f"Disparo de {usuario}: Bala cayó a {bala:.2f}m, distancia al centro: {distancia:.2f}m")
        
        return disparos_pb2.Distancia(distancia=distancia)
    
    def mejorDisparo(self, request, context):
        # Retorna el mejor usuario almacenado
        return disparos_pb2.Usuario(usuario=self.mejor_usuario)
    

def serve():
    port = "50051"
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    disparos_pb2_grpc.add_DisparoServicer_to_server(Disparo(), server)
    server.add_insecure_port("[::]:" + port)
    server.start()
    print("Server started, listening on " + port)
    server.wait_for_termination()


if __name__ == "__main__":
    logging.basicConfig()
    serve()