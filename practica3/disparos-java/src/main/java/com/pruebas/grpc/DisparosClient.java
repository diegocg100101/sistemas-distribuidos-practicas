package com.pruebas.grpc;

import disparos.DisparoGrpc;
import disparos.Disparos;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import java.util.Scanner;

/**
 * @author diego
 */
public class DisparosClient {
    public static void main(String[] args) {
        ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 50051)
                .usePlaintext()
                .build();

        DisparoGrpc.DisparoBlockingStub stub = DisparoGrpc.newBlockingStub(channel);

        // Solicita el centro de la dianna
        Disparos.Distancia centro = stub.dimeCentroDianna(Disparos.Vacio.newBuilder().build());
        System.out.printf("El centro de la diana es de %.2f metros\n", centro.getDistancia());

        Scanner scanner = new Scanner(System.in);

        // Mantiene el servicio abierto
        while (true) {
            System.out.print("Ingresa el nombre del usuario: ");
            String usuario = scanner.nextLine();

            System.out.print("Ingresa la velocidad del disparo (en m/s): ");
            float velocidad = Float.parseFloat(scanner.nextLine());

            System.out.print("Ingresa el ángulo del disparo (en grados): ");
            float angulo = Float.parseFloat(scanner.nextLine());

            // Crea la petición con los valores ingresados por el usuario
            Disparos.InfoDisparo disparoRequest = Disparos.InfoDisparo.newBuilder()
                    .setUsuario(usuario)
                    .setVelocidad(velocidad)
                    .setAngulo(angulo)
                    .build();

            // Manda la petición para disparar
            Disparos.Distancia disparoResponse = stub.dispararCannon(disparoRequest);
            float distanciaAlCentro = disparoResponse.getDistancia();

            // Verifica la distancia de la bala al centro
            if (distanciaAlCentro < 0) {
                System.out.printf("La bala cayó %.2fm después del centro\n", Math.abs(distanciaAlCentro));
            } else {
                System.out.printf("La bala cayó %.2fm antes del centro\n", distanciaAlCentro);
            }

            if (Math.abs(distanciaAlCentro) < 1) {
                System.out.println("\n¡Felicidades! Has acertado al centro de la diana.\n");
            }

            Disparos.Usuario mejorDisparoResponse = stub.mejorDisparo(Disparos.Vacio.newBuilder().build());
            System.out.printf("\nEl mejor disparo hasta ahora lo hizo: %s\n", mejorDisparoResponse.getUsuario());
        }
    }
}
