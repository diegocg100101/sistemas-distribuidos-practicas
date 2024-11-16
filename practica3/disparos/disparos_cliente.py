from __future__ import print_function

import logging

import grpc
import disparos_pb2
import disparos_pb2_grpc


def run():

    with grpc.insecure_channel("localhost:50051") as channel:
        stub = disparos_pb2_grpc.DisparoStub(channel)

        #Obtener centro de diana 
        centro = stub.dimeCentroDianna(disparos_pb2.Vacio())
        centro_diana = centro.distancia

        print(f"El centro de la diana es de {centro_diana:.2f} metros\n")

        while True:

            # Solicitar al usuario los datos para disparar
            usuario = input("Ingresa el nombre del usuario: ")
            velocidad = float(input("Ingresa la velocidad del disparo (en m/s): "))
            angulo = float(input("Ingresa el ángulo del disparo (en grados): "))

            # Crear la solicitud de disparo
            disparo_request = disparos_pb2.InfoDisparo(
                usuario=usuario,
                velocidad=velocidad,
                angulo=angulo
            )

            # Hacer el disparo
            disparo_response = stub.dispararCannon(disparo_request)
            distancia_al_centro = disparo_response.distancia
            print(f"Distancia al centro: {distancia_al_centro:.2f} metros.")

            # Comprobar si el disparo está dentro del rango de acierto
            if distancia_al_centro <= 1:
                print("¡Felicidades! Has acertado al centro de la diana.")
                break

            # Consultar el mejor disparo hasta el momento
            mejor_disparo_response = stub.mejorDisparo(disparos_pb2.Vacio())
            mejor_usuario = mejor_disparo_response.usuario
            print(f"El mejor disparo hasta ahora lo hizo: {mejor_usuario}")
            
        print("Fin del juego. ¡Gracias por participar!")




if __name__ == "__main__":
    logging.basicConfig()
    run()