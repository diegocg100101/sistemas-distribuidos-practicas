package com.example.uber

import io.grpc.ManagedChannel
import io.grpc.ManagedChannelBuilder
import uber.UberGrpc
import uber.UberOuterClass
import uber.UberOuterClass.Posicion

class UberClient(private val serverUrl: String, private val port : Int) {
    private val channel: ManagedChannel = ManagedChannelBuilder
        .forAddress(serverUrl, port)
        .usePlaintext()
        .build()

    private val stub : UberGrpc.UberBlockingStub = UberGrpc.newBlockingStub(channel)

    fun solicitarViaje(x : Float, y : Float) : UberOuterClass.infoAuto? {
        val posicion = Posicion.newBuilder().setX(x).setY(y).build()
        return stub.solicitarViaje(posicion)
    }

//    fun terminarViaje() {
//        return stub.terminarViaje()
//    }


    fun shutdown() {
        channel.shutdown()
    }
}