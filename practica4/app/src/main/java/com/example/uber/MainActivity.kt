package com.example.uber

import android.content.Context
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.OutlinedButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.focus.FocusRequester
import androidx.compose.ui.focus.focusRequester
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.uber.ui.theme.UberTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            UberTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    EnviarPosicion(
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun EnviarPosicion(modifier: Modifier = Modifier) {
    val context = LocalContext.current
    val focusY = remember {
        FocusRequester()
    }

    val focusEnviar = remember {
        FocusRequester()
    }

    var posX by remember {
        mutableStateOf("")
    }

    var posY by remember {
        mutableStateOf("")
    }

    Box (
        Modifier
            .fillMaxSize()
            .padding(16.dp),
        contentAlignment = Alignment.Center) {
        Column (horizontalAlignment = Alignment.CenterHorizontally){
            Text(text = "Uber")
            OutlinedTextField(value = posX,
                onValueChange = {posX = it},
                label = { Text(text = "X")},
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Number,
                    imeAction = ImeAction.Next,
                    ),
                keyboardActions = KeyboardActions(
                    onNext = {focusY.requestFocus()}
                )
            )

            Spacer(modifier = Modifier.size(30.dp))

            OutlinedTextField(value = posY,
                onValueChange = {posY = it},
                label = { Text(text = "Y")},
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Number,
                    imeAction = ImeAction.Done
                ),
                keyboardActions = KeyboardActions(
                    onDone = {focusEnviar.requestFocus()}
                ),
                modifier = Modifier.focusRequester(focusY)
            )

            Spacer(modifier = Modifier.size(30.dp))

            OutlinedButton(
                onClick = { solicitarViaje(context, posX, posY)},
                modifier = Modifier.focusRequester(focusEnviar)
            ) {
                Text(text = "Enviar")
            }
        }
    }
}

fun solicitarViaje(context : Context, x : String, y : String) {
    if(x.isEmpty() || y.isEmpty()) {
        Toast.makeText(context, "Ingresa los valores de X y Y", Toast.LENGTH_SHORT).show()
    } else {
        // Hacer la conexión con el servidor
        val client = UberClient("192.168.100.21", 50051)
        try {
            val response = client.solicitarViaje(x.toFloat(), y.toFloat())

        } catch (e : Exception) {
            println(e)
            Toast.makeText(context, "No se pudo conectar", Toast.LENGTH_SHORT).show()
        }
    }
}



@Preview(showBackground = true)
@Composable
fun UberPreview() {
    UberTheme {
        EnviarPosicion()
    }
}