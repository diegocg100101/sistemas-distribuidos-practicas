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

            if (distancia_al_centro < 0):
                print(f"La bala cayó {abs(distancia_al_centro):.2f}m después del centro")
            else:
                print(f"La bala cayó {abs(distancia_al_centro):.2f}m antes del centro") 

            # Comprobar si el disparo está dentro del rango de acierto
            if abs(distancia_al_centro) < 1:
                print("¡Felicidades! Has acertado al centro de la diana.\n")

            # Consultar el mejor disparo hasta el momento
            mejor_disparo_response = stub.mejorDisparo(disparos_pb2.Vacio())
            print(f"El mejor disparo hasta ahora lo hizo: {mejor_disparo_response.usuario}\n")


if __name__ == "__main__":
    logging.basicConfig()
    run()